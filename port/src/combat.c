#include "dw4/combat.h"
#include "dw4/hitbox.h"
#include "dw4/playerstats.h"
#include "dw4/fightstatus.h"
#include "dw4/fightstatus_e2p.h"
#include "dw4/fightmagic.h"
#include "dw4/magicapply.h"
#include "dw4/buffapply.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
struct hit_source;
struct dw4_combat {
    dw4_model_fight fight_table;   /* the contacts a hit leaves for the next frame keep a pointer to it, so it outlives the emit call (ASan: stack-use-after-return in dng102b3) */
    dw4_playerrecords *records;const dw4_databases *databases;dw4_dbtable enemy,eneatk;dw4_random *rng;dw4_controllers *models;
    dw4_scriptengine *scripts;uint64_t scope;dw4_script_model player_state[4];char player_name[4][16];int player_bound[4];
    dw4_combat_stats stats;
    struct status_host {struct dw4_combat *combat;int32_t slot;} host[4];   /* the player records behind each player model's status lists */
    dw4_modelctrl *players[4];                 /* borrowed player models of the current tick (support area queries, buff delivery, poison cure) */
    int downed[4];float downed_pos[4][3];      /* PLAYER2 capsules (Raise targets): created by dw4_combat_ko_tick, or by dw4_combat_set_downed in tests */
    unsigned capsule_age[4],ko_ticks[4];int capsule_near[4],armed[4],gameover_due;   /* capsule ONE counter / ticks since the KO / SQ_SWON state / HP seen above 0 / end chunk already due */
    dw4_combat_hud_fn hud;void *hud_user;
    dw4_combat_popup_fn popup;void *popup_user;
    struct hit_source *sources;int binding_failed;int64_t world_ns; /* sampled session service clock */
    char error[160];
};
/* Callback resources, not gameplay state. Either owner can close first. */
struct hit_source {dw4_combat *owner;dw4_modelctrl *model;int player,slot;size_t index;struct hit_source *next;};
static int source_emit(void *,dw4_modelctrl *,const dw4_modelctrl_hitbox *,const float[16],int64_t);
static void source_release(void *u)
{
    struct hit_source *s=u;dw4_combat *c=s->owner;
    if(s->player){
        if(c->players[s->slot]==s->model)c->players[s->slot]=NULL;
        dw4_modelctrl_status_player(s->model,NULL);
        if(c->player_bound[s->slot]){dw4_modelctrl_script(s->model,NULL,0,NULL);c->player_bound[s->slot]=0;}
    }
    struct hit_source **p=&c->sources;while(*p && *p!=s)p=&(*p)->next;
    if(*p)*p=s->next;
    free(s);
}
static int source_bind(dw4_combat *c,dw4_modelctrl *model,int player,int slot,size_t index)
{
    for(struct hit_source *s=c->sources;s;s=s->next)if(s->model==model){
        if(s->player==player && s->slot==slot)return 0;
        snprintf(c->error,sizeof c->error,"combat model bound to two source slots");return -1;}
    struct hit_source *s=calloc(1,sizeof *s);if(!s){snprintf(c->error,sizeof c->error,"combat hit-source allocation failed");return -1;}
    *s=(struct hit_source){c,model,player,slot,index,c->sources};c->sources=s;
    dw4_modelctrl_hit_sink(model,source_emit,s,source_release);return 0;
}
static dw4_fight_ctx context(dw4_combat *c,int32_t shooter)
{return (dw4_fight_ctx){dw4_playerrecords_get(c->records,"GETPLAYER",shooter),c->enemy,c->rng,dw4_databases_table(c->databases,"pcTech")};}
/* The receiver's active _downDataList entries the P2E rules read: [3] lowers its evasion, [5] its defense (zero without a status). */
static dw4_fight_down target_down(const dw4_status *t)
{return (dw4_fight_down){dw4_status_down(t,DW4_DOWN_EVASION),dw4_status_down(t,DW4_DOWN_DEFENSE)};}
static int is_hit(void *u,int32_t shooter,int32_t row,int32_t attack,const dw4_status *target,int *hit)
{dw4_combat *c=u;dw4_fight_ctx x=context(c,shooter);return dw4_fight_p2e_is_hit(&x,row,attack,target_down(target),hit);}
static int is_crit(void *u,int32_t shooter,int32_t row,int32_t attack,int *crit)
{dw4_combat *c=u;dw4_fight_ctx x=context(c,shooter);return dw4_fight_p2e_is_critical(&x,row,attack,crit);}
static int damage(void *u,int32_t shooter,int32_t row,int32_t attack,int crit,const dw4_status *target,int32_t out[3])
{
    dw4_combat *c=u;dw4_fight_ctx x=context(c,shooter);dw4_fight_damage d;
    if(dw4_fight_p2e_damage(&x,row,attack,crit,target_down(target),&d))return -1;
    out[0]=d.damage;out[1]=d.element;out[2]=d.high_roll;return 0;
}
static int stun(void *u,int32_t shooter,int32_t row,int32_t max_hp,int32_t dmg,int32_t *time)
{dw4_combat *c=u;dw4_fight_ctx x=context(c,shooter);return dw4_fight_p2e_stun_time(&x,row,max_hp,dmg,time);}
/* BLTget{Poison,Sleep,Bind,AttackDown,PowerDown}Time: the shooter's context, the target's enemy row (modelcontact.c has applied the retail gate on the technique base number). */
static int p2e_status(void *u,int32_t shooter,int32_t row,int32_t attack,const char *method,const char *what,int32_t *out)
{
    dw4_combat *c=u;dw4_fight_ctx x=context(c,shooter);
    if(!strcmp(method,"BLTgetPoisonTime"))return dw4_fight_p2e_poison_time(&x,row,attack,what,out);
    if(!strcmp(method,"BLTgetSleepTime"))return dw4_fight_p2e_sleep_time(&x,row,attack,out);
    if(!strcmp(method,"BLTgetBindTime"))return dw4_fight_p2e_bind_time(&x,row,attack,out);
    if(!strcmp(method,"BLTgetAttackDownTime"))return dw4_fight_p2e_atkdwn_time(&x,row,attack,what,out);
    if(!strcmp(method,"BLTgetPowerDownTime"))return dw4_fight_p2e_powdwn_time(&x,row,attack,what,out);
    return -1;
}
static int skill_up(void *u,int32_t shooter,int32_t attack,int32_t hit,int32_t crit)
{
    dw4_combat *c=u;(void)hit;int32_t raised;
    dw4_random before=*c->rng;   /* the chance draw is made only below the level cap: count the calls that really drew */
    int rc=dw4_fight_p2e_skillup(c->records,c->databases,c->rng,shooter,attack,crit!=0,&raised);
    if(memcmp(&before,c->rng,sizeof before))c->stats.skill_draws++;
    if(rc>0)c->stats.skill_ups++;
    return rc<0?-1:0;
}
static int exp_up(void *u,int32_t shooter,int32_t row,int32_t *share)
{
    dw4_combat *c=u;int rc=dw4_fight_p2e_expup(c->records,c->databases,row,shooter,share);
    if(!rc){c->stats.last_exp=*share;c->stats.exp_total+=(unsigned)*share;}
    return rc;
}
static void show_damage(void *u,int32_t v){dw4_combat *c=u;c->stats.last_damage=v;c->stats.damage_total+=v>0?(unsigned)v:0;}
static void show_popup(void *u,int32_t row,int32_t v,const float position[3])
{dw4_combat *c=u;if(c->popup)c->popup(c->popup_user,row,v,position);}
static dw4_fight_e2p_ctx e2p_context(dw4_combat *c,int32_t player)
{return (dw4_fight_e2p_ctx){dw4_playerrecords_get(c->records,"GETPLAYER",player),c->enemy,c->eneatk,c->rng};}
static int e2p_hit(void *u,int32_t player,int32_t row,int32_t attack,int *hit)
{dw4_combat *c=u;dw4_fight_e2p_ctx x=e2p_context(c,player);return dw4_fight_e2p_is_hit(&x,row,attack,hit);}
/* The attacking enemy's _downDataList entries the E2P rules read: [1] lowers its critical chance, [4] its strength, [2] its paralysis chance. */
static int e2p_damage(void *u,int32_t player,int32_t row,int32_t attack,const dw4_status *attacker,int32_t out[3])
{
    dw4_combat *c=u;dw4_fight_e2p_ctx x=e2p_context(c,player);dw4_fight_damage d;
    dw4_fight_e2p_down down={dw4_status_down(attacker,DW4_DOWN_CRITICAL),dw4_status_down(attacker,DW4_DOWN_ATTACK)};
    if(dw4_fight_e2p_damage(&x,row,attack,down,&d))return -1;
    out[0]=d.damage;out[1]=d.element;out[2]=d.high_roll;return 0;
}
static int e2p_rank(void *u,int32_t player,int32_t attack,int32_t hp,int32_t dmg,int32_t *rank)
{dw4_combat *c=u;dw4_fight_e2p_ctx x=e2p_context(c,player);return dw4_fight_e2p_damage_rank(&x,attack,hp,dmg,0,rank);}
static int e2p_stun(void *u,int32_t player,int32_t row,int32_t attack,int32_t dmg,int32_t rank,const dw4_status *attacker,int32_t *time)
{
    dw4_combat *c=u;dw4_fight_e2p_ctx x=e2p_context(c,player);
    return dw4_fight_e2p_status_stun(&x,row,attack,dmg,rank,dw4_status_down(attacker,DW4_DOWN_PARALYSIS),time);
}
/* The `apply_down` hook of the E2P attack/power-down rules: they write the player record's DOWNDATA entry before reading the stat, then the
 * equipment-applying recalculation (FUN_003fab90) runs, always. */
