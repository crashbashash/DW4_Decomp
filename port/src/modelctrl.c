#include "dw4/modelctrl.h"
#include "arenalist.h"
#include "dw4/arenapack.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "dw4/npcmotion.h"
#include "dw4/modelai.h"
#include "dw4/modelfade.h"
#include "dw4/hitbox.h"
#include "dw4/modelsubcom.h"
struct command { const char *type,*name,*target,*bone; uint32_t v[6];float box[6]; };
struct sequence { const char *name; struct command *cmd; size_t n; };
struct action { const char *name; dw4_action2_component *cmd; size_t n; int supported;int64_t duration[DW4_A2_MAX_COMPONENTS]; };
struct motion_duration {const char *name;int64_t ns;};
struct aimap { const char *name,*target_type; uint32_t bounds[3],rot_limit; dw4_model_ai_choice *choices[4];size_t count[4]; };
struct model_program {dw4_arena_pack pack;int32_t sequences;};
struct dw4_modelctrl {
    dw4_model_contact last_contact;int has_last_contact;   /* the bullet of the latest hit callback: a sequence it starts may LUACALL the hit script again (g_dbutton1) */
    struct model_program *program;
    unsigned *refs;
    struct sequence *seq; size_t nseq;
    struct action *action; size_t naction;
    struct motion_duration *duration;size_t nduration;
    struct aimap *map; size_t nmap;
    float *hit_boxes;size_t nhit_boxes;uint8_t hit_player_talk,hit_player_bullet,hit_enemy_bullet;unsigned status_commands,flash_count,missing_motions,long_actions;int64_t flash_start_ns;
    float *hit_world_boxes;int hit_cached;int64_t hit_timestamp;
    dw4_modelctrl_hitbox hitbox_snapshot[8]; /* read-only projection, refreshed from Work */
    dw4_modelctrl_dependencies dependencies;int subcommand_clearing,dependencies_active,dependencies_changing;
    dw4_modelctrl_hit_emit hit_emit;void *hit_user;void (*hit_release)(void *);
    dw4_scriptengine *scripts;dw4_script_model *model;dw4_script_model bridge_last;uint64_t scope;
    uint64_t generation;
    dw4_handle ai_timer;int32_t ai_timer_name,erase_name;
    dw4_arena *arena;dw4_handle ram,data,work,node;
    /* Authored Euler reconstruction and matrix publication are native pose
     * services; animation and recovered Work/channel state live in the arena. */
    struct {float rotation[3],matrix_rotation[3];int matrix_valid;} pose;
    dw4_modelctrl_collision collision;void *collision_user;
    float land[4];   /* beHitLandDelivInfoRam _halfWidth/_upRange/_downRange and _checkFlag: the model's own collision delivery size and wall-info selection (3/4/4 and flag 3 when the pack has no record) */
    dw4_modelctrl_near near;void *near_user;
    int floor_signal,land_signal;
    int64_t previous,subcommand_clock;
    int sampled;
    int raw_sampled;int64_t raw_previous;uint64_t held_ns;

    int object_kind,player_kind,enemy_kind,player_walking;float player_yaw;uint32_t player_pad;int atck_state,atck_released;
    /* Status ailments (beNDMWMdlPEBase work): enemies and players only. A player's stat lists are mirrored through the host. */
    dw4_status status_snapshot; /* read-only compatibility projection, never rule storage */
    dw4_handle status_timer[DW4_STATUS_TIMER_SLOTS];int32_t status_name[DW4_STATUS_TIMER_SLOTS];
    int has_status;dw4_status_player_host status_host;int status_clock_valid;int64_t status_clock,status_elapsed;
    dw4_modelctrl_trace trace;void *trace_user;
    int64_t now;
    dw4_action2_host clock;
    int fade_updated,fade_in;unsigned fade_event_seen;int64_t fade_clock; /* native render sampling context */
    char error[256];
};
static void model_pose_publish(dw4_modelctrl *);
static int model_subcommand_event(void *,dw4_handle,int,int *);
static beAction2InfoWork *model_action_work(const dw4_modelctrl *m)
{dw4_action2_record r=dw4_action2_host_records(&m->clock);return DW4_ARENA_OBJ(r.arena,beAction2InfoWork,r.work);}
static void model_fade_write(dw4_modelctrl *m,const dw4_modelfade *f)
{
    beAction2InfoWork *w=model_action_work(m);memcpy(&w->_fadeValue,&f->value,4);memcpy(&w->_fadeAddValue,&f->step,4);memcpy(&w->_fadeLimitValue,&f->limit,4);
    w->_fadeSt0=f->direction;m->fade_updated=f->updated;m->fade_clock=f->clock;
}
/* Apply the FADESETs the Action2 host has started since the last call: the latest one wins (HIDE clears the fade, IN / OUT start one). */
static void model_fade_events(dw4_modelctrl *m)
{
    const dw4_action2_host *h=&m->clock;if(h->fade_event==m->fade_event_seen)return;
    m->fade_event_seen=h->fade_event;
    if(h->fade_kind=='H'){model_action_work(m)->_fadeSt0=0;return;}
    m->fade_in=h->fade_kind=='I';dw4_modelfade f;dw4_modelfade_start(&f,m->fade_in,h->fade_first_bits,h->fade_limit_bits,m->now);model_fade_write(m,&f);
}
static void model_fade_tick(dw4_modelctrl *m,int64_t now)
{
    beAction2InfoWork *w=model_action_work(m);if(!w->_fadeSt0)return;
    dw4_modelfade f={0};memcpy(&f.value,&w->_fadeValue,4);memcpy(&f.step,&w->_fadeAddValue,4);memcpy(&f.limit,&w->_fadeLimitValue,4);
    f.direction=w->_fadeSt0;f.updated=m->fade_updated;f.clock=m->fade_clock;dw4_modelfade_tick(&f,now);model_fade_write(m,&f);
}
static int model_program_load(dw4_modelctrl *m,const dw4_igb *g,uint32_t root)
{
    m->arena=dw4_session_arena();if(!m->arena)return -1;
    m->program=calloc(1,sizeof *m->program);if(!m->program)return -1;
    if(dw4_arena_pack_load_from(m->arena,DW4_REGION_PERSISTENT,g,&root,1,&m->program->pack,m->error,sizeof m->error))return -1;
    m->program->sequences=(int32_t)dw4_arena_pack_handle(&m->program->pack,root).off;
    if(!m->program->sequences || (size_t)al_count(m->arena,m->program->sequences)!=m->nseq)return -1;
    int32_t *rows=al_words(m->arena,m->program->sequences);
    for(size_t i=0;i<m->nseq;i++){
        const beModelCtrlData *d=rows[i]?DW4_ARENA_OBJ(m->arena,beModelCtrlData,al_handle(rows[i])):NULL;
        if(!d || (size_t)al_count(m->arena,d->_comList)!=m->seq[i].n)return -1;
        int32_t *commands=al_words(m->arena,d->_comList);
        for(size_t j=0;j<m->seq[i].n;j++)if(!commands[j])return -1;
    }
    return 0;
}
static beModelCtrlInfoWork *model_work(const dw4_modelctrl *m)
{return DW4_ARENA_OBJ(m->arena,beModelCtrlInfoWork,m->work);}
static int model_hitbox_count(const dw4_modelctrl *m)
{
    beModelCtrlSubCom *s=DW4_ARENA_OBJ(m->arena,beModelCtrlSubCom,al_handle(model_work(m)->_subCommand));int n=0;
    for(int i=0;i<al_count(m->arena,s->_comList);i++)if(dw4_modelsubcom_type(m->arena,al_handle(al_words(m->arena,s->_comList)[i]))==DW4_SC_HITBOX)n++;
    return n;
}
static int model_subcommands_clear(dw4_modelctrl *m,int type)
{
    if(m->subcommand_clearing){snprintf(m->error,sizeof m->error,"recursive model subcommand finish");return -1;}
    m->subcommand_clearing=1;int rc=dw4_modelsubcom_clear_events(m->arena,al_handle(model_work(m)->_subCommand),type,model_subcommand_event,m);
    m->subcommand_clearing=0;return rc;
}
static beBaseInfoRam *model_ram(const dw4_modelctrl *m)
{return DW4_ARENA_OBJ(m->arena,beBaseInfoRam,m->ram);}
static uint32_t model_float_bits(const float *f){uint32_t u;memcpy(&u,f,4);return u;}
static void model_float_store(float *f,uint32_t u){memcpy(f,&u,4);}
static float *model_position(const dw4_modelctrl *m)
{return (float *)(void *)(DW4_ARENA_OBJ(m->arena,beModelCtrlNode2,m->node)->_m+12);}
static beModelCtrlMoveObject *model_channel(const dw4_modelctrl *m,unsigned i)
{
    int32_t list=model_work(m)->_moveObjectList;
    return i<4?DW4_ARENA_OBJ(m->arena,beModelCtrlMoveObject,al_handle(al_words(m->arena,list)[i])):NULL;
}
/* The EE rule ABI is a transient bit-pattern projection. Copy only the
 * payload back; the recovered object's vtable and refcount remain intact. */
static void model_move_start(beModelCtrlMoveObject *d,uint32_t value,uint32_t frame,uint32_t time,int mode)
{dw4_npc_motion s;memcpy(&s,d,sizeof s);dw4_npc_motion_start(&s,value,frame,time,mode);memcpy(&d->_isRun,&s.active,sizeof *d - offsetof(beModelCtrlMoveObject,_isRun));}
static void model_move_expire(beModelCtrlMoveObject *d)
{dw4_npc_motion s;memcpy(&s,d,sizeof s);dw4_npc_motion_expire(&s);memcpy(&d->_isRun,&s.active,sizeof *d - offsetof(beModelCtrlMoveObject,_isRun));}
static uint32_t model_move_tick(beModelCtrlMoveObject *d,uint32_t delta)
{dw4_npc_motion s;memcpy(&s,d,sizeof s);uint32_t v=dw4_npc_motion_tick(&s,delta);memcpy(&d->_isRun,&s.active,sizeof *d - offsetof(beModelCtrlMoveObject,_isRun));return v;}
static beModelCtrlInfoAI *model_ai(const dw4_modelctrl *m)
{return DW4_ARENA_OBJ(m->arena,beModelCtrlInfoAI,al_handle(model_work(m)->_aI));}
static float *model_ai_target(const dw4_modelctrl *m){return (float *)(void *)model_ai(m)->_worldPos;}
static beBaseInfoRamTimer *model_ai_timer(const dw4_modelctrl *m)
{return DW4_ARENA_OBJ(m->arena,beBaseInfoRamTimer,m->ai_timer);}
static int model_ai_timed(const dw4_modelctrl *m){return model_ai_timer(m)->_name!=0;}
static int64_t model_ai_start(const dw4_modelctrl *m){return -model_ai_timer(m)->_timeBias;}
static int64_t model_ai_duration(const dw4_modelctrl *m){return model_ai_timer(m)->_endTime;}
static void model_timers_publish(dw4_modelctrl *m)
{
    igDataList *l=al_list(m->arena,model_ram(m)->_dataList);
    int32_t *v=dw4_arena_at(m->arena,al_handle(l->_data),(uint32_t)l->_capacity*4);int n=1;
    if(m->ai_timer.off && model_ai_timed(m))v[n++]=(int32_t)m->ai_timer.off;
    for(int i=0;i<DW4_STATUS_TIMER_SLOTS;i++)if(m->status_timer[i].off && DW4_ARENA_OBJ(m->arena,beBaseInfoRamTimer,m->status_timer[i])->_name)v[n++]=(int32_t)m->status_timer[i].off;
    for(int i=n;i<l->_capacity;i++)v[i]=0;
    l->_count=n;
}
static void model_ai_timer_clear(dw4_modelctrl *m)
{model_ai_timer(m)->_name=0;model_timers_publish(m);}
static void model_ai_timer_arm(dw4_modelctrl *m,int64_t start,int64_t duration)
{
    beBaseInfoRamTimer *t=model_ai_timer(m);t->_timeBias=-start;t->_endTime=duration;t->_svWorldTime=m->now;t->_name=m->ai_timer_name;t->_keikaFrame=1;model_timers_publish(m);
}
static int model_ai_sequence(dw4_modelctrl *m,const char *name)
{
    int32_t h=al_string(m->arena,name);if(!h)return -1;
    al_free(m->arena,model_ai(m)->_seqName);model_ai(m)->_seqName=h;return 0;
}
static beModelCtrlPDMOVE *model_walk(const dw4_modelctrl *m,int move)
{return DW4_ARENA_OBJ(m->arena,beModelCtrlPDMOVE,al_handle(al_words(m->arena,model_work(m)->_pdMoveDataList)[move?1:0]));}
static const char *model_label(const dw4_modelctrl *m,size_t i)
{return al_text(m->arena,al_words(m->arena,model_work(m)->_labelNameList)[i]);}
static int model_current(const dw4_modelctrl *m)
{
    const char *name=al_text(m->arena,model_work(m)->_seqCodeName);
    for(size_t i=0;name && i<m->nseq;i++)if(!strcmp(name,m->seq[i].name))return (int)i;
    return 0;
}
static const char *model_wait(const dw4_modelctrl *m){return al_text(m->arena,model_work(m)->_wCheckName);}
static void model_wait_clear(dw4_modelctrl *m){al_free(m->arena,model_work(m)->_wCheckName);model_work(m)->_wCheckName=0;}
static int model_wait_set(dw4_modelctrl *m,const char *name)
{
    int32_t h=al_string(m->arena,name);if(!h){snprintf(m->error,sizeof m->error,"model wait allocation failed");return -1;}
    model_wait_clear(m);model_work(m)->_wCheckName=h;return 0;
}
static int model_record_init(dw4_modelctrl *m)
{
    if(m->nseq>INT32_MAX)return -1;
    m->arena=dw4_session_arena();if(!m->arena)return -1;
    const char *classes[]={"beBaseInfoRam","beModelCtrlInfoRamData",m->player_kind?"beNDMWMdlPlayerInfoWork":m->enemy_kind?"beNDMWMdlEnemyInfoWork":"beModelCtrlInfoWork","beModelCtrlNode2"};
    dw4_handle *fields[]={&m->ram,&m->data,&m->work,&m->node};
    for(unsigned i=0;i<4;i++){const dw4_metaobject *mo=dw4_metaobject_find(classes[i]);*fields[i]=dw4_arena_object_new(m->arena,DW4_REGION_PERSISTENT,mo->vtable);if(!fields[i]->off)return -1;}
    beModelCtrlInfoRamData *d=DW4_ARENA_OBJ(m->arena,beModelCtrlInfoRamData,m->data);
    d->_name=al_string(m->arena,"MODEL");d->_node=(int32_t)m->node.off;d->_work=(int32_t)m->work.off;
    int32_t h=(int32_t)m->data.off;model_ram(m)->_dataList=al_new(m->arena,"igNamedObjectList",4,1,&h);
    beModelCtrlNode2 *node=DW4_ARENA_OBJ(m->arena,beModelCtrlNode2,m->node);float identity[16]={0};identity[0]=identity[5]=identity[10]=identity[15]=1;memcpy(node->_m,identity,sizeof identity);
    beModelCtrlInfoWork *w=model_work(m);w->_recNo=-1;
    const dw4_metaobject *number=dw4_metaobject_find("beDataObjInt");
    w->_hp=(int32_t)dw4_arena_object_new(m->arena,DW4_REGION_PERSISTENT,number->vtable).off;
    w->_mHp=(int32_t)dw4_arena_object_new(m->arena,DW4_REGION_PERSISTENT,number->vtable).off;
    if(!w->_hp || !w->_mHp)return -1;
    w->_labelSeqList=al_new(m->arena,"igStringRefList",4,(int)m->nseq,NULL);
    w->_labelNameList=al_new(m->arena,"igStringRefList",4,(int)m->nseq,NULL);
    w->_labelOffsetList=al_new(m->arena,"igIntList",4,(int)m->nseq,NULL);
    w->_moveObjectList=al_new(m->arena,"beModelCtrlMoveObjectList",4,4,NULL);
    if(!d->_name || !model_ram(m)->_dataList || !w->_labelSeqList || !w->_labelNameList || !w->_labelOffsetList || !w->_moveObjectList)return -1;
    for(size_t i=0;i<m->nseq;i++)if(!(al_words(m->arena,w->_labelSeqList)[i]=al_string(m->arena,m->seq[i].name)))return -1;
    const dw4_metaobject *move=dw4_metaobject_find("beModelCtrlMoveObject");
    for(int i=0;i<4;i++){dw4_handle c=dw4_arena_object_new(m->arena,DW4_REGION_PERSISTENT,move->vtable);if(!c.off)return -1;al_words(m->arena,w->_moveObjectList)[i]=(int32_t)c.off;}
    const dw4_metaobject *ai=dw4_metaobject_find("beModelCtrlInfoAI"),*timer=dw4_metaobject_find("beBaseInfoRamTimer"),*walk=dw4_metaobject_find("beModelCtrlPDMOVE");
    w->_aI=(int32_t)dw4_arena_object_new(m->arena,DW4_REGION_PERSISTENT,ai->vtable).off;
    m->ai_timer=dw4_arena_object_new(m->arena,DW4_REGION_PERSISTENT,timer->vtable);m->ai_timer_name=al_string(m->arena,"AITIMER");
    w->_pdMoveDataList=al_new(m->arena,"igNamedObjectList",4,2,NULL);
    if(!w->_aI || !m->ai_timer.off || !m->ai_timer_name || !w->_pdMoveDataList)return -1;
    model_ai(m)->_mapNo=-1;model_ai_timer(m)->_timeScale=1;
    for(int i=0;i<2;i++){
        dw4_handle h=dw4_arena_object_new(m->arena,DW4_REGION_PERSISTENT,walk->vtable);if(!h.off)return -1;
        al_words(m->arena,w->_pdMoveDataList)[i]=(int32_t)h.off;
        beModelCtrlPDMOVE *d=DW4_ARENA_OBJ(m->arena,beModelCtrlPDMOVE,h);d->_name=al_string(m->arena,i?"Move":"Stop");if(!d->_name)return -1;
    }
    m->erase_name=al_string(m->arena,"SQ_ERAS");
    w->_subCommand=(int32_t)dw4_modelsubcom_new(m->arena).off;
    return w->_subCommand && m->erase_name?0:-1;
}
static beNDMWMdlPEBaseInfoWork *status_work(const dw4_modelctrl *m)
{return DW4_ARENA_OBJ(m->arena,beNDMWMdlPEBaseInfoWork,m->work);}
static int32_t *model_list_storage(const dw4_modelctrl *m,int32_t h,uint32_t width)
{
    igDataList *l=al_list(m->arena,h);return l && l->_capacity?dw4_arena_at(m->arena,al_handle(l->_data),(uint32_t)l->_capacity*width):NULL;
}
static int status_record_init(dw4_modelctrl *m)
{
    if(!(m->enemy_kind || m->player_kind))return 0;
    beNDMWMdlPEBaseInfoWork *w=status_work(m);
    w->_timerList=al_new(m->arena,"igIntList",4,DW4_STATUS_TIMER_SLOTS,NULL);
    w->_isFirstList=al_new(m->arena,"igBoolList",1,DW4_STATUS_FRAME,NULL);
    w->_dispRamNoList=al_new(m->arena,"igIntList",4,DW4_STATUS_TIMER_SLOTS,NULL);
    w->_dispPosNoList=al_new(m->arena,"igIntList",4,DW4_STATUS_TIMER_SLOTS,NULL);
    w->_downDataList=al_new(m->arena,"igIntList",4,DW4_STATUS_DOWN_SLOTS,NULL);
    w->_upDataList=al_new(m->arena,"igIntList",4,DW4_STATUS_UP_SLOTS,NULL);
    if(!w->_timerList || !w->_isFirstList || !w->_dispRamNoList || !w->_dispPosNoList || !w->_downDataList || !w->_upDataList)return -1;
    const dw4_metaobject *mo=dw4_metaobject_find("beBaseInfoRamTimer");
    static const char *const names[]={"POISON","ATKDOWN","POWDOWN","BIND","REFRACT","SPEEDUP","POWERUP","METAL","SLEEP","STUN","RARE","FRAME"};
    for(int i=0;i<DW4_STATUS_TIMER_SLOTS;i++){
        m->status_timer[i]=dw4_arena_object_new(m->arena,DW4_REGION_PERSISTENT,mo->vtable);
        m->status_name[i]=al_string(m->arena,names[i]);if(!m->status_timer[i].off || !m->status_name[i])return -1;
        DW4_ARENA_OBJ(m->arena,beBaseInfoRamTimer,m->status_timer[i])->_timeScale=1;
    }
    return 0;
}
/* The existing native nanosecond sampler remains a clock service. All rule
 * values are reconstructed from the recovered Work/list/timer instances. */