struct down_target {dw4_combat *combat;int32_t player;};
/* The recalculation refills HP of a player at 0 (the revive path); a KO'd player must stay at 0 while a stale status result is applied. */
static int player_down(dw4_property_folder *f){int32_t hp=1;return f && !dw4_property_number(f,"HP",&hp) && hp==0;}
static int apply_down(void *u,int slot,int32_t value)
{
    struct down_target *t=u;dw4_property_folder *f=dw4_playerrecords_get(t->combat->records,"GETPLAYER",t->player);
    size_t n=0;const int32_t *old=f?dw4_property_array(f,"DOWNDATA",&n):NULL;
    int32_t list[DW4_STATUS_DOWN_SLOTS];
    if(!old || n!=DW4_STATUS_DOWN_SLOTS)return -1;
    memcpy(list,old,sizeof list);
    if(slot>=0 && (size_t)slot<n){list[slot]=value;if(dw4_property_set_array(f,"DOWNDATA",list,n))return -1;}
    return player_down(f)?0:dw4_playerstats_recalculate((void *)t->combat->databases,f);
}
/* BLPget{Poison,Sleep,Bind,AttackDown,PowerDown}Time for the player of `player` struck by enemy row `row`. */
static int e2p_status(void *u,int32_t player,int32_t row,int32_t attack,const char *method,const char *what,int32_t *out)
{
    dw4_combat *c=u;dw4_fight_e2p_ctx x=e2p_context(c,player);
    struct down_target target={c,player};dw4_fight_status_ctx sx={&x,apply_down,&target};
    if(!strcmp(method,"BLPgetPoisonTime"))return dw4_fight_e2p_status_poison(&x,what,attack,out);
    if(!strcmp(method,"BLPgetSleepTime"))return dw4_fight_e2p_status_sleep(&x,row,attack,out);
    if(!strcmp(method,"BLPgetBindTime"))return dw4_fight_e2p_status_bind(&x,row,attack,out);
    if(!strcmp(method,"BLPgetAttackDownTime"))return dw4_fight_e2p_status_atkdown(&sx,what,row,attack,out);
    if(!strcmp(method,"BLPgetPowerDownTime"))return dw4_fight_e2p_status_powdown(&sx,what,row,attack,out);
    return -1;
}
/* The gauge publication of FUN_003f9c80 (METERCTRL hpmt SETPERCENT, NUMBERCTRL hpnm SETVALUE): a dead player publishes nothing (0x3f9c80 returns first). */
static void publish_hp(dw4_combat *c,int32_t slot)
{
    dw4_property_folder *f=dw4_playerrecords_get(c->records,"GETPLAYER",slot);
    int32_t hp,mhp;
    if(c->hud && f && !dw4_property_number(f,"HP",&hp) && !dw4_property_number(f,"MHP",&mhp) && hp>0 && mhp>0)c->hud(c->hud_user,slot,hp,mhp);
}
/* A player's status lists are the record's DOWNDATA (7) and UPDATA (11): loaded into the model's status before every message, tick and hook,
 * stored back afterwards, and every stat-changing result recalculates the player (0x445c60 sends GAMERAM RECALCPLAYER). */
static void host_load(void *u,dw4_status *s)
{
    struct status_host *h=u;dw4_property_folder *f=dw4_playerrecords_get(h->combat->records,"GETPLAYER",h->slot);
    size_t nd=0,nu=0;const int32_t *down=f?dw4_property_array(f,"DOWNDATA",&nd):NULL,*up=f?dw4_property_array(f,"UPDATA",&nu):NULL;
    if(down && up && nd==DW4_STATUS_DOWN_SLOTS && nu==DW4_STATUS_UP_SLOTS)dw4_status_load_lists(s,down,up);
}
static void host_store(void *u,dw4_status *s,const dw4_status_tick_result *r)
{
    struct status_host *h=u;dw4_property_folder *f=dw4_playerrecords_get(h->combat->records,"GETPLAYER",h->slot);
    if(!f)return;
    if(s->lists_dirty){
        int32_t down[DW4_STATUS_DOWN_SLOTS],up[DW4_STATUS_UP_SLOTS];
        dw4_status_store_lists(s,down,up);
        dw4_property_set_array(f,"DOWNDATA",down,DW4_STATUS_DOWN_SLOTS);dw4_property_set_array(f,"UPDATA",up,DW4_STATUS_UP_SLOTS);
    }
    if(r){
        /* Speed / Power / Resist that ended (or were cleared) in this result. */
        uint32_t buffs=r->expired&(1u<<DW4_STATUS_SPEEDUP|1u<<DW4_STATUS_POWERUP|1u<<DW4_STATUS_REFRACT);
        for(;buffs;buffs&=buffs-1)h->combat->stats.buff_expiries++;
    }
    if(r && r->recalc_player && !player_down(f)){
        dw4_playerstats_recalculate((void *)h->combat->databases,f);h->combat->stats.recalcs++;
        publish_hp(h->combat,h->slot);   /* 0x445c60 follows RECALCPLAYER with ADDHP(index, 0), which republishes the gauge */
    }
}
static void bind_player(dw4_combat *c,int32_t slot,dw4_modelctrl *p)
{
    c->host[slot]=(struct status_host){c,slot};
    dw4_modelctrl_status_player(p,&(dw4_status_player_host){&c->host[slot],host_load,host_store});
}
static void show_damage_player(void *u,int32_t player,int32_t v)
{dw4_combat *c=u;(void)player;c->stats.player_last_damage=v;c->stats.player_damage_total+=v>0?(unsigned)v:0;}
/* BLPcalcKoukaMagic / BLPgetAttackZokusei for the hit scripts (modelcontact.c): the support work below and the shooter's element rule. */
static int p2p_magic(void *u,int32_t receiver,int32_t shooter,int32_t attack,int32_t *result)
{return dw4_combat_cast_support(u,receiver,shooter,attack,NULL,result)?-1:0;}
static int attack_element(void *u,int32_t shooter,int32_t attack,int32_t *element)
{dw4_combat *c=u;dw4_fight_ctx x=context(c,shooter);return dw4_fight_attack_element(&x,attack,element);}
static const dw4_model_fight fight={
    .is_hit=is_hit,.is_critical=is_crit,.damage=damage,.stun_time=stun,.skill_up=skill_up,.exp_up=exp_up,.display_damage=show_damage,.display_popup=show_popup,
    .e2p_is_hit=e2p_hit,.e2p_damage=e2p_damage,.e2p_rank=e2p_rank,.display_damage_player=show_damage_player,.e2p_stun=e2p_stun,
    .p2e_status=p2e_status,.e2p_status=e2p_status,.p2p_magic=p2p_magic,.attack_element=attack_element,
};
dw4_combat *dw4_combat_open(dw4_playerrecords *records,const dw4_databases *databases,dw4_random *rng,dw4_controllers *models)
{
    if(!records || !databases || !rng || !models)return NULL;
    dw4_combat *c=calloc(1,sizeof *c);if(!c)return NULL;
    c->records=records;c->databases=databases;c->enemy=dw4_databases_table(databases,"enemy");c->eneatk=dw4_databases_table(databases,"eneatk");c->rng=rng;c->models=models;
    if(!dw4_dbtable_valid(c->enemy) || !dw4_dbtable_valid(c->eneatk)){free(c);return NULL;}
    for(size_t i=0;i<dw4_controllers_count(models);i++){
        const dw4_stageobject *info;int32_t slot;dw4_controllers_model(models,i,&info,&slot);
        const char *kind=dw4_stageobject_kind_string(info);dw4_modelctrl *model=dw4_controllers_owned_model(models,i);
        if(model && kind && !strcmp(kind,"KIND_ENEMY") && source_bind(c,model,0,slot,i)){dw4_combat_close(c);return NULL;}
    }
    return c;
}
void dw4_combat_scripts(dw4_combat *c,dw4_scriptengine *scripts,uint64_t scope){if(c){c->scripts=scripts;c->scope=scope;}}
void dw4_combat_close(dw4_combat *c)
{if(c){while(c->sources)dw4_modelctrl_hit_sink(c->sources->model,NULL,NULL,NULL);free(c);}}
const dw4_combat_stats *dw4_combat_get_stats(const dw4_combat *c){return c?&c->stats:NULL;}
/* Offer one enemy bullet to the player model of `slot`: its script state is bound on first use, the record HP is handed to the hit script and
 * written back when the script changed it. Returns 1 when the hit script ran, 0 when nothing was hit, -1 with `error` filled. */