static dw4_status status_record_read(const dw4_modelctrl *m)
{
    dw4_status s={0};s.lists_dirty=m->status_snapshot.lists_dirty;const beNDMWMdlPEBaseInfoWork *w=status_work(m);
    s.is_player=w->_isPlayer;s.ready=w->_isOnCtrl;s.poison_damage=w->_poisonDamage;s.poison_endurance=w->_poisonEndurance;
    memcpy(s.timer,al_words(m->arena,w->_timerList),sizeof s.timer);
    memset(s.first,0,sizeof s.first);memcpy(s.first,al_data(m->arena,w->_isFirstList,1),DW4_STATUS_FRAME);
    memcpy(s.icon_position,al_words(m->arena,w->_dispPosNoList),sizeof s.icon_position);
    const int32_t *icons=al_words(m->arena,w->_dispRamNoList);for(int i=0;i<DW4_STATUS_TIMER_SLOTS;i++)s.icon_shown[i]=(int8_t)(icons[i]!=-1);
    int nd=al_count(m->arena,w->_downDataList),nu=al_count(m->arena,w->_upDataList);
    s.has_down=nd>0;s.has_up=nu>0;s.down_count=nd?nd:s.is_player?DW4_STATUS_DOWN_SLOTS:DW4_STATUS_DOWN_ENEMY;
    s.up_count=nu?nu:s.is_player?DW4_STATUS_UP_SLOTS:DW4_STATUS_UP_ENEMY;
    memset(s.down,0,sizeof s.down);memset(s.up,0,sizeof s.up);
    if(nd)memcpy(s.down,al_words(m->arena,w->_downDataList),(size_t)nd*4);
    if(nu)memcpy(s.up,al_words(m->arena,w->_upDataList),(size_t)nu*4);
    s.clock_ns=m->status_elapsed;
    for(int i=0;i<DW4_STATUS_TIMER_SLOTS;i++){
        const beBaseInfoRamTimer *t=DW4_ARENA_OBJ(m->arena,beBaseInfoRamTimer,m->status_timer[i]);
        s.named[i].armed=t->_name!=0;s.named[i].start_ns=t->_svWorldTime;s.named[i].duration_ns=t->_endTime;
    }
    return s;
}
static void status_record_write(dw4_modelctrl *m,const dw4_status *s)
{
    beNDMWMdlPEBaseInfoWork *w=status_work(m);w->_isPlayer=s->is_player;
    w->_poisonDamage=s->poison_damage;w->_poisonEndurance=s->poison_endurance;
    memcpy(al_words(m->arena,w->_timerList),s->timer,sizeof s->timer);
    memcpy(al_data(m->arena,w->_isFirstList,1),s->first,DW4_STATUS_FRAME);
    memcpy(al_words(m->arena,w->_dispPosNoList),s->icon_position,sizeof s->icon_position);
    int32_t *icons=al_words(m->arena,w->_dispRamNoList);for(int i=0;i<DW4_STATUS_TIMER_SLOTS;i++)icons[i]=s->icon_shown[i]?0:-1;
    igDataList *down=al_list(m->arena,w->_downDataList),*up=al_list(m->arena,w->_upDataList);
    down->_count=s->has_down?s->down_count:0;up->_count=s->has_up?s->up_count:0;
    if(down->_count)memcpy(model_list_storage(m,w->_downDataList,4),s->down,(size_t)down->_count*4);
    if(up->_count)memcpy(model_list_storage(m,w->_upDataList,4),s->up,(size_t)up->_count*4);
    for(int i=0;i<DW4_STATUS_TIMER_SLOTS;i++){
        beBaseInfoRamTimer *t=DW4_ARENA_OBJ(m->arena,beBaseInfoRamTimer,m->status_timer[i]);
        t->_name=s->named[i].armed?m->status_name[i]:0;t->_svWorldTime=s->named[i].start_ns;t->_endTime=s->named[i].duration_ns;
    }
    model_timers_publish(m);
    m->status_elapsed=s->clock_ns;m->status_snapshot=*s;
}
static void status_record_close(dw4_modelctrl *m)
{
    if(!(m->enemy_kind || m->player_kind) || !m->work.off)return;
    beNDMWMdlPEBaseInfoWork *w=status_work(m);
    int32_t *fields[]={&w->_timerList,&w->_isFirstList,&w->_dispRamNoList,&w->_dispPosNoList,&w->_downDataList,&w->_upDataList};
    for(int i=0;i<6;i++)al_drop(m->arena,fields[i]);
    for(int i=0;i<DW4_STATUS_TIMER_SLOTS;i++){al_free(m->arena,m->status_name[i]);if(m->status_timer[i].off)dw4_arena_object_release(m->arena,m->status_timer[i]);}
}
static void model_record_close(dw4_modelctrl *m)
{
    status_record_close(m);
    if(m->work.off){beModelCtrlInfoWork *w=model_work(m);
        int n=al_count(m->arena,w->_moveObjectList);int32_t *v=al_words(m->arena,w->_moveObjectList);
        for(int i=0;i<n;i++)if(v[i])dw4_arena_object_release(m->arena,al_handle(v[i]));
        al_drop(m->arena,&w->_moveObjectList);model_wait_clear(m);al_free(m->arena,w->_hitParentName);al_free(m->arena,m->erase_name);
        dw4_modelsubcom_close(m->arena,al_handle(w->_subCommand));
        if(w->_aI){al_free(m->arena,model_ai(m)->_seqName);dw4_arena_object_release(m->arena,al_handle(w->_aI));}
        int nw=al_count(m->arena,w->_pdMoveDataList);int32_t *walk=al_words(m->arena,w->_pdMoveDataList);
        for(int i=0;i<nw;i++)if(walk[i]){beModelCtrlPDMOVE *d=DW4_ARENA_OBJ(m->arena,beModelCtrlPDMOVE,al_handle(walk[i]));al_free(m->arena,d->_name);dw4_arena_object_release(m->arena,al_handle(walk[i]));}
        al_drop(m->arena,&w->_pdMoveDataList);al_free(m->arena,m->ai_timer_name);if(m->ai_timer.off)dw4_arena_object_release(m->arena,m->ai_timer);
        if(w->_hp)dw4_arena_object_release(m->arena,al_handle(w->_hp));
        if(w->_mHp)dw4_arena_object_release(m->arena,al_handle(w->_mHp));
        al_strings_drop(m->arena,&w->_labelSeqList);al_strings_drop(m->arena,&w->_labelNameList);al_drop(m->arena,&w->_labelOffsetList);
        dw4_arena_object_release(m->arena,m->work);}
    if(m->data.off){beModelCtrlInfoRamData *d=DW4_ARENA_OBJ(m->arena,beModelCtrlInfoRamData,m->data);al_free(m->arena,d->_name);dw4_arena_object_release(m->arena,m->data);}
    if(m->ram.off){al_drop(m->arena,&model_ram(m)->_dataList);dw4_arena_object_release(m->arena,m->ram);}
    if(m->node.off)dw4_arena_object_release(m->arena,m->node);
}
static int32_t *model_hp(const dw4_modelctrl *m,int maximum)
{return &DW4_ARENA_OBJ(m->arena,beDataObjInt,al_handle(maximum?model_work(m)->_mHp:model_work(m)->_hp))->_data;}
/* Legacy callback state is an input/output projection. Only edits since its
 * last publication are imported, so an unchanged projection cannot overwrite
 * a native arena write. Native callbacks operate on fresh scalar snapshots. */
static void model_bridge_pull(dw4_modelctrl *m)
{
    if(!m || !m->model)return;
    if(m->model->hp!=m->bridge_last.hp)*model_hp(m,0)=m->model->hp;
    if(m->model->max_hp!=m->bridge_last.max_hp)*model_hp(m,1)=m->model->max_hp;
    if(m->model->rec_no!=m->bridge_last.rec_no)model_work(m)->_recNo=m->model->rec_no;
    if(m->model->ram_no!=m->bridge_last.ram_no)model_ram(m)->_ramNo=m->model->ram_no;
    m->bridge_last=*m->model;
}
static void model_bridge_push(dw4_modelctrl *m)
{
    if(!m || !m->model)return;
    m->model->hp=*model_hp(m,0);m->model->max_hp=*model_hp(m,1);
    m->model->rec_no=model_work(m)->_recNo;m->model->ram_no=model_ram(m)->_ramNo;m->bridge_last=*m->model;
}
static dw4_script_model model_script_snapshot(dw4_modelctrl *m)
{model_bridge_push(m);return *m->model;}
static void model_pose_write(dw4_modelctrl *m)
{
    dw4_modelctrl_actor actor;float matrix[16];dw4_modelctrl_actor_state(m,&actor);dw4_modelctrl_actor_matrix(&actor,matrix);
    memcpy(DW4_ARENA_OBJ(m->arena,beModelCtrlNode2,m->node)->_m,matrix,sizeof matrix);
    memcpy(m->pose.matrix_rotation,m->pose.rotation,12);m->pose.matrix_valid=1;
}
static void model_move_unlock(dw4_modelctrl *m)
{
    beModelCtrlInfoWork *w=model_work(m);if(!w->_isPosLock)return;
    const beModelCtrlNode2 *n=DW4_ARENA_OBJ(m->arena,beModelCtrlNode2,m->node);
    uint32_t x=(uint32_t)n->_m[8],z=(uint32_t)n->_m[10];
    uint32_t angle=dw4_model_ai_direction(x,z,0),degrees=ee_f32_mul(angle,0x42652ee1);
    w->_direction[1]=w->_targetDirection[1]=angle;memcpy(m->pose.rotation+1,&degrees,4);
    w->_isPosLock=0;m->pose.matrix_valid=0;
}
static void model_pose_publish(dw4_modelctrl *m)
{
    if(!m || !m->node.off || !model_ram(m)->_isRun || model_work(m)->_isPosLock ||
       (m->pose.matrix_valid && !memcmp(m->pose.rotation,m->pose.matrix_rotation,12)))return;
    model_pose_write(m);
}
static uint32_t slot(const dw4_igb_record *r,unsigned ordinal) {
    for(unsigned i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ordinal)return r->values[i].raw;
    return UINT32_MAX;
}
static const char *string_slot(const dw4_igb_record *r,unsigned ordinal) {
    for(unsigned i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ordinal)return r->values[i].str;
    return NULL;
}
/* The work a model keeps for the status manager exists for enemies and players; objects, NPCs and bullets have none. */
static void status_reset(dw4_modelctrl *m)
{
    m->has_status=m->enemy_kind || m->player_kind;
    m->status_clock_valid=0;
    if(m->has_status){dw4_status s;dw4_status_init(&s,m->player_kind);status_record_write(m,&s);}
}
static int record(const dw4_igb *g,uint32_t id,dw4_igb_record *r) {
    return id<g->table_n && g->id_kind[id]==2 && dw4_igb_decode(g,g->id_off[id],r);
}
static const uint8_t *list(const dw4_igb *g,uint32_t id,size_t *n) {
    dw4_igb_record r={0};uint32_t bytes=0;
    static const uint8_t empty[4]={0};
    if(id==UINT32_MAX){*n=0;return empty;}
    if(!record(g,id,&r))return NULL;
    size_t type_len=strlen(r.class_name);
    if(type_len<4 || strcmp(r.class_name+type_len-4,"List")){dw4_igb_record_free(&r);return NULL;}
    uint32_t count=slot(&r,2);
    if(count==0){*n=0;dw4_igb_record_free(&r);return empty;}
    const uint8_t *p=dw4_igb_block(g,slot(&r,4),&bytes);
    dw4_igb_record_free(&r);
    if(!p || bytes%4 || count>bytes/4)return NULL;
    *n=count;return p;
}
static uint32_t item(const uint8_t *p,size_t i) { uint32_t id;memcpy(&id,p+4*i,4);return id; }
/* Retail MOVE command names select the local translation channel and mode. */
static int move_mode(const char *name,int *channel) {
    static const char *names[]={"Move","Stop","Push","Back","Jump","Fall"};
    static const int modes[]={0,2,4,5,4,1},channels[]={2,2,2,2,1,1};
    for(unsigned i=0;i<6;i++)if(!strcmp(name,names[i])){*channel=channels[i];return modes[i];}
    return -1;
}
static int moveex_mode(const char *name,int *channel) {
    if(strlen(name)!=6 || (name[2]!='P' && name[2]!='M'))return -1;
    if(name[0]=='T' && name[1]>='X' && name[1]<='Z')*channel=name[1]-'X';
    else if(name[0]=='R' && name[1]=='Y')*channel=3;
    else return -1;
    /* FUN_00393260 switches on name[3] alone ('A' 0, 'D' 2, 'T' 4); the last two letters are never read (Mammothmon's TZMTGD is a TMP move). */
    int mode=name[3]=='A'?0:name[3]=='D'?2:name[3]=='T'?4:-1;
    return mode<0?-1:mode+(name[2]=='M');
}
static int hit_data(dw4_modelctrl *m,const dw4_igb *g,uint32_t id)
{
    if(id==UINT32_MAX)return 0;
    dw4_igb_record r={0};if(!record(g,id,&r))return -1;
    m->hit_player_talk=slot(&r,7)==UINT32_MAX?0:(uint8_t)slot(&r,7);
    m->hit_player_bullet=slot(&r,4)==UINT32_MAX?0:(uint8_t)slot(&r,4);m->hit_enemy_bullet=slot(&r,5)==UINT32_MAX?0:(uint8_t)slot(&r,5);uint32_t boxes=slot(&r,6);dw4_igb_record_free(&r);
    size_t count;const uint8_t *rows=list(g,boxes,&count);
    if(!rows || count>SIZE_MAX/(6*sizeof(float)))return -1;
    if(!count)return 0;
    m->hit_boxes=calloc(count,6*sizeof(float));if(!m->hit_boxes)return -1;m->nhit_boxes=count;
    for(size_t i=0;i<count;i++) {
        if(!record(g,item(rows,i),&r))return -1;
        int valid=!strcmp(r.class_name,"igAABox");unsigned vectors=0;
        for(unsigned v=0;v<r.nvalues;v++)if(r.values[v].ordinal==2 || r.values[v].ordinal==3) {
            if(r.values[v].vsize<12 || r.values[v].voff>g->size || g->size-r.values[v].voff<12){valid=0;break;}
            float *to=m->hit_boxes+6*i+3*(r.values[v].ordinal-2);memcpy(to,g->data+r.values[v].voff,12);vectors++;
            for(unsigned k=0;k<3;k++)if(!isfinite(to[k]))valid=0;
        }
        dw4_igb_record_free(&r);if(!valid || vectors!=2)return -1;
    }
    return 0;
}
/* The model's beHitLandDelivInfo lists its beHitLandDelivInfoRam records (ordinals 13..15: _halfWidth, _upRange, _downRange; 12: _checkFlag). The retail reflection defaults
 * are 3/4/4; a pack record overrides them (Mammothmon's has _halfWidth 10). All records of one info are read as the first: none of the shipped lists differs. */