static int offer_body(dw4_combat *c,int32_t slot,dw4_modelctrl *p,dw4_model_bullet *bullet,int enemy_hit,char *error,size_t cap)
{
    dw4_property_folder *folder=dw4_playerrecords_get(c->records,"GETPLAYER",slot);
    int32_t hp,mhp;
    if(!folder || !c->scripts || c->downed[slot] || dw4_property_number(folder,"HP",&hp) || dw4_property_number(folder,"MHP",&mhp))return 0;   /* a capsule is no PLAYER body */
    dw4_modelctrl *slots[4];memcpy(slots,c->players,sizeof slots);slots[slot]=p;dw4_combat_players(c,slots);
    if(c->binding_failed){snprintf(error,cap,"combat: %.140s",c->error);return -1;}
    if(!c->player_bound[slot]){
        const char *name=dw4_property_string(folder,"DIGIMONNAME");
        if(!name)return 0;
        snprintf(c->player_name[slot],sizeof c->player_name[slot],"%s",name);
        c->player_state[slot]=(dw4_script_model){.ram_no=slot,.rec_no=-1,.info_name=c->player_name[slot]};
        dw4_modelctrl_script(p,c->scripts,c->scope,c->player_state+slot);c->player_bound[slot]=1;
    }
    bind_player(c,slot,p);
    c->player_state[slot].hp=hp;c->player_state[slot].max_hp=mhp;
    float pworld[16];
    dw4_modelctrl_matrix(p,pworld);
    int rc=dw4_modelctrl_bullet_hit(p,pworld,bullet);
    if(rc<0){snprintf(error,cap,"combat: player %d: %.140s",slot,dw4_modelctrl_error(p));return -1;}
    if(rc>0){
        if(enemy_hit)c->stats.player_hits++;
        int32_t after=c->player_state[slot].hp;
        if(after!=hp && dw4_property_set_number(folder,"HP",after)){snprintf(error,cap,"combat: cannot store player HP");return -1;}
    }
    return rc;
}
static int offer_player(dw4_combat *c,int32_t slot,dw4_modelctrl *p,dw4_model_bullet *bullet,char *error,size_t cap)
{return offer_body(c,slot,p,bullet,1,error,cap);}
/* A support volume (80000..89999, an enemy-group bullet) is the caster's own: it is offered to the shooter's body only, so hit_p_<species>.lua reaches
 * BLPcalcKoukaMagic once with receiver == shooter; mates in range are reached by the area query inside p2p_magic, not by a second hit chunk (offering it
 * to every overlapped body would run the chunk, and its BLTcalcSkillUp skill-growth draw, once per body). It is not an enemy hit (player_hits stays);
 * the count is support_hits. Returns the bodies whose script ran, or -1. */
static int deliver_support(dw4_combat *c,int32_t shooter,dw4_model_bullet *bullet,char *error,size_t cap)
{
    int hits=0;
    dw4_modelctrl *p=shooter>=0 && shooter<4?c->players[shooter]:NULL;
    if(p && dw4_modelctrl_active(p)){
        int rc=offer_body(c,shooter,p,bullet,0,error,cap);
        if(rc<0)return -1;
        hits+=rc;
    }
    if(hits)c->stats.support_hits+=(unsigned)hits;else c->stats.support_missed++;
    return hits;
}
void dw4_combat_fight(dw4_combat *c,dw4_model_fight *out){if(c && out){*out=fight;out->user=c;}}
int dw4_combat_hit_player(dw4_combat *c,int32_t slot,dw4_modelctrl *player,int64_t now_ns,int32_t kind,int32_t enemy_row,int32_t enemy_slot,
    const dw4_status *attacker,char *error,size_t cap)
{
    if(!c || !player || slot<0 || slot>=4)return -1;
    dw4_model_fight *fp=&c->fight_table;dw4_combat_fight(c,fp);
    dw4_model_bullet bullet={.kind=kind,.shoot_ram_no=enemy_slot,.source_row=enemy_row,.group=DW4_BULLET_ENEMY,.world_ns=now_ns,.name="",.fight=fp,.source_status=attacker,
        .source_world={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1},.box={-1e6f,-1e6f,-1e6f,1e6f,1e6f,1e6f}};
    return offer_player(c,slot,player,&bullet,error,cap);
}
int dw4_combat_status_tick(dw4_combat *c,dw4_modelctrl *const players[4],char *error,size_t cap)
{
    if(!c)return 0;
    dw4_combat_players(c,players);
    if(c->binding_failed){snprintf(error,cap,"combat: %.140s",c->error);return -1;}
    for(int32_t slot=0;slot<4;slot++){
        dw4_modelctrl *p=players[slot];
        dw4_property_folder *folder=p && dw4_modelctrl_active(p)?dw4_playerrecords_get(c->records,"GETPLAYER",slot):NULL;
        int32_t hp,after;
        if(!folder || dw4_property_number(folder,"HP",&hp))continue;
        bind_player(c,slot,p);
        after=hp;
        if(dw4_modelctrl_status_tick(p,&after,NULL)){snprintf(error,cap,"combat: player %d status: %.140s",slot,dw4_modelctrl_error(p));return -1;}
        if(after!=hp && dw4_property_set_number(folder,"HP",after)){snprintf(error,cap,"combat: cannot store player HP");return -1;}
    }
    return 0;
}
/* 3993e0 emits at the source model's subcommand phase. There is no outer
 * active-volume scan, timestamp gate or once-per-volume scheduling policy. */