static int land_data(dw4_modelctrl *m,const dw4_igb *g,uint32_t ram_list)
{
    m->land[0]=3;m->land[1]=4;m->land[2]=4;m->land[3]=3;
    if(ram_list==UINT32_MAX)return 0;
    size_t count=0;const uint8_t *rows=list(g,ram_list,&count);if(!rows)return -1;
    if(!count)return 0;
    dw4_igb_record r={0};if(!record(g,item(rows,0),&r))return -1;
    int valid=!strcmp(r.class_name,"beHitLandDelivInfoRam");float v[3];
    for(unsigned k=0;k<3;k++){uint32_t raw=slot(&r,13+k);memcpy(&v[k],&raw,4);valid&=raw!=UINT32_MAX && isfinite(v[k]) && v[k]>=0;}
    uint32_t flags=slot(&r,12);   /* _checkFlag: which wall infos the model collides with (dw4_hitland_info_applies) */
    dw4_igb_record_free(&r);if(!valid)return -1;
    memcpy(m->land,v,sizeof v);if(flags!=UINT32_MAX && flags<=0xFFFFu)m->land[3]=(float)flags;return 0;
}
static int find_seq(const dw4_modelctrl *m,const char *name) {
    for(size_t i=0;i<m->nseq;i++)if(!strcmp(m->seq[i].name,name))return (int)i;
    return -1;
}
static int find_action(const dw4_modelctrl *m,const char *name) {
    for(size_t i=0;i<m->naction;i++)if(!strcmp(m->action[i].name,name))return (int)i;
    return -1;
}
static int sequences(dw4_modelctrl *m,const dw4_igb *g,uint32_t id) {
    size_t n=0;const uint8_t *p=list(g,id,&n);if(!p)return -1;
    m->seq=calloc(n?n:1,sizeof(*m->seq));if(!m->seq)return -1;m->nseq=n;
    for(size_t i=0;i<n;i++) {
        dw4_igb_record r={0};struct sequence *s=m->seq+i;
        if(!record(g,item(p,i),&r))return -1;
        s->name=r.name;const uint8_t *commands=list(g,slot(&r,3),&s->n);
        dw4_igb_record_free(&r);if(!s->name || !commands)return -1;
        s->cmd=calloc(s->n?s->n:1,sizeof(*s->cmd));if(!s->cmd)return -1;
        for(size_t j=0;j<s->n;j++) {
            if(!record(g,item(commands,j),&r))return -1;
            char *type=malloc(strlen(r.class_name)+1);
            if(type)strcpy(type,r.class_name);
            s->cmd[j]=(struct command){.type=type,.name=r.name,.target=string_slot(&r,3),.bone=string_slot(&r,4)};
            for(unsigned k=0;k<6;k++)s->cmd[j].v[k]=slot(&r,k+3);
            /* beModelCtrlHITBOX: _kind, _start, _length are scalars (v[0..2]); _offset and _boxSize are inline vectors (ordinals 6, 7). */
            if(!strcmp(r.class_name,"beModelCtrlHITBOX"))for(unsigned k=0;k<r.nvalues;k++)
                if((r.values[k].ordinal==6 || r.values[k].ordinal==7) && r.values[k].vsize>=12 && r.values[k].voff<=g->size && g->size-r.values[k].voff>=12)
                    memcpy(s->cmd[j].box+3*(r.values[k].ordinal-6),g->data+r.values[k].voff,12);
            dw4_igb_record_free(&r);
            if(!s->cmd[j].name || !s->cmd[j].type)return -1;
        }
    }
    return 0;
}
static int durations(dw4_modelctrl *m,const dw4_igb *g,uint32_t id)
{
    if(id==UINT32_MAX)return 0;
    dw4_igb_record r={0};if(!record(g,id,&r))return -1;
    int valid=!strcmp(r.class_name,"igAnimationDatabase");uint32_t animations=slot(&r,6);
    dw4_igb_record_free(&r);if(!valid)return -1;
    size_t count;const uint8_t *ids=list(g,animations,&count);if(!ids)return -1;
    m->duration=calloc(count?count:1,sizeof *m->duration);if(!m->duration)return -1;
    for(size_t i=0;i<count;i++) {
        if(!record(g,item(ids,i),&r))return -1;
        int64_t ns=0;for(unsigned k=0;k<r.nvalues;k++)if(r.values[k].ordinal==9 && r.values[k].vsize==8)
            memcpy(&ns,g->data+r.values[k].voff,8);
        valid=!strcmp(r.class_name,"igAnimation") && r.name && ns>0;
        if(valid)m->duration[m->nduration++]=(struct motion_duration){r.name,ns};
        dw4_igb_record_free(&r);if(!valid)return -1;
    }
    return 0;
}
static int actions(dw4_modelctrl *m,const dw4_igb *g,uint32_t id) {
    size_t n=0;const uint8_t *p=list(g,id,&n);if(!p)return -1;
    m->action=calloc(n?n:1,sizeof(*m->action));if(!m->action)return -1;m->naction=n;
    for(size_t i=0;i<n;i++) {
        dw4_igb_record r={0};struct action *a=m->action+i;
        if(!record(g,item(p,i),&r))return -1;
        a->name=r.name;const uint8_t *commands=list(g,slot(&r,3),&a->n);
        dw4_igb_record_free(&r);if(!a->name || !commands)return -1;
        a->cmd=calloc(a->n?a->n:1,sizeof(*a->cmd));if(!a->cmd)return -1;
        /* The Action2 host holds DW4_A2_MAX_COMPONENTS components; the longest authored action (the FLASH1 blink-outs) has 24. */
        a->supported=a->n<=DW4_A2_MAX_COMPONENTS;
        for(size_t j=0;j<a->n;j++) {
            if(!record(g,item(commands,j),&r))return -1;
            dw4_action2_component *c=a->cmd+j;
            c->name=r.name?r.name:"";c->first=slot(&r,3);c->last=slot(&r,4);
            c->loop=string_slot(&r,5);
            if(!c->loop)c->loop="";
            if(strlen(c->name)>=32 || strlen(c->loop)>=32)a->supported=0;
            if(!strcmp(r.class_name,"beAction2JOINTSET")) {
                c->kind=DW4_A2_JOINTSET;float first,last;
                memcpy(&first,&c->first,4);memcpy(&last,&c->last,4);
                if(!c->loop || (strcmp(c->loop,"OS") && strcmp(c->loop,"LP")) ||
                   !isfinite(first) || !isfinite(last) || first<0 || last<first || last>10000 ||
                   (!strcmp(c->loop,"LP") && first==last))a->supported=0;
            } else if(!strcmp(r.class_name,"beAction2WAITCHECK")) {
                c->kind=DW4_A2_WAITCHECK;float frames;memcpy(&frames,&c->first,4);
                /* beAction2WAITCHECK_Start dispatches on the first letter: "R..." (RNDS stores the shared rhythm, RNDE / R00S-style names draw a random wait,
                 * src/action2host.c) is the random wait the Mammothmon walk uses (RUNN02: RNDS 420, RNDE 600 frames). */
                if((strcmp(c->name,"Frame") && strcmp(c->name,"Joint") && strcmp(c->name,"Motion") && !(c->name[0]=='R' && strlen(c->name)>=4)) ||
                   !isfinite(frames) || frames<0 || frames>10000)a->supported=0;
            } else if(!strcmp(r.class_name,"beAction2FADESET")) {
                c->kind=DW4_A2_FADESET;float frames;memcpy(&frames,&c->first,4);
                /* The host (0x376930) tells the kinds apart by the first letter; the player packs' revive step REVE*1 spells the hide "HID". */
                if((strcmp(c->name,"IN") && strcmp(c->name,"OUT") && strcmp(c->name,"HIDE") && strcmp(c->name,"HID")) ||
                   !isfinite(frames) || frames<0 || frames>10000)a->supported=0;
            } else if(!strcmp(r.class_name,"beAction2FLASHSET")) {
                /* The damage blink: presentation only, never gates the program (not given to the Action2 host). */
                c->kind=5;
            } else if(!strcmp(r.class_name,"beAction2MOTIONSET")) {
                /* Arrival motions loop and never gate the component cursor.
                 * Preserve playback separately from subsequent Frame actions. */
                c->kind=4;c->loop=string_slot(&r,5);
                /* beAction2MOTIONSET_Start reads only loopMode[0] == 'L' (a loop, playMode 3); every other string, IP included, plays once like OS. */
                if(!c->loop || (strcmp(c->loop,"LP") && strcmp(c->loop,"OS") && strcmp(c->loop,"IP")) || (string_slot(&r,3) && *string_slot(&r,3) &&
                   strcmp(string_slot(&r,3),"RR") && strcmp(string_slot(&r,3),"RS")))a->supported=0;   /* RR and RS are treated alike (the difference is not recovered) */   /* the blend-mode string may be absent (n_leomon action01) */
                float blend;memcpy(&blend,&c->last,4);
                if(getenv("DW4_ACT_DEBUG"))fprintf(stderr,"motionset %s loop %s s3 %s blend %g sup %d\n",c->name,c->loop?c->loop:"(null)",string_slot(&r,3)?string_slot(&r,3):"(null)",blend,a->supported);
                if(!isfinite(blend) || blend<0 || blend>10000)a->supported=0;
                for(size_t k=0;j<DW4_A2_MAX_COMPONENTS && k<m->nduration;k++)if(!strcmp(c->name,m->duration[k].name)){a->duration[j]=m->duration[k].ns;break;}
                if(j>=DW4_A2_MAX_COMPONENTS)a->supported=0;
                /* A motion the model's animation database does not hold plays nothing (the program continues): stagGF03's n_leomon KYRO01 names action01. */
                else if(a->duration[j]<=0)c->kind=6;
            } else a->supported=0;
            dw4_igb_record_free(&r);
        }
    }
    return 0;
}
static int maps(dw4_modelctrl *m,const dw4_igb *g,uint32_t id) {
    size_t n;const uint8_t *p=list(g,id,&n);if(!p)return -1;
    m->map=calloc(n?n:1,sizeof(*m->map));if(!m->map)return -1;m->nmap=n;
    for(size_t i=0;i<n;i++) {
        dw4_igb_record r={0};if(!record(g,item(p,i),&r))return -1;
        struct aimap *a=m->map+i;
        int valid=!strcmp(r.class_name,"beModelCtrlAIMap");
        a->name=r.name;a->target_type=string_slot(&r,11);a->rot_limit=slot(&r,6);
        for(unsigned j=0;j<3;j++)a->bounds[j]=slot(&r,j+3);
        for(unsigned z=0;z<4;z++) {
            const uint8_t *rows=list(g,slot(&r,z+7),&a->count[z]);
            if(!rows){dw4_igb_record_free(&r);return -1;}
            a->choices[z]=calloc(a->count[z]?a->count[z]:1,sizeof(*a->choices[z]));
            if(!a->choices[z]){dw4_igb_record_free(&r);return -1;}
            for(size_t k=0;k<a->count[z];k++) {
                dw4_igb_record choice={0};
                if(!record(g,item(rows,k),&choice)){dw4_igb_record_free(&r);return -1;}
                a->choices[z][k]=(dw4_model_ai_choice){choice.name,slot(&choice,3),slot(&choice,4),(int32_t)slot(&choice,5)};
                int ok=!strcmp(choice.class_name,"beModelCtrlAIData") && choice.name;
                dw4_igb_record_free(&choice);if(!ok){dw4_igb_record_free(&r);return -1;}
            }
        }
        dw4_igb_record_free(&r);if(!valid || !a->name || !a->target_type)return -1;
    }
    return 0;
}
static int find_map(const dw4_modelctrl *m,const char *name) {
    for(size_t i=0;i<m->nmap;i++)if(!strcmp(m->map[i].name,name))return (int)i;
    return -1;
}
/* `borrowed` is an already opened pack with its reference tables built (read only here); NULL opens `blob` privately.
 * Re-opening and re-indexing the whole pack per model made every controller cost 10-14 ms regardless of its size. */
static dw4_modelctrl *open_model(const uint8_t *blob,size_t size,const char *name,uint32_t info,const dw4_igb *borrowed) {
    dw4_igb own={0};dw4_igb *gp=borrowed?(dw4_igb *)borrowed:&own;dw4_modelctrl *m=calloc(1,sizeof(*m));uint32_t seq=UINT32_MAX,action=UINT32_MAX,aim=UINT32_MAX,animation=UINT32_MAX,hit=UINT32_MAX,deliv=UINT32_MAX;
    if(!m || (!borrowed && (dw4_igb_open(gp,blob,size,0) || dw4_igb_refs_open(gp))) || !gp->id_kind)goto fail;
    if(info!=UINT32_MAX) {
        dw4_igb_record r={0};
        if(!record(gp,info,&r))goto fail;
        int valid=!strcmp(r.class_name,"beModelCtrlInfo");name=r.name;
        dw4_igb_record_free(&r);if(!valid)goto fail;
    }
    if(!name)goto fail;
    for(uint32_t i=0;i<gp->table_n;i++) {
        dw4_igb_record r={0};if(!record(gp,i,&r))continue;
        if(r.name && !strcmp(r.name,name)) {
            if(!strcmp(r.class_name,"beAction2Info")){action=slot(&r,9);animation=slot(&r,8);}
            if(!strcmp(r.class_name,"beHitLandDelivInfo"))deliv=slot(&r,6);   /* _ramList */
            if(!strcmp(r.class_name,"beModelCtrlInfo") && (info==UINT32_MAX || info==i)) {
                const char *kind=string_slot(&r,7);
                m->object_kind=kind && !strcmp(kind,"KIND_OBJECT");
                m->player_kind=kind && !strcmp(kind,"KIND_PLAYER");
                m->enemy_kind=kind && !strcmp(kind,"KIND_ENEMY");
                size_t n=0;const uint8_t *p=list(gp,slot(&r,5),&n);
                if(!p){dw4_igb_record_free(&r);goto fail;}
                for(size_t j=0;j<n;j++) {
                    dw4_igb_record group={0};
                    if(!record(gp,item(p,j),&group)){dw4_igb_record_free(&r);goto fail;}
                    if(!strcmp(group.class_name,"beModelCtrlInfoDataSeq"))seq=slot(&group,4);
                    if(!strcmp(group.class_name,"beModelCtrlInfoDataAIM"))aim=slot(&group,4);
                    if(hit==UINT32_MAX && !strcmp(group.class_name,"beModelCtrlInfoDataHit") && group.name && !strcmp(group.name,"HIT"))hit=item(p,j);
                    dw4_igb_record_free(&group);
                }
            }
        }
        dw4_igb_record_free(&r);
    }
    if(seq==UINT32_MAX || action==UINT32_MAX || durations(m,gp,animation) || sequences(m,gp,seq) || actions(m,gp,action) || maps(m,gp,aim))goto fail;
    m->refs=malloc(sizeof(*m->refs));if(!m->refs)goto fail;
    *m->refs=1;
    if(model_program_load(m,gp,seq) || model_record_init(m) || status_record_init(m) || al_reserve(m->arena,model_ram(m)->_dataList,4,DW4_STATUS_TIMER_SLOTS+2))goto fail;
    if(hit_data(m,gp,hit) || land_data(m,gp,deliv))goto fail;
    status_reset(m);
    model_ai(m)->_mapNo=-1;dw4_action2_host_init(&m->clock);if(m->clock.error)goto fail;if(!borrowed)dw4_igb_close(gp);return m;
fail:
    if(!borrowed)dw4_igb_close(gp);
    dw4_modelctrl_close(m);return NULL;
}
dw4_modelctrl *dw4_modelctrl_open(const uint8_t *blob,size_t size,const char *name) {
    return open_model(blob,size,name,UINT32_MAX,NULL);
}
dw4_modelctrl *dw4_modelctrl_open_info(const dw4_igb *g,uint32_t info) {
    /* the caller's pack is open with its reference tables; fall back to a private open when it is not */
    return g?open_model(g->data,g->size,NULL,info,g->id_kind?g:NULL):NULL;
}
dw4_modelctrl *dw4_modelctrl_instance(const dw4_modelctrl *source) {
    if(!source || !source->refs || *source->refs==UINT_MAX)return NULL;
    dw4_modelctrl *m=calloc(1,sizeof(*m));if(!m)return NULL;
    m->program=source->program;
    m->seq=source->seq;m->nseq=source->nseq;m->action=source->action;m->naction=source->naction;
    m->duration=source->duration;m->nduration=source->nduration;
    m->map=source->map;m->nmap=source->nmap;
    m->hit_boxes=source->hit_boxes;m->nhit_boxes=source->nhit_boxes;m->hit_player_talk=source->hit_player_talk;m->hit_player_bullet=source->hit_player_bullet;m->hit_enemy_bullet=source->hit_enemy_bullet;
    m->object_kind=source->object_kind;memcpy(m->land,source->land,sizeof m->land);
    m->player_kind=source->player_kind;m->enemy_kind=source->enemy_kind;
    if(model_record_init(m) || status_record_init(m) || al_reserve(m->arena,model_ram(m)->_dataList,4,DW4_STATUS_TIMER_SLOTS+2)){model_record_close(m);free(m);return NULL;}
    status_reset(m);
    m->refs=source->refs;(*m->refs)++;dw4_action2_host_init(&m->clock);if(m->clock.error){dw4_modelctrl_close(m);return NULL;}return m;
}
void dw4_modelctrl_close(dw4_modelctrl *m) {
    if(!m)return;
    dw4_modelctrl_hit_sink(m,NULL,NULL,NULL);
    if(m->work.off){model_subcommands_clear(m,0);dw4_modelctrl_position_lock(m,NULL,NULL);}
    dw4_modelctrl_dependencies_bind(m,NULL);
    dw4_action2_host_close(&m->clock);model_record_close(m);
    free(m->hit_world_boxes);
    if(m->refs && --*m->refs){free(m);return;}
    free(m->refs);
    if(m->program){dw4_arena_pack_release(m->arena,&m->program->pack);free(m->program);}
    for(size_t i=0;i<m->nseq;i++) {
        for(size_t j=0;m->seq[i].cmd && j<m->seq[i].n;j++)free((void *)m->seq[i].cmd[j].type);
        free(m->seq[i].cmd);
    }
    for(size_t i=0;i<m->naction;i++)free(m->action[i].cmd);
    for(size_t i=0;i<m->nmap;i++)for(unsigned z=0;z<4;z++)free(m->map[i].choices[z]);
    free(m->seq);free(m->action);free(m->duration);free(m->map);free(m->hit_boxes);free(m);
}
/* Validate all reachable programs before replacing live state. Cycles are legal
 * when a WCHECK yields; dispatch also has a budget for malformed immediate loops. */
static int validate(dw4_modelctrl *m,int index,unsigned char *visited) {
    if(visited[index])return 0;
    visited[index]=1;struct sequence *s=m->seq+index;size_t j=0;
    int player_labels=0;
    if(m->player_kind && model_label(m,index))for(size_t k=0;k<s->n;k++)
        if(!strcmp(s->cmd[k].type,"beModelCtrlLABEL") && !strcmp(s->cmd[k].name,model_label(m,index))){j=k;break;}
    for(;j<s->n;j++) {
        struct command *c=s->cmd+j;
        /* A player's weapon sections are alternative authored programs. Match
         * dispatch's first/next LABEL boundary rather than admitting an unused
         * weapon action merely to run the selected section. */
        if(m->player_kind && !strcmp(c->type,"beModelCtrlLABEL") && player_labels++)return 0;
        if(!strcmp(c->type,"beModelCtrlACTION")) {
            int a=find_action(m,c->name);
            if(a<0 || !m->action[a].supported)goto bad;
        } else if(!strcmp(c->type,"beModelCtrlWCHECK")) {
            if(strcmp(c->name,"Action") && strcmp(c->name,"Moving") && ((strcmp(c->name,"TurnY") && strcmp(c->name,"Landing")) || (!m->enemy_kind && !m->player_kind)) &&
               (!m->player_kind || (strcmp(c->name,"Atck01") && strcmp(c->name,"Atck02") && strcmp(c->name,"Atck03"))))goto bad;
        } else if(!strcmp(c->type,"beModelCtrlJUMP")) {
            if(!strcmp(c->name,"SQ_ERAS"))return 0;
            int to=find_seq(m,c->name);if(to<0)goto bad;
            if(validate(m,to,visited))return -1;
            return 0;
        } else if(!strcmp(c->type,"beModelCtrlLABELCTRL")) {
            int to=c->target?find_seq(m,c->target):-1;if(to<0)goto bad;
            int found=0;for(size_t k=0;k<m->seq[to].n;k++)
                if(!strcmp(m->seq[to].cmd[k].type,"beModelCtrlLABEL") &&
                   !strcmp(m->seq[to].cmd[k].name,c->name))found=1;
            if(!found)goto bad;
        } else if(!strcmp(c->type,"beModelCtrlMOVE")) {
            int channel;if(move_mode(c->name,&channel)<0)goto bad;
        } else if(!strcmp(c->type,"beModelCtrlMOVECTRL") || !strcmp(c->type,"beModelCtrlPDMOVE")) {
            if(strcmp(c->name,"Move") && strcmp(c->name,"Stop"))goto bad;
        } else if(!strcmp(c->type,"beModelCtrlMOVEEX")) {
            int channel;if(moveex_mode(c->name,&channel)<0)goto bad;
        } else if(!strcmp(c->type,"beModelCtrlMOVERL")) {
            if(!c->target || (!strcmp(c->name,"JOINT")?!m->dependencies.track:(!c->bone || !m->dependencies.bone)))goto bad;
        } else if(!strcmp(c->type,"beModelCtrlAIMAP")) {
            int a=find_map(m,c->name);
            /* Only the recovered WPOS acquisition boundary is implemented.
             * NEAR needs a player/target owner; never silently substitute it. */
            if(a<0)goto bad;
            if(!strcmp(m->map[a].target_type,"NEAR")){if(!m->near)goto bad;}
            else if(strcmp(m->map[a].target_type,"WPOS") || !m->scripts || !m->model)goto bad;
        } else if(!strcmp(c->type,"beModelCtrlCTRL")) {
            if(strcmp(c->name,"isLive") && strcmp(c->name,"toWalk") &&
               strcmp(c->name,"toWait") && strcmp(c->name,"onWalk") &&
               strcmp(c->name,"onFall") && strcmp(c->name,"noFall"))goto bad;
        } else if(!strcmp(c->type,"beModelCtrlLUACALL")) {
            if(!m->scripts || !m->model || !m->model->info_name)goto bad;
        } else if(!strcmp(c->type,"beModelCtrlHITBOX")) {
            if(strcmp(c->name,"Set") && strcmp(c->name,"AllClear"))goto bad;
        } else if(strcmp(c->type,"beModelCtrlLABEL") && strcmp(c->type,"beModelCtrlMUTEKI"))goto bad;
    }
    return 0;
bad:
    snprintf(m->error,sizeof(m->error),"unsupported model program %s: %s %s",s->name,s->cmd[j].type,s->cmd[j].name);
    return -1;
}
/* Check each reachable entry for a command cycle that never yields. */
static int yields(dw4_modelctrl *m,size_t index) {
    size_t pc=0;unsigned budget=1024;
    while(pc<m->seq[index].n) {
        if(!budget--){snprintf(m->error,sizeof(m->error),"model immediate command loop");return -1;}
        struct command *c=m->seq[index].cmd+pc++;
        if(!strcmp(c->type,"beModelCtrlWCHECK"))return 0;
        if(!strcmp(c->type,"beModelCtrlJUMP")) {
            if(!strcmp(c->name,"SQ_ERAS"))return 0;
            index=(size_t)find_seq(m,c->name);pc=0;
        }
    }
    return 0;
}
static size_t entry(const dw4_modelctrl *m,size_t seq) {
    if(model_label(m,seq))for(size_t i=0;i<m->seq[seq].n;i++)
        if(!strcmp(m->seq[seq].cmd[i].type,"beModelCtrlLABEL") &&
           !strcmp(m->seq[seq].cmd[i].name,model_label(m,seq)))return i;
    return 0;
}
static int select_sequence(dw4_modelctrl *m,size_t seq) {
    m->generation++;model_work(m)->_comData=al_words(m->arena,m->program->sequences)[seq];model_work(m)->_seqCodeName=al_words(m->arena,model_work(m)->_labelSeqList)[seq];model_work(m)->_comIndex=entry(m,seq);model_wait_clear(m);model_work(m)->_comLabelCount=0;model_work(m)->_ctrlSt0=0;model_work(m)->_ctrlSt1=0;if(model_subcommands_clear(m,0))return -1;
    model_work(m)->_isWallCheck=model_work(m)->_isFloorCheck=1;
    model_work(m)->_isFallCheck=1;
    /* The same set (0x3981f8..0x398344) replaces the wait name (+0x4c) and the three LUACALL hit callbacks (_luaBHit +0x30, _luaWHit +0x34, _luaFHit +0x38) by a null
     * string, so a "WHit" registered by one sequence (the boss's wh1 in SQ_ATCK2) lives only until the next sequence starts. */
    al_free(m->arena,model_work(m)->_luaBHit);al_free(m->arena,model_work(m)->_luaWHit);al_free(m->arena,model_work(m)->_luaFHit);
    model_work(m)->_luaBHit=model_work(m)->_luaWHit=model_work(m)->_luaFHit=0;
    /* 396a80's name-based sequence set (398100..398370, also the AI consumer's route through
     * virtual slot 140) resets bytes 216..218 and replaces a negative MUTEKI by zero. Positive
     * countdowns persist; SQ_SILENT's permanent -1 therefore ends when SQ_WAIT is selected. */
    if(ee_f32_cmp(model_float_bits(&model_work(m)->_mutekiCount),0)<0)model_float_store(&model_work(m)->_mutekiCount,0);
    for(unsigned i=0;i<4;i++) {
        if(i==3){model_channel(m,i)->_isRun=0;model_channel(m,i)->_speed=0;}
        else if(model_channel(m,i)->_isSeqStop)model_move_expire(model_channel(m,i));
    }
    return 0;
}
void dw4_modelctrl_script(dw4_modelctrl *m,dw4_scriptengine *scripts,uint64_t scope,
    dw4_script_model *state) {
    if(m){m->scripts=scripts;m->scope=scope;m->model=state;
        if(state){*model_hp(m,0)=state->hp;*model_hp(m,1)=state->max_hp;model_work(m)->_recNo=state->rec_no;model_ram(m)->_ramNo=state->ram_no;m->bridge_last=*state;}}
}
void dw4_modelctrl_aim_state(const dw4_modelctrl *m,dw4_modelctrl_aim *out)
{
    if(!m || !out)return;
    memset(out,0,sizeof *out);out->index=model_ai(m)->_mapNo;
    if(out->index>=0 && (size_t)out->index<m->nmap){out->name=m->map[out->index].name;out->rot_limit=m->map[out->index].rot_limit;memcpy(out->bounds,m->map[out->index].bounds,sizeof out->bounds);}
    memcpy(out->target,model_ai_target(m),12);out->sequence=al_text(m->arena,model_ai(m)->_seqName);
    out->timer_present=model_ai_timed(m);out->timer_start=model_ai_start(m);out->timer_duration=model_ai_duration(m);
}
static int select_map(dw4_modelctrl *m,const char *name) {
    int index=find_map(m,name);
    model_ai(m)->_mapNo=index;

    dw4_script_model snapshot=model_script_snapshot(m);int32_t before=(*model_hp(m,0));
    snapshot.call_name="WPos";snapshot.target_enabled=1;
    memset(snapshot.target,0,sizeof snapshot.target);
    char script[256];
    if(!snapshot.info_name || snprintf(script,sizeof script,"aim_%s.lua",snapshot.info_name)>=(int)sizeof script) {
        snprintf(m->error,sizeof m->error,"model AIMAP callback name unavailable");return -1;
    }
    if(dw4_scriptengine_model_event(m->scripts,m->scope,script,&snapshot)) {
        snprintf(m->error,sizeof m->error,"model AIMAP WPos: %.220s",dw4_scriptengine_error(m->scripts));
        return -1;
    }
    model_bridge_pull(m);
    if((*model_hp(m,0))==before)(*model_hp(m,0))=snapshot.hp;
    memcpy(model_ai_target(m),snapshot.target,sizeof snapshot.target);
    model_ai_timer_clear(m);
    return 0;
}
/* The named script event "<call>_<model>.lua" of a LUACALL command or a registered hit callback (FUN_00394400). */
static int model_lua_call(dw4_modelctrl *m,const char *call)
{
    char script[256];
    if(!m->scripts || !m->model || !m->model->info_name){snprintf(m->error,sizeof m->error,"LUACALL %s: no script context",call);return -1;}
    if(snprintf(script,sizeof script,"%s_%s.lua",call,m->model->info_name)>=(int)sizeof script){snprintf(m->error,sizeof m->error,"LUACALL name too long");return -1;}
    dw4_script_model snapshot=model_script_snapshot(m);int32_t before=(*model_hp(m,0));snapshot.call_name=call;
    dw4_model_contact contact=m->has_last_contact?m->last_contact:(dw4_model_contact){.bullet_kind=-1,.bullet_box=-1,.shoot_ram_no=-1,.damage_turn=1,.target_slot=-1,.source_row=-1};   /* a sequence started by a script (SQ_SWON) has no bullet: neutral context */   /* retail keeps the latest bullet on the model: the callback reads it through MDLgetBulletName and the BLT calls */
    if((!strncmp(call,"hit",3) || m->has_last_contact)?dw4_scriptengine_contact_event(m->scripts,m->scope,script,&snapshot,&contact):dw4_scriptengine_model_event(m->scripts,m->scope,script,&snapshot)) {
        snprintf(m->error,sizeof m->error,"model LUACALL %s: %.200s",script,dw4_scriptengine_error(m->scripts));return -1;
    }
    model_bridge_pull(m);
    if((*model_hp(m,0))==before)(*model_hp(m,0))=snapshot.hp;
    return 0;
}
static int status_hook(dw4_modelctrl *m);
static int dispatch_commands(dw4_modelctrl *m) {
    unsigned budget=1024;
    while(model_ram(m)->_isRun && !(model_wait(m)!=NULL) && (size_t)model_work(m)->_comIndex<m->seq[model_current(m)].n) {
        if(!budget--) {snprintf(m->error,sizeof(m->error),"model immediate command loop");return -1;}
        struct command *c=m->seq[model_current(m)].cmd+model_work(m)->_comIndex++;
        if(!strcmp(c->type,"beModelCtrlLABEL")) {
            if(model_work(m)->_comLabelCount){model_work(m)->_comIndex--;break;}
            model_work(m)->_comLabelCount=1;
        }
        if(m->trace)m->trace(m->trace_user,m->seq[model_current(m)].name,c->type,c->name,m->now);
        if(!strcmp(c->type,"beModelCtrlACTION")) {
            struct action *a=m->action+find_action(m,c->name);
            /* An action longer than the host's component storage cannot start: it is skipped and counted (none of the retail packs has one: the longest has 24 components,
             * and the loot test asserts the count stays zero). */
            if(a->n>DW4_A2_MAX_COMPONENTS){m->long_actions++;continue;}
            /* Retail Action2 message dispatch restores the instance switch bit
             * before testing whether the requested action is already current
             * (377990, including its active-owner branch). FADESET HIDE clears
             * that bit for the current action; it cannot hide later actions. */
            m->clock.hidden=0;
            const char *playing=dw4_action2_host_name(&m->clock);
            if(playing && !strcmp(playing,a->name))continue;
            dw4_action2_component components[DW4_A2_MAX_COMPONENTS];unsigned count=0;
            for(size_t i=0;i<a->n;i++) {
                if(a->cmd[i].kind==DW4_A2_MOTIONSET) {
                    /* The host's component walk starts each MOTIONSET when it reaches it (0x377340), so a WAITCHECK Motion holds the next MOTIONSET back
                     * until this animation has played out (Mammothmon's ACTN03: actn03, wait, actn04, wait). */
                    components[count]=a->cmd[i];
                    components[count].duration=a->duration[i];components[count].blend=dw4_model_ai_duration(a->cmd[i].last);
                    count++;
                } else if(a->cmd[i].kind==6) {
                    m->missing_motions++;   /* no such animation: nothing plays */
                } else if(a->cmd[i].kind==5) {
                    m->flash_start_ns=m->now;m->flash_count++;   /* presentation only */
                } else components[count++]=a->cmd[i];
            }
            dw4_action2_host_start_program(&m->clock,components,count,m->now);
            dw4_action2_host_set_name(&m->clock,a->name);
            model_fade_events(m);
            if(m->clock.error)goto clock_error;
        } else if(!strcmp(c->type,"beModelCtrlWCHECK")){if(model_wait_set(m,c->name))return -1;}
        else if(!strcmp(c->type,"beModelCtrlJUMP")) {
            if(!strcmp(c->name,"SQ_ERAS"))dw4_modelctrl_remove(m);
            else if(select_sequence(m,(size_t)find_seq(m,c->name)))return -1;
        } else if(!strcmp(c->type,"beModelCtrlAIMAP")) {
            uint64_t generation=m->generation;
            int map=find_map(m,c->name);
            if(map>=0 && !strcmp(m->map[map].target_type,"NEAR")) {
                /* A NEAR map takes the nearest player as its target; the authored zones and choices run in ai_tick. */
                model_ai(m)->_mapNo=map;
                model_ai_timer_clear(m);continue;
            }
            if(select_map(m,c->name))return -1;
            /* A synchronous callback can REMOVE or select another sequence.
             * Let its new cursor win rather than consuming the old tail. */
            if(m->generation!=generation)return 0;
        } else if(!strcmp(c->type,"beModelCtrlLUACALL")) {
            /* FUN_00394640: a command whose mode is "BHit", "WHit" or "FHit" only registers the callback name on the Work (_luaBHit/_luaWHit/_luaFHit, kept
             * until the next sequence is selected or the model is removed; FUN_003926d0 runs the wall and floor ones after the move). Any other mode, the empty one included, runs the
             * named script event now ("<call>_<model>.lua": bck/wh1/wh2/ded of the bosses); the model state commits like the AIMAP callback's. */
            uint64_t generation=m->generation;
            const char *mode=c->target?c->target:"";
            int32_t *registered=!strcmp(mode,"BHit")?&model_work(m)->_luaBHit:!strcmp(mode,"WHit")?&model_work(m)->_luaWHit:!strcmp(mode,"FHit")?&model_work(m)->_luaFHit:NULL;
            if(registered) {
                int32_t h=al_string(m->arena,c->name);if(!h){snprintf(m->error,sizeof m->error,"LUACALL registration allocation failed");return -1;}
                al_free(m->arena,*registered);*registered=h;continue;
            }
            if(model_lua_call(m,c->name))return -1;
            if(m->generation!=generation)return 0;   /* the script selected another sequence */
        } else if(!strcmp(c->type,"beModelCtrlLABELCTRL")){
            if(dw4_modelctrl_label(m,c->target,c->name))return -1;
        }
        else if(!strcmp(c->type,"beModelCtrlMOVERL")) {
            if(dw4_modelctrl_relative(m,c->name,c->target,c->bone))return -1;
        }
        else if(!strcmp(c->type,"beModelCtrlMOVE")) {
            model_move_unlock(m);
            int channel=0,mode=move_mode(c->name,&channel);
            model_move_start(model_channel(m,channel),c->v[0],c->v[1],0,mode);
        }
        else if(!strcmp(c->type,"beModelCtrlMOVECTRL") || !strcmp(c->type,"beModelCtrlPDMOVE")) {
            unsigned offset=!strcmp(c->name,"Move")?2:0;
            model_float_store(&model_walk(m,offset!=0)->_value,c->v[0]);model_float_store(&model_walk(m,offset!=0)->_frame,c->v[1]);
        }
        else if(!strcmp(c->type,"beModelCtrlMOVEEX")) {
            model_move_unlock(m);
            int channel=0,mode=moveex_mode(c->name,&channel);
            beModelCtrlMoveObject *ch=model_channel(m,channel);
            model_move_start(ch,c->v[0],c->v[1],c->v[2],mode);
            ch->_isSeqStop=(uint8_t)c->v[3];model_float_store(&ch->_stopValue,c->v[4]);model_float_store(&ch->_stopFrame,c->v[5]);
        } else if(!strcmp(c->type,"beModelCtrlCTRL")) {
            if(!strcmp(c->name,"onFall") || !strcmp(c->name,"noFall")) {
                model_work(m)->_isFallCheck=!strcmp(c->name,"onFall");continue;
            }
            model_work(m)->_ctrlSt1=0;
            model_work(m)->_ctrlSt0=!strcmp(c->name,"onWalk")?1:!strcmp(c->name,"toWalk")?2:
                !strcmp(c->name,"toWait")?3:4;
        } else if(!strcmp(c->type,"beModelCtrlHITBOX")) {
            if(!strcmp(c->name,"AllClear")){if(model_subcommands_clear(m,DW4_SC_HITBOX))return -1;}
            else if(model_hitbox_count(m)<8){
                if(dw4_modelsubcom_hitbox(m->arena,al_handle(model_work(m)->_subCommand),(int32_t)c->v[0],c->v[1],c->v[2],c->box,c->box+3)){
                    snprintf(m->error,sizeof m->error,"model HITBOX allocation failed");return -1;}
            }
        } else if(!strcmp(c->type,"beModelCtrlMUTEKI")) {
            if(!strcmp(c->name,"OFFWALL"))model_work(m)->_isWallCheck=0;
            else if(!strcmp(c->name,"ONWALL"))model_work(m)->_isWallCheck=1;
            else if(!strcmp(c->name,"OFFFLOOR"))model_work(m)->_isFloorCheck=0;
            else if(!strcmp(c->name,"ONFLOOR"))model_work(m)->_isFloorCheck=1;
            else model_float_store(&model_work(m)->_mutekiCount,c->v[0]);
        }
    }
    return 0;
clock_error:
    snprintf(m->error,sizeof(m->error),"model Action2 error %d",m->clock.error);return -1;
}
/* Runs the commands of the current sequence; when they selected another one (a JUMP, a script) the sequence-change hook follows. */
static int dispatch(dw4_modelctrl *m) {
    uint64_t generation=m->generation;
    int rc=dispatch_commands(m);
    return rc || m->generation==generation?rc:status_hook(m);
}
static int start_sequence(dw4_modelctrl *m,const char *name,int generate) {
    if(!m || !name)return -1;
    m->error[0]=0;
    if(!strcmp(name,"SQ_ERAS")){dw4_modelctrl_remove(m);return 0;}
    int i=find_seq(m,name);
    if(i<0){snprintf(m->error,sizeof(m->error),"model sequence unavailable: %s",name);return -1;}
    unsigned char *visited=calloc(m->nseq?m->nseq:1,1);if(!visited)return -1;
    int rc=validate(m,i,visited);
    for(size_t j=0;!rc && j<m->nseq;j++)if(visited[j])rc=yields(m,j);
    free(visited);if(rc)return -1;
    /* Retail GENERATE 0x396d74..98: preserve existing object health, but
     * initialize both scalar values to 100 when max HP is zero. */
    if(generate && m->object_kind && m->model && !(*model_hp(m,1)))
        (*model_hp(m,0))=(*model_hp(m,1))=100;
    /* Work field 15's retail initializer (3511ac..c0) defaults _isOnCtrl
     * to true. Direct messages and active replacements retain its gate. */
    if(generate && !model_ram(m)->_isRun){model_work(m)->_isOnCtrl=1;status_reset(m);}
    model_ram(m)->_isRun=1;if(select_sequence(m,(size_t)i))return -1;
    rc=dispatch_commands(m);
    return rc?rc:status_hook(m);
}
/* FUN_00445200, run by the model class after every by-name sequence set and every JUMP (vtable slot 44): a sleeper wakes when anything but SQ_SLEP
 * starts, a stunned model that falls back to SQ_WAIT is held in SQ_STUN, any other sequence ends the stun. A KO clears every timer. A player's
 * HP is not tracked here (its record is authoritative): the tick applies the KO branch. */