static int source_emit(void *u,dw4_modelctrl *model,const dw4_modelctrl_hitbox *h,const float world[16],int64_t sample_ns)
{
    (void)sample_ns;struct hit_source *s=u;dw4_combat *c=s->owner;dw4_model_fight *fp=&c->fight_table;*fp=fight;fp->user=c;
    int32_t k=h->kind;int64_t now=c->world_ns;char error[160];
    if(s->player){
        int32_t slot=s->slot;
        if(k==60000){
            dw4_model_talk_probe probe={.shoot_ram_no=slot,.world_ns=now};
            memcpy(probe.source_world,world,sizeof probe.source_world);dw4_hitbox_bullet(world,h->offset,h->size,probe.box);
            if(dw4_controllers_talk(c->models,&probe)<0){snprintf(c->error,sizeof c->error,"combat talk probe: %.120s",dw4_controllers_error(c->models));return -1;}
            return 0;
        }
        if(k>=80000 && k<90000){
            dw4_model_bullet bullet={.kind=k,.shoot_ram_no=slot,.source_row=-1,.group=DW4_BULLET_ENEMY,.world_ns=now,.name="",.fight=fp};
            memcpy(bullet.source_world,world,sizeof bullet.source_world);dw4_hitbox_bullet(world,h->offset,h->size,bullet.box);
            int rc=deliver_support(c,slot,&bullet,error,sizeof error);
            if(rc<0){snprintf(c->error,sizeof c->error,"%.159s",error);return -1;}
            return 0;
        }
        if(!(k<10000?k>=0 && k<1000:k<60000))return 0;
        dw4_model_bullet bullet={.kind=k,.shoot_ram_no=slot,.group=DW4_BULLET_PLAYER,.world_ns=now,.name="",.fight=fp};
        memcpy(bullet.source_world,world,sizeof bullet.source_world);dw4_hitbox_bullet(world,h->offset,h->size,bullet.box);
        int hits=dw4_controllers_enemy_bullet(c->models,&bullet);if(hits<0)return -1;
        c->stats.hits+=(unsigned)hits;return 0;
    }
    if(k<70000 || k>=80000)return 0;
    dw4_script_model state;if(dw4_controllers_model_state(c->models,s->index,&state))return 0;
    for(int32_t slot=0;slot<4;slot++){
        dw4_modelctrl *p=c->players[slot];if(!p || !dw4_modelctrl_active(p) || !c->scripts)continue;
        dw4_model_bullet bullet={.kind=k,.shoot_ram_no=s->slot,.source_row=state.rec_no,.group=DW4_BULLET_ENEMY,.world_ns=now,.name="",.fight=fp,
            .source_status=dw4_modelctrl_status(model)};
        memcpy(bullet.source_world,world,sizeof bullet.source_world);dw4_hitbox_bullet(world,h->offset,h->size,bullet.box);
        if(offer_player(c,slot,p,&bullet,error,sizeof error)<0){snprintf(c->error,sizeof c->error,"%.159s",error);return -1;}
    }
    return 0;
}
int dw4_combat_tick(dw4_combat *c,int64_t now_ns,dw4_modelctrl *const players[4],char *error,size_t cap)
{
    if(!c)return 0;c->world_ns=now_ns;dw4_combat_players(c,players);
    if(c->binding_failed){snprintf(error,cap,"combat: %.140s",c->error);return -1;}
    return 0;
}
/* Technique bullet volume: an attack number 40000+base goes to the enemy and prop receivers
 * through the same player-bullet rules as a weapon volume. A support number (80000+base) is the
 * caster's own: it is offered to the caster's body as an enemy-group bullet (the player's hit data
 * takes that group only) so hit_p_<species>.lua runs its 80000 branch, which reaches
 * BLPcalcKoukaMagic (p2p_magic). Returns the contacts, or -1. */