static int status_sequence(dw4_modelctrl *m,const char *name);
static int status_hook(dw4_modelctrl *m)
{
    if(!m->has_status || !model_ram(m)->_isRun)return 0;
    dw4_status_tick_result res;dw4_status state=status_record_read(m);
    dw4_status_sequence_changed(&state,dw4_modelctrl_sequence(m),m->player_kind || !m->model?1:(*model_hp(m,0)),&res);
    status_record_write(m,&state);return status_sequence(m,res.sequence);
}
/* A sequence the status manager asks for. Enemy packs may lack SQ_SLEP/SQ_STUN: those are skipped rather than failing the tick. */
static int status_sequence(dw4_modelctrl *m,const char *name)
{
    static int depth;    /* a pack whose SQ_STUN/SQ_SLEP jumps straight back must not recurse through the sequence hook */
    if(!name || !model_ram(m)->_isRun || depth || find_seq(m,name)<0 || !strcmp(name,dw4_modelctrl_sequence(m)))return 0;
    depth++;model_bridge_pull(m);int rc=start_sequence(m,name,0);depth--;
    return rc;
}
int dw4_modelctrl_start(dw4_modelctrl *m,const char *name) {
    model_bridge_pull(m);int rc=start_sequence(m,name,m && !model_ram(m)->_isRun);model_pose_publish(m);model_bridge_pull(m);model_bridge_push(m);return rc;
}
void dw4_modelctrl_random(dw4_modelctrl *m,dw4_random *r,uint32_t *rhythm) {
    if(m)dw4_action2_host_random(&m->clock,r,rhythm);
}
void dw4_modelctrl_request_erase(dw4_modelctrl *m)
{
    if(m && model_ram(m)->_isRun){m->generation++;model_work(m)->_seqCodeName=m->erase_name;}
}
void dw4_modelctrl_remove(dw4_modelctrl *m) { if(m){m->generation++;model_ram(m)->_isRun=0;model_wait_clear(m);dw4_action2_host_set_name(&m->clock,NULL);model_ai_timer_clear(m);model_work(m)->_isOnFreeze=0;
    model_float_store(&model_work(m)->_mutekiCount,0);
    m->hit_cached=0;
    al_free(m->arena,model_work(m)->_luaBHit);al_free(m->arena,model_work(m)->_luaWHit);al_free(m->arena,model_work(m)->_luaFHit);   /* the Work's destructor (FUN_00350410) releases the hit callbacks */
    model_work(m)->_luaBHit=model_work(m)->_luaWHit=model_work(m)->_luaFHit=0;
    if(m->has_status)status_reset(m);   /* an erased enemy keeps none of its ailments for the next instance */
    /* Retail Action2 REMOVE clears node +88 default attributes and releases
     * its Work. A later instance cannot inherit the old OUT opacity. */
    model_subcommands_clear(m,0);dw4_modelctrl_position_lock(m,NULL,NULL);
    al_free(m->arena,model_work(m)->_hitParentName);model_work(m)->_hitParentName=0;model_work(m)->_hitParentRamNo=0;
    model_action_work(m)->_fadeSt0=0;} }
void dw4_modelctrl_sample(dw4_modelctrl *m,int64_t now) {
    if(m){
        if(m->raw_sampled && model_ram(m)->_isRun && model_work(m)->_isOnFreeze)m->held_ns+=(uint64_t)now-(uint64_t)m->raw_previous;
        m->raw_previous=now;m->raw_sampled=1;m->now=(int64_t)((uint64_t)now-m->held_ns);
        if(!m->sampled){m->previous=m->now;m->sampled=1;}
    }
}
static uint32_t float_bits(float value){uint32_t b;memcpy(&b,&value,4);return b;}
static float bits_float(uint32_t b){float value;memcpy(&value,&b,4);return value;}
/* Object manager 395b50 calls control/AI before sequence and movement. No
 * target query, timer or RNG work is performed by queries/presentation. */