int dw4_combat_fire(dw4_combat *c,int64_t now_ns,int32_t slot,dw4_modelctrl *caster,int32_t attack,const float world[16],const float offset[3],const float size[3],char *error,size_t cap)
{
    if(!c || slot<0 || slot>3)return 0;
    dw4_model_fight *fp=&c->fight_table;*fp=fight;fp->user=c;
    dw4_model_bullet b={.kind=attack,.shoot_ram_no=slot,.group=DW4_BULLET_PLAYER,.world_ns=now_ns,.name="",.fight=fp};
    memcpy(b.source_world,world,sizeof b.source_world);dw4_hitbox_bullet(world,offset,size,b.box);
    if(attack/10000==4) {
        int hits=dw4_controllers_enemy_bullet(c->models,&b);
        if(hits<0){snprintf(error,cap,"combat: %.140s",c->error[0]?c->error:dw4_controllers_error(c->models));return -1;}
        c->stats.hits+=(unsigned)hits;return hits;
    }
    if(attack/10000!=8 || !caster || !dw4_modelctrl_active(caster) || !c->scripts)return 0;
    b.group=DW4_BULLET_ENEMY;b.source_row=-1;
    return deliver_support(c,slot,&b,error,cap);
}
void dw4_combat_players(dw4_combat *c,dw4_modelctrl *const players[4])
{
    if(!c || !players)return;
    for(int i=0;i<4;i++){
        dw4_modelctrl *next=players[i];
        if(c->players[i] && c->players[i]!=next)dw4_modelctrl_hit_sink(c->players[i],NULL,NULL,NULL);
        if(next && source_bind(c,next,1,i,0)){c->binding_failed=1;return;}
        c->players[i]=next;
    }
}
void dw4_combat_hud(dw4_combat *c,dw4_combat_hud_fn fn,void *user){if(c){c->hud=fn;c->hud_user=user;}}
void dw4_combat_popup(dw4_combat *c,dw4_combat_popup_fn fn,void *user){if(c){c->popup=fn;c->popup_user=user;}}
const char *dw4_combat_error(const dw4_combat *c){return c?c->error:"";}
void dw4_combat_set_downed(dw4_combat *c,int32_t slot,int downed,const float pos[3])
{
    if(!c || slot<0 || slot>3)return;
    c->downed[slot]=downed!=0;c->capsule_age[slot]=downed?DW4_CAPSULE_READY_TICKS:0;c->capsule_near[slot]=0;c->ko_ticks[slot]=0;
    if(pos)memcpy(c->downed_pos[slot],pos,sizeof c->downed_pos[slot]);else memset(c->downed_pos[slot],0,sizeof c->downed_pos[slot]);
}
void dw4_combat_view_current(const dw4_combat *c,dw4_combat_view *v)
{
    memset(v,0,sizeof *v);
    for(int i=0;i<4;i++){
        dw4_modelctrl *p=c->players[i];
        if(p && dw4_modelctrl_active(p) && !c->downed[i]){
            dw4_modelctrl_actor a;dw4_modelctrl_actor_state(p,&a);
            v->joined[i]=v->running[i]=1;memcpy(v->pos[i],a.position,sizeof v->pos[i]);
        }else if(c->downed[i])memcpy(v->pos[i],c->downed_pos[i],sizeof v->pos[i]);   /* a capsule's slot is not a running PLAYER, whatever its (kept) model still does */
        v->downed[i]=c->downed[i];v->young[i]=c->downed[i] && c->capsule_age[i]<DW4_CAPSULE_READY_TICKS;
    }
}
/* Deliver one buff message (SETSPEEDUP / SETPOWERUP / SETREFRACT, the text of retail case 20) to a player model's status work. The record's UPDATA is
 * loaded, written and stored by the status host (bind_player), the player is recalculated and the gauge republished by host_store. */
static int send_buff(dw4_combat *c,int32_t slot,const char *name,const char *args)
{
    dw4_modelctrl *p=c->players[slot];
    char error[160]="";dw4_script_value r,a[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"",0},{DW4_SCRIPT_NUMBER,slot,NULL,0},
        {DW4_SCRIPT_STRING,0,name,strlen(name)},{DW4_SCRIPT_STRING,0,args,strlen(args)}};
    if(!p || !dw4_modelctrl_active(p)){c->stats.buff_no_model++;return 0;}
    bind_player(c,slot,p);
    if(dw4_modelctrl_service(p,"sd",a,5,&r,error,sizeof error)){snprintf(c->error,sizeof c->error,"support: %s to player %d: %.100s",name,slot,error);return -1;}
    c->stats.buff_applies++;
    return 0;
}
/* Erases a downed player's model once its capsule exists. Retail's SQ_DEAD ends in SQ_ERAS (p_<species>: DEAD*1, then JUMP SQ_ERAS), and the capture shows the
 * model gone 2-3 s after the KO (the capsule appears ~2 s after it): the PLAYER lookup then finds only the survivor. The model controller is removed (not drawn,
 * not active: the lobby hides it and the slot's PLAYER/MODELCTRL receiver reports inactive); its records and weapon sections stay for the revive. */
static int erase_model(dw4_combat *c,int32_t slot)
{
    dw4_modelctrl *p=c->players[slot];
    char error[160]="";dw4_script_value r;
    dw4_script_value rm[4]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"",0},{DW4_SCRIPT_NUMBER,slot,NULL,0},{DW4_SCRIPT_STRING,0,"REMOVE",6}};
    if(!p || !dw4_modelctrl_active(p))return 0;
    if(dw4_modelctrl_service(p,"sd",rm,4,&r,error,sizeof error)){snprintf(c->error,sizeof c->error,"KO: erasing player %d: %.100s",(int)slot,error);return -1;}
    return 0;
}
/* The Raise receiver (0x3d50c0) generates the PLAYER model at the caster's matrix with SQ_CMBK.
 * The KO flow erased the model with the capsule, so the revive is the same GENERATE (caster
 * position and yaw, sequence): SQ_CMBK is `MUTEKI 120`, the REVE*1 action, JUMP SQ_CMBK02
 * (REVE*2), then SQ_WAIT, in the weapon section of the player's SQ_WAIT. A model that was never
 * erased (a fixture's set_downed) is moved and sent the sequence instead; a pack without SQ_CMBK
 * falls back to SQ_WAIT. The sparkle ring at the capsule is not reproduced: no recovered code or
 * script names it. */