static int ai_tick(dw4_modelctrl *m)
{
    if(!model_work(m)->_ctrlSt0){model_ai_timer_clear(m);return 0;}
    if(m->player_kind) {
        if(!model_work(m)->_isOnCtrl) {
            /* Control is off (a travel prompt, a talk): the stick no longer reaches the player, so a walking player stops instead of
             * running in place. Only the walk sequence is ended; entry, jump and scripted sequences are left alone. */
            const char *cur=dw4_modelctrl_sequence(m);
            if(cur && !strcmp(cur,"SQ_WALK"))return dw4_modelctrl_start(m,"SQ_WAIT");
            /* A jump or fall in progress loses its horizontal momentum (retail, measured by clearing the player's _isOnCtrl byte mid-jump with the stick held:
             * the player drops straight down, about 0.7 units of horizontal travel over the whole arc). The vertical channel keeps running. */
            if(cur && (!strcmp(cur,"SQ_JUMP") || !strcmp(cur,"SQ_FALL"))){model_channel(m,2)->_isRun=0;model_channel(m,2)->_speed=0;}
            return 0;
        }
        int move=-1,phase=model_work(m)->_ctrlSt1;
        const char *next=dw4_model_ai_control(model_work(m)->_ctrlSt0,m->player_walking,"SQ_NONE",&phase,&move);
        if(move>=0) {
            unsigned offset=move==0?2:0;
            model_move_start(model_channel(m,2),model_float_bits(&model_walk(m,offset!=0)->_value),model_float_bits(&model_walk(m,offset!=0)->_frame),0,move);
            model_work(m)->_ctrlSt1=phase;
        }
        if(m->player_walking)m->pose.rotation[1]=bits_float(ee_f32_mul(float_bits(m->player_yaw),0x42652ee1));
        if(next && strcmp(next,"SQ_NONE") && strcmp(next,dw4_modelctrl_sequence(m)))return dw4_modelctrl_start(m,next);
        return 0;
    }
    const char *next="SQ_NONE";
    if(model_work(m)->_isOnCtrl && model_ai(m)->_mapNo>=0) {
        struct aimap *a=m->map+model_ai(m)->_mapNo;
        if(!model_ai_timed(m) || model_ai_duration(m)<(int64_t)((uint64_t)dw4_model_ai_clock(m->now)-(uint64_t)model_ai_start(m))) {
            if(!strcmp(a->target_type,"NEAR") && (!m->near || m->near(m->near_user,model_position(m),model_ai_target(m)))) {
                snprintf(m->error,sizeof m->error,"NEAR map requires a live scene target");return -1;
            }
            uint32_t d[3];for(unsigned i=0;i<3;i++)d[i]=ee_f32_sub(float_bits(model_position(m)[i]),float_bits(model_ai_target(m)[i]));
            /* 3a6750 evaluates Z, then X, then Y. */
            uint32_t distance=ee_f32_add(ee_f32_add(ee_f32_mul(d[2],d[2]),ee_f32_mul(d[0],d[0])),ee_f32_mul(d[1],d[1]));
            unsigned zone=dw4_model_ai_zone(distance,a->bounds);
            int choice=dw4_model_ai_choose(m->clock.random,a->choices[zone],(unsigned)a->count[zone]);
            if(choice<0){snprintf(m->error,sizeof m->error,"AIMAP %s: missing RNG/zone choices",a->name);return -1;}
            const dw4_model_ai_choice *c=a->choices[zone]+choice;
            uint32_t dx=ee_f32_sub(float_bits(model_ai_target(m)[0]),float_bits(model_position(m)[0]));
            uint32_t dz=ee_f32_sub(float_bits(model_ai_target(m)[2]),float_bits(model_position(m)[2]));
            (model_work(m)->_targetDirection[1])=dw4_model_ai_direction(dx,dz,c->direction);
            (model_work(m)->_directionLimiter[1])=a->rot_limit;if(model_ai_sequence(m,c->sequence))return -1;
            model_ai_timer_arm(m,dw4_model_ai_clock(m->now),dw4_model_ai_duration(c->frames));
        }
        next=al_text(m->arena,model_ai(m)->_seqName);
    }
    /* 391cf0 consumes CTRL only when the AI publishes SQ_NONE. The
     * work flag compares SQ_WALK (50ef88), not SQ_WAIT. */
    int move=-1,phase=model_work(m)->_ctrlSt1;
    next=dw4_model_ai_control(model_work(m)->_ctrlSt0,next && !strcmp(next,"SQ_WALK"),next,&phase,&move);
    if(move>=0) {
        unsigned offset=move==0?2:0;
        model_move_start(model_channel(m,2),model_float_bits(&model_walk(m,offset!=0)->_value),model_float_bits(&model_walk(m,offset!=0)->_frame),0,move);
        model_work(m)->_ctrlSt1=phase;
    }
    if(next && strcmp(next,"SQ_NONE") && strcmp(next,dw4_modelctrl_sequence(m)))return dw4_modelctrl_start(m,next);
    return 0;
}
static int model_emit_hit(void *u,dw4_handle child)
{
    dw4_modelctrl *m=u;if(!m->hit_emit)return 0;
    beModelCtrlSCHitBox *b=DW4_ARENA_OBJ(m->arena,beModelCtrlSCHitBox,child);
    dw4_modelctrl_hitbox event={.kind=b->_kind,.start_frames=b->_startFrame,.end_frames=b->_endFrame,
        .length_frames=b->_endFrame-b->_startFrame,.object=child,.run_frame=b->_runFrame};
    memcpy(event.offset,b->_offset,12);memcpy(event.size,b->_boxSize,12);
    float world[16];dw4_modelctrl_matrix(m,world);uint64_t generation=m->generation;
    /* Publish the current typed identity/health before an external transport
     * reads it, then import only deliberate callback edits. */
    model_bridge_push(m);
    int rc=m->hit_emit(m->hit_user,m,&event,world,m->raw_previous);
    model_bridge_pull(m);
    if(rc<0)return -1;
    return m->generation!=generation;
}
static int model_subcommand_event(void *u,dw4_handle child,int finish,int *keep)
{
    dw4_modelctrl *m=u;int type=dw4_modelsubcom_type(m->arena,child);int rc=0;
    uint64_t generation=m->generation;
    if(type==DW4_SC_HITBOX)return finish?0:model_emit_hit(u,child);
    m->dependencies_active++;
    if(type==DW4_SC_EFFECT){
        beModelCtrlSCEffect *e=DW4_ARENA_OBJ(m->arena,beModelCtrlSCEffect,child);
        if(finish && (!e->_isOneSet || e->_geneRamNo==-1)){m->dependencies_active--;return 0;}
        if(!m->dependencies.effect){m->dependencies_active--;snprintf(m->error,sizeof m->error,"model effect service unavailable");return -1;}
        rc=m->dependencies.effect(m->dependencies.user,m,child,finish,keep);
    }else if(type==DW4_SC_SOUND){
        beModelCtrlSCSound *s=DW4_ARENA_OBJ(m->arena,beModelCtrlSCSound,child);
        if(finish){
            if(s->_sndHandle){if(!m->dependencies.sound_down)goto unavailable;
                rc=m->dependencies.sound_down(m->dependencies.user,s->_sndHandle);}
        }else{
            if(!m->dependencies.sound_play)goto unavailable;
            int64_t handle=0;int kind=0;
            rc=m->dependencies.sound_play(m->dependencies.user,al_text(m->arena,s->_sndName),&handle,&kind);
            *keep=dw4_modelsubcom_sound_result(m->arena,child,handle,kind);
        }
    }else{m->dependencies_active--;return -1;}
    m->dependencies_active--;
    if(rc<0){snprintf(m->error,sizeof m->error,"model %s subcommand service failed",type==DW4_SC_EFFECT?"effect":"sound");return -1;}
    return m->generation!=generation;
unavailable:
    m->dependencies_active--;
    snprintf(m->error,sizeof m->error,"model sound service unavailable");return -1;
}
int dw4_modelctrl_dependencies_bind(dw4_modelctrl *m,const dw4_modelctrl_dependencies *d)
{
    if(!m)return -1;
    if(m->subcommand_clearing || m->dependencies_active || m->dependencies_changing)return -1;
    dw4_modelctrl_dependencies next=d?*d:(dw4_modelctrl_dependencies){0},old=m->dependencies;
    if(old.user==next.user && old.effect==next.effect && old.sound_play==next.sound_play &&
       old.sound_down==next.sound_down && old.bone==next.bone && old.track==next.track && old.release==next.release)return 0;
    m->dependencies_changing=1;int rc=0;
    if(m->work.off){
        if(model_subcommands_clear(m,DW4_SC_DEPENDENCIES))rc=-1;
        beModelCtrlInfoWork *w=model_work(m);
        if(w->_posLockTrc || w->_posLockModelName)dw4_modelctrl_position_lock(m,NULL,NULL);
    }
    m->dependencies=(dw4_modelctrl_dependencies){0};
    if(old.release)old.release(old.user);
    if(!rc)m->dependencies=next;
    m->dependencies_changing=0;m->generation++;return rc;
}
int dw4_modelctrl_relative(dw4_modelctrl *m,const char *kind,const char *name,const char *bone)
{
    if(!m || !kind || !name)return -1;
    beModelCtrlInfoWork *w=model_work(m);model_move_unlock(m);
    if(!strcmp(kind,"JOINT")){
        if(!m->dependencies.track){snprintf(m->error,sizeof m->error,"model track resolver unavailable");return -1;}
        dw4_handle next={0};m->dependencies_active++;
        int rc=m->dependencies.track(m->dependencies.user,m,name,&next);m->dependencies_active--;
        if(rc<0)return -1;
        if(!rc || !next.off)return 0;
        if(!dw4_arena_object_is(m->arena,next,dw4_metaobject_find("beModelCtrlInfoDataTrc")->vtable) || dw4_arena_object_addref(m->arena,next)<0)return -1;
        dw4_handle old=al_handle(w->_posLockTrc);w->_posLockTrc=(int32_t)next.off;w->_isPosLock=1;
        if(old.off)dw4_arena_object_release(m->arena,old);
    }else{
        if(!bone || !m->dependencies.bone){snprintf(m->error,sizeof m->error,"model named-bone resolver unavailable");return -1;}
        int32_t n=al_string(m->arena,name),b=al_string(m->arena,bone);
        if(!n || !b){al_free(m->arena,n);al_free(m->arena,b);return -1;}
        al_free(m->arena,w->_posLockModelName);al_free(m->arena,w->_posLockBoneName);
        w->_posLockModelName=n;w->_posLockBoneName=b;w->_isPosLock=1;
    }
    return 0;
}
int dw4_modelctrl_generate_effect(dw4_modelctrl *m,dw4_modelctrl *source,const char *seq,
    const float offset[3],const float rotation[3],int follow)
{
    if(!m || !source || !seq || !offset || !rotation || m==source)return -1;
    beModelCtrlInfoWork *sw=model_work(source),*w=model_work(m);
    const char *name=al_text(source->arena,sw->_hitParentName);
    int32_t slot=sw->_hitParentRamNo;
    if(!name){beBaseInfoRam *r=model_ram(source);slot=r->_ramNo;
        beBaseInfo *info=r->_parentInfo?DW4_ARENA_OBJ(source->arena,beBaseInfo,al_handle(r->_parentInfo)):NULL;
        name=info?al_text(source->arena,info->_name):source->model?source->model->info_name:NULL;}
    if(!name)return -1;
    int32_t parent=al_string(m->arena,name);if(!parent)return -1;
    unsigned char *visited=calloc(m->nseq?m->nseq:1,1);int index=find_seq(m,seq);
    if(!visited || index<0 || validate(m,index,visited)){free(visited);al_free(m->arena,parent);return -1;}
    free(visited);dw4_modelctrl_position_lock(m,NULL,NULL);
    al_free(m->arena,w->_hitParentName);w->_hitParentName=parent;w->_hitParentRamNo=slot;
    if(follow && dw4_modelctrl_position_lock(m,source,offset))return -1;
    float world[16];dw4_modelctrl_matrix(source,world);dw4_model_lock_matrix(world,world,offset);
    /* 396340 applies each nonzero radian axis by pre-multiplication, leaving
     * the translated origin intact. Native trig remains the pose backend. */
    for(unsigned i=0;i<3;i++)if(rotation[i]!=0){
        unsigned a=(i+1)%3,b=(i+2)%3;float axis[16]={0};axis[0]=axis[5]=axis[10]=axis[15]=1;
        axis[4*a+a]=axis[4*b+b]=cosf(rotation[i]);axis[4*a+b]=sinf(rotation[i]);axis[4*b+a]=-sinf(rotation[i]);
        dw4_model_local_matrix(world,world,axis);
    }
    memcpy(DW4_ARENA_OBJ(m->arena,beModelCtrlNode2,m->node)->_m,world,64);
    w->_aIHOffsetY=offset[1];
    /* GENERATE samples the initialized node's forward axis after vfunc36. */
    uint32_t facing=dw4_model_ai_direction(model_float_bits(world+8),model_float_bits(world+10),0);
    w->_direction[1]=w->_targetDirection[1]=facing;
    uint32_t degrees=ee_f32_mul(facing,0x42652ee1);memcpy(m->pose.rotation+1,&degrees,4);
    m->pose.matrix_valid=1;memcpy(m->pose.matrix_rotation,m->pose.rotation,12);
    return dw4_modelctrl_start(m,seq);
}
void dw4_modelctrl_hit_sink(dw4_modelctrl *m,dw4_modelctrl_hit_emit emit,void *u,void (*release)(void *))
{
    if(!m || (m->hit_emit==emit && m->hit_user==u && m->hit_release==release))return;
    void *old=m->hit_user;void (*drop)(void *)=m->hit_release;
    m->hit_emit=emit;m->hit_user=u;m->hit_release=release;if(drop)drop(old);
}
int dw4_modelctrl_position_lock(dw4_modelctrl *m,const dw4_modelctrl *source,const float offset[3])
{
    if(!m || !m->work.off || (source && source->arena!=m->arena))return -1;
    dw4_handle next=source?source->node:(dw4_handle){0};
    if(next.off && dw4_arena_object_addref(m->arena,next)<0)return -1;
    float local[3]={0};if(offset)memcpy(local,offset,12);
    beModelCtrlInfoWork *w=model_work(m);dw4_handle old=al_handle(w->_posLockNode);
    w->_posLockNode=(int32_t)next.off;w->_isPosLock=!!next.off;memcpy(w->_posLockOffset,local,12);
    if(old.off)dw4_arena_object_release(m->arena,old);
    if(!next.off){
        if(w->_posLockTrc)dw4_arena_object_release(m->arena,al_handle(w->_posLockTrc));
        w->_posLockTrc=0;
        al_free(m->arena,w->_posLockModelName);al_free(m->arena,w->_posLockBoneName);w->_posLockModelName=w->_posLockBoneName=0;
        m->pose.matrix_valid=0;
    }
    return 0;
}
static int model_tick_impl(dw4_modelctrl *m,int64_t now,uint32_t system_frame) {
    if(!m)return -1;
    dw4_modelctrl_sample(m,now);now=m->now;
    if(!model_ram(m)->_isRun){m->previous=now;m->sampled=1;return 0;}
    if(model_work(m)->_isOnFreeze){m->previous=now;return 0;}
    const char *pending=al_text(m->arena,model_work(m)->_seqCodeName);
    if(pending && !strcmp(pending,"SQ_ERAS")){dw4_modelctrl_remove(m);return 0;}
    model_fade_tick(m,now);
    if(ai_tick(m))return -1;
    if(m->has_status)dw4_status_bind_movement(m->arena,m->work);
    uint32_t frame_delta=dw4_model_frame_delta(m->previous,now);
    m->floor_signal=-1;m->land_signal=0;
    beModelCtrlInfoWork *pose_work=model_work(m);
    if(pose_work->_isPosLock){
        float locked[16];int found=0;
        if(pose_work->_posLockNode){
            igTransform *parent=DW4_ARENA_OBJ(m->arena,igTransform,al_handle(pose_work->_posLockNode));
            if(!parent)return -1;
            float source[16],offset[3];memcpy(source,parent->_m,64);memcpy(offset,pose_work->_posLockOffset,12);
            dw4_model_lock_matrix(locked,source,offset);found=1;
        }else if(pose_work->_posLockTrc){
            beModelCtrlInfoDataTrc *t=DW4_ARENA_OBJ(m->arena,beModelCtrlInfoDataTrc,al_handle(pose_work->_posLockTrc));
            if(!t || !t->_recorderNode)return -1;
            /* Recorder's reflected final field is a full 64-byte matrix. */
            unsigned char *r=dw4_arena_at(m->arena,al_handle(t->_recorderNode),160);
            if(!r)return -1;
            memcpy(locked,r+96,64);found=1;
        }else if(pose_work->_posLockModelName){
            if(!m->dependencies.bone){snprintf(m->error,sizeof m->error,"model named-bone resolver unavailable");return -1;}
            m->dependencies_active++;
            found=m->dependencies.bone(m->dependencies.user,m,al_text(m->arena,pose_work->_posLockModelName),al_text(m->arena,pose_work->_posLockBoneName),locked);
            m->dependencies_active--;
            if(found<0){snprintf(m->error,sizeof m->error,"model named-bone evaluation failed");return -1;}
        }
        if(found)memcpy(DW4_ARENA_OBJ(m->arena,beModelCtrlNode2,m->node)->_m,locked,64);
    }
    if(!pose_work->_isPosLock && m->sampled && now>=m->previous) {
        float old[3];memcpy(old,model_position(m),sizeof old);
        float frames=(float)((now/100-m->previous/100)*100)/16666667.0f;
        uint32_t delta;memcpy(&delta,&frames,4);
        int turning=model_channel(m,3)->_isRun;
        uint32_t turn=model_move_tick(model_channel(m,3),delta);float rotation;memcpy(&rotation,&turn,4);
        if(model_ai(m)->_mapNo<0)m->pose.rotation[1]+=rotation;
        else (model_work(m)->_targetDirection[1])=ee_f32_add((model_work(m)->_targetDirection[1]),ee_f32_mul(turn,0x3c8efa35));
        if(turning)(model_work(m)->_directionLimiter[1])=ee_f32_mul(ee_f32_mul(turn&0x7fffffff,0x3c8efa35),0x3fa00000);
        if(model_ai(m)->_mapNo>=0) {
            uint32_t current=(model_work(m)->_direction[1]);
            uint32_t out=dw4_model_ai_turn(current,(model_work(m)->_targetDirection[1]),(model_work(m)->_directionLimiter[1]),delta);
            (model_work(m)->_direction[1])=out;m->pose.rotation[1]=bits_float(ee_f32_mul(out,0x42652ee1));
        }
        float step[3];for(unsigned i=0;i<3;i++) {
            uint32_t bits=model_move_tick(model_channel(m,i),delta);memcpy(step+i,&bits,4);
        }
        float yaw=m->pose.rotation[1]*0.017453292f;
        model_position(m)[0]+=cosf(yaw)*step[0]+sinf(yaw)*step[2];
        model_position(m)[1]+=step[1];
        model_position(m)[2]+=-sinf(yaw)*step[0]+cosf(yaw)*step[2];
        float proposed_y=model_position(m)[1];
        /* An enemy's Jump/Fall hop (the SQ_xDMG knockback: MOVE Jump, WCHECK TurnY, MOVE Fall, WCHECK Landing) leaves the floor: while it rises there is no floor response and
         * while it falls only a floor at or below where it was catches it (DW4_COLLIDE_AIR), so Landing waits for the real ballistic arc. No floor edge holds an enemy: it
         * walks, hops and falls off a ledge that has no wall (DW4_COLLIDE_FALLS), and the support its query reports drives the retail floor response below. */
        int floor=model_work(m)->_isFloorCheck,air=0;
        if(m->enemy_kind && floor){beModelCtrlMoveObject *v=model_channel(m,1);air=v->_isRun && (v->_mode==4 || v->_mode==1);floor=(air?DW4_COLLIDE_AIR:1)|DW4_COLLIDE_FALLS;}
        unsigned contacts=m->collision?m->collision(m->collision_user,old,model_position(m),model_work(m)->_isWallCheck,floor,m->land):0;
        if(m->collision && m->enemy_kind && floor) {   /* HITFLOORCHECK's reply: bool 0 support (a walking model's floor, a falling model's landing), bool 1 landing */
            m->floor_signal=air?!!(contacts&4):!(contacts&2);m->land_signal=air && (contacts&4);
        }
        /* FUN_003926d0: a wall contact runs the callback a "WHit" LUACALL registered (the Mammothmon charge, SQ_WALK, ends in wht -> SQ_ATCK3). */
        if((contacts&1) && model_work(m)->_isWallCheck && model_work(m)->_luaWHit && model_ram(m)->_isRun) {
            const char *call=al_text(m->arena,model_work(m)->_luaWHit);
            if(call && model_lua_call(m,call))return -1;
        }
        /* Legacy position-only consumers retain their completion boundary (an enemy keeps it too, so the landing of a knockback hop or an SQ_FALL ends the
         * Landing wait in the tick it happens). The player publishes explicit floor results, consumed after waits. */
        if((m->floor_signal<0 || m->enemy_kind) && model_channel(m,1)->_isRun && model_channel(m,1)->_mode==1 &&
           model_position(m)[1]>proposed_y){model_channel(m,1)->_isRun=0;model_channel(m,1)->_speed=0;}
    }
    m->previous=now;m->sampled=1;
    int done=dw4_action2_host_tick(&m->clock,now);
    if(m->clock.error){snprintf(m->error,sizeof(m->error),"model Action2 error %d",m->clock.error);return -1;}
    model_fade_events(m);
    /* The player's attack-chain waits (beNDMWMdlPlayer::vfunc_39 at 0x3d31f0, decoded from the instructions): the Cross button (0x4000)
     * held-state decides whether a combo continues. Atck01: when the action completes, continue the chain if Cross was held throughout,
     * else SQ_WAIT; Atck02: SQ_WAIT as soon as Cross is released, continue when the action completes; Atck03: continue once released. */
    if((model_wait(m)!=NULL) && m->player_kind && model_wait(m) && !strncmp(model_wait(m),"Atck0",5)) {
        int cross=model_work(m)->_isOnCtrl && (m->player_pad&0x4000);
        if(!strcmp(model_wait(m),"Atck01")) {
            if(!m->atck_state){m->atck_released=0;m->atck_state=1;}
            if(!cross)m->atck_released=1;
            if(done){
                model_wait_clear(m);m->atck_state=0;
                if(m->atck_released)return dw4_modelctrl_start(m,"SQ_WAIT");
                if(dispatch(m))return -1;
            }
        } else if(!strcmp(model_wait(m),"Atck02")) {
            if(!cross)return dw4_modelctrl_start(m,"SQ_WAIT");
            if(done){model_wait_clear(m);if(dispatch(m))return -1;}
        } else if(!strcmp(model_wait(m),"Atck03")) {
            if(!cross){model_wait_clear(m);if(dispatch(m))return -1;}
        }
    } else
    if((model_wait(m)!=NULL) && (model_wait(m) && !strcmp(model_wait(m),"Moving")?
        !model_channel(m,0)->_isRun && !model_channel(m,2)->_isRun:
        model_wait(m) && strcmp(model_wait(m),"Action")?
        !model_channel(m,1)->_isRun:done)){model_wait_clear(m);if(dispatch(m))return -1;}
    /* 395b50: completion/sequence dispatch precedes 3951e0, then subcommands
     * and floor response. Negative authored counts are permanent. */
    if(model_ram(m)->_isRun)model_float_store(&model_work(m)->_mutekiCount,dw4_model_muteki_tick(model_float_bits(&model_work(m)->_mutekiCount),frame_delta));
    if(model_ram(m)->_isRun){
        model_pose_publish(m);
        if(dw4_modelsubcom_step_events(m->arena,al_handle(model_work(m)->_subCommand),system_frame,model_subcommand_event,m)){
            if(!m->error[0])snprintf(m->error,sizeof m->error,"model subcommand update/delivery failed");
            return -1;}
    }
    if(model_ram(m)->_isRun && (m->player_kind || m->enemy_kind) && m->floor_signal>=0) {
        beModelCtrlMoveObject *vertical=model_channel(m,1);
        int response=dw4_model_floor_response(model_work(m)->_isFloorCheck,model_work(m)->_isFallCheck,
            vertical->_isRun && vertical->_mode==4,vertical->_isRun && vertical->_mode==1,
            m->floor_signal,m->land_signal,!strcmp(dw4_modelctrl_sequence(m),"SQ_SLEP"));
        if(response==DW4_FLOOR_ADJUST){vertical->_isRun=0;vertical->_speed=0;}
        /* HITFLOORCHECK found no support: 3926d0 sends the model "SQ_FALL". Every KIND_ENEMY e_* and most f_* packs have one; a model without it (the g_* turrets, f_luce2,
         * f_devl21..23) has no recovered fall motion and keeps its place. */
        else if(response==DW4_FLOOR_FALL && (find_seq(m,"SQ_FALL")>=0 || m->player_kind) && dw4_modelctrl_start(m,"SQ_FALL"))return -1;
    }
    return 0;
}
void dw4_modelctrl_collide(dw4_modelctrl *m,dw4_modelctrl_collision collision,void *user)
{if(m){m->collision=collision;m->collision_user=user;}}
void dw4_modelctrl_player_floor(dw4_modelctrl *m,int supported,int landed)
{if(m && m->player_kind){m->floor_signal=!!supported;m->land_signal=!!landed;}}
size_t dw4_modelctrl_motion_count(const dw4_modelctrl *m){return m?m->nduration:0;}
const char *dw4_modelctrl_motion_name(const dw4_modelctrl *m,size_t i){return m && i<m->nduration?m->duration[i].name:NULL;}
int dw4_modelctrl_has_near_map(const dw4_modelctrl *m)
{return m && m->nmap && !strcmp(m->map[0].target_type,"NEAR");}
int dw4_modelctrl_nearest(dw4_modelctrl *m,dw4_modelctrl_near near,void *user)
{
    if(!m || (near && (!m->nmap || strcmp(m->map[0].target_type,"NEAR"))))return -1;
    m->near=near;m->near_user=user;
    if(near){model_ai(m)->_mapNo=0;
        }
    else model_ai(m)->_mapNo=-1;
    model_ai_timer_clear(m);return 0;
}
int dw4_modelctrl_player_input(dw4_modelctrl *m,int walking,float yaw)
{
    if(!m || !m->player_kind || !isfinite(yaw))return -1;
    m->player_walking=!!walking;m->player_yaw=yaw;return 0;
}
int dw4_modelctrl_label(dw4_modelctrl *m,const char *sequence,const char *label)
{
    if(!m || !sequence || !label)return -1;
    int index=find_seq(m,sequence);if(index<0)return -1;
    for(size_t i=0;i<m->seq[index].n;i++)if(!strcmp(m->seq[index].cmd[i].type,"beModelCtrlLABEL") &&
        !strcmp(m->seq[index].cmd[i].name,label)){int32_t name=al_string(m->arena,m->seq[index].cmd[i].name);if(!name)return -1;
            int32_t *labels=al_words(m->arena,model_work(m)->_labelNameList);al_free(m->arena,labels[index]);labels[index]=name;
            al_words(m->arena,model_work(m)->_labelOffsetList)[index]=(int32_t)i;return 0;}
    return -1;
}
int dw4_modelctrl_has_sequence(const dw4_modelctrl *m,const char *sequence){return m && sequence && find_seq((dw4_modelctrl *)m,sequence)>=0;}
/* Gives `to` the weapon section `from` was set to (the revive sequences SQ_CMBK / SQ_CMBK02 follow the player's SQ_WAIT section). */
int dw4_modelctrl_label_copy(dw4_modelctrl *m,const char *from,const char *to)
{
    if(!m || !from || !to)return -1;
    int index=find_seq(m,from);if(index<0)return -1;
    const char *label=model_label(m,(size_t)index);
    return label && *label?dw4_modelctrl_label(m,to,label):-1;
}
int dw4_modelctrl_active(const dw4_modelctrl *m) { return m && model_ram(m)->_isRun; }
int dw4_modelctrl_drawable(const dw4_modelctrl *m) { return m && model_ram(m)->_isRun && !m->clock.hidden; }
float dw4_modelctrl_alpha(const dw4_modelctrl *m) {
    if(!m || !model_ram(m)->_isRun || m->clock.hidden)return 0;
    const beAction2InfoWork *w=model_action_work(m);
    if(!w->_fadeSt0 || (w->_fadeSt0==3 && m->fade_in))return 1;
    float value=w->_fadeValue;return value<0?0:value>1?1:value;
}
int dw4_modelctrl_frozen(const dw4_modelctrl *m) { return m && model_ram(m)->_isRun && model_work(m)->_isOnFreeze; }
const char *dw4_modelctrl_sequence(const dw4_modelctrl *m) {return m && model_ram(m)->_isRun?al_text(m->arena,model_work(m)->_seqCodeName):NULL;}
const char *dw4_modelctrl_action(const dw4_modelctrl *m) {return m && model_ram(m)->_isRun?dw4_action2_host_name(&m->clock):NULL;}
/* Action2 node time is the clock minus the running action's start. A model whose sequences never
 * ran an ACTION (i_stpnl06's empty SQ_WAIT) is not animated: its nodes keep their authored initial
 * transforms, so sampling the raw clock would wrongly clamp to the end of an embedded animation. */