static int revive_model(dw4_combat *c,int32_t slot,int32_t caster,const float where[3])
{
    dw4_modelctrl *p=c->players[slot],*cm=c->players[caster];
    char error[160]="",text[128];dw4_script_value r;
    if(!p)return 0;
    float yaw=0;
    if(cm && dw4_modelctrl_active(cm)){dw4_modelctrl_actor a;dw4_modelctrl_actor_state(cm,&a);yaw=a.rotation[1];}
    const char *seq=dw4_modelctrl_has_sequence(p,"SQ_CMBK")?"SQ_CMBK":"SQ_WAIT";
    if(!strcmp(seq,"SQ_CMBK")){dw4_modelctrl_label_copy(p,"SQ_WAIT","SQ_CMBK");dw4_modelctrl_label_copy(p,"SQ_WAIT","SQ_CMBK02");}
    if(!dw4_modelctrl_active(p)){
        snprintf(text,sizeof text,"%s/V<%g,%g,%g>/V<0,%g,0>",seq,where[0],where[1],where[2],yaw);
        dw4_script_value gen[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"",0},{DW4_SCRIPT_NUMBER,slot,NULL,0},{DW4_SCRIPT_STRING,0,"GENERATE",8},
            {DW4_SCRIPT_STRING,0,text,strlen(text)}};
        if(dw4_modelctrl_service(p,"sd",gen,5,&r,error,sizeof error)){snprintf(c->error,sizeof c->error,"support: reviving player %d: %.100s",(int)slot,error);return -1;}
        return 0;
    }
    snprintf(text,sizeof text,"V<%g,%g,%g>/V<0,%g,0>",where[0],where[1],where[2],yaw);
    dw4_script_value mv[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"",0},{DW4_SCRIPT_NUMBER,slot,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},
        {DW4_SCRIPT_STRING,0,text,strlen(text)}};
    dw4_script_value sq[4]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"",0},{DW4_SCRIPT_NUMBER,slot,NULL,0},{DW4_SCRIPT_STRING,0,seq,strlen(seq)}};
    if(dw4_modelctrl_service(p,"sd",mv,5,&r,error,sizeof error) || dw4_modelctrl_service(p,"sd",sq,4,&r,error,sizeof error)){
        snprintf(c->error,sizeof c->error,"support: reviving player %d: %.100s",(int)slot,error);return -1;
    }
    return 0;
}
int dw4_combat_capsule_state(const dw4_combat *c,int32_t slot,dw4_combat_capsule *out)
{
    if(!c || slot<0 || slot>3)return 0;
    if(out){
        memset(out,0,sizeof *out);
        out->downed=c->downed[slot];out->ready=c->downed[slot] && c->capsule_age[slot]>=DW4_CAPSULE_READY_TICKS;out->near_player=c->capsule_near[slot];
        out->age=c->capsule_age[slot];out->ko_ticks=c->ko_ticks[slot];
        memcpy(out->pos,c->downed_pos[slot],sizeof out->pos);
    }
    return c->downed[slot];
}
int dw4_combat_ko_tick(dw4_combat *c,const char *stage,int *game_over)
{
    int live[4]={0},ncap=0,nlive=0;float livepos[4][3];
    if(!c || !stage || !game_over)return -1;
    *game_over=0;c->error[0]=0;
    for(int i=0;i<4;i++){
        dw4_modelctrl *p=c->players[i];
        if(p && dw4_modelctrl_active(p) && !c->downed[i]){   /* a PLAYER that answers the NEAR query: a joined, running model that is not a capsule */
            dw4_modelctrl_actor a;dw4_modelctrl_actor_state(p,&a);
            live[i]=1;nlive++;memcpy(livepos[i],a.position,sizeof livepos[i]);
        }
    }
    /* beNDMWMdlPlayer2::vfunc_38 for the capsules that already exist: ONE counts up to 10; with a living PLAYER the nearest one (squared distance, inferred)
     * toggles SQ_SWON below 900 and SQ_SWOF above; with none the end chunk is due. */
    for(int i=0;i<4;i++){
        if(!c->downed[i])continue;
        ncap++;
        if(c->capsule_age[i]<DW4_CAPSULE_READY_TICKS)c->capsule_age[i]++;
        if(!nlive)continue;
        float best=0;int have=0;
        for(int j=0;j<4;j++)if(live[j]){
            float dx=livepos[j][0]-c->downed_pos[i][0],dy=livepos[j][1]-c->downed_pos[i][1],dz=livepos[j][2]-c->downed_pos[i][2],d=dx*dx+dy*dy+dz*dz;
            if(!have || d<best){best=d;have=1;}
        }
        if(!c->capsule_near[i]){if(best<DW4_CAPSULE_NEAR_SQ)c->capsule_near[i]=1;}
        else if(!(best<=DW4_CAPSULE_NEAR_SQ))c->capsule_near[i]=0;
    }
    if(ncap && !nlive && !c->gameover_due){c->gameover_due=1;c->stats.gameovers++;*game_over=1;}
    /* The KO trigger: the record HP reaches 0 on a player seen alive. */
    for(int i=0;i<4;i++){
        dw4_modelctrl *p=c->players[i];int32_t hp=1,use=0;
        dw4_property_folder *f=dw4_playerrecords_get(c->records,"GETPLAYER",i);
        if(!live[i] || !f || dw4_property_number(f,"ISUSE",&use) || !(uint8_t)use || dw4_property_number(f,"HP",&hp)){c->ko_ticks[i]=0;continue;}
        if(hp>0){c->armed[i]=1;c->ko_ticks[i]=0;continue;}
        if(!c->armed[i] || ++c->ko_ticks[i]<DW4_KO_CAPSULE_DELAY)continue;
        dw4_modelctrl_actor a;dw4_modelctrl_actor_state(p,&a);
        if(dw4_magic_capsule_start(c->records,i,stage,a.position) || dw4_magic_bkchip_bitexp(c->records,i)){
            snprintf(c->error,sizeof c->error,"KO: the bank-chip records of player %d could not be written",i);return -1;
        }
        c->downed[i]=1;c->capsule_age[i]=0;c->capsule_near[i]=0;c->armed[i]=0;c->ko_ticks[i]=0;memcpy(c->downed_pos[i],a.position,sizeof c->downed_pos[i]);
        c->stats.downs++;
        if(erase_model(c,i))return -1;   /* the model went away with its death sequence: only the capsule and the records remain */
    }
    return 0;
}
int dw4_combat_cast_support(dw4_combat *c,int32_t receiver,int32_t shooter,int32_t attack,const dw4_combat_view *view,int32_t *result)
{
    dw4_combat_view own;dw4_magic m;dw4_magic_group g;
    if(!c || !result || receiver<0 || receiver>3 || shooter<0 || shooter>3){if(c)snprintf(c->error,sizeof c->error,"support: invalid slots %d/%d",(int)receiver,(int)shooter);return -1;}
    c->error[0]=0;
    /* Case 20 appends 1 only for a self hit; for receiver != shooter nothing is appended and the
     * first integer (the receiver) is read back. The script passes the number on to
     * BLTcalcSkillUp, which ignores it. The read-back value is an inference. */
    *result=receiver==shooter?1:receiver;
    if(receiver!=shooter)return 0;
    if(!view){dw4_combat_view_current(c,&own);view=&own;}
    dw4_fight_ctx x=context(c,receiver);
    if(!x.player || !dw4_dbtable_valid(x.tech)){snprintf(c->error,sizeof c->error,"support: no player record or pcTech for slot %d",(int)receiver);return -1;}
    if(dw4_fight_p2p_magic(&x,receiver,shooter,attack,&m)){snprintf(c->error,sizeof c->error,"support: attack %d: the technique family is not learned or its data is missing",(int)attack);return -1;}
    if(m.kind==DW4_MAGIC_NONE)return 0;   /* a number that matches no family still counts as a self hit (result 1) */
    if(m.kind!=DW4_MAGIC_RAISE && dw4_magic_player_group(c->records,view->joined,(const float (*)[3])view->pos,&g)){
        snprintf(c->error,sizeof c->error,"support: the PLAYER group could not be read");return -1;
    }
    switch(m.kind){
    case DW4_MAGIC_HEAL:{
        int applied[4];
        /* The caster first, then (Heal) the area, the full delta each; a dead player is left alone (FUN_003f9c80). */
        if(dw4_magic_apply_heal(c->records,&m,receiver,&g,applied)<0){snprintf(c->error,sizeof c->error,"support: heal failed");return -1;}
        for(int i=0;i<4;i++)if(applied[i]){c->stats.heals++;publish_hp(c,i);}
        return 0;
    }
    case DW4_MAGIC_CURE:{
        int poisoned[4]={0},cured[4];int32_t endurance[4]={0};
        for(int i=0;i<4;i++){
            const dw4_status *st=view->joined[i] && c->players[i]?dw4_modelctrl_status(c->players[i]):NULL;
            if(st && dw4_status_is_set(st,DW4_STATUS_POISON)){poisoned[i]=1;endurance[i]=st->poison_endurance;}
        }
        if(dw4_magic_apply_cure(&x,&m,receiver,&g,poisoned,endurance,cured)<0){snprintf(c->error,sizeof c->error,"support: cure failed");return -1;}
        for(int i=0;i<4;i++)if(cured[i] && c->players[i]){bind_player(c,i,c->players[i]);if(dw4_modelctrl_cure_poison(c->players[i]))c->stats.cures++;}
        return 0;
    }
    case DW4_MAGIC_RAISE:{
        dw4_magic_group down;memset(&down,0,sizeof down);
        int32_t targets[4],percent[4];
        for(int i=0;i<4;i++){
            down.member[i]=view->downed[i]!=0 && !view->young[i];   /* a capsule whose ONE counter is below 10 returns early from the RAISE handler: no revive, no refund */
            down.answer[i]=down.member[i];   /* what the PLAYER2 capsule answers to GETHP is unresolved: a downed slot is assumed non-zero */
            memcpy(down.pos[i],view->pos[i],sizeof down.pos[i]);
        }
        int n=dw4_magic_apply_raise(c->records,&m,&down,view->pos[receiver],view->running,targets,percent);
        if(n<0){snprintf(c->error,sizeof c->error,"support: raise failed");return -1;}
        for(int i=0;i<n;i++){
            if(dw4_magic_apply_raise_refund(c->records,targets[i],percent[i])){snprintf(c->error,sizeof c->error,"support: bank-chip refund failed");return -1;}
            c->downed[targets[i]]=0;c->capsule_age[targets[i]]=0;c->ko_ticks[targets[i]]=0;c->capsule_near[targets[i]]=0;   /* the capsule is sent SQ_EXIT after the refund */
            if(revive_model(c,targets[i],receiver,view->pos[receiver]))return -1;
            c->stats.raises++;
        }
        return 0;
    }
    default:{
        /* Speed / Power / Resist: the area around the caster, then the caster last. */
        char name[DW4_BUFF_NAME_CAP],args[DW4_BUFF_ARGS_CAP];int32_t targets[4];
        if(dw4_buff_message(&m,name,args)){snprintf(c->error,sizeof c->error,"support: no buff message for kind %d",(int)m.kind);return -1;}
        int n=dw4_magic_buff_targets(&g,receiver,targets);
        if(n<0){snprintf(c->error,sizeof c->error,"support: buff targets failed");return -1;}
        for(int i=0;i<n;i++)if(send_buff(c,targets[i],name,args))return -1;
        return 0;
    }
    }
}