int64_t dw4_modelctrl_time(const dw4_modelctrl *m) {return m && dw4_action2_host_started(&m->clock)?dw4_action2_host_node_time(&m->clock,m->now):0;}
const char *dw4_modelctrl_error(const dw4_modelctrl *m) {return m?m->error:"no model controller";}
void dw4_modelctrl_actor_state(const dw4_modelctrl *m,dw4_modelctrl_actor *out) {
    if(m && out){memset(out,0,sizeof *out);memcpy(out->position,model_position(m),12);memcpy(out->rotation,m->pose.rotation,12);
        for(unsigned i=0;i<4;i++){memcpy(out->channel+i,model_channel(m,i),sizeof(dw4_npc_motion));memset(out->channel[i].reserved,0,sizeof out->channel[i].reserved);}
        out->control=model_work(m)->_ctrlSt0;out->enabled=model_work(m)->_isOnCtrl;
        out->wall_check=model_work(m)->_isWallCheck;out->floor_check=model_work(m)->_isFloorCheck;out->fall_check=model_work(m)->_isFallCheck;
        out->muteki=model_float_bits(&model_work(m)->_mutekiCount);
        dw4_action2_record r=dw4_action2_host_records(&m->clock);
        const igAnimation *animation=DW4_ARENA_OBJ(r.arena,igAnimation,r.animation),*old=DW4_ARENA_OBJ(r.arena,igAnimation,r.previous_animation);
        const igAnimationState *state=DW4_ARENA_OBJ(r.arena,igAnimationState,r.motion),*previous=DW4_ARENA_OBJ(r.arena,igAnimationState,r.previous_motion);
        out->motion=al_text(r.arena,animation->_name);out->previous_motion=al_text(r.arena,old->_name);
        out->motion_duration_ns=animation->_duration;out->blend_ns=state->_blendDuration;out->motion_loop=m->clock.motion_loop;
        out->motion_ns=(int64_t)((uint64_t)(m->now>>18)*262144u+(uint64_t)state->_timeBias);
        out->previous_motion_ns=(int64_t)((uint64_t)(m->now>>18)*262144u+(uint64_t)previous->_timeBias);}

}
void dw4_modelctrl_observe(dw4_modelctrl *m,dw4_modelctrl_trace trace,void *user) {
    if(m){m->trace=trace;m->trace_user=user;}
}
static int equal(dw4_script_value v,const char *s) {
    return s && v.type==DW4_SCRIPT_STRING && v.string && v.length==strlen(s) && !memcmp(v.string,s,v.length);
}
/* The status messages of vfunc_47: SETxxx carry "I<n>/I<n>/..." (n == 5), CLEARSTATUS and ALLCLEARSTATUS none (n == 4). */
static int status_message_kind(const dw4_script_value *a,size_t n)
{
    static const char *const set[]={"SETPOISON","SETSLEEP","SETSTUN","SETBIND","SETATTACKDOWN","SETPOWERDOWN","SETSPEEDUP","SETPOWERUP","SETREFRACT","SETRAREICON"};
    if(n==4)return equal(a[3],"CLEARSTATUS") || equal(a[3],"ALLCLEARSTATUS");
    for(unsigned i=0;i<sizeof set/sizeof *set;i++)if(equal(a[3],set[i]))return a[4].type==DW4_SCRIPT_STRING && a[4].string;
    return 0;
}
static dw4_status status_load(dw4_modelctrl *m)
{dw4_status s=status_record_read(m);if(m->status_host.load)m->status_host.load(m->status_host.user,&s);return s;}
static void status_store(dw4_modelctrl *m,dw4_status *s,const dw4_status_tick_result *r)
{status_record_write(m,s);if(m->status_host.store)m->status_host.store(m->status_host.user,s,r);
 m->status_snapshot.lists_dirty=s->lists_dirty;}
const dw4_status *dw4_modelctrl_status(const dw4_modelctrl *m)
{
    if(!m || !m->has_status)return NULL;
    ((dw4_modelctrl *)m)->status_snapshot=status_record_read(m);return &m->status_snapshot;
}
void dw4_modelctrl_status_player(dw4_modelctrl *m,const dw4_status_player_host *host)
{if(m)m->status_host=host?*host:(dw4_status_player_host){0};}
int dw4_modelctrl_cure_poison(dw4_modelctrl *m)
{
    if(!m || !m->has_status || !model_ram(m)->_isRun)return 0;
    dw4_status state=status_load(m);
    int cured=dw4_status_cure_poison(&state);
    status_store(m,&state,NULL);   /* no stat list changed: the host stores nothing and does not recalculate */
    return cured;
}
static int model_status_tick_impl(dw4_modelctrl *m,int32_t *hp,dw4_status_tick_result *out)
{
    dw4_status_tick_result res={0};
    if(out)*out=res;
    if(!m || !hp || !m->has_status || !model_ram(m)->_isRun)return 0;
    /* The model's own clock, so a frozen model (ONFREEZE) holds its timers; the first frame only latches it. */
    int64_t dt=m->status_clock_valid && m->now>m->status_clock?m->now-m->status_clock:0;
    m->status_clock=m->now;m->status_clock_valid=1;
    dw4_status state=status_load(m);
    state.ready=model_work(m)->_isOnCtrl;   /* InfoWork+0x44 is _isOnCtrl: the timers wait while control is off */
    dw4_status_tick(&state,dt,dw4_modelctrl_sequence(m),hp,&res);
    status_store(m,&state,&res);
    if(out)*out=res;
    return status_sequence(m,res.sequence);
}
/* The SD transport keeps encoded values as strings. Recover only the typed
 * operands consumed by SETEFFECT/SETSOUND; reject truncated/extra operands. */
static int model_subcommand_message(dw4_modelctrl *m,int effect,const dw4_script_value *value)
{
    if(value->type!=DW4_SCRIPT_STRING || !value->string || value->length>=512 || memchr(value->string,0,value->length))return -1;
    char text[512];memcpy(text,value->string,value->length);text[value->length]=0;
    char *strings[2]={0},*save=NULL;unsigned ns=0,nf=0,nv=0,nb=0;
    float frame=0,vec[2][3]={{0}};uint8_t flags[2]={0};
    for(char *t=strtok_r(text,"/",&save);t;t=strtok_r(NULL,"/",&save)){
        int used=0;
        if(!strncmp(t,"F<",2)){
            if(nf++ || sscanf(t,"F<%f>%n",&frame,&used)!=1 || t[used] || !isfinite(frame))return -1;
        }else if(!strncmp(t,"V<",2)){
            if(nv>=2 || sscanf(t,"V<%f,%f,%f>%n",vec[nv],vec[nv]+1,vec[nv]+2,&used)!=3 || t[used])return -1;
            for(int i=0;i<3;i++)if(!isfinite(vec[nv][i]))return -1;
            nv++;
        }else if(!strcmp(t,"TRUE") || !strcmp(t,"FALSE")){
            if(nb>=2)return -1;
            flags[nb++]=!strcmp(t,"TRUE");
        }else{if(ns>=2 || !*t)return -1;strings[ns++]=t;}
    }
    dw4_handle h=al_handle(model_work(m)->_subCommand);
    if(effect){if(ns!=2 || nv<1)return -1;
        return dw4_modelsubcom_effect(m->arena,h,strings[0],strings[1],model_float_bits(&frame),vec[0],vec[1],flags[0],flags[1]);}
    if(ns!=1 || nv || nb)return -1;
    return dw4_modelsubcom_sound(m->arena,h,strings[0],model_float_bits(&frame));
}
static int model_service_impl(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap) {
    dw4_modelctrl *m=user;*r=(dw4_script_value){0};
    if(!m || n<4 || n>5)goto bad;
    if(!strcmp(method,"querySD")) {
        if(n==4 && equal(a[3],"ISRUN")){*r=(dw4_script_value){DW4_SCRIPT_NUMBER,model_ram(m)->_isRun,NULL,0};return 0;}
        if(n==5 && equal(a[3],"ISSEQNAME") && a[4].type==DW4_SCRIPT_STRING) {
            *r=(dw4_script_value){DW4_SCRIPT_NUMBER,equal(a[4],dw4_modelctrl_sequence(m)),NULL,0};return 0;
        }
        /* MDLisStatus: CHECKSTATUS is `_timerList[id] != 0` (0x447108); a model without status work reports nothing set. */
        if(n==5 && equal(a[3],"CHECKSTATUS") && a[4].type==DW4_SCRIPT_STRING && a[4].string && a[4].length<16) {
            char name[16];memcpy(name,a[4].string,a[4].length);name[a[4].length]=0;
            int set=m->has_status?dw4_status_check(dw4_modelctrl_status(m),name):dw4_status_id(name)>=0?0:-1;
            if(set<0){snprintf(error,cap,"unknown status name %s",name);return -1;}
            *r=(dw4_script_value){DW4_SCRIPT_NUMBER,set,NULL,0};return 0;
        }
    } else if(!strcmp(method,"sd")) {
        if(n==5 && (equal(a[3],"SETEFFECT") || equal(a[3],"SETSOUND"))){
            if(!model_ram(m)->_isRun)return 0;
            if(model_subcommand_message(m,equal(a[3],"SETEFFECT"),a+4))goto bad;
            return 0;
        }
        /* 396a80 cases 20/21: only generated RAM with Work is affected.
         * Newly generated menu slots therefore keep their independent clocks. */
        if(n==4 && (equal(a[3],"ONFREEZE") || equal(a[3],"OFFREEZE"))){
            if(model_ram(m)->_isRun){
                if(!m->raw_sampled){m->raw_previous=m->now;m->raw_sampled=1;}
                model_work(m)->_isOnFreeze=equal(a[3],"ONFREEZE");
            }return 0;
        }
        if(n==4 && (equal(a[3],"ONCTRL") || equal(a[3],"OFCTRL"))) {
            model_work(m)->_isOnCtrl=equal(a[3],"ONCTRL");return 0;
        }
        if(n==5 && equal(a[3],"MOVETRANS") && a[4].type==DW4_SCRIPT_STRING &&
           a[4].string && a[4].length<256 && !memchr(a[4].string,0,a[4].length)) {
            char text[256];float pos[3],rot[3];int used=0;
            memcpy(text,a[4].string,a[4].length);text[a[4].length]=0;
            if(sscanf(text,"V<%f,%f,%f>/V<%f,%f,%f>%n",pos,pos+1,pos+2,rot,rot+1,rot+2,&used)!=6 ||
               (size_t)used!=a[4].length)goto bad;
            for(unsigned i=0;i<3;i++)if(!isfinite(pos[i]) || !isfinite(rot[i]))goto bad;
            if(model_ram(m)->_isRun){memcpy(model_position(m),pos,sizeof pos);memcpy(m->pose.rotation,rot,sizeof rot);
                (model_work(m)->_direction[1])=(model_work(m)->_targetDirection[1])=ee_f32_mul(float_bits(rot[1]),0x3c8efa35);model_pose_write(m);}
            return 0;
        }
        if(n==4 && equal(a[3],"REMOVE")){dw4_modelctrl_remove(m);return 0;}
        /* MDLsetSD from a hit script: SETLABEL "SQ_xDMG/<element>" selects the element's section of the damage sequence. */
        if(n==5 && equal(a[3],"SETLABEL") && a[4].type==DW4_SCRIPT_STRING && a[4].string && a[4].length<64) {
            char text[64];memcpy(text,a[4].string,a[4].length);text[a[4].length]=0;
            char *slash=strchr(text,'/');
            if(slash){*slash++=0;if(dw4_modelctrl_label(m,text,slash))dw4_modelctrl_label(m,text,"common");}
            return 0;
        }
        /* The status messages go to the model's status work; like the other direct messages they are ignored on an inactive slot. A player's lists
         * are loaded from its record first and stored (with the recalculation the result asks for) afterwards. */
        if(status_message_kind(a,n)) {
            m->status_commands++;
            if(!model_ram(m)->_isRun || !m->has_status)return 0;
            char name[24],args[128];
            if(a[3].length>=sizeof name || (n==5 && a[4].length>=sizeof args))goto bad;
            memcpy(name,a[3].string,a[3].length);name[a[3].length]=0;
            if(n==5){memcpy(args,a[4].string,a[4].length);args[a[4].length]=0;}
            dw4_status_tick_result res;
            dw4_status state=status_load(m);
            if(dw4_status_message(&state,name,n==5?args:NULL,&res)){snprintf(error,cap,"invalid status message %s(%s)",name,n==5?args:"");return -1;}
            status_store(m,&state,&res);
            if(status_sequence(m,res.sequence)){snprintf(error,cap,"%s",m->error);return -1;}
            return 0;
        }
        int generate=equal(a[3],"GENERATE");
        dw4_script_value v=n==5 && generate?a[4]:n==4?a[3]:(dw4_script_value){0};
        if(generate && n==4)v=(dw4_script_value){DW4_SCRIPT_STRING,0,"SQ_WAIT",7};
        if(v.type==DW4_SCRIPT_STRING && v.string && !memchr(v.string,0,v.length)) {
            char *name=malloc(v.length+1);if(!name)goto bad;
            memcpy(name,v.string,v.length);name[v.length]=0;
            /* Retail direct sequence messages are ignored on inactive slots.
             * GENERATE is the creation path; the explicit start API is also
             * used by native owners to create their first sequence. */
            int positioned=0,rotated=0;
            float position[3],rotation[3];char *params=generate?strchr(name,'/'):NULL;
            /* 396a80 GENERATE selects SQ_WAIT without a string operand.
             * Vector-only optional payloads are transforms, not seq names. */
            if(generate && !strncmp(name,"V<",2)) {
                int used=0;
                const char *seq_after=NULL;
                if(sscanf(name,"V<%f,%f,%f>/V<%f,%f,%f>%n",position,position+1,position+2,
                    rotation,rotation+1,rotation+2,&used)==6 && (!name[used] || name[used]=='/')){rotated=1;if(name[used]=='/')seq_after=name+used+1;}
                else if(sscanf(name,"V<%f,%f,%f>%n",position,position+1,position+2,&used)==3 && (!name[used] || name[used]=='/')){if(name[used]=='/')seq_after=name+used+1;}
                else {free(name);goto bad;}
                for(unsigned i=0;i<3;i++)if(!isfinite(position[i]) || (rotated && !isfinite(rotation[i]))){free(name);goto bad;}
                /* "V<pos>/V<rot>/SQ_OPEN0" (the point-message cursor): the transform, then the sequence to start. */
                positioned=1;if(seq_after && *seq_after){memmove(name,seq_after,strlen(seq_after)+1);}else strcpy(name,"SQ_WAIT");params=NULL;
            }
            if(params) {
                *params++=0;int used=0;
                /* "SEQ/V<position>" or, as the vector-only form above, "SEQ/V<position>/V<rotation>" (stagML14's GENERATEs). */
                if(sscanf(params,"V<%f,%f,%f>/V<%f,%f,%f>%n",position,position+1,position+2,
                    rotation,rotation+1,rotation+2,&used)==6 && !params[used])rotated=1;
                else if(sscanf(params,"V<%f,%f,%f>%n",position,position+1,position+2,&used)!=3 || params[used]){free(name);goto bad;}
                for(unsigned i=0;i<3;i++)if(!isfinite(position[i]) || (rotated && !isfinite(rotation[i]))){free(name);goto bad;}
                positioned=1;
            }
            int rc=(!model_ram(m)->_isRun && !generate && find_seq(m,name)>=0)?0:start_sequence(m,name,generate);
            if(!rc && positioned)memcpy(model_position(m),position,sizeof position);
            if(!rc && rotated){memcpy(m->pose.rotation,rotation,sizeof rotation);
                (model_work(m)->_direction[1])=(model_work(m)->_targetDirection[1])=ee_f32_mul(float_bits(rotation[1]),0x3c8efa35);model_pose_write(m);}
            free(name);
            if(rc)snprintf(error,cap,"%s",m->error);
            return rc;
        }
    }
bad:
    snprintf(error,cap,"unsupported model controller %s",method);return -1;
}

unsigned dw4_modelctrl_long_actions(const dw4_modelctrl *m){return m?m->long_actions:0;}
int dw4_modelctrl_talk_boxes(const dw4_modelctrl *m,const float **boxes,size_t *count)
{
    if(!m || !boxes || !count)return -1;
    *boxes=m->hit_boxes;*count=m->nhit_boxes;return m->hit_player_talk!=0;
}
void dw4_modelctrl_actor_matrix(const dw4_modelctrl_actor *actor,float matrix[16])
{
    memset(matrix,0,64);matrix[0]=matrix[5]=matrix[10]=matrix[15]=1;
    for(unsigned z=0;z<3;z++) {
        unsigned a=(z+1)%3,b=(z+2)%3;float angle=actor->rotation[z]*.017453292519943295f;
        float axis[16]={0},product[16];axis[0]=axis[5]=axis[10]=axis[15]=1;
        axis[a*4+a]=axis[b*4+b]=cosf(angle);axis[a*4+b]=sinf(angle);axis[b*4+a]=-sinf(angle);
        for(unsigned r=0;r<4;r++)for(unsigned c=0;c<4;c++) {
            float v=0;for(unsigned k=0;k<4;k++)v+=matrix[4*r+k]*axis[4*k+c];product[4*r+c]=v;
        }
        memcpy(matrix,product,64);
    }
    memcpy(matrix+12,actor->position,12);
}
static int model_talk_hit_impl(dw4_modelctrl *m,const float world[16],const dw4_model_talk_probe *probe)
{
    if(!m || !world || !probe)return -1;
    /* NPC path of396a80 case6; the player/player damage exception belongs to
     * the combat receiver and is deliberately outside this talk consumer. */
    if(!model_ram(m)->_isRun || !m->hit_player_talk || !model_work(m)->_isOnCtrl ||
       ee_f32_cmp(model_float_bits(&model_work(m)->_mutekiCount),0) || !strcmp(dw4_modelctrl_sequence(m),"SQ_ERAS"))return 0;
    for(unsigned i=0;i<16;i++)if(!isfinite(world[i]) || !isfinite(probe->source_world[i]))goto invalid;
    for(unsigned i=0;i<6;i++)if(!isfinite(probe->box[i]))goto invalid;
    if(!m->nhit_boxes)return 0;
    if(!m->hit_world_boxes) {
        m->hit_world_boxes=malloc(m->nhit_boxes*6*sizeof(float));
        if(!m->hit_world_boxes){snprintf(m->error,sizeof m->error,"model hit-body allocation failed");return -1;}
    }
    if(!m->hit_cached || m->hit_timestamp!=probe->world_ns) {
        for(size_t i=0;i<m->nhit_boxes;i++)dw4_hitbox_fixed_world(m->hit_boxes+6*i,world,m->hit_world_boxes+6*i);
        m->hit_cached=1;m->hit_timestamp=probe->world_ns;
    }
    size_t box=0;while(box<m->nhit_boxes && !dw4_hitbox_intersects(m->hit_world_boxes+6*box,probe->box))box++;
    if(box==m->nhit_boxes)return 0;
    if(!m->scripts || !m->model || !m->model->info_name) {
        snprintf(m->error,sizeof m->error,"model talk callback context unavailable");return -1;
    }
    char script[256];int n=snprintf(script,sizeof script,"hit_%s.lua",m->model->info_name);
    if(n<0 || (size_t)n>=sizeof script)goto invalid;
    /* Objects without a hit script (doors, NPCs, decor) simply do not react to bullets. */
    if(!m->enemy_kind && !dw4_scriptengine_has_script(m->scripts,script))return 0;
    dw4_script_model snapshot=model_script_snapshot(m);snapshot.call_name="Hit";int32_t before=(*model_hp(m,0));
    dw4_model_contact contact={.bullet_kind=60000,.bullet_box=(int32_t)box,.shoot_ram_no=probe->shoot_ram_no,.damage_turn=1};
    memcpy(contact.world,world,sizeof contact.world);
    /* Positions used for the turn were captured before the original script. */
    ee_f32 dx=ee_f32_sub(float_bits(probe->source_world[12]),float_bits(world[12]));
    ee_f32 dz=ee_f32_sub(float_bits(probe->source_world[14]),float_bits(world[14]));
    if(dw4_scriptengine_contact_event(m->scripts,m->scope,script,&snapshot,&contact)) {
        snprintf(m->error,sizeof m->error,"model Hit: %.230s",dw4_scriptengine_error(m->scripts));return -1;
    }
    model_bridge_pull(m);
    if((*model_hp(m,0))==before)(*model_hp(m,0))=snapshot.hp;
    if(model_ram(m)->_isRun && contact.damage_turn) {
        (model_work(m)->_direction[1])=(model_work(m)->_targetDirection[1])=dw4_model_ai_direction(dx,dz,0);   /* retail: the victim snaps to face the attacker and keeps that yaw (the AI turn has nothing left to do), #3083 */
        m->pose.rotation[1]=bits_float(ee_f32_mul((model_work(m)->_direction[1]),0x42652ee1));
    }
    return 1;
invalid:
    snprintf(m->error,sizeof m->error,"invalid model talk probe");return -1;
}
/* Diagnostic: every command type/name of every sequence, one per line, with its sequence. */
void dw4_modelctrl_census(const dw4_modelctrl *m,FILE *out)
{
    if(!m)return;
    for(size_t i=0;i<m->nseq;i++)for(size_t j=0;j<m->seq[i].n;j++)
        fprintf(out,"%s %s %s\n",m->seq[i].name,m->seq[i].cmd[j].type,m->seq[i].cmd[j].name);
    for(size_t i=0;i<m->naction;i++){
        fprintf(out,"ACTION %s components %zu supported %d:",m->action[i].name,m->action[i].n,m->action[i].supported);
        for(size_t j=0;j<m->action[i].n;j++){const dw4_action2_component *c=m->action[i].cmd+j;float a,b;memcpy(&a,&c->first,4);memcpy(&b,&c->last,4);fprintf(out," [%d %s %g %g %s",c->kind,c->name,a,b,c->loop?c->loop:"-");
            if(c->kind==DW4_A2_MOTIONSET)fprintf(out," d=%lld",(long long)m->action[i].duration[j]);   /* the animation's length in ns (the host's motion wait) */
            fputc(']',out);}
        fputc('\n',out);
    }
}

const dw4_modelctrl_hitbox *dw4_modelctrl_hitboxes(const dw4_modelctrl *m,unsigned *count)
{
    unsigned n=m?(unsigned)model_hitbox_count(m):0;if(n>8)n=8;if(count)*count=n;if(!m)return NULL;
    beModelCtrlSubCom *s=DW4_ARENA_OBJ(m->arena,beModelCtrlSubCom,al_handle(model_work(m)->_subCommand));
    int32_t *v=al_words(m->arena,s->_comList);dw4_modelctrl_hitbox *out=((dw4_modelctrl *)m)->hitbox_snapshot;
    for(unsigned i=0,j=0;i<n;j++){
        if(dw4_modelsubcom_type(m->arena,al_handle(v[j]))!=DW4_SC_HITBOX)continue;
        const beModelCtrlSCHitBox *b=DW4_ARENA_OBJ(m->arena,beModelCtrlSCHitBox,al_handle(v[j]));
        out[i]=(dw4_modelctrl_hitbox){.kind=b->_kind,.start_frames=b->_startFrame,.end_frames=b->_endFrame,
            .length_frames=b->_endFrame==100000000.0f?-1:b->_endFrame-b->_startFrame,.object=al_handle(v[j]),.run_frame=b->_runFrame};
        memcpy(out[i].offset,b->_offset,12);memcpy(out[i].size,b->_boxSize,12);i++;
    }
    return out;
}

/* Combat bullet consumer (the player/enemy-bullet branch of 396a80's CHKBULLET): a source volume against this model's body boxes. */
static int model_bullet_hit_impl(dw4_modelctrl *m,const float world[16],const dw4_model_bullet *b)
{
    if(!m || !world || !b)return -1;
    /* ASSUMPTION: a support volume (attack numbers 80000..89999, an enemy-group bullet on the
     * caster's own body) ignores the MUTEKI counter. The port's player carries a positive count on
     * the very tick the cast starts (observed; its source was not traced) and a damage sequence
     * leaves 30 frames of it, so honouring it would drop a Heal cast at the start of the sequence
     * or right after a hit; the gate of 0x396a80 case 6 for these kinds was not read. */
    int support=b->group==DW4_BULLET_ENEMY && b->kind>=80000 && b->kind<90000;
    if(!model_ram(m)->_isRun || !model_work(m)->_isOnCtrl || !m->nhit_boxes || (!support && ee_f32_cmp(model_float_bits(&model_work(m)->_mutekiCount),0)) || !strcmp(dw4_modelctrl_sequence(m),"SQ_ERAS"))return 0;
    if(!(b->group==DW4_BULLET_PLAYER?m->hit_player_bullet:m->hit_enemy_bullet))return 0;
    for(unsigned i=0;i<16;i++)if(!isfinite(world[i]) || !isfinite(b->source_world[i]))goto invalid;
    for(unsigned i=0;i<6;i++)if(!isfinite(b->box[i]))goto invalid;
    if(!m->hit_world_boxes) {
        m->hit_world_boxes=malloc(m->nhit_boxes*6*sizeof(float));
        if(!m->hit_world_boxes){snprintf(m->error,sizeof m->error,"model hit-body allocation failed");return -1;}
    }
    if(!m->hit_cached || m->hit_timestamp!=b->world_ns) {
        for(size_t i=0;i<m->nhit_boxes;i++)dw4_hitbox_fixed_world(m->hit_boxes+6*i,world,m->hit_world_boxes+6*i);
        m->hit_cached=1;m->hit_timestamp=b->world_ns;
    }
    size_t box=0;while(box<m->nhit_boxes && !dw4_hitbox_intersects(m->hit_world_boxes+6*box,b->box))box++;
    if(box==m->nhit_boxes)return 0;
    if(!m->scripts || !m->model || !m->model->info_name){snprintf(m->error,sizeof m->error,"model bullet callback context unavailable");return -1;}
    char script[256];int n=snprintf(script,sizeof script,"hit_%s.lua",m->model->info_name);
    if(n<0 || (size_t)n>=sizeof script)goto invalid;
    dw4_script_model snapshot=model_script_snapshot(m);snapshot.call_name="Hit";int32_t before=(*model_hp(m,0));
    dw4_model_contact contact={.bullet_kind=b->kind,.bullet_box=(int32_t)box,.shoot_ram_no=b->shoot_ram_no,.damage_turn=1,
        .fight=b->fight,.target_row=model_work(m)->_recNo,.target_max_hp=(*model_hp(m,1)),.target_slot=model_ram(m)->_ramNo,.source_row=b->source_row,
        .receiver_status=dw4_modelctrl_status(m),.source_status=b->source_status,.sequence=dw4_modelctrl_sequence(m),.bullet_name=b->name};
    memcpy(contact.world,world,sizeof contact.world);
    ee_f32 dx=ee_f32_sub(float_bits(b->source_world[12]),float_bits(world[12]));
    ee_f32 dz=ee_f32_sub(float_bits(b->source_world[14]),float_bits(world[14]));
    m->last_contact=contact;m->has_last_contact=1;
    if(dw4_scriptengine_contact_event(m->scripts,m->scope,script,&snapshot,&contact)) {
        snprintf(m->error,sizeof m->error,"model Hit: %.230s",dw4_scriptengine_error(m->scripts));return -1;
    }
    model_bridge_pull(m);
    if((*model_hp(m,0))==before)(*model_hp(m,0))=snapshot.hp;
    if(model_ram(m)->_isRun && contact.damage_turn) {
        (model_work(m)->_direction[1])=(model_work(m)->_targetDirection[1])=dw4_model_ai_direction(dx,dz,0);   /* retail: the victim snaps to face the attacker and keeps that yaw (the AI turn has nothing left to do), #3083 */
        m->pose.rotation[1]=bits_float(ee_f32_mul((model_work(m)->_direction[1]),0x42652ee1));
    }
    return 1;
invalid:
    snprintf(m->error,sizeof m->error,"invalid model bullet");return -1;
}

void dw4_modelctrl_player_pad(dw4_modelctrl *m,uint32_t held){if(m)m->player_pad=held;}

int64_t dw4_modelctrl_now(const dw4_modelctrl *m){return m?m->now:0;}

dw4_modelctrl_record dw4_modelctrl_records(const dw4_modelctrl *m)
{return m?(dw4_modelctrl_record){m->arena,m->ram,m->data,m->work,m->node,dw4_action2_host_records(&m->clock)}:(dw4_modelctrl_record){0};}
void dw4_modelctrl_bind_record(dw4_modelctrl *m,int32_t slot,dw4_handle info,dw4_handle manager)
{if(m){beBaseInfoRam *r=model_ram(m);r->_ramNo=slot;r->_parentInfo=(int32_t)info.off;r->_parentManager=(int32_t)manager.off;}}

int dw4_modelctrl_tick_frame(dw4_modelctrl *m,int64_t ns,uint32_t system_frame)
{if(m)m->subcommand_clock=ns;model_bridge_pull(m);int rc=model_tick_impl(m,ns,system_frame);model_pose_publish(m);model_bridge_pull(m);model_bridge_push(m);return rc;}
int dw4_modelctrl_tick(dw4_modelctrl *m,int64_t ns)
{
    /* Standalone convenience sampler. Session owners supply their shared frame
     * explicitly so fresh/inactive slots never accumulate time since creation. */
    uint32_t frame=m && m->sampled?dw4_modelsubcom_frame(m->subcommand_clock,ns):0;
    return dw4_modelctrl_tick_frame(m,ns,frame);
}
int dw4_modelctrl_service(void *u,const char *method,const dw4_script_value *args,size_t n,dw4_script_value *r,char *error,size_t cap)
{model_bridge_pull(u);int rc=model_service_impl(u,method,args,n,r,error,cap);model_pose_publish(u);model_bridge_pull(u);model_bridge_push(u);return rc;}
int dw4_modelctrl_talk_hit(dw4_modelctrl *m,const float world[16],const dw4_model_talk_probe *p)
{model_bridge_pull(m);int rc=model_talk_hit_impl(m,world,p);model_pose_publish(m);model_bridge_pull(m);model_bridge_push(m);return rc;}
int dw4_modelctrl_bullet_hit(dw4_modelctrl *m,const float world[16],const dw4_model_bullet *b)
{model_bridge_pull(m);int rc=model_bullet_hit_impl(m,world,b);model_pose_publish(m);model_bridge_pull(m);model_bridge_push(m);return rc;}

int dw4_modelctrl_status_tick(dw4_modelctrl *m,int32_t *hp,dw4_status_tick_result *out)
{
    model_bridge_pull(m);model_bridge_push(m);int rc=model_status_tick_impl(m,hp,out);
    if(m && hp && m->has_status)*model_hp(m,0)=*hp;
    model_bridge_push(m);return rc;
}
void dw4_modelctrl_health(dw4_modelctrl *m,int32_t hp,int32_t maximum)
{if(m){model_bridge_pull(m);*model_hp(m,0)=hp;*model_hp(m,1)=maximum;model_bridge_push(m);}}

void dw4_modelctrl_matrix(const dw4_modelctrl *m,float world[16])
{if(m && world)memcpy(world,DW4_ARENA_OBJ(m->arena,beModelCtrlNode2,m->node)->_m,64);}
