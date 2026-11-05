/* First field stage (stag0101, Goblin Pass valley entrance) through the hub runtime: original start/first scripts, the authored
 * generator registry, the arrival hand-off and the draw. Headless. Enemies are not spawned yet (docs/combat.md, milestone 3):
 * a first visit stops at the scripted enemy introduction, a revisit (flag 355) restores player control. */
#include "dw4/hubruntime.h"
#include "dw4/png.h"
#include "dw4/options.h"
#include "dw4/fefont.h"
#include "dw4/frontaudio.h"
#include "dw4/fieldgen.h"
#include "dw4/fightcalc.h"
#include "dw4/fightstatus.h"
#include "dw4/fightstatus_e2p.h"
#include "dw4/fightmagic.h"
#include "dw4/magicapply.h"
#include "dw4/statusapply.h"
#include "dw4/buffapply.h"
#include "dw4/playerstats.h"
#include "dw4/igfile.h"
#include "dw4/igb.h"
#include "dw4/filelist.h"
#include "dw4/database.h"
#include "dw4/playerinit.h"
#include "dw4/hitbox.h"
#include "dw4/technique.h"
#include "../src/arenalist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct boot {dw4_playerrecords *players;dw4_scriptservices *sd;};
static int binding(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    struct boot *b=user;int rc=dw4_playerrecords_call(b->players,method,a,n,r,error,cap);if(rc<=0)return rc;
    if(!strcmp(method,"SYSgetLightMode")){*r=(dw4_script_value){DW4_SCRIPT_NUMBER,1,NULL,0};return 0;}
    return dw4_scriptservices_call(b->sd,method,a,n,r,error,cap);
}
static void flag(dw4_playerrecords *p,int number)
{
    char error[256];dw4_script_value a[2]={{DW4_SCRIPT_NUMBER,number,NULL,0},{DW4_SCRIPT_NUMBER,1,NULL,0}},r;
    assert(!dw4_playerrecords_call(p,"FLGset",a,2,&r,error,sizeof error));
}
struct downlog {int calls,slot,value;};
static int down_apply(void *u,int slot,int32_t value){struct downlog *l=u;l->calls++;l->slot=slot;l->value=value;return 0;}
static dw4_hubruntime *enter(dw4_mount *mount,const int *flags,unsigned nflags)
{
    dw4_playerrecords *players=dw4_playerrecords_open();dw4_be_state state;dw4_be_init(&state);
    struct boot host={players,dw4_scriptservices_open()};assert(players && host.sd);
    assert(dw4_scriptservices_register(host.sd,0,"GAMERAM",NULL,-1,1,dw4_playerrecords_service,players));
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&host);dw4_filelist *f=dw4_filelist_open(mount);assert(e && f);
    dw4_scriptengine_filelist(e,f);
    assert(!dw4_filelist_begin(f,e,"stagIS10",1) && !dw4_filelist_shared(f));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(f,dw4_stageobjects_route,objects) && !dw4_filelist_bind_layers(f,dw4_stageobjects_bind_layers,objects));
    char error[512];dw4_databases *db=dw4_databases_open(objects,error,sizeof error);assert(db);
    assert(!dw4_playerrecords_create(players,db,0,getenv("STARTER")?getenv("STARTER"):"p_dorumon","FldTest",error,sizeof error));
    if(getenv("STARTER")){dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",0);const char *k[]={"MHP","MMP","TSUYOSA","MAMORI","KASHIKOSA","SEISHIN","SUBAYASA","MEICHURITSU","CHIMEIRITSU","WEAPONSKILLNO","WEAPONRECNO","ATTACKDELAY","MAHIRITSU","KAIHIRITSU"};
        fprintf(stderr,"starter %s:",getenv("STARTER"));for(unsigned i=0;i<sizeof k/sizeof *k;i++){int32_t v=-99;dw4_property_number(f,k[i],&v);fprintf(stderr," %s %d",k[i],v);}fputc(10,stderr);}
    for(unsigned i=0;i<nflags;i++)flag(players,flags[i]);
    if(getenv("DW4_TEST_DIFFICULTY"))assert(!dw4_property_set_number(dw4_playerrecords_get(players,"GETCOMMON",0),"DIFFICULTY",atoi(getenv("DW4_TEST_DIFFICULTY"))));   /* the save's difficulty (title selection) */
    if(getenv("FORM")){   /* the player is one of the 16 forms: DIGIMONNO and the model name of that shinka row, stats recalculated */
        int form=atoi(getenv("FORM"));dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",0);
        const char *model=dw4_database_string(dw4_databases_get(db,"shinka"),form,"MODEL_NAME");assert(model && f);
        int32_t use[16]={0};use[form]=1;int32_t lvl=getenv("FORMLEVEL")?atoi(getenv("FORMLEVEL")):1,mhp,mmp;
        assert(!dw4_property_set_number(f,"DIGIMONNO",form) && !dw4_property_set_string(f,"DIGIMONNAME",model) && !dw4_property_set_array(f,"BASE_ISUSE",use,16) && !dw4_property_set_number(f,"LEVEL",lvl));
        assert(!dw4_playerstats_recalculate((void *)db,f) && !dw4_property_number(f,"MHP",&mhp) && !dw4_property_number(f,"MMP",&mmp) && !dw4_property_set_number(f,"HP",mhp) && !dw4_property_set_number(f,"MP",mmp));
        {int32_t t=0,m=0,sb=0,me=0,ch=0,ws=0;dw4_property_number(f,"TSUYOSA",&t);dw4_property_number(f,"MAMORI",&m);dw4_property_number(f,"SUBAYASA",&sb);dw4_property_number(f,"MEICHURITSU",&me);dw4_property_number(f,"CHIMEIRITSU",&ch);dw4_property_number(f,"WEAPONSKILLNO",&ws);
            fprintf(stderr,"form %d = %s level %d HP %d TSUYOSA %d MAMORI %d SUBAYASA %d MEICHURITSU %d CHIMEIRITSU %d WEAPONSKILLNO %d\n",form,model,lvl,mhp,t,m,sb,me,ch,ws);}
    }
    dw4_hubruntime_source src={players,&state,NULL,0};
    assert(!dw4_hubruntime_prepare(mount,&src,"stag0401",0,1,error,sizeof error));   /* other field stages stay refused */
    dw4_hubruntime *h=dw4_hubruntime_prepare(mount,&src,getenv("STAGE")?getenv("STAGE"):"stag0101",getenv("POINT")?atoi(getenv("POINT")):0,1,error,sizeof error);
    if(!h){fprintf(stderr,"stag0101: %s\n",error);exit(1);}
    /* The destination owns its snapshot; release the temporary source scene. */
    dw4_scriptengine_filelist(e,NULL);dw4_scriptengine_close(e);dw4_scriptservices_close(host.sd);
    dw4_databases_close(db);dw4_stageobjects_close(objects);dw4_filelist_close(f);dw4_playerrecords_close(players);
    return h;
}
/* Mammothmon's SQ_ATCK3 span (finding #3005): ACTN03 plays actn03 (1.517 s) and then actn04 (0.05 s), one after the other. While `on`, every tick of the
 * pilots samples the boss; `first` is the first run, `clean` the first run that ended into SQ_WAIT (its own JUMP) and so was not cut short by a hit. */
static struct {int on;unsigned run,runs,first,clean;} boss_atck3;
static void boss_atck3_sample(dw4_hubruntime *h)
{
    if(!boss_atck3.on)return;
    int atck3=0,to_wait=0;
    for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){
        const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
        if(mc && info && !strcmp(dw4_stageobject_name(info),"e_mammos") && dw4_modelctrl_active(mc)){
            if(!strcmp(dw4_modelctrl_sequence(mc),"SQ_ATCK3"))atck3=1;
            else if(!strcmp(dw4_modelctrl_sequence(mc),"SQ_WAIT"))to_wait=1;}}
    if(atck3)boss_atck3.run++;
    else if(boss_atck3.run){if(!boss_atck3.runs++)boss_atck3.first=boss_atck3.run;if(to_wait && !boss_atck3.clean)boss_atck3.clean=boss_atck3.run;boss_atck3.run=0;}
}
static void run(dw4_hubruntime *h,unsigned *frame,unsigned count,float x,float y)
{
    for(unsigned i=0;i<count;i++,(*frame)++) {
        dw4_hubruntime_input(h,x,y,0,0,0);
        if(dw4_hubruntime_tick(h,(uint64_t)*frame*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",*frame,dw4_hubruntime_error(h));exit(1);}
        boss_atck3_sample(h);
    }
}
/* Drop presentation helpers (loot mode): how many instances of a model run, and the state of a player's item-name label text. */
static unsigned running_models(dw4_hubruntime *h,const char *name)
{
    unsigned n=0;
    for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
        if(mc && info && !strcmp(dw4_stageobject_name(info),name) && dw4_modelctrl_active(mc))n++;}
    return n;
}
static const dw4_dialogue_text *label_text(dw4_hubruntime *h,unsigned slot)
{
    const dw4_dialogue *d=dw4_hubruntime_dialogue(h);char font[8];snprintf(font,sizeof font,"font%02u",slot);
    for(size_t k=0;d && k<dw4_dialogue_text_count(d);k++){const dw4_dialogue_text *t=dw4_dialogue_text_at(d,k);if(!strcmp(t->group,"ITNAMEFONT") && !strcmp(t->name,font))return t;}
    return NULL;
}
static void atk_trace(void *user,const char *sequence,const char *type,const char *name,int64_t ns)
{(void)user;fprintf(stderr,"  cmd %s %s %s @%lld\n",sequence,type,name,(long long)(ns/16666667));}
/* The floating damage number's colour (docs/dungeon-floors.md, "Floating numbers"): its model carries no vertex colours, so the
 * orange-to-white gradient with the dark outline is the numdmg.png palette itself. A compact component of saturated orange pixels
 * (the upper part of the upright glyph) with pale pixels in or just below its box is that digit; a digit drawn without the texture
 * colour (flat grey, wrong palette) has no such component. Returns the orange and pale pixel counts of the best component. */
static int popup_digit_colour(const dw4_fb *fb,const dw4_fb *before,unsigned *orange_out,unsigned *pale_out,int *orange_y,int *pale_y)
{
    /* Only pixels that changed since the frame before the number spawned count: the world has orange of its own, the player's. */
    #define ADDED(q) (abs((int)fb->rgba[4*(q)]-before->rgba[4*(q)])+abs((int)fb->rgba[4*(q)+1]-before->rgba[4*(q)+1])+abs((int)fb->rgba[4*(q)+2]-before->rgba[4*(q)+2])>40)
    #define ORANGE(p) ((p)[0]>=190 && (p)[0]-(p)[2]>=110 && (p)[1]>=70 && (p)[1]+30<=(p)[0])
    #define PALE(p) ((p)[0]>=185 && (p)[1]>=185 && (p)[2]>=185 && (p)[0]-(p)[2]<=45 && (p)[2]-(p)[0]<=45)
    size_t n=(size_t)fb->w*fb->h;uint8_t *seen=calloc(n,1);int *stack=malloc(n*sizeof *stack);int best=0;
    assert(seen && stack);*orange_out=*pale_out=0;
    for(size_t start=0;start<n;start++){
        const uint8_t *p=fb->rgba+4*start;if(seen[start] || !ORANGE(p) || !ADDED(start) || start/fb->w>=320)continue;   /* the field HUD (lower part of the frame) has its own orange */
        int top=0,x0=fb->w,x1=0,y0=fb->h,y1=0;unsigned size=0;stack[top++]=(int)start;seen[start]=1;
        while(top){
            int at=stack[--top],x=at%fb->w,y=at/fb->w;size++;
            if(x<x0)x0=x;if(x>x1)x1=x;if(y<y0)y0=y;if(y>y1)y1=y;
            for(int dy=-1;dy<=1;dy++)for(int dx=-1;dx<=1;dx++){
                int nx=x+dx,ny=y+dy;if(nx<0||ny<0||nx>=fb->w||ny>=fb->h)continue;
                size_t q=(size_t)ny*fb->w+nx;if(seen[q] || !ORANGE(fb->rgba+4*q) || !ADDED(q))continue;seen[q]=1;stack[top++]=(int)q;
            }
        }
        if(size<10 || x1-x0>40 || y1-y0>40)continue;
        unsigned pale=0;long ysum=0,oy=0,on=0;
        for(int y=y0-6;y<=y1+34;y++)for(int x=x0-8;x<=x1+8;x++){
            if(x<0||y<0||x>=fb->w||y>=fb->h)continue;
            const uint8_t *q=fb->rgba+4*((size_t)y*fb->w+x);
            if(PALE(q) && ADDED((size_t)y*fb->w+x)){pale++;ysum+=y;}else if(ORANGE(q) && y<=y1){oy+=y;on++;}
        }
        if(pale>=8 && size+pale>(unsigned)best){best=(int)(size+pale);*orange_out=size;*pale_out=pale;*orange_y=on?(int)(oy/on):0;*pale_y=(int)(ysum/(long)pale);}
    }
    free(seen);free(stack);
    #undef ADDED
    #undef ORANGE
    #undef PALE
    return best>0;
}
/* Put the Goblin back in front of the player (knock-back moves it away between swings). */
static void replace_goblin(dw4_hubruntime *h,const char *where_v)
{
    char error[512],text[96];dw4_script_value r;
    snprintf(text,sizeof text,"%s",where_v);
    dw4_script_value a[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"e_goburi",8},{DW4_SCRIPT_NUMBER,5,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,text,strlen(text)}};
    if(dw4_hubruntime_sd(h,a,5,&r,error,sizeof error)){fprintf(stderr,"place goblin: %s\n",error);exit(1);}
}
/* The stage's sound PLAY requests during a flow (typed SCSound and script SOUND PLAY): every name asked for must name a prepared clip. */
static void sound_stats(dw4_hubruntime *h,const char *what)
{
    unsigned requests=0,unresolved=0;const char *last=NULL;
    dw4_frontaudio_model_stats(dw4_lobby_audio(dw4_hubruntime_world(h)),&requests,&unresolved,&last);
    fprintf(stderr,"%s sound requests: %u, unresolved %u%s%s\n",what,requests,unresolved,last?" (last: ":"",last?last:"");
    if(last)fprintf(stderr,")\n");
    for(unsigned i=0;i<requests && i<16;i++)fprintf(stderr,"  request %u: %s\n",i,dw4_frontaudio_request_name(dw4_lobby_audio(dw4_hubruntime_world(h)),i));
    assert(unresolved==0);
}
static int control(dw4_hubruntime *h)
{dw4_lobby_control_state c;assert(!dw4_lobby_control(dw4_hubruntime_world(h),&c));return c.player_control;}
static void mat_list(dw4_mount *mount,const char *stage)
{
    dw4_igfile file={0};dw4_igb g={0};
    assert(!dw4_igfile_open_stage_pack(&file,mount,stage,0,0) && !dw4_igb_open(&g,file.data,file.len,0) && !dw4_igb_refs_open(&g));
    for(uint32_t id=0;id<g.table_n;id++)if(g.id_kind[id]==2){
        dw4_igb_record r={0};if(!dw4_igb_decode(&g,g.id_off[id],&r))continue;
        if(!strcmp(r.class_name,"beMatCtrlData") && r.name){
            uint32_t box=0;for(unsigned v=0;v<r.nvalues;v++)if(r.values[v].ordinal==3)box=r.values[v].raw;
            dw4_igb_record b={0};float lo[3]={0},hi[3]={0};
            if(box<g.table_n && dw4_igb_decode(&g,g.id_off[box],&b)){for(unsigned v=0;v<b.nvalues;v++){if(b.values[v].ordinal==2)memcpy(lo,g.data+b.values[v].voff,12);if(b.values[v].ordinal==3)memcpy(hi,g.data+b.values[v].voff,12);}dw4_igb_record_free(&b);}
            fprintf(stderr,"mat %s: (%g %g %g)..(%g %g %g)\n",r.name,lo[0],lo[1],lo[2],hi[0],hi[1],hi[2]);}
        if(!strcmp(r.class_name,"beLuaData") && r.name)fprintf(stderr,"lua %s\n",r.name);
        dw4_igb_record_free(&r);}
    dw4_igb_close(&g);dw4_igfile_close(&file);
}
static void place(dw4_hubruntime *h,const char *where);
static void place_slot(dw4_hubruntime *h,unsigned slot,const char *where);
/* Test pilot: fights like a player with the pad. Finds the nearest live enemy (any "e_" model), steps next to it facing it (a MOVETRANS stands in for walking) and
 * taps Cross with the ATTACKDELAY cooldown between swings; with no enemy alive it visits the generators that have not finished, which wakes radar generators.
 * Stops at `ticks`, when every generator is done, or when the player is down. Returns the number of enemy kills (EXP awards) seen. */
static unsigned pilot_extra;   /* co-op: the other joined slots (1..pilot_extra) follow the first player to the target and swing with it */
static int pilot_confirm;  /* dungeon floors: while a script holds control (boss intro, info windows), tap Cross like a player */
static int pilot_sticky;   /* dungeon floors: keep swinging at one enemy until it is gone instead of re-picking the nearest every swing */
static struct {char name[24];unsigned n;} boss_seq[24];static unsigned boss_seq_n;
static unsigned pilot(dw4_hubruntime *h,unsigned *frame,unsigned ticks,int verbose)
{
    dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
    dw4_modelctrl *player=dw4_lobby_player_model(dw4_hubruntime_world(h));
    const dw4_fieldgen *gen=dw4_hubruntime_fieldgen(h);
    unsigned start=*frame,kills=0,idle=0;int32_t level=0,exp0=0,hp=0;
    static float home[3];static int have_home;   /* the first standing position: offsets toward it keep the player on the floor */
    {dw4_modelctrl_actor a0;dw4_modelctrl_actor_state(player,&a0);if(!have_home && a0.position[1]>-50){memcpy(home,a0.position,12);have_home=1;}}
    dw4_property_number(p0,"LEVEL",&level);dw4_property_number(p0,"EXP",&exp0);
    size_t gi=0;
    while(*frame-start<ticks){
        if(getenv("BOSSSEQ")){   /* BOSSSEQ=<model>: tally the sequences that model runs each tick (compared with the retail sampling in findings #2926) */
            for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
                if(!info || strcmp(dw4_stageobject_name(info),getenv("BOSSSEQ")) || !dw4_modelctrl_active(mc) || !dw4_modelctrl_sequence(mc))continue;
                const char *sq=dw4_modelctrl_sequence(mc);unsigned q;
                for(q=0;q<boss_seq_n && strcmp(boss_seq[q].name,sq);q++);
                if(q==boss_seq_n && q<24){snprintf(boss_seq[q].name,sizeof boss_seq[q].name,"%s",sq);boss_seq[q].n=0;boss_seq_n++;}
                if(q<boss_seq_n)boss_seq[q].n++;}
        }
        {static int32_t last_hp=-1;int32_t before=hp;(void)before;
         if(!dw4_property_number(p0,"HP",&hp) && verbose && getenv("HPLOG") && last_hp>=0 && hp<last_hp)fprintf(stderr,"  pilot t%u: HP %d -> %d (%d)\n",*frame-start,last_hp,hp,last_hp-hp);
         last_hp=hp;}
        if(dw4_property_number(p0,"HP",&hp) || hp<=0){fprintf(stderr,"pilot: player down at tick %u\n",*frame-start);break;}
        if(!control(h)){
            if(pilot_confirm){static unsigned held;for(unsigned i=0;i<10;i++,held++){dw4_hubruntime_input(h,0,0,0,held%90<4?0x4000:0,held%90==0?0x4000:0);if(dw4_hubruntime_tick(h,(uint64_t)(*frame)++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));exit(1);}boss_atck3_sample(h);}}
            else run(h,frame,10,0,0);
            continue;}
        dw4_modelctrl_actor pa;dw4_modelctrl_actor_state(player,&pa);
        const dw4_modelctrl *best=NULL;float bd=1e30f,bp[3]={0};size_t best_k=0;int forced=0;static size_t sticky_k=SIZE_MAX;
        for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){
            const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
            dw4_script_model st;
            if(!mc || !info || (strncmp(dw4_stageobject_name(info),"e_",2) && strncmp(dw4_stageobject_name(info),"g_rock",6) && strncmp(dw4_stageobject_name(info),"g_bush",6) && strncmp(dw4_stageobject_name(info),"g_box",5) && strncmp(dw4_stageobject_name(info),"x_rock",6)) || !dw4_modelctrl_active(mc) || dw4_controllers_model_state(dw4_hubruntime_models(h),k,&st) || st.hp<=0)continue;
            dw4_modelctrl_actor ea;dw4_modelctrl_actor_state(mc,&ea);
            float dx=ea.position[0]-pa.position[0],dy=ea.position[1]-pa.position[1],dz=ea.position[2]-pa.position[2],d=dx*dx+dy*dy+dz*dz;
            if(pilot_sticky && k==sticky_k){forced=1;bd=d;best=mc;best_k=k;memcpy(bp,ea.position,12);}
            else if(!forced && d<bd){bd=d;best=mc;best_k=k;memcpy(bp,ea.position,12);}
        }
        sticky_k=best?best_k:SIZE_MAX;
        if(!best){
            /* nothing alive: visit the next generator that still has enemies to deliver */
            size_t n=dw4_fieldgen_count(gen);const dw4_gene *e=NULL;
            for(size_t t=0;t<n;t++){const dw4_gene *c=dw4_fieldgen_at(gen,(gi+t)%n);if(c->state==DW4_GENE_STARTED && (!c->spawned_total || c->remaining) && c->npoints){e=c;gi=(gi+t+1)%n;break;}}
            if(!e){if(++idle>6)break;run(h,frame,60,0,0);continue;}
            char where[96];float x=e->points[0]+(e->global?0:e->pos[0]),y=e->points[1]+(e->global?0:e->pos[1]),z=e->points[2]+(e->global?0:e->pos[2]);
            snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",x,y,z-12);place(h,where);run(h,frame,90,0,0);continue;
        }
        idle=0;
        float hx=home[0]-bp[0],hz=home[2]-bp[2],hl=sqrtf(hx*hx+hz*hz);if(hl<.01f){hx=0;hz=-1;hl=1;}
        {   /* A target that loses no HP over four swings in a row is attacking the placed player before the swing box opens (the stun-lock of docs/dungeon-floors.md): come at it from
             * another side, a quarter turn further every four misses. Targets that keep losing HP never rotate, so the usual runs are unchanged. */
            static size_t fail_k=SIZE_MAX;static int32_t fail_hp;static unsigned fails;dw4_script_model ft;
            if(!dw4_controllers_model_state(dw4_hubruntime_models(h),best_k,&ft)){
                if(best_k!=fail_k){fail_k=best_k;fail_hp=ft.hp;fails=0;}
                else if(ft.hp<fail_hp){fail_hp=ft.hp;fails=0;}
                else fails++;
            }
            unsigned quarter=(fails/4)%4;
            for(unsigned r=0;r<quarter;r++){float t=hx;hx=-hz;hz=t;}
        }
        float px=bp[0]+hx/hl*7,pz=bp[2]+hz/hl*7;                  /* 7 units from the enemy on the side of home, facing it */
        char where[96];snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,%g,0>",px,bp[1],pz,atan2f(bp[0]-px,bp[2]-pz)*57.29578f);place(h,where);
        for(unsigned q=1;q<=pilot_extra;q++){   /* the mates stand 6 units to the side of the target, each on its own bearing, facing it */
            float a=1.2f*(float)q,ox=bp[0]+(px-bp[0])*cosf(a)-(pz-bp[2])*sinf(a),oz=bp[2]+(px-bp[0])*sinf(a)+(pz-bp[2])*cosf(a);
            char w2[96];snprintf(w2,sizeof w2,"V<%g,%g,%g>/V<0,%g,0>",ox,bp[1],oz,atan2f(bp[0]-ox,bp[2]-oz)*57.29578f);place_slot(h,q,w2);
        }
        int32_t delay=26;dw4_property_number(p0,"ATTACKDELAY",&delay);
        for(unsigned i=0;i<12;i++){dw4_hubruntime_input(h,0,0,0,i<3?0x4000:0,i==0?0x4000:0);for(unsigned q=1;q<=pilot_extra;q++)dw4_hubruntime_input_slot(h,q,0,0,0,i<3?0x4000:0,i==0?0x4000:0);if(dw4_hubruntime_tick(h,(uint64_t)(*frame)++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));exit(1);}boss_atck3_sample(h);}
        run(h,frame,(unsigned)delay*5/2,0,0);
        if(verbose && getenv("HPLOG")){dw4_script_model st;if(!dw4_controllers_model_state(dw4_hubruntime_models(h),best_k,&st)){const dw4_stageobject *bi;int32_t bs;dw4_controllers_model(dw4_hubruntime_models(h),best_k,&bi,&bs);fprintf(stderr,"  pilot t%u: target %s[%d] row %d hp %d/%d\n",*frame-start,dw4_stageobject_name(bi),bs,st.rec_no,st.hp,st.max_hp);}}
        int32_t l2=0,e2=0;dw4_property_number(p0,"LEVEL",&l2);dw4_property_number(p0,"EXP",&e2);
        if(e2!=exp0){kills++;exp0=e2;}
        if(l2!=level){if(verbose)fprintf(stderr,"pilot: level %d -> %d after %u kills at tick %u\n",level,l2,kills,*frame-start);level=l2;}
    }
    if(verbose)fprintf(stderr,"pilot: %u kills, level %d, exp %d, ticks %u\n",kills,level,exp0,*frame-start);
    return kills;
}
static int control(dw4_hubruntime *h);
/* The centre x/z and floor-level y of an authored material region of a stage pack. */
static void mat_region(dw4_mount *mount,const char *stage,const char *name,float lo[3],float hi[3])
{
    dw4_igfile file={0};dw4_igb g={0};int found=0;
    assert(!dw4_igfile_open_stage_pack(&file,mount,stage,0,0) && !dw4_igb_open(&g,file.data,file.len,0) && !dw4_igb_refs_open(&g));
    for(uint32_t id=0;id<g.table_n && !found;id++)if(g.id_kind[id]==2){
        dw4_igb_record r={0};if(!dw4_igb_decode(&g,g.id_off[id],&r))continue;
        if(!strcmp(r.class_name,"beMatCtrlData") && r.name && !strcmp(r.name,name)){
            uint32_t box=0;for(unsigned v=0;v<r.nvalues;v++)if(r.values[v].ordinal==3)box=r.values[v].raw;
            dw4_igb_record b={0};assert(box<g.table_n && dw4_igb_decode(&g,g.id_off[box],&b));
            for(unsigned v=0;v<b.nvalues;v++){if(b.values[v].ordinal==2)memcpy(lo,g.data+b.values[v].voff,12);if(b.values[v].ordinal==3)memcpy(hi,g.data+b.values[v].voff,12);}
            dw4_igb_record_free(&b);found=1;}
        dw4_igb_record_free(&r);}
    assert(found);dw4_igb_close(&g);dw4_igfile_close(&file);
    if(getenv("MATREGION_PRINT"))fprintf(stderr,"region %s/%s: lo %.1f %.1f %.1f hi %.1f %.1f %.1f\n",stage,name,lo[0],lo[1],lo[2],hi[0],hi[1],hi[2]);   /* the box, for placing a retail player (emu_state teleport) */
}
static void place_slot(dw4_hubruntime *h,unsigned slot,const char *where)
{
    char error[512];dw4_script_value r;
    dw4_script_value mv[5]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,(double)slot,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,where,strlen(where)}};
    if(dw4_hubruntime_sd(h,mv,5,&r,error,sizeof error)){fprintf(stderr,"place slot %u: %s\n",slot,error);exit(1);}
}
static void place(dw4_hubruntime *h,const char *where)
{
    char error[512];dw4_script_value r;
    dw4_script_value mv[5]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,where,strlen(where)}};
    if(dw4_hubruntime_sd(h,mv,5,&r,error,sizeof error)){fprintf(stderr,"place: %s\n",error);exit(1);}
}
/* Enemy floor and wall tests (mode enemyfall): one generated enemy followed tick by tick. */
struct ef_obs {float miny,maxy,minx,maxx,minz,maxz,first[3],last[3],focus[2],nearest;unsigned ticks;int sq_fall,ended,fell_tick;char last_seq[32];};
static const dw4_modelctrl *ef_find(dw4_hubruntime *h,const char *name,int32_t slot)
{
    for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t sl;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&sl);
        if(mc && sl==slot && !strcmp(dw4_stageobject_name(info),name))return mc;}
    return NULL;
}
static void ef_sd(dw4_hubruntime *h,const char *name,int32_t slot,const char *command,const char *argument)
{
    char error[512];dw4_script_value r,a[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,name,strlen(name)},{DW4_SCRIPT_NUMBER,slot,NULL,0},{DW4_SCRIPT_STRING,0,command,strlen(command)},{DW4_SCRIPT_STRING,0,argument,argument?strlen(argument):0}};
    if(dw4_hubruntime_sd(h,a,argument?5:4,&r,error,sizeof error)){fprintf(stderr,"MODELCTRL %s %d %s: %s\n",name,slot,command,error);exit(1);}
}
/* Generate `name`[slot] at (x,y,z) facing `yaw` (degrees; its heading is (sin yaw, cos yaw)) in SQ_WAIT. hop: no AI, the knockback sequence SQ_DDMG instead (the
 * victim slides back along yaw + 180); otherwise the authored AI chases the player, who is put at (px,py,pz) first. Samples until the instance ends or `limit` ticks. */
static void ef_follow(dw4_hubruntime *h,unsigned *frame,dw4_property_folder *p0,int32_t mhp,const char *name,int32_t slot,const float at[3],float yaw,int hop,const float player[3],unsigned limit,struct ef_obs *o,int trace)
{
    char where[128];{float f0=o->focus[0],f1=o->focus[1];memset(o,0,sizeof *o);o->focus[0]=f0;o->focus[1]=f1;}o->nearest=1e9f;o->miny=o->minx=o->minz=1e9f;o->maxy=o->maxx=o->maxz=-1e9f;o->fell_tick=-1;
    if(dw4_controllers_live(dw4_hubruntime_models(h),name,slot)>0){ef_sd(h,name,slot,"SQ_ERAS",NULL);run(h,frame,30,0,0);}
    snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",player[0],player[1],player[2]);place(h,where);run(h,frame,15,0,0);
    snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,%g,0>/SQ_WAIT",at[0],at[1],at[2],yaw);
    ef_sd(h,name,slot,"GENERATE",where);
    dw4_script_model *enemy=dw4_hubruntime_enemy_state(h,name,slot);assert(enemy);enemy->rec_no=0;enemy->hp=enemy->max_hp=5000;
    const dw4_modelctrl *e=ef_find(h,name,slot);assert(e && dw4_modelctrl_active(e));
    if(hop){assert(!dw4_controllers_nearest(dw4_hubruntime_models(h),name,slot,NULL,NULL));ef_sd(h,name,slot,"SQ_DDMG",NULL);}
    for(;o->ticks<limit;o->ticks++) {
        dw4_hubruntime_input(h,0,0,0,0,0);
        if(dw4_hubruntime_tick(h,(uint64_t)(*frame)++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",*frame,dw4_hubruntime_error(h));exit(1);}
        assert(!dw4_property_set_number(p0,"HP",mhp));
        if(!dw4_modelctrl_active(e)){o->ended=1;break;}
        dw4_modelctrl_actor a;dw4_modelctrl_actor_state(e,&a);
        if(!o->ticks)memcpy(o->first,a.position,12);
        memcpy(o->last,a.position,12);snprintf(o->last_seq,sizeof o->last_seq,"%s",dw4_modelctrl_sequence(e));
        if(a.position[0]<o->minx)o->minx=a.position[0];if(a.position[0]>o->maxx)o->maxx=a.position[0];
        if(a.position[1]<o->miny)o->miny=a.position[1];if(a.position[1]>o->maxy)o->maxy=a.position[1];
        if(a.position[2]<o->minz)o->minz=a.position[2];if(a.position[2]>o->maxz)o->maxz=a.position[2];
        {float d=hypotf(a.position[0]-o->focus[0],a.position[2]-o->focus[1]);if(d<o->nearest)o->nearest=d;}
        if(!strcmp(o->last_seq,"SQ_FALL"))o->sq_fall=1;
        if(trace && o->ticks%trace==0)fprintf(stderr,"   t%u %s at %.2f %.2f %.2f\n",o->ticks,o->last_seq,a.position[0],a.position[1],a.position[2]);
        if(!hop && o->sq_fall && !strcmp(o->last_seq,"SQ_WAIT"))break;   /* the fall ended into its own JUMP SQ_WAIT */
    }
}
/* Local co-op menus: one tick with a pad word set per joined slot (slot 0 through the main input, the others through dw4_hubruntime_input_slot). */
struct padw {uint32_t analog,held,pressed;};
static void coop_tick(dw4_hubruntime *h,unsigned *frame,unsigned players,const struct padw w[4])
{
    dw4_hubruntime_input(h,0,0,w[0].analog,w[0].held,w[0].pressed);
    for(unsigned q=1;q<players;q++)dw4_hubruntime_input_slot(h,q,0,0,w[q].analog,w[q].held,w[q].pressed);
    if(dw4_hubruntime_tick(h,(uint64_t)(*frame)++*1000000000ULL/60)){fprintf(stderr,"coop tick: %s\n",dw4_hubruntime_error(h));exit(1);}
}
/* The model state the pads act on: whether slot `q`'s player model takes control input (PLAYER OFCTRL clears it). */
static int slot_control(dw4_hubruntime *h,unsigned q)
{
    dw4_lobby *w=dw4_hubruntime_world(h);assert(!dw4_lobby_select_player(w,q));
    dw4_modelctrl_actor a={0};dw4_modelctrl_actor_state(dw4_lobby_player_model(w),&a);
    dw4_lobby_select_player(w,0);return a.enabled;
}
static int lua_number(dw4_hubruntime *h,const char *name)
{
    dw4_script_value r={0};
    if(dw4_script_get(dw4_scriptengine_vm(dw4_hubruntime_scripts(h)),name,&r) || r.type!=DW4_SCRIPT_NUMBER)return -999;
    return (int)r.number;
}
/* A hash of the open talk text (the visible TALKFONT groups), to tell one message page from the next. */
static uint32_t talk_text_hash(const dw4_hubruntime *h)
{
    uint32_t hash=2166136261u;const dw4_dialogue *d=dw4_hubruntime_dialogue(h);
    for(size_t i=0;i<dw4_dialogue_text_count(d);i++){
        const dw4_dialogue_text *t=dw4_dialogue_text_at(d,i);
        if(!t->visible || !t->count || strncmp(t->group,"TALKFONT",8))continue;
        for(const char *c=t->group;*c;c++)hash=(hash^(uint8_t)*c)*16777619u;
        for(size_t k=0;k<t->count;k++)hash=(hash^t->codes[k])*16777619u;
    }
    return hash;
}
/* Join `players` (1..4) in a field stage: the mates are Agumons in the records, then the stage is prepared again from this runtime's records. */
static dw4_hubruntime *rejoin_party(dw4_mount *mount,dw4_hubruntime *h,const char *stage,unsigned players)
{
    dw4_playerrecords *rec=dw4_hubruntime_records(h);const dw4_databases *db=dw4_hubruntime_databases(h);char error[512];
    for(unsigned q=1;q<players;q++)
        assert(!dw4_playerrecords_create(rec,db,(int)q,"p_agumon","Mate",error,sizeof error) && !dw4_property_set_number(dw4_playerrecords_get(rec,"GETPLAYER",(int)q),"ISUSE",1));
    assert(!dw4_property_set_number(dw4_playerrecords_get(rec,"GETCOMMON",0),"NINZU",(int32_t)players));
    dw4_stageinput in=*dw4_hubruntime_input_state(h);
    dw4_hubruntime_source prior={rec,dw4_hubruntime_state(h),&in,dw4_hubruntime_time(h)};
    dw4_hubruntime *next=dw4_hubruntime_prepare(mount,&prior,stage,0,1,error,sizeof error);
    if(!next){fprintf(stderr,"prepare %s: %s\n",stage,error);exit(1);}
    dw4_hubruntime_close(h);return next;
}
/* Stick-only walking (no MOVETRANS): the pad direction that makes the player's heading point at (tx,tz) under the camera the world has this tick
 * (the inverse of the stick-to-yaw rule, as test_lobby_portaledge does; box cameras change camera_world as the player crosses regions). */
static void stick_toward(dw4_hubruntime *h,unsigned *frame,float tx,float tz,uint32_t held,uint32_t pressed)
{
    dw4_lobby_walk_state w;dw4_lobby_control_state c;
    assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w) && !dw4_lobby_control(dw4_hubruntime_world(h),&c));
    float yaw=atan2f(tx-w.position[0],tz-w.position[2])-atan2f(c.camera_world[8],c.camera_world[10]);
    dw4_hubruntime_input(h,sinf(yaw),-cosf(yaw),0,held,pressed);
    if(dw4_hubruntime_tick(h,(uint64_t)(*frame)++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));exit(1);}
}
struct walkstat {unsigned ticks,wall_ticks,floor_loss_ticks;float max_step,end[3];int reached;};
/* Hold the stick toward (tx,tz) for up to max ticks or until within tol of it on the floor plane. The per-tick displacement bound (a run speed
 * well under the thickest wall) catches tunnelling; wall_ticks counts ticks whose collision pass reported a wall push (contact bit 1). */
static struct walkstat stick_walk(dw4_hubruntime *h,unsigned *frame,float tx,float tz,float tol,unsigned max)
{
    struct walkstat s={0};dw4_lobby_walk_state w;
    for(;s.ticks<max;s.ticks++){
        assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w));
        if(hypotf(tx-w.position[0],tz-w.position[2])<tol){s.reached=1;break;}
        float before[3];memcpy(before,w.position,12);
        dw4_lobby_walk_clear_contacts(dw4_hubruntime_world(h));
        if(!control(h)){run(h,frame,1,0,0);continue;}
        stick_toward(h,frame,tx,tz,0,0);
        assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w));
        float step=hypotf(w.position[0]-before[0],w.position[2]-before[2]);if(step>s.max_step)s.max_step=step;
        if(w.contacts&1)s.wall_ticks++;
        if(w.contacts&2)s.floor_loss_ticks++;
    }
    assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w));memcpy(s.end,w.position,12);
    return s;
}
/* Route planning over the live walking collision: a breadth-first search on an 8-unit grid whose every edge is walked with the player's own
 * collision pass (dw4_lobby_walk_probe, 2-unit sub-steps). An edge exists only if the solver leaves the move untouched (no wall within the
 * player's radius) and keeps support, so the search sees exactly the walls, doors and ledges the walk will meet, in the state they are in now. */
#define PL_X0 -900.0f
#define PL_Z0 -800.0f
#define PL_C 8.0f
#define PL_NX 260
#define PL_NZ 220
struct plan {unsigned char seen[PL_NX*PL_NZ];int parent[PL_NX*PL_NZ];float pos[PL_NX*PL_NZ][3];int queue[PL_NX*PL_NZ];unsigned reached;};
static int plan_cell(float x,float z)
{int ix=(int)floorf((x-PL_X0)/PL_C),iz=(int)floorf((z-PL_Z0)/PL_C);return ix<0||ix>=PL_NX||iz<0||iz>=PL_NZ?-1:iz*PL_NX+ix;}
static float plan_drop;   /* > 0: a step that loses the floor is a fall when a floor lies at most this far below the next position (the player walks off a ledge and lands; dungeondoors2 only) */
static int plan_edge(const dw4_lobby *wd,const float from[3],float tx,float tz,float out[3])
{
    float cur[3]={from[0],from[1],from[2]};float d=hypotf(tx-cur[0],tz-cur[2]);unsigned n=(unsigned)ceilf(d/2.0f);if(!n)n=1;
    for(unsigned i=0;i<n;i++){
        float nx=cur[0]+(tx-cur[0])/(float)(n-i),nz=cur[2]+(tz-cur[2])/(float)(n-i),next[3]={nx,cur[1],nz};
        unsigned c=dw4_lobby_walk_probe(wd,cur,next);
        if((c&2) && plan_drop>0){   /* the floor ends here: the landing is the highest floor below (the probe window is 4 units, so look down in 4-unit levels) */
            for(float dy=4;dy<=plan_drop;dy+=4){float lo[3]={cur[0],cur[1]-dy,cur[2]},nn[3]={nx,cur[1]-dy,nz};
                if(!(dw4_lobby_walk_probe(wd,lo,nn)&2)){memcpy(next,nn,12);c=0;cur[1]=lo[1];break;}}
        }
        if((c&2) || fabsf(next[0]-nx)>.5f || fabsf(next[2]-nz)>.5f || fabsf(next[1]-cur[1])>4.5f)return 0;
        memcpy(cur,next,12);
    }
    memcpy(out,cur,12);return 1;
}
static struct plan *plan_build(const dw4_lobby *wd,const float start[3])
{
    struct plan *p=calloc(1,sizeof *p);assert(p);
    int c0=plan_cell(start[0],start[2]);assert(c0>=0);
    p->seen[c0]=1;p->parent[c0]=-1;memcpy(p->pos[c0],start,12);
    unsigned head=0,tail=0;p->queue[tail++]=c0;
    while(head<tail){
        int c=p->queue[head++];
        for(int dz=-1;dz<=1;dz++)for(int dx=-1;dx<=1;dx++){
            if(!dx && !dz)continue;
            int ix=c%PL_NX+dx,iz=c/PL_NX+dz;if(ix<0||ix>=PL_NX||iz<0||iz>=PL_NZ)continue;
            int n=iz*PL_NX+ix;if(p->seen[n])continue;
            float out[3];
            if(!plan_edge(wd,p->pos[c],PL_X0+((float)ix+.5f)*PL_C,PL_Z0+((float)iz+.5f)*PL_C,out))continue;
            p->seen[n]=1;p->parent[n]=c;memcpy(p->pos[n],out,12);p->queue[tail++]=(int)n;
        }
    }
    p->reached=tail;return p;
}
/* The reached cell nearest to (gx,gz); *gap = its distance to the goal (small when the goal itself is reachable). */
static int plan_nearest(const struct plan *p,float gx,float gz,float *gap)
{
    int best=-1;float bd=1e30f;
    for(unsigned i=0;i<p->reached;i++){int c=p->queue[i];float d=hypotf(p->pos[c][0]-gx,p->pos[c][2]-gz);if(d<bd){bd=d;best=c;}}
    if(gap)*gap=bd;return best;
}
/* Diagnostic (DUMPPLAN=x0,x1,z0,z1, DUMPPROBE=x,z): the cells the player can reach (o), the target box (T) and the player (P), every 12 units; DUMPPROBE adds eight
 * 2-unit +z probes from the reached cell at x,z (contacts: 1 wall, 2 no floor). */
static void plan_dump(const dw4_lobby *wd,const float pp[3],const float lo[3],const float hi[3])
{
    int bx0=-900,bx1=1000,bz0=-800,bz1=900;sscanf(getenv("DUMPPLAN"),"%d,%d,%d,%d",&bx0,&bx1,&bz0,&bz1);
    struct plan *dp=plan_build(wd,pp);fprintf(stderr,"reach map (12-unit cells), x %d..%d, z %d..%d\n",bx0,bx1,bz0,bz1);
    if(getenv("DUMPPROBE")){float qx=pp[0],qz=pp[2];sscanf(getenv("DUMPPROBE"),"%f,%f",&qx,&qz);int qc=plan_cell(qx,qz);float cur[3];memcpy(cur,dp->seen[qc]?dp->pos[qc]:pp,12);
        for(int s=0;s<8;s++){float nx[3]={cur[0],cur[1],cur[2]+2};unsigned c=dw4_lobby_walk_probe(wd,cur,nx);fprintf(stderr,"  probe +z step %d from %.1f %.1f %.1f: contacts %u\n",s,cur[0],cur[1],cur[2],c);memcpy(cur,nx,12);}}
    for(int z=bz0;z<bz1;z+=12){char line[400];int n=0;for(int x=bx0;x<bx1 && n<390;x+=12,n++){int c=plan_cell((float)x+6,(float)z+6);
            line[n]=((float)x+6>=lo[0]&&(float)x+6<=hi[0]&&(float)z+6>=lo[2]&&(float)z+6<=hi[2])?'T':(fabsf((float)x+6-pp[0])<6&&fabsf((float)z+6-pp[2])<6)?'P':(c>=0&&dp->seen[c])?'o':'.';}
        line[n]=0;fprintf(stderr,"%5d %s\n",z,line);}
    free(dp);
}
/* The path from the plan's start to cell c (start first); returns its length. */
static unsigned plan_path(const struct plan *p,int c,int *path,unsigned cap)
{
    unsigned n=0;for(int k=c;k>=0 && n<cap;k=p->parent[k])path[n++]=k;
    for(unsigned i=0;i<n/2;i++){int t=path[i];path[i]=path[n-1-i];path[n-1-i]=t;}
    return n;
}
/* The stick-only pilot. Every tick goes through wtick: it clears the collision contacts, runs the world with the pad state, and records what the
 * solver did (a wall push is contact bit 1) and how far the player moved (a speed bound for tunnelling). Nothing here calls MOVETRANS. */
static struct {float max_step;unsigned ticks,wall_ticks,loss_ticks,kills,placed;} wstat;
static float walk_fight_range=55;   /* walk_box stops to fight an enemy this close (smaller while walking up to a door, so the wave does not open it on the way) */
static void wtick(dw4_hubruntime *h,unsigned *frame,float x,float y,uint32_t held,uint32_t pressed)
{
    dw4_lobby *wd=dw4_hubruntime_world(h);dw4_lobby_walk_state a,b;
    assert(!dw4_lobby_walk(wd,&a));dw4_lobby_walk_clear_contacts(wd);
    dw4_hubruntime_input(h,x,y,0,held,pressed);
    if(dw4_hubruntime_tick(h,(uint64_t)(*frame)++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));exit(1);}
    assert(!dw4_lobby_walk(wd,&b));
    float step=hypotf(b.position[0]-a.position[0],b.position[2]-a.position[2]);
    wstat.ticks++;
    if(step>12.0f){wstat.placed++;fprintf(stderr,"  scripted placement: %.0f %.0f -> %.0f %.0f\n",a.position[0],a.position[2],b.position[0],b.position[2]);}   /* the boss intro's MOVETRANS, not walking */
    else if(step>wstat.max_step)wstat.max_step=step;
    if(b.contacts&1)wstat.wall_ticks++;
    if(b.contacts&2)wstat.loss_ticks++;
    if(getenv("BOSSBOX")){   /* development aid: every distinct (sequence, box count) of Mammothmon once, with the boxes' kind, start/end frame, offset and size */
        static char seen[64][24];static unsigned nseen;
        for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){
            const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
            if(!mc || !info || strcmp(dw4_stageobject_name(info),"e_mammos") || !dw4_modelctrl_active(mc))continue;
            unsigned nb=0;const dw4_modelctrl_hitbox *bx=dw4_modelctrl_hitboxes(mc,&nb);char key[24];snprintf(key,sizeof key,"%s/%u",dw4_modelctrl_sequence(mc),nb);
            unsigned q;for(q=0;q<nseen && strcmp(seen[q],key);q++);
            if(q==nseen && nseen<64){snprintf(seen[nseen++],24,"%s",key);fprintf(stderr,"    boxes %s:",key);
                for(unsigned i=0;i<nb;i++)fprintf(stderr," [%d %g..%g run %g off %g %g %g size %g %g %g]",bx[i].kind,bx[i].start_frames,bx[i].end_frames,bx[i].run_frame,bx[i].offset[0],bx[i].offset[1],bx[i].offset[2],bx[i].size[0],bx[i].size[1],bx[i].size[2]);fputc(10,stderr);}}
    }
    if(getenv("BOSSBOX")){   /* the player's own boxes (the weapon sweep) once per (sequence, count) */
        static char pseen[32][24];static unsigned npseen;
        const dw4_modelctrl *pm=dw4_lobby_player_model(dw4_hubruntime_world(h));
        if(pm){unsigned nb=0;const dw4_modelctrl_hitbox *bx=dw4_modelctrl_hitboxes(pm,&nb);char key[24];snprintf(key,sizeof key,"%s/%u",dw4_modelctrl_sequence(pm),nb);
            unsigned q;for(q=0;q<npseen && strcmp(pseen[q],key);q++);
            if(q==npseen && npseen<32){snprintf(pseen[npseen++],24,"%s",key);fprintf(stderr,"    player boxes %s:",key);
                for(unsigned i=0;i<nb;i++)fprintf(stderr," [%d %g..%g run %g off %g %g %g size %g %g %g]",bx[i].kind,bx[i].start_frames,bx[i].end_frames,bx[i].run_frame,bx[i].offset[0],bx[i].offset[1],bx[i].offset[2],bx[i].size[0],bx[i].size[1],bx[i].size[2]);fputc(10,stderr);}}
    }
    boss_atck3_sample(h);
    if(getenv("BOSSTRACE") && wstat.ticks%(unsigned)atoi(getenv("BOSSTRACE"))==0){   /* development aid: Mammothmon's position, yaw and sequence every BOSSTRACE ticks */
        for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){
            const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
            if(!mc || !info || strcmp(dw4_stageobject_name(info),"e_mammos") || !dw4_modelctrl_active(mc))continue;
            dw4_modelctrl_actor ea;dw4_modelctrl_actor_state(mc,&ea);
            fprintf(stderr,"    trace t%u: boss %.1f %.1f yaw %.1f seq %s, player %.1f %.1f\n",wstat.ticks,ea.position[0],ea.position[2],ea.rotation[1],dw4_modelctrl_sequence(mc),b.position[0],b.position[2]);}
    }
}
static void stick_dir(dw4_hubruntime *h,float tx,float tz,float *x,float *y)
{
    dw4_lobby_walk_state w;dw4_lobby_control_state c;
    assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w) && !dw4_lobby_control(dw4_hubruntime_world(h),&c));
    float yaw=atan2f(tx-w.position[0],tz-w.position[2])-atan2f(c.camera_world[8],c.camera_world[10]);
    *x=sinf(yaw);*y=-cosf(yaw);
}
/* One walking tick toward (tx,tz); while a script holds control (boss intro, info windows) tap Cross like a player instead. */
static void wstep(dw4_hubruntime *h,unsigned *frame,float tx,float tz,uint32_t held,uint32_t pressed)
{
    if(!control(h)){static unsigned t;t++;wtick(h,frame,0,0,t%90<4?0x4000:0,t%90==0?0x4000:0);return;}
    float x,y;stick_dir(h,tx,tz,&x,&y);
    if(getenv("WDBG2") && wstat.ticks%15==0){dw4_lobby_walk_state w;dw4_lobby_control_state c;dw4_lobby_walk(dw4_hubruntime_world(h),&w);dw4_lobby_control(dw4_hubruntime_world(h),&c);
        fprintf(stderr,"      w t%u pos %.1f %.1f yaw %.0f -> target %.0f %.0f stick %.2f %.2f cam fwd %.2f %.2f region %u motion %s contacts %u\n",wstat.ticks,w.position[0],w.position[2],w.yaw,tx,tz,x,y,c.camera_world[8],c.camera_world[10],c.camera_region,w.motion?w.motion:"-",w.contacts);}
    wtick(h,frame,x,y,held,pressed);
}
static int player_pos(dw4_hubruntime *h,float p[3])
{dw4_lobby_walk_state w;if(dw4_lobby_walk(dw4_hubruntime_world(h),&w))return -1;memcpy(p,w.position,12);return 0;}
/* The nearest living enemy model ("e_") not in the ignore list; returns its controller index or -1. */
static long nearest_enemy(dw4_hubruntime *h,const float from[3],const size_t *ignore,unsigned nignore,float pos[3])
{
    long best=-1;float bd=1e30f;
    for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){
        const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
        dw4_script_model st;
        if(!mc || !info || strncmp(dw4_stageobject_name(info),"e_",2) || !dw4_modelctrl_active(mc) || dw4_controllers_model_state(dw4_hubruntime_models(h),k,&st) || st.hp<=0)continue;
        int skip=0;for(unsigned i=0;i<nignore;i++)skip|=ignore[i]==k;if(skip)continue;
        dw4_modelctrl_actor ea;dw4_modelctrl_actor_state(mc,&ea);
        float d=hypotf(ea.position[0]-from[0],ea.position[2]-from[2]);
        if(d<bd){bd=d;best=(long)k;memcpy(pos,ea.position,12);}
    }
    return best;
}
static int enemy_alive(dw4_hubruntime *h,long k,float pos[3])
{
    const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),(size_t)k,&info,&slot);
    dw4_script_model st;if(!mc || !dw4_modelctrl_active(mc) || dw4_controllers_model_state(dw4_hubruntime_models(h),(size_t)k,&st) || st.hp<=0)return 0;
    dw4_modelctrl_actor ea;dw4_modelctrl_actor_state(mc,&ea);memcpy(pos,ea.position,12);return 1;
}
/* ---- Mammothmon with the pad alone (BOSSSMART=1, BOSSSTRAT=<1..6>, dungeondoors2) ----
 * The pilot reads the boss's sequence, age (ticks since the sequence started), position and heading from the model state, as a player reads the screen, and
 * drives only the stick and the buttons (wtick): nothing places the player or scripts the boss. The boss's attack boxes (BOSSBOX=1 prints them):
 * SQ_ATCK1 70014 boxes 12..35 frames after its start, 20-30 units ahead of the boss; SQ_FIRE 70015 boxes 20..84 frames, 37-72 units ahead; SQ_WALK the
 * 70016 charge boxes; every other sequence only the 70000 body boxes (SQ_ATCK2, SQ_ATCK3, SQ_SWON, SQ_WAIT, SQ_WALKIN and SQ_ATON are the harmless ones).
 * Strategies: 1 keep away, rush in during the harmless phase after the charge (SQ_ATCK3/SQ_ATCK2) and swing; 2 the same, also rushing in at the end of
 * SQ_FIRE and standing on the flank; 3 as 1 with a jump (Circle) or the guard button (Square, BOSSGUARD=1) pressed while the attack boxes are out; 4 R1
 * technique casts from a distance (the default; the brawl when the MP is gone); 5 stay behind the boss (out of every attack box) and swing in the harmless
 * phases; 6 brawl: stand 9 units from the boss and swing whenever free. Measured over 3,000 ticks of the arena-only fight (docs/dungeon-floors.md,
 * "Pad-only kill"): 1, 2, 3 and 5 deal 0, 0, 0 and 140 damage; 4 and 6 kill the boss in about 1,650 ticks. */
typedef struct {float pos[3],yaw;char seq[24];unsigned age;} bossview;
static int boss_view(dw4_hubruntime *h,long k,bossview *v)
{
    static char last[24];static unsigned since;
    const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),(size_t)k,&info,&slot);
    if(!mc)return 0;
    dw4_modelctrl_actor ea;dw4_modelctrl_actor_state(mc,&ea);memcpy(v->pos,ea.position,12);v->yaw=ea.rotation[1];
    const char *sq=dw4_modelctrl_sequence(mc);if(!sq)sq="";
    if(strcmp(last,sq)){snprintf(last,sizeof last,"%s",sq);since=wstat.ticks;}
    snprintf(v->seq,sizeof v->seq,"%s",sq);v->age=wstat.ticks-since;return 1;
}
static int boss_harmless(const bossview *v)
{
    static const char *const ok[]={"SQ_ATCK2","SQ_ATCK3","SQ_SWON","SQ_WAIT","SQ_WALKIN","SQ_ATON","SQ_ENTR"};
    for(unsigned i=0;i<sizeof ok/sizeof *ok;i++)if(!strcmp(v->seq,ok[i]))return 1;
    return 0;
}
static void boss_local(const bossview *v,const float me[3],float *lx,float *lz)
{float d0=me[0]-v->pos[0],d2=me[2]-v->pos[2],r=v->yaw*3.14159265f/180.0f;*lz=d0*sinf(r)+d2*cosf(r);*lx=d0*cosf(r)-d2*sinf(r);}
static void boss_world(const bossview *v,float lx,float lz,float *x,float *z)
{float r=v->yaw*3.14159265f/180.0f;*x=v->pos[0]+lx*cosf(r)+lz*sinf(r);*z=v->pos[2]-lx*sinf(r)+lz*cosf(r);}
static const char *player_seq(dw4_hubruntime *h){const char *s=dw4_modelctrl_sequence(dw4_lobby_player_model(dw4_hubruntime_world(h)));return s?s:"";}
/* One swing: face the boss for two ticks, press Cross (held three ticks), then stand until the swing is over. */
static void smart_swing(dw4_hubruntime *h,unsigned *frame,long bk,uint32_t extra_held)
{
    float bp[3];
    for(unsigned i=0;i<60;i++){
        if(!control(h)){wtick(h,frame,0,0,0,0);continue;}
        if(!enemy_alive(h,bk,bp))break;
        float x=0,y=0;if(i<2)stick_dir(h,bp[0],bp[2],&x,&y);
        wtick(h,frame,x,y,extra_held|(i>=2&&i<5?0x4000:0),i==2?0x4000:0);
        if(i>=20 && strncmp(player_seq(h),"SQ_ATCK",7))break;
    }
}
static int smart_fight(dw4_hubruntime *h,unsigned *frame,long bk,dw4_property_folder *p0,int strat,unsigned budget)
{
    const dw4_combat_stats *cs=dw4_hubruntime_combat(h);
    unsigned t0=wstat.ticks,swings=0,casts=0,hits0=cs->hits,dmg0=cs->damage_total,ph0=cs->player_hits,pd0=cs->player_damage_total,lastcast=0,jumps=0;
    int32_t hp0=0,bhp0=-1,mp0=0;dw4_property_number(p0,"HP",&hp0);dw4_property_number(p0,"MP",&mp0);
    const float back=getenv("BOSSBACK")?(float)atof(getenv("BOSSBACK")):18.0f,away=getenv("BOSSAWAY")?(float)atof(getenv("BOSSAWAY")):45.0f;
    const unsigned maxage=getenv("BOSSAGE")?(unsigned)atoi(getenv("BOSSAGE")):22;
    float bp[3];
    while(wstat.ticks-t0<budget && enemy_alive(h,bk,bp)){
        int32_t hp=0;float me[3];if(dw4_property_number(p0,"HP",&hp) || hp<=0 || player_pos(h,me))break;
        if(!control(h)){wtick(h,frame,0,0,0,0);continue;}
        bossview v;if(!boss_view(h,bk,&v))break;
        dw4_script_model bs={0};dw4_controllers_model_state(dw4_hubruntime_models(h),(size_t)bk,&bs);if(bhp0<0)bhp0=bs.hp;
        const float dist=hypotf(v.pos[0]-me[0],v.pos[2]-me[2]);float lx,lz;boss_local(&v,me,&lx,&lz);
        const int harmless=boss_harmless(&v);
        if(getenv("BOSSLOG") && (wstat.ticks-t0)%(unsigned)atoi(getenv("BOSSLOG"))==0)fprintf(stderr,"    smart t%u: %s age %u dist %.0f local %.0f %.0f, player %s HP %d, boss HP %d, swings %u contacts %u dmg %u\n",wstat.ticks-t0,v.seq,v.age,dist,lx,lz,player_seq(h),hp,bs.hp,swings,cs->hits-hits0,cs->damage_total-dmg0);
        float tx=me[0],tz=me[2];int go=1,swing=0;uint32_t extra=0;
        const float ux=(me[0]-v.pos[0])/(dist>.1f?dist:.1f),uz=(me[2]-v.pos[2])/(dist>.1f?dist:.1f);
        int32_t mp_now=0;dw4_property_number(p0,"MP",&mp_now);const int st=strat==4 && mp_now<16?6:strat;   /* the technique pilot falls back to the brawl when the MP is gone */
        if(st==1 || st==2 || st==3){
            const int fire_end=strat==2 && !strcmp(v.seq,"SQ_FIRE") && v.age>=80;
            const float eta=(dist>9.0f?dist-9.0f:0.0f)/1.5f;   /* the player runs about 1.5 units per tick */
            const int window=(harmless && (!strcmp(v.seq,"SQ_ATCK2")?v.age+eta<=maxage+20.0f:strcmp(v.seq,"SQ_WALKIN") && strcmp(v.seq,"SQ_ATON"))) || fire_end;
            if(window && dist<=80.0f){   /* run in to 9 units from the boss's centre */
                if(strat==2){float sx,sz;boss_world(&v,lx<0?-9.0f:9.0f,-2.0f,&sx,&sz);tx=sx;tz=sz;}   /* the flank, beside the boss */
                else{tx=v.pos[0]+ux*9.0f;tz=v.pos[2]+uz*9.0f;}
                if(hypotf(tx-me[0],tz-me[2])<2.5f || dist<=11.0f)swing=1;
            }else{   /* out of the window: wait on the flank, outside the attack boxes ahead of the boss */
                if(!strcmp(v.seq,"SQ_WALK"))boss_world(&v,lx<0?-30.0f:30.0f,lz>0?lz:5.0f,&tx,&tz);   /* the charge runs along the boss's heading: step aside */
                else if(dist<away || fabsf(lx)<0.7f*away)boss_world(&v,lx<0?-away:away,lz<0?lz:-8.0f,&tx,&tz);
                else go=0;
            }
            if(strat==3 && !swing && dist<60 && (!strcmp(v.seq,"SQ_ATCK1")||!strcmp(v.seq,"SQ_FIRE"))){   /* jump while the boxes are out (Circle), or guard (Square) */
                if(getenv("BOSSGUARD")){extra=0x8000;go=0;}
                else if(strcmp(player_seq(h),"SQ_JUMP") && strcmp(player_seq(h),"SQ_FALL")){wtick(h,frame,0,0,0,0x2000);jumps++;continue;}
            }
        }else if(st==5){
            boss_world(&v,0.0f,-back,&tx,&tz);
            if(hypotf(tx-me[0],tz-me[2])<3.0f){go=0;if(harmless && strcmp(v.seq,"SQ_WALKIN") && strcmp(v.seq,"SQ_ATON") && (strcmp(v.seq,"SQ_ATCK2")||v.age<=maxage))swing=1;}
        }else if(st==6){   /* brawl: stay at the boss's side and swing whenever the player is free and within reach, whatever the boss is doing */
            const float reach=getenv("BOSSREACH")?(float)atof(getenv("BOSSREACH")):12.0f,stand=getenv("BOSSSTAND")?(float)atof(getenv("BOSSSTAND")):9.0f;
            const char *ps=player_seq(h);
            tx=v.pos[0]+ux*stand;tz=v.pos[2]+uz*stand;
            if(dist<=reach && (!strcmp(ps,"SQ_WAIT") || !strcmp(ps,"SQ_WALK")))swing=1;
        }else if(st==4){
            const float want=getenv("BOSSRANGE")?(float)atof(getenv("BOSSRANGE")):45.0f;
            if(!strcmp(v.seq,"SQ_WALK"))boss_world(&v,lx<0?-30.0f:30.0f,lz>0?lz:5.0f,&tx,&tz);
            else if(fabsf(dist-want)>6.0f){tx=v.pos[0]+ux*want;tz=v.pos[2]+uz*want;}
            else{go=0;if(wstat.ticks-lastcast>=45){   /* face the boss, open the panel (R1), fire (Cross), close the panel (16 MP: the first technique) */
                    float x,y;stick_dir(h,v.pos[0],v.pos[2],&x,&y);wtick(h,frame,x,y,0,0);{dw4_technique_panel pv0;if(dw4_technique_panel_get(dw4_hubruntime_technique(h),0,&pv0) || !pv0.open)wtick(h,frame,0,0,0x800,0);}for(unsigned q=0;q<3;q++)wtick(h,frame,0,0,0,0);
                    wtick(h,frame,0,0,0x4000,0x4000);for(unsigned q=0;q<40;q++){wtick(h,frame,0,0,0,0);if(q>2 && strncmp(player_seq(h),"SQ_WAZA",7))break;}
                    {dw4_technique_panel pv;if(!dw4_technique_panel_get(dw4_hubruntime_technique(h),0,&pv) && pv.open){wtick(h,frame,0,0,0x800,0);wtick(h,frame,0,0,0,0);}}   /* the panel closes itself after a cast; close it if a refused press left it open */
                    casts++;lastcast=wstat.ticks;continue;}}
        }
        if(swing){swings++;smart_swing(h,frame,bk,extra);continue;}
        if(extra){wtick(h,frame,0,0,extra,(extra&0x8000) && strcmp(player_seq(h),"SQ_GUARD") && (wstat.ticks&1)?0x8000:0);continue;}   /* the guard request is the Square press edge (vfunc_38 reads the edge word), pressed whenever the player is out of SQ_GUARD */
        if(go){float x,y;stick_dir(h,tx,tz,&x,&y);if(hypotf(tx-me[0],tz-me[2])<1.0f)x=y=0;wtick(h,frame,x,y,0,0);}else wtick(h,frame,0,0,0,0);
    }
    int32_t hp=0;dw4_property_number(p0,"HP",&hp);dw4_script_model bs={0};dw4_controllers_model_state(dw4_hubruntime_models(h),(size_t)bk,&bs);
    int alive=enemy_alive(h,bk,bp);int32_t mpn=0;dw4_property_number(p0,"MP",&mpn);
    fprintf(stderr,"  BOSSSMART strategy %d: %u ticks, %u swings, %u casts, %u jumps, %u contacts, %u damage dealt, boss HP %d -> %d, boss hits on player %u (%u damage), player HP %d -> %d, MP %d -> %d: %s\n",strat,wstat.ticks-t0,swings,casts,jumps,cs->hits-hits0,cs->damage_total-dmg0,bhp0,alive?bs.hp:0,cs->player_hits-ph0,cs->player_damage_total-pd0,hp0,hp,mp0,mpn,alive?"boss still up":"BOSS DOWN");
    return !alive;
}
/* Fight one enemy with the pad alone: close in with the stick (the heading follows the stick, so the swing goes where the enemy is), then tap Cross
 * with the ATTACKDELAY cooldown. Returns 1 when it died, 0 when it was left (out of reach for `max` ticks, or the player is down). */
static int stick_fight(dw4_hubruntime *h,unsigned *frame,long k,unsigned max)
{
    dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
    int32_t exp0=0;dw4_property_number(p0,"EXP",&exp0);
    float ep[3],pp[3];unsigned t=0,stuck=0;float last=1e30f;
    while(t<max && enemy_alive(h,k,ep)){
        int32_t hp=0;if(dw4_property_number(p0,"HP",&hp) || hp<=0)return 0;
        if(player_pos(h,pp))return 0;
        float d=hypotf(ep[0]-pp[0],ep[2]-pp[2]);
        if(getenv("WDBG") && t%120==0){const dw4_stageobject *oi;int32_t os;dw4_controllers_model(dw4_hubruntime_models(h),(size_t)k,&oi,&os);dw4_script_model st={0};dw4_controllers_model_state(dw4_hubruntime_models(h),(size_t)k,&st);
            fprintf(stderr,"    fight t%u: %s[%d] hp %d at %.0f %.0f %.0f, player %.0f %.0f %.0f, dist %.1f\n",t,dw4_stageobject_name(oi),os,st.hp,ep[0],ep[1],ep[2],pp[0],pp[1],pp[2],d);}
        if(d>11.0f){
            wstep(h,frame,ep[0],ep[2],0,0);t++;
            if(d>last-.05f){if(++stuck>90)return 0;}else stuck=0;   /* walls between: let the route planner take over */
            last=d;continue;
        }
        stuck=0;last=1e30f;
        int32_t delay=26;dw4_property_number(p0,"ATTACKDELAY",&delay);
        for(unsigned i=0;i<14;i++,t++){   /* two ticks of full stick turn the player to the enemy, then the swing */
            if(!control(h)){wstep(h,frame,ep[0],ep[2],0,0);continue;}
            float x,y;stick_dir(h,ep[0],ep[2],&x,&y);float sc=i<2?1.0f:.05f;
            wtick(h,frame,x*sc,y*sc,i>=2&&i<5?0x4000:0,i==2?0x4000:0);}
        for(unsigned i=0;i<(unsigned)delay*3/2;i++,t++)wtick(h,frame,0,0,0,0);
    }
    int32_t exp1=0;dw4_property_number(p0,"EXP",&exp1);
    if(exp1!=exp0){wstat.kills++;return 1;}
    return !enemy_alive(h,k,ep);
}
/* Walk (planner + stick) into the xz box [lox,hix]x[loz,hiz]. fight: stop to kill any enemy that comes within 55 units. Returns 1 when inside,
 * 0 when the box is not reachable in the current collision (the player is left at the nearest point of the route; *gap = its distance) or time ran out. */
static int walk_box(dw4_hubruntime *h,unsigned *frame,float lox,float hix,float loz,float hiz,unsigned max,int fight,float *gap)
{
    unsigned t0=wstat.ticks;float cx=(lox+hix)/2,cz=(loz+hiz)/2;size_t ign[32];unsigned nign=0;
    if(gap)*gap=0;
    for(unsigned replans=0;wstat.ticks-t0<max && replans<400;replans++){
        float pp[3];if(player_pos(h,pp))return 0;
        if(pp[0]>=lox && pp[0]<=hix && pp[2]>=loz && pp[2]<=hiz)return 1;
        if(getenv("DUMPPLANWB") && replans==0){float blo[3]={lox,0,loz},bhi[3]={hix,0,hiz};plan_dump(dw4_hubruntime_world(h),pp,blo,bhi);}
        struct plan *pl=plan_build(dw4_hubruntime_world(h),pp);
        int goal=-1;float bd=1e30f;
        for(unsigned i=0;i<pl->reached;i++){int c=pl->queue[i];const float *q=pl->pos[c];if(q[0]<lox||q[0]>hix||q[2]<loz||q[2]>hiz)continue;float d=hypotf(q[0]-cx,q[2]-cz);if(d<bd){bd=d;goal=c;}}
        if(goal<0){goal=plan_nearest(pl,cx,cz,gap);if(goal<0 || goal==plan_cell(pp[0],pp[2])){free(pl);return 0;}}
        static int path[PL_NX*PL_NZ];unsigned n=plan_path(pl,goal,path,PL_NX*PL_NZ);
        int inside=pl->pos[goal][0]>=lox && pl->pos[goal][0]<=hix && pl->pos[goal][2]>=loz && pl->pos[goal][2]<=hiz;
        float gx=pl->pos[goal][0],gz=pl->pos[goal][2];
        unsigned idx=0,since=0;float best=1e30f;int fought=0;
        if(getenv("WDBG"))fprintf(stderr,"  walk_box: from %.0f %.0f to cell %.0f %.0f (path %u cells, inside %d, box %.0f..%.0f %.0f..%.0f) t=%u\n",pp[0],pp[2],gx,gz,n,inside,lox,hix,loz,hiz,wstat.ticks-t0);
        while(wstat.ticks-t0<max){
            if(player_pos(h,pp))return 0;
            if(getenv("WDBG") && (wstat.ticks%(getenv("WDBGSTEP")?(unsigned)atoi(getenv("WDBGSTEP")):60))==0)fprintf(stderr,"    t%u pos %.1f %.1f y %.1f idx %u/%u wall %u plan cell %.0f %.0f y %.1f\n",wstat.ticks,pp[0],pp[2],pp[1],idx,n,wstat.wall_ticks,pl->pos[path[idx]][0],pl->pos[path[idx]][2],pl->pos[path[idx]][1]);
            if(inside && pp[0]>=lox && pp[0]<=hix && pp[2]>=loz && pp[2]<=hiz){free(pl);return 1;}
            if(!inside && hypotf(pp[0]-gx,pp[2]-gz)<4){free(pl);return 0;}
            if(fight && control(h)){float ep[3];long e=nearest_enemy(h,pp,ign,nign,ep);
                if(e>=0 && hypotf(ep[0]-pp[0],ep[2]-pp[2])<walk_fight_range){
                    if(!stick_fight(h,frame,e,900) && nign<32){float ep2[3];if(enemy_alive(h,e,ep2))ign[nign++]=(size_t)e;}   /* out of reach (a wall between): not this walk's business */
                    fought=1;break;}}
            while(idx+1<n && hypotf(pp[0]-pl->pos[path[idx]][0],pp[2]-pl->pos[path[idx]][2])<10)idx++;
            unsigned la=idx+2<n?idx+2:n-1;
            {float cur_[3]={pp[0],pp[1],pp[2]},o_[3];   /* cut a corner only when the straight line from where the player really is stays clear (a wall corner on a ledge would push it off the edge) */
                while(la>idx && !plan_edge(dw4_hubruntime_world(h),cur_,pl->pos[path[la]][0],pl->pos[path[la]][2],o_))la--;}
            if(idx+1>=n){   /* on the last cell of the route: finish straight toward the box centre */
                if(hypotf(pp[0]-cx,pp[2]-cz)<2.5f)break;
                wstep(h,frame,cx,cz,0,0);
            }else wstep(h,frame,pl->pos[path[la]][0],pl->pos[path[la]][2],0,0);
            float dg=hypotf(pp[0]-gx,pp[2]-gz);
            if(dg<best-.5f){best=dg;since=0;}else if(++since>240)break;   /* no progress: plan again from here */
        }
        free(pl);
        (void)fought;
    }
    return 0;
}
/* Clear what is alive and reachable: fight the nearest living enemy the planner can reach, and visit started generators that still owe enemies
 * (radar generators wake when the player is near their points). Ends after a quiet stretch or `max` ticks. */
static void hunt(dw4_hubruntime *h,unsigned *frame,unsigned max)
{
    unsigned t0=wstat.ticks,quiet=0;size_t ignore[64];unsigned nign=0;size_t gi=0;
    while(wstat.ticks-t0<max && quiet<8){
        if(!control(h)){wstep(h,frame,0,0,0,0);continue;}
        int32_t hp=0;if(dw4_property_number(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0),"HP",&hp) || hp<=0)return;
        float pp[3],ep[3];if(player_pos(h,pp))return;
        long e=nearest_enemy(h,pp,ignore,nign,ep);
        if(e>=0){quiet=0;
            if(getenv("WDBG"))fprintf(stderr,"  hunt: enemy %ld at %.0f %.0f, player %.0f %.0f, kills %u, t=%u\n",e,ep[0],ep[2],pp[0],pp[2],wstat.kills,wstat.ticks-t0);
            unsigned before=wstat.ticks;float gap=0;
            if(hypotf(ep[0]-pp[0],ep[2]-pp[2])>=30)walk_box(h,frame,ep[0]-14,ep[0]+14,ep[2]-14,ep[2]+14,1500,1,&gap);
            if(enemy_alive(h,e,ep) && !stick_fight(h,frame,e,900) && enemy_alive(h,e,ep) && nign<64)ignore[nign++]=(size_t)e;
            if(wstat.ticks==before)wtick(h,frame,0,0,0,0);
            continue;}
        const dw4_fieldgen *gen=dw4_hubruntime_fieldgen(h);size_t n=dw4_fieldgen_count(gen);const dw4_gene *g=NULL;
        for(size_t q=0;q<n;q++){const dw4_gene *c=dw4_fieldgen_at(gen,(gi+q)%n);if(c->state==DW4_GENE_STARTED && (!c->spawned_total || c->remaining) && c->npoints){g=c;gi=(gi+q+1)%n;break;}}
        if(getenv("WDBG"))fprintf(stderr,"  hunt: no enemy; generator %s\n",g?g->name:"none");
        if(!g){quiet++;for(unsigned i=0;i<60;i++)wtick(h,frame,0,0,0,0);continue;}
        float x=g->points[0]+(g->global?0:g->pos[0]),z=g->points[2]+(g->global?0:g->pos[2]),gap=0;
        quiet++;
        if(!walk_box(h,frame,x-16,x+16,z-16,z+16,900,1,&gap))for(unsigned i=0;i<30;i++)wtick(h,frame,0,0,0,0);
        else for(unsigned i=0;i<60;i++)wtick(h,frame,0,0,0,0);
    }
}
/* A door of a floor: the named collision mesh, its authored centre, the flag the floor script sets for it, and the region whose arrival is the
 * moment a player first stands before it (pushed on arrival, then the wave is fought and the door must open). near/far are cells of the live
 * route, found by switching the door off for a moment: the far side is what only the open door makes reachable. */
struct door {const char *name;float x,z;int flag;float near[2],far[2];int tested;unsigned walls_closed;};
static int door_probe(dw4_hubruntime *h,struct door *d)
{
    dw4_lobby *wd=dw4_hubruntime_world(h);float pp[3];player_pos(h,pp);
    if(dw4_lobby_hit_state(wd,d->name)!=1)return 0;
    struct plan *closed=plan_build(wd,pp);
    assert(!dw4_lobby_collision_hit(wd,d->name,0));struct plan *open=plan_build(wd,pp);assert(!dw4_lobby_collision_hit(wd,d->name,1));
    int far=-1,near=-1;float bd=1e30f;
    for(unsigned i=0;i<open->reached;i++){int c=open->queue[i];if(closed->seen[c])continue;float q=hypotf(open->pos[c][0]-d->x,open->pos[c][2]-d->z);if(q<bd){bd=q;far=c;}}
    if(far>=0){bd=1e30f;for(unsigned i=0;i<closed->reached;i++){int c=closed->queue[i];float q=hypotf(closed->pos[c][0]-open->pos[far][0],closed->pos[c][2]-open->pos[far][2]);if(q<bd){bd=q;near=c;}}}
    int ok=far>=0 && near>=0 && bd<48;
    if(ok){d->near[0]=closed->pos[near][0];d->near[1]=closed->pos[near][2];d->far[0]=open->pos[far][0];d->far[1]=open->pos[far][2];}
    fprintf(stderr,"  door %s: %u cells closed, %u open; %s (near %.0f %.0f, far %.0f %.0f)\n",d->name,closed->reached,open->reached,ok?"probed":"no far side from here",d->near[0],d->near[1],d->far[0],d->far[1]);
    free(closed);free(open);return ok;
}
/* (1) Stand before the closed door and push into it for 120 ticks: the player stays on the side it came from, the solver reports a wall push on
 * nearly every tick, and the door's own collision is what stops it (hit state 1). */
static void door_push(dw4_hubruntime *h,unsigned *frame,struct door *d)
{
    dw4_lobby *wd=dw4_hubruntime_world(h);float pp[3],q[3];
    float gap=0;walk_fight_range=0;   /* no stops on the way: the wave must still be closed when the player stands at the door */
    int ok=walk_box(h,frame,d->near[0]-3,d->near[0]+3,d->near[1]-3,d->near[1]+3,40000,1,&gap);
    walk_fight_range=55;
    if(dw4_lobby_hit_state(wd,d->name)!=1){   /* the wave was cleared on the way and the script opened the door before the player stood at it */
        fprintf(stderr,"  %s opened (flag %d) before the player reached it\n",d->name,d->flag>=0?1:0);d->tested=3;return;}
    assert(ok);player_pos(h,pp);
    struct plan *side=plan_build(wd,pp);unsigned w_before=wstat.wall_ticks;
    for(unsigned t=0;t<120;t++)wstep(h,frame,d->far[0],d->far[1],0,0);
    player_pos(h,q);
    int c=plan_cell(q[0],q[2]),near_side=0;
    for(int dz=-1;dz<=1;dz++)for(int dx=-1;dx<=1;dx++)if(c+dz*PL_NX+dx>=0 && side->seen[c+dz*PL_NX+dx])near_side=1;
    float to_far=hypotf(q[0]-d->far[0],q[2]-d->far[1]);
    fprintf(stderr,"  %s closed: pushed 120 ticks toward %.0f %.0f from %.0f %.0f: ended %.0f %.0f (%.1f from the far side), wall push on %u ticks, near side %d\n",d->name,d->far[0],d->far[1],pp[0],pp[2],q[0],q[2],to_far,wstat.wall_ticks-w_before,near_side);
    assert(near_side && to_far>3 && wstat.wall_ticks-w_before>=60 && dw4_lobby_hit_state(wd,d->name)==1);
    dw4_lobby_collision_counts(wd,&d->walls_closed,NULL);d->tested=1;free(side);
}
/* The live flag bytes of the shared common folder. A folder commit replaces its payload, so a pointer fetched earlier goes stale (a door script's flag then
 * reads clear): every read fetches the bytes again. */
static const uint8_t *flagnow(dw4_hubruntime *h){return dw4_property_bytes(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0),"FLAG",NULL);}
/* (2) The floor script opened the door: its flag is set, the mesh left the wall set (fewer wall triangles), and the same walk now crosses. */
static void door_cross(dw4_hubruntime *h,unsigned *frame,struct door *d,const uint8_t *fb)
{(void)fb;   /* the flag bytes are fetched again on every read (flagnow) */
    dw4_lobby *wd=dw4_hubruntime_world(h);
    for(unsigned t=0;t<400 && dw4_lobby_hit_state(wd,d->name)!=0;t++)wtick(h,frame,0,0,0,0);
    unsigned w1;dw4_lobby_collision_counts(wd,&w1,NULL);
    fprintf(stderr,"  %s: flag %d, hit state %d, wall triangles %u -> %u\n",d->name,flagnow(h)[d->flag],dw4_lobby_hit_state(wd,d->name),d->walls_closed,w1);
    assert(flagnow(h)[d->flag] && dw4_lobby_hit_state(wd,d->name)==0 && w1<d->walls_closed);
    float gap=0;int ok=walk_box(h,frame,d->far[0]-4,d->far[0]+4,d->far[1]-4,d->far[1]+4,20000,1,&gap);
    float pp[3];player_pos(h,pp);fprintf(stderr,"  %s open: walked across to %.0f %.0f (%d)\n",d->name,pp[0],pp[2],ok);
    assert(ok);d->tested=2;
}
/* After fighting: a pushed door whose flag is now set gets its crossing proof; a door opened before the push is checked; a door with a clear flag is solid. */
static void doors_settle(dw4_hubruntime *h,unsigned *frame,struct door *doors,unsigned ndoors,const uint8_t *fb,unsigned *crossed)
{
    dw4_lobby *wd=dw4_hubruntime_world(h);
    for(unsigned d=0;d<ndoors;d++){
        if(doors[d].tested==1 && doors[d].flag>=0 && flagnow(h)[doors[d].flag]){door_cross(h,frame,doors+d,fb);(*crossed)++;}
        if(doors[d].tested==3 && doors[d].flag>=0 && flagnow(h)[doors[d].flag]){for(unsigned t=0;t<400 && dw4_lobby_hit_state(wd,doors[d].name)!=0;t++)wtick(h,frame,0,0,0,0);assert(dw4_lobby_hit_state(wd,doors[d].name)==0);doors[d].tested=4;}
        if(doors[d].flag>=0 && !flagnow(h)[doors[d].flag])assert(dw4_lobby_hit_state(wd,doors[d].name)==1);
    }
}
/* Walk up to a model (a button) and swing at it with the pad until the floor script's flag is set. */
static void hit_target(dw4_hubruntime *h,unsigned *frame,const float pos[3],const uint8_t *fb,int flag)
{(void)fb;
    float gap=0;int ok=walk_box(h,frame,pos[0]-12,pos[0]+12,pos[2]-12,pos[2]+12,4000,1,&gap);
    dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);int32_t delay=26;dw4_property_number(p0,"ATTACKDELAY",&delay);
    fprintf(stderr,"  walked to the target at %.0f %.0f (%d), swinging\n",pos[0],pos[2],ok);
    for(unsigned n=0;n<16 && !flagnow(h)[flag];n++){
        float pp[3];player_pos(h,pp);
        for(unsigned t=0;t<150 && hypotf(pos[0]-pp[0],pos[2]-pp[2])>6.0f;t++){wstep(h,frame,pos[0],pos[2],0,0);player_pos(h,pp);}   /* close in to a swing's reach */
        for(unsigned i=0;i<14;i++){if(!control(h)){wstep(h,frame,pos[0],pos[2],0,0);continue;}float x,y,sc=i<2?1.0f:.05f;stick_dir(h,pos[0],pos[2],&x,&y);wtick(h,frame,x*sc,y*sc,i>=2&&i<5?0x4000:0,i==2?0x4000:0);}
        for(unsigned i=0;i<(unsigned)delay*5/2;i++)wtick(h,frame,0,0,0,0);
        if(getenv("WDBG")){player_pos(h,pp);fprintf(stderr,"    swing %u at the target from %.1f %.1f (target %.1f %.1f), flag %d\n",n,pp[0],pp[2],pos[0],pos[2],flagnow(h)[flag]);}
    }
}
/* gene09refill: the victim's life cycle under the generator. One tick with optional Cross, then the observations of this tick (frame numbers are ticks of 1/60 s). */
struct g9obs {int hp0,end,refill;unsigned base_total;float rot0,drift;};   /* tick (from the start of g9_kill) of HP 0, of the instance ending and of the refill; -1 until seen */
static int g9_active(dw4_hubruntime *h,const char *model,int32_t slot,float pos[3])
{
    for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){
        const dw4_stageobject *info;int32_t s;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&s);
        if(!mc || !info || s!=slot || strcmp(dw4_stageobject_name(info),model))continue;
        if(pos){dw4_modelctrl_actor a;dw4_modelctrl_actor_state(mc,&a);memcpy(pos,a.position,12);}
        return dw4_modelctrl_active(mc);}
    return 0;
}
/* Kill `slot` (HP set to 1 first so the one swing kills; the damage, HP 0 and the death sequences are the port's own) from a spot 7 units off on the side of
 * `home`, then follow it for `limit` ticks. `away` (when given) is where the player is placed on the tick HP reaches 0. Returns when `limit` ticks passed or,
 * with `stop_on_refill` 1 at the refill, with 2 two ticks after the end. */
static void g9_kill(dw4_hubruntime *h,unsigned *frame,const dw4_gene *g,const char *model,int32_t slot,const float home[3],const char *away,struct g9obs *o,unsigned limit,int stop_on_refill)
{
    dw4_script_model *st=dw4_hubruntime_enemy_state(h,model,slot);assert(st);
    st->hp=1;o->hp0=o->end=o->refill=-1;o->base_total=g->spawned_total;o->drift=0;
    float vp[3];assert(g9_active(h,model,slot,vp));
    float hx=home[0]-vp[0],hz=home[2]-vp[2],hl=sqrtf(hx*hx+hz*hz);if(hl<.01f){hx=0;hz=-1;hl=1;}
    for(unsigned t=0;t<limit;t++){
        if(o->hp0<0 && t%90==0){   /* (re)place and swing: a miss or a guard costs the attempt */
            g9_active(h,model,slot,vp);float px=vp[0]+hx/hl*7,pz=vp[2]+hz/hl*7;char where[96];
            snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,%g,0>",px,vp[1],pz,atan2f(vp[0]-px,vp[2]-pz)*57.29578f);place(h,where);}
        unsigned k=t%90;dw4_hubruntime_input(h,0,0,0,o->hp0<0 && k<3?0x4000:0,o->hp0<0 && k==0?0x4000:0);
        if(dw4_hubruntime_tick(h,(uint64_t)(*frame)++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));exit(1);}
        if(o->hp0<0 && st->hp<=0){o->hp0=(int)t;if(away)place(h,away);}
        if(o->hp0>=0 && (int)t<=o->hp0+24) {   /* retail: the victim snaps to face the attacker at the lethal hit and keeps that yaw through the first hop (40 victims, 0.000 degrees of change), #3083 */
            for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t sl;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&sl);
                if(mc && info && sl==slot && !strcmp(dw4_stageobject_name(info),model) && dw4_modelctrl_active(mc)){dw4_modelctrl_actor a;dw4_modelctrl_actor_state(mc,&a);
                    if((int)t==o->hp0)o->rot0=a.rotation[1];else{float d=fabsf(fmodf(a.rotation[1]-o->rot0+540.f,360.f)-180.f);if(d>o->drift)o->drift=d;}}}
        }
        /* a refill reuses the freed slot in the tick the instance ends (first_inactive), so the end is the first tick that no longer shows the dying victim (HP 0 and running) */
        if(o->hp0>=0 && o->end<0 && !(g9_active(h,model,slot,NULL) && st->hp<=0))o->end=(int)t;
        if(getenv("G9TRACE")){const char *sq="-";for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t s;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&s);
            if(mc && info && s==slot && !strcmp(dw4_stageobject_name(info),model) && dw4_modelctrl_active(mc)){dw4_modelctrl_actor a;dw4_modelctrl_actor_state(mc,&a);static char mb[48];snprintf(mb,sizeof mb,"%s/%s",dw4_modelctrl_sequence(mc),a.motion?a.motion:"");sq=mb;}}
            static char last[24];if(strcmp(last,sq)){fprintf(stderr,"    g9 t%u: hp %d seq %s total %u live %u\n",t,st->hp,sq,g->spawned_total,g->nlive);snprintf(last,sizeof last,"%s",sq);}}
        if(o->refill<0 && g->spawned_total>o->base_total)o->refill=(int)t;
        if(stop_on_refill==1 && o->refill>=0)return;
        if(stop_on_refill==2 && o->end>=0 && (int)t>=o->end+2)return;
    }
}
static int exit_by_stick;   /* take_exit walks into the exit region with the stick instead of placing the player in it */
static float getenv_f(const char *n,float d){const char *v=getenv(n);return v?(float)atof(v):d;}
static void set_party_level(dw4_hubruntime *h,unsigned party)   /* the route fixture: every joined player at FIXLEVEL (default 40; dungeonroute2 passes 60, see there), full HP / MP */
{
    for(unsigned q=0;q<party;q++){int lvl=getenv("FIXLEVEL")?atoi(getenv("FIXLEVEL")):40;int32_t mhp=0,mmp=0;
        dw4_property_folder *pq=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",(int)q);
        assert(!dw4_property_set_number(pq,"LEVEL",lvl) && !dw4_playerstats_recalculate((void *)dw4_hubruntime_databases(h),pq));
        assert(!dw4_property_number(pq,"MHP",&mhp) && !dw4_property_number(pq,"MMP",&mmp) && !dw4_property_set_number(pq,"HP",mhp) && !dw4_property_set_number(pq,"MP",mmp));}
}
static void practice_lessons(dw4_hubruntime *h,unsigned *frame_p)
{
    unsigned frame_local=*frame_p;unsigned *frame=&frame_local;
    dw4_property_folder *q=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);int32_t exp=0;unsigned t=0;
    while(t<80000){
        if(control(h))pilot(h,frame,300,0);else{for(unsigned i=0;i<300;i++){dw4_hubruntime_input(h,0,0,0,i%90<4?0x4000:0,i%90==0?0x4000:0);if(dw4_hubruntime_tick(h,(uint64_t)(*frame)++*1000000000ULL/60)){fprintf(stderr,"practice tick: %s\n",dw4_hubruntime_error(h));exit(1);}}}
        t+=300;dw4_property_number(q,"EXP",&exp);
        if(exp>=18 && !dw4_controllers_enemies_alive(dw4_hubruntime_models(h),NULL) && control(h)){pilot(h,frame,1500,0);break;}
    }
    /* the closing message ("Good luck!") waits for Cross while the player already has control */
    for(unsigned i=0;i<3000 && dw4_scriptengine_pending(dw4_hubruntime_scripts(h));i++){dw4_hubruntime_input(h,0,0,0,i%30<4?0x4000:0,i%30==0?0x4000:0);if(dw4_hubruntime_tick(h,(uint64_t)(*frame)++*1000000000ULL/60)){fprintf(stderr,"practice tick: %s\n",dw4_hubruntime_error(h));exit(1);}}
    fprintf(stderr,"practice: lessons done after %u ticks, EXP %d, DM groups left %zu\n",t,exp,dw4_scriptengine_pending(dw4_hubruntime_scripts(h)));assert(exp>=18 && !dw4_scriptengine_pending(dw4_hubruntime_scripts(h)));
    *frame_p=*frame;
}
/* Step into an exit region and confirm its prompt (Cross taps) until the stage request appears; then prepare the destination from this runtime's record. */
static dw4_hubruntime *take_exit(dw4_mount *mount,dw4_hubruntime *h,unsigned *frame,const char *stage,const char *mate,const char *expect,int expect_point)
{
    float lo[3],hi[3];char where[96],error[512];
    mat_region(mount,stage,mate,lo,hi);
    for(unsigned w=0;w<120;w++){dw4_hubruntime_input(h,0,0,0,0,0);if(dw4_hubruntime_tick(h,(uint64_t)(*frame)++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));exit(1);}}   /* settle after the arrival hand-off */
    if(exit_by_stick){float gap=0,pe[3];int ok=!player_pos(h,pe) && pe[0]>=lo[0] && pe[0]<=hi[0] && pe[2]>=lo[2] && pe[2]<=hi[2];   /* already inside the region: the trigger is the box itself, not its 1.5-unit inset */
        if(!ok)ok=walk_box(h,frame,lo[0]+1.5f,hi[0]-1.5f,lo[2]+1.5f,hi[2]-1.5f,9000,1,&gap);{float pp_[3];player_pos(h,pp_);fprintf(stderr,"%s/%s: walked into the exit region %d (gap %.1f, player %.1f %.1f %.1f)\n",stage,mate,ok,gap,pp_[0],pp_[1],pp_[2]);}assert(ok);}
    else{snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",(lo[0]+hi[0])/2,strcmp(stage,"stag0001")?lo[1]+60:10.0f,(lo[2]+hi[2])/2-2);place(h,where);}   /* the practice arena floor is y 10 */
    for(unsigned q=1;q<=pilot_extra;q++){   /* the exit scripts ask MATisAllPlayer: every joined player stands in the region */
        char w2[96];float lp[3]={0,0,0};if(exit_by_stick)player_pos(h,lp);   /* walked in: the others stand at the leader's height (the exit floor need not be the region's base) */
        if(exit_by_stick)snprintf(w2,sizeof w2,"V<%g,%g,%g>/V<0,0,0>",lp[0]+((q&1)?1.0f:-1.0f)*(float)((q+1)/2)*0.8f,lp[1]+1.0f,lp[2]);   /* on the leader's own floor */
        else snprintf(w2,sizeof w2,"V<%g,%g,%g>/V<0,0,0>",(lo[0]+hi[0])/2+((q&1)?-1.0f:1.0f)*(float)((q+1)/2)*2.2f,strcmp(stage,"stag0001")?lo[1]+60:10.0f,(lo[2]+hi[2])/2-2);
        place_slot(h,q,w2);
    }
    unsigned i=0;
    for(;i<2000 && !dw4_hubruntime_travel(h)->pending;i++){
        if(getenv("WDBG") && (i==1 || i==100 || i==500 || i==1500)){fprintf(stderr,"  exit wait i=%u dm pending %zu control %d\n",i,dw4_scriptengine_pending(dw4_hubruntime_scripts(h)),control(h));for(unsigned q=0;q<=pilot_extra;q++){dw4_lobby_walk_state ws;dw4_lobby_select_player(dw4_hubruntime_world(h),q);if(!dw4_lobby_walk(dw4_hubruntime_world(h),&ws))fprintf(stderr,"  exit wait i=%u slot %u at %.1f %.1f %.1f\n",i,q,ws.position[0],ws.position[1],ws.position[2]);}dw4_lobby_select_player(dw4_hubruntime_world(h),0);}
        dw4_hubruntime_input(h,0,0,0,i%40<4?0x4000:0,i>60 && i%40==0?0x4000:0);
        for(unsigned q=1;q<=pilot_extra;q++)dw4_hubruntime_input_slot(h,q,0,0,0,i%40<4?0x4000:0,i>60 && i%40==0?0x4000:0);   /* the prompt belongs to the player who completed the party in the region (MATgetPlayerNo), the last one placed after a walk */
        if(dw4_hubruntime_tick(h,(uint64_t)(*frame)++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));exit(1);}
    }
    const dw4_stagetravel *t=dw4_hubruntime_travel(h);
    fprintf(stderr,"%s/%s -> %s point %d after %u ticks\n",stage,mate,t->destination,t->generate_pos,i);
    assert(t->pending && !strcasecmp(t->destination,expect) && t->generate_pos==expect_point);
    dw4_stageinput in=*dw4_hubruntime_input_state(h);
    dw4_hubruntime_source prior={dw4_hubruntime_records(h),dw4_hubruntime_state(h),&in,dw4_hubruntime_time(h)};
    dw4_hubruntime *next=dw4_hubruntime_prepare(mount,&prior,expect,expect_point,1,error,sizeof error);
    if(!next){fprintf(stderr,"prepare %s: %s\n",expect,error);exit(1);}
    dw4_hubruntime_close(h);return next;
}
/* A fake combat owner for the contact-wrapper checks of `statusapply`: it records what the BLT / BLP wrappers hand to the rules. */
struct fake {
    unsigned p2e,e2p;
    char p2e_method[32],p2e_what[16],e2p_method[32],e2p_what[16];
    int32_t p2e_attack,p2e_row,p2e_shooter,e2p_player,e2p_row,e2p_attack;
    const dw4_status *hit_target,*dmg_target,*e2p_dmg_attacker,*stun_attacker;
};
static int fk_hit(void *u,int32_t sh,int32_t row,int32_t atk,const dw4_status *t,int *hit){struct fake *f=u;(void)sh;(void)row;(void)atk;f->hit_target=t;*hit=1;return 0;}
static int fk_dmg(void *u,int32_t sh,int32_t row,int32_t atk,int crit,const dw4_status *t,int32_t out[3]){struct fake *f=u;(void)sh;(void)row;(void)atk;(void)crit;f->dmg_target=t;out[0]=5;out[1]=-1;out[2]=0;return 0;}
static int fk_p2e(void *u,int32_t sh,int32_t row,int32_t atk,const char *method,const char *what,int32_t *out)
{struct fake *f=u;f->p2e++;snprintf(f->p2e_method,sizeof f->p2e_method,"%s",method);snprintf(f->p2e_what,sizeof f->p2e_what,"%s",what?what:"-");f->p2e_attack=atk;f->p2e_row=row;f->p2e_shooter=sh;*out=77;return 0;}
static int fk_e2p_hit(void *u,int32_t p,int32_t row,int32_t atk,int *hit){(void)u;(void)p;(void)row;(void)atk;*hit=1;return 0;}
static int fk_e2p_dmg(void *u,int32_t p,int32_t row,int32_t atk,const dw4_status *a,int32_t out[3]){struct fake *f=u;(void)p;(void)row;(void)atk;f->e2p_dmg_attacker=a;out[0]=3;out[1]=-1;out[2]=0;return 0;}
static int fk_e2p_stun(void *u,int32_t p,int32_t row,int32_t atk,int32_t dmg,int32_t rank,const dw4_status *a,int32_t *time){struct fake *f=u;(void)p;(void)row;(void)atk;(void)dmg;(void)rank;f->stun_attacker=a;*time=9;return 0;}
static int fk_e2p(void *u,int32_t p,int32_t row,int32_t atk,const char *method,const char *what,int32_t *out)
{struct fake *f=u;f->e2p++;snprintf(f->e2p_method,sizeof f->e2p_method,"%s",method);snprintf(f->e2p_what,sizeof f->e2p_what,"%s",what?what:"-");f->e2p_attack=atk;f->e2p_row=row;f->e2p_player=p;*out=-1;return 0;}
/* statusflow helpers:the Goblin Pass goblin (RAM slot 5) as the status target, and one synthetic player bullet through the real hit chunk. */
static const dw4_modelctrl *goblin_model(dw4_hubruntime *h)
{
    for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){
        const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
        if(mc && !strcmp(dw4_stageobject_name(info),"e_goburi") && slot==5)return mc;
    }
    return NULL;
}
static const dw4_status *goblin_status(dw4_hubruntime *h){return dw4_controllers_status(dw4_hubruntime_models(h),"e_goburi",5);}
static const char *goblin_seq(dw4_hubruntime *h){const char *s=dw4_modelctrl_sequence(goblin_model(h));return s?s:"-";}
/* MDLisStatus as the hit script asks it: MODELCTRL <name> <ram> querySD CHECKSTATUS <status>. */
static int goblin_check(dw4_hubruntime *h,const char *status)
{
    char error[256];dw4_script_value a[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"e_goburi",8},{DW4_SCRIPT_NUMBER,5,NULL,0},{DW4_SCRIPT_STRING,0,"CHECKSTATUS",11},{DW4_SCRIPT_STRING,0,status,strlen(status)}},r;
    assert(!dw4_controllers_send((dw4_controllers *)dw4_hubruntime_models(h),"e_goburi",5,"querySD",a,5,&r,error,sizeof error) && r.type==DW4_SCRIPT_NUMBER);
    return (int)r.number;
}
/* One synthetic player bullet of `kind` (a technique's 4xxxx number: no technique volume can be fired yet) on the goblin's body. */
static int fire(dw4_hubruntime *h,unsigned frame,int32_t kind)
{
    dw4_model_fight f;dw4_combat_fight(dw4_hubruntime_combat_owner(h),&f);
    dw4_modelctrl_actor ga;float gw[16];const float zero[3]={0,0,0},size[3]={6,6,6};
    dw4_modelctrl_actor_state(goblin_model(h),&ga);dw4_modelctrl_actor_matrix(&ga,gw);
    dw4_model_bullet b={.kind=kind,.shoot_ram_no=0,.group=DW4_BULLET_PLAYER,.world_ns=(int64_t)frame*1000000000LL/60,.name="",.fight=&f};
    memcpy(b.source_world,gw,sizeof gw);dw4_hitbox_bullet(gw,zero,size,b.box);
    int hits=dw4_controllers_enemy_bullet((dw4_controllers *)dw4_hubruntime_models(h),&b);
    if(hits<0){fprintf(stderr,"fire %d: %s\n",kind,dw4_controllers_error(dw4_hubruntime_models(h)));exit(1);}
    return hits;
}
/* A weapon bullet (kind 10000) on the goblin, replayed against the P2E rules on a copy of the random stream with the receiver's down values `down`: the HP it
 * lost must equal the replayed damage. Repeats (a miss costs the attempt) until a hit landed; `*plain` is the damage the same draws give with no down values. */
static int32_t weapon_hit_checked(dw4_hubruntime *h,unsigned *frame,dw4_property_folder *p0,const dw4_database *enemy,const dw4_database *tech,dw4_script_model *goblin,
    dw4_fight_down down,int32_t *plain)
{
    const int32_t big=goblin->max_hp;
    for(unsigned tries=0;tries<40;tries++){
        goblin->hp=big;
        dw4_random a=dw4_hubruntime_state(h)->random,b;dw4_fight_ctx ca={p0,dw4_database_typed(enemy),&a,dw4_database_typed(tech)},cb={p0,dw4_database_typed(enemy),&b,dw4_database_typed(tech)};
        int hit=0,crit=0;dw4_fight_damage da={0},db={0};
        assert(!dw4_fight_p2e_is_hit(&ca,0,10000,down,&hit));
        if(hit){
            assert(!dw4_fight_p2e_is_critical(&ca,0,10000,&crit));
            b=a;
            assert(!dw4_fight_p2e_damage(&ca,0,10000,crit,down,&da) && !dw4_fight_p2e_damage(&cb,0,10000,crit,(dw4_fight_down){0,0},&db));
        }
        fire(h,*frame,10000);
        int32_t dealt=big-goblin->hp;
        run(h,frame,100,0,0);
        if(!hit){assert(dealt==0);continue;}
        assert(dealt==da.damage);
        *plain=db.damage;return dealt;
    }
    assert(!"no weapon hit landed");return 0;
}
/* One scripted mission: ... */
/* One world frame for the technique test: pad input (held word, Cross/Circle edge word), then the tick. Returns the tick result. */
static int tech_frame(dw4_hubruntime *h,unsigned *frame,uint32_t held,uint32_t pressed)
{
    dw4_hubruntime_input(h,0,0,0,held,pressed);
    return dw4_hubruntime_tick(h,(uint64_t)(*frame)++*1000000000ULL/60);
}
static int32_t tech_prop(dw4_property_folder *f,const char *key){int32_t v=-99999;assert(f && !dw4_property_number(f,key,&v));return v;}
static dw4_technique_panel tech_panel(const dw4_technique *t,int slot){dw4_technique_panel p;assert(!dw4_technique_panel_get(t,slot,&p));return p;}
static void tech_step(dw4_hubruntime *h,unsigned *frame,uint32_t held,uint32_t pressed)
{if(tech_frame(h,frame,held,pressed)){fprintf(stderr,"technique tick %u: %s\n",*frame,dw4_hubruntime_error(h));exit(1);}}
static void tech_frames(dw4_hubruntime *h,unsigned *frame,unsigned count)
{
    for(unsigned i=0;i<count;i++)if(tech_frame(h,frame,0,0)){fprintf(stderr,"technique tick %u: %s\n",*frame,dw4_hubruntime_error(h));exit(1);}
}
/* Per slot: the runtime admits one player, so two independent panels are driven through the module itself (own list, cursor, MP and lock). */
static void tech_slots(dw4_playerrecords *rec,const dw4_databases *dbs,const dw4_database *tdb,dw4_property_folder *p0,int32_t cost,int32_t delay)
{
    dw4_technique_panel pv;
    char err2[256];
    assert(!dw4_playerrecords_create(rec,dbs,1,"p_agumon","Mate",err2,sizeof err2));
    dw4_property_folder *p1=dw4_playerrecords_get(rec,"GETPLAYER",1);assert(p1);
    dw4_item_record items[6];for(int i=0;i<6;i++)items[i]=(dw4_item_record){9,i*5,0,i*5,0};   /* Fire, Ice, Bolt, Dark, Venom, Impact: tier-1 rows */
    assert(!dw4_property_set_items(p1,"WAZALIST",items,6) && !dw4_property_set_number(p1,"MP",600) && !dw4_property_set_number(p1,"MMP",600));
    assert(!dw4_property_set_number(p0,"MP",60));
    dw4_technique *two=dw4_technique_open(rec,dbs);assert(two);
    dw4_technique_pad r1={.pressed=0x800,.can_open=1},none={.can_open=1},cross={.pressed=0x4000,.can_open=1},down={.down=1,.can_open=1},up={.up=1,.can_open=1};
    uint64_t now=1000000000ULL;
    assert(!dw4_technique_input(two,0,now,&none) && !dw4_technique_input(two,1,now,&none));
    assert(dw4_technique_input(two,1,now,&r1));                          /* slot 1 opens ... */
    pv=tech_panel(two,1);assert(pv.open && pv.count==6);
    pv=tech_panel(two,0);assert(!pv.open);                               /* ... slot 0 does not */
    assert(dw4_technique_input(two,0,now,&r1));
    for(int t=0;t<2;t++){dw4_technique_tick(two,0,1);dw4_technique_tick(two,1,1);now+=16666667;}
    /* slot 1: the four-row window scrolls without wrapping (down x4 -> cursor 3, offset 1; down x5 reaches the last entry) */
    for(int i=0;i<4;i++)dw4_technique_input(two,1,now,&down);
    pv=tech_panel(two,1);assert(pv.cursor==3 && pv.offset==1);
    for(int i=0;i<4;i++)dw4_technique_input(two,1,now,&down);
    pv=tech_panel(two,1);assert(pv.cursor==3 && pv.offset==2);          /* stops at the last entry (cursor + offset == 5) */
    for(int i=0;i<8;i++)dw4_technique_input(two,1,now,&up);
    pv=tech_panel(two,1);assert(pv.cursor==0 && pv.offset==0);          /* stops at the top row */
    for(int i=0;i<4;i++)dw4_technique_input(two,1,now,&down);
    pv=tech_panel(two,1);assert(pv.cursor+pv.offset==4);                /* Venom */
    int32_t vcost=0,vdelay=0;assert(!dw4_database_number(tdb,20,"MP",&vcost) && !dw4_database_number(tdb,20,"DELAY",&vdelay) && vdelay>delay);
    pv=tech_panel(two,0);assert(pv.cursor==0);                           /* slot 0's cursor did not move */
    assert(dw4_technique_input(two,1,now,&cross));
    assert(tech_prop(p1,"MP")==600-vcost && tech_prop(p0,"MP")==60);     /* only the casting slot pays */
    assert(dw4_technique_input(two,0,now,&cross));
    assert(tech_prop(p0,"MP")==60-cost && tech_prop(p1,"MP")==600-vcost);  /* slot 1's lock does not stop slot 0 */
    dw4_technique_cast c1,c0;
    assert(dw4_technique_poll(two,1,0,&c1) && c1.row==20 && c1.attack==40020 && !c1.support && !strcmp(c1.label,"venom1"));
    assert(dw4_technique_poll(two,0,0,&c0) && c0.row==5 && c0.attack==40005 && !strcmp(c0.label,"ice1"));
    assert(!dw4_technique_poll(two,0,0,&c0));                            /* a fire is consumed by one poll */
    /* each slot's own DELAY: slot 0 (75) is free again when slot 1 (90) is still locked */
    uint64_t later=now+(uint64_t)delay*1000000000ULL/60;
    assert(!dw4_property_set_number(p1,"MP",600));
    dw4_technique_input(two,1,later,&cross);assert(tech_prop(p1,"MP")==600);               /* still locked */
    dw4_technique_input(two,0,later,&cross);assert(tech_prop(p0,"MP")==60-2*cost);          /* free */
    dw4_technique_input(two,1,now+(uint64_t)vdelay*1000000000ULL/60,&cross);assert(tech_prop(p1,"MP")==600-vcost);
    /* a panel closes when its player loses control (OFCTRL clears the open byte); the other slot's stays */
    dw4_technique_tick(two,0,0);pv=tech_panel(two,0);assert(!pv.open);
    pv=tech_panel(two,1);assert(pv.open);
    dw4_technique_close(two);
}
/* One scenario per process: the record/database owners are created once per run. */
/* ---- support technique fixtures (docs/combat.md "Support technique wiring"): shared by the support* modes. The field runtime admits one player, so a second
 * joined player is a record (slot 1) plus a second player model made from the lobby player's programs (dw4_modelctrl_instance); the seam tests drive the
 * combat owner directly (dw4_combat_players / dw4_combat_cast_support / dw4_combat_status_tick) and never tick the hub after slot 1 exists. ---- */
struct sup {
    dw4_hubruntime *h;dw4_combat *c;dw4_playerrecords *rec;const dw4_databases *dbs;const dw4_database *tdb;
    dw4_property_folder *p[2];dw4_modelctrl *m[2];dw4_modelctrl *players[4];int64_t t0[2];unsigned k;dw4_combat_view view;
};
static dw4_script_value sstr(const char *s){return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
/* An SD message to one player model ("MODELCTRL <name> <ram> <message> [args]"), as MDLsetSD / PLAYER sd would deliver it. */
static void sup_sd(dw4_modelctrl *m,int slot,const char *msg,const char *args)
{
    dw4_script_value a[5]={sstr("MODELCTRL"),sstr("p"),{DW4_SCRIPT_NUMBER,slot,NULL,0},sstr(msg),args?sstr(args):(dw4_script_value){0}},r;char e[256];
    if(dw4_modelctrl_service(m,"sd",a,args?5:4,&r,e,sizeof e)){fprintf(stderr,"sd %s: %s\n",msg,e);exit(1);}
}
static void sup_place(struct sup *s,int slot,float x,float y,float z)
{
    char text[96];snprintf(text,sizeof text,"V<%g,%g,%g>/V<0,0,0>",x,y,z);
    sup_sd(s->m[slot],slot,"MOVETRANS",text);s->view.pos[slot][0]=x;s->view.pos[slot][1]=y;s->view.pos[slot][2]=z;
}
/* Species 15 at `level` (Heal Lt from level 1, Cure Lt 12, Speed 22, Resist 33); with `second` a mate in slot 1 with a model, both joined. */
static void sup_open(dw4_mount *mount,struct sup *s,unsigned *frame,int level,int second)
{
    const int revisit[]={2,355,503};char error[256];
    memset(s,0,sizeof *s);
    s->h=enter(mount,revisit,3);run(s->h,frame,600,0,0);assert(control(s->h));
    s->c=dw4_hubruntime_combat_owner(s->h);s->rec=dw4_hubruntime_records(s->h);s->dbs=dw4_hubruntime_databases(s->h);s->tdb=dw4_databases_get(s->dbs,"pcTech");
    s->m[0]=dw4_lobby_player_model(dw4_hubruntime_world(s->h));s->p[0]=dw4_playerrecords_get(s->rec,"GETPLAYER",0);
    assert(s->c && s->tdb && s->m[0] && s->p[0]);
    assert(!dw4_property_set_number(s->p[0],"DIGIMONNO",15) && !dw4_property_set_number(s->p[0],"LEVEL",level));
    s->view.joined[0]=s->view.running[0]=1;
    if(second){
        assert(!dw4_playerrecords_create(s->rec,s->dbs,1,"p_agumon","Mate",error,sizeof error));
        s->p[1]=dw4_playerrecords_get(s->rec,"GETPLAYER",1);assert(s->p[1]);
        assert(!dw4_property_set_number(s->p[1],"ISUSE",1) && !dw4_property_set_number(dw4_playerrecords_get(s->rec,"GETCOMMON",0),"NINZU",2));
        s->m[1]=dw4_modelctrl_instance(s->m[0]);assert(s->m[1] && !dw4_modelctrl_active(s->m[1]) && !dw4_modelctrl_start(s->m[1],"SQ_WAIT") && dw4_modelctrl_active(s->m[1]));
        s->view.joined[1]=s->view.running[1]=1;
    }
    s->players[0]=s->m[0];s->players[1]=s->m[1];
    dw4_combat_players(s->c,s->players);
    s->t0[0]=dw4_modelctrl_now(s->m[0]);s->t0[1]=s->t0[0];
    if(second){dw4_modelctrl_sample(s->m[1],s->t0[1]);sup_place(s,0,0,0,0);sup_place(s,1,100,0,0);}
}
/* The skill array and a recalculation (which sets WAZALIST), then the values the recalculation would otherwise own. mhp 0 keeps the recalculated MHP. */
static void sup_record(struct sup *s,int slot,const int32_t sk[9],int32_t kash,int32_t mhp,int32_t hp)
{
    dw4_property_folder *f=s->p[slot];int32_t v;
    assert(!dw4_property_set_array(f,"SKILL",sk,9) && !dw4_playerstats_recalculate((void *)s->dbs,f));
    if(kash>=0)assert(!dw4_property_set_number(f,"KASHIKOSA",kash));
    if(mhp>0)assert(!dw4_property_set_number(f,"MHP",mhp));
    if(hp<0){assert(!dw4_property_number(f,"MHP",&v));hp=v;}
    assert(!dw4_property_set_number(f,"HP",hp));
}
/* `frames` simulation frames of the status manager for every model (the model clocks advance by whole frames of the 60 Hz world clock). */
static void sup_advance(struct sup *s,unsigned frames)
{
    char error[256];
    for(unsigned i=0;i<frames;i++){
        s->k++;
        for(int q=0;q<2;q++)if(s->m[q])dw4_modelctrl_sample(s->m[q],s->t0[q]+(int64_t)s->k*1000000000LL/60);
        dw4_combat_players(s->c,s->players);
        if(dw4_combat_status_tick(s->c,s->players,error,sizeof error)){fprintf(stderr,"status tick: %s\n",error);exit(1);}
    }
}
static int wazalist_row(dw4_property_folder *f,int base)
{
    size_t n=0;const dw4_item_record *w=dw4_property_items(f,"WAZALIST",&n);
    for(size_t i=0;w && i<n;i++)if(w[i].revision==base)return w[i].record;
    return -1;
}
/* Fabricate WAZALIST items after the last recalculation (the next recalculation rebuilds the list from the species and skills). */
static void waza_set(dw4_property_folder *f,const int32_t (*items)[2],unsigned n)
{
    dw4_item_record w[6];assert(n<=6);
    for(unsigned i=0;i<n;i++)w[i]=(dw4_item_record){9,items[i][0],0,items[i][1],0};
    assert(!dw4_property_set_items(f,"WAZALIST",w,n));
}
static void waza_add(dw4_property_folder *f,int32_t record,int32_t base)
{
    size_t n=0;const dw4_item_record *w=dw4_property_items(f,"WAZALIST",&n);dw4_item_record out[6];
    assert(n<6);memcpy(out,w,n*sizeof *w);out[n++]=(dw4_item_record){9,record,0,base,0};
    assert(!dw4_property_set_items(f,"WAZALIST",out,n));
}
static int32_t tdb_num(const dw4_database *t,int row,const char *col){int32_t v=-99999;assert(!dw4_database_number(t,row,col,&v));return v;}
static int32_t rec_num(dw4_property_folder *f,const char *key){return tech_prop(f,key);}
static int floored_sum(int32_t old,int32_t add,int32_t now){return now==old+add || (old==1 && now==add);}
static const int32_t *rec_up(dw4_property_folder *f){size_t n=0;const int32_t *u=dw4_property_array(f,"UPDATA",&n);assert(u && n==11);return u;}
/* The number of draws between two copies of the engine stream (-1 when more than eight). */
static int rng_draws(const dw4_random *before,const dw4_random *after)
{
    dw4_random r=*before;
    for(int n=0;n<=8;n++){if(!memcmp(&r,after,sizeof r))return n;dw4_random_next(&r);}
    return -1;
}
/* The numbers FIGHTCALC would append for `attack` cast by `slot`, computed from the record as it is now. */
static dw4_magic sup_magic(struct sup *s,int slot,int32_t attack)
{
    dw4_random scratch=dw4_hubruntime_state(s->h)->random;dw4_fight_ctx x={s->p[slot],dw4_database_typed(dw4_databases_get(s->dbs,"enemy")),&scratch,dw4_database_typed(s->tdb)};dw4_magic m;
    assert(!dw4_fight_p2p_magic(&x,slot,slot,attack,&m) && m.kind!=DW4_MAGIC_NONE);return m;
}
int main(int argc,char **argv)
{
    dw4_mount mount;assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../local/extracted"));
    const char *mode=argc>2?argv[2]:"revisit";
    if(!strcmp(mode,"dungeon") && getenv("FLOOR") && strcmp(getenv("FLOOR"),"dng101b1") && strcmp(getenv("FLOOR"),"dng101b2"))mode="dungeonopen";   /* FLOOR names a floor with no route from stag0101 in this build */
    assert(dw4_hubruntime_destination_available("stag0101") && !dw4_hubruntime_destination_available("stag0401") && !getenv("STAGE")==!getenv("STAGE"));

    dw4_hubruntime *h;unsigned frame=0;
    if(!strcmp(mode,"hitschedule")) {
        /* Callback ownership: models and combat may close in either order. */
        dw4_arena *arena=dw4_session_arena();unsigned baseline=dw4_arena_live(arena,DW4_REGION_PERSISTENT);
        struct sup s;sup_open(&mount,&s,&frame,1,0);char error[256];
        /* The real field publication binds player dependencies without adding
         * a second model updater. Leave an owned effect live through teardown. */
        dw4_modelctrl_record player_record=dw4_modelctrl_records(s.m[0]);
        beBaseInfoRam *player_ram=DW4_ARENA_OBJ(arena,beBaseInfoRam,player_record.ram);
        assert(player_ram->_parentInfo && player_ram->_parentManager);
        const char *player_name=dw4_property_string(s.p[0],"DIGIMONNAME");float bone[16];
        assert(dw4_controllers_bone((dw4_controllers *)dw4_hubruntime_models(s.h),player_name,0,"RArm04",bone)==1);
        dw4_script_value fx[]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},
            {DW4_SCRIPT_STRING,0,"SETEFFECT",9},{DW4_SCRIPT_STRING,0,"x_250healhit00/SQ_HEALEFONLY/F<0>/V<0,0,0>/TRUE/FALSE",0}},reply;
        fx[4].length=strlen(fx[4].string);
        assert(!dw4_hubruntime_sd(s.h,fx,5,&reply,error,sizeof error));
        run(s.h,&frame,1,0,0);
        assert(dw4_controllers_live(dw4_hubruntime_models(s.h),"x_250healhit00",0)==1);
        assert(!dw4_playerrecords_create(s.rec,s.dbs,1,"p_dorumon","Partner",error,sizeof error));
        uint32_t bytes;const uint8_t *blob=dw4_mount_data(&mount,"m_dorumon.igb",&bytes);assert(blob);
        dw4_modelctrl *extra=dw4_modelctrl_open(blob,bytes,"p_dorumon");assert(extra);
        dw4_modelctrl_sample(extra,0);assert(!dw4_modelctrl_start(extra,"SQ_WAIT"));
        dw4_modelctrl *players[4]={s.m[0],extra,NULL,NULL};dw4_combat_players(s.c,players);
        for(int i=0;i<32;i++){
            unsigned before=dw4_arena_live(arena,DW4_REGION_PERSISTENT);
            dw4_modelctrl *temporary=dw4_modelctrl_instance(extra);assert(temporary);players[2]=temporary;
            dw4_combat_players(s.c,players);dw4_modelctrl_close(temporary);players[2]=NULL;
            dw4_combat_view view;dw4_combat_view_current(s.c,&view);assert(!view.joined[2]);
            assert(dw4_arena_live(arena,DW4_REGION_PERSISTENT)==before);
        }
        dw4_modelctrl_record r=dw4_modelctrl_records(extra);
        DW4_ARENA_OBJ(arena,beModelCtrlInfoWork,r.work)->_isOnCtrl=0;
        /* Bind the actual HP/script transport, but reject the controlled hit
         * before executing a hit chunk, so teardown checks own the dependency. */
        assert(!dw4_combat_hit_player(s.c,1,extra,1,70009,0,0,NULL,error,sizeof error));
        dw4_hubruntime_close(s.h);
        int32_t hp=50;assert(!dw4_modelctrl_status_tick(extra,&hp,NULL));
        assert(!dw4_modelctrl_tick_frame(extra,16666667,0x3f800000));dw4_modelctrl_close(extra);
        assert(dw4_arena_live(arena,DW4_REGION_PERSISTENT)==baseline);
        puts("HITBOX delivery: both callback teardown orders, player membership invalidation and surviving stat/script transport detach pass");return 0;
    }
    if(!strcmp(mode,"statusapply")) {
        /* Status application on a model (port/docs/combat.md "Status application on models"); every number is an instruction-level fact. */
        const int64_t f=(1000000000LL+59)/60;   /* one frame in ns, rounded up (the retail timers compare strictly greater) */
        dw4_status s;dw4_status_tick_result r;int32_t hp=100;
        dw4_status_init(&s,0);
        assert(dw4_status_id("POISON")==0 && dw4_status_id("STUN")==9 && dw4_status_id("RARE")==10 && dw4_status_id("BOGUS")<0);
        /* Slots: ATTACKDOWN owns down[0..3], POWERDOWN down[4..5] (readers: [3] evasion, [5] defense, [4] attack, [1] critical, [2] paralysis). */
        assert(!dw4_status_message(&s,"SETATTACKDOWN","I<300>/I<5>/I<6>/I<7>/I<8>",&r));
        assert(dw4_status_check(&s,"ATTACKDOWN")==1 && dw4_status_down(&s,0)==5 && dw4_status_down(&s,1)==6 && dw4_status_down(&s,2)==7 && dw4_status_down(&s,3)==8);
        assert(!dw4_status_message(&s,"SETPOWERDOWN","I<120>/I<9>/I<10>",&r) && dw4_status_down(&s,4)==9 && dw4_status_down(&s,5)==10 && !r.recalc_player);
        assert(dw4_status_down(&s,6)==0 && dw4_status_message(&s,"SETLABEL","I<1>",&r)==1 && dw4_status_message(&s,"SETSTUN","oops",&r)<0);
        /* Refresh overwrites, it does not stack; times are frames: POWERDOWN (120) ends after 2 s, ATTACKDOWN (300) after 5 s. */
        assert(!dw4_status_message(&s,"SETATTACKDOWN","I<300>/I<1>/I<1>/I<1>/I<1>",&r) && dw4_status_down(&s,0)==1);
        for(int i=0;i<119;i++){dw4_status_tick(&s,f,"SQ_WAIT",&hp,&r);}
        assert(dw4_status_is_set(&s,DW4_STATUS_POWERDOWN) && dw4_status_down(&s,4)==9);
        dw4_status_tick(&s,f,"SQ_WAIT",&hp,&r);dw4_status_tick(&s,f,"SQ_WAIT",&hp,&r);
        assert(!dw4_status_is_set(&s,DW4_STATUS_POWERDOWN) && dw4_status_down(&s,4)==0 && dw4_status_down(&s,5)==0 && dw4_status_down(&s,0)==1);
        for(int i=0;i<200;i++)dw4_status_tick(&s,f,"SQ_WAIT",&hp,&r);
        assert(!dw4_status_is_set(&s,DW4_STATUS_ATTACKDOWN) && dw4_status_down(&s,0)==0 && dw4_status_down(&s,3)==0 && hp==100);
        /* The hook of the E2P status rules writes the same list; a player asks for the stat recalculation. */
        assert(!dw4_status_apply_down_slot(&s,4,33) && dw4_status_down(&s,4)==33 && dw4_status_apply_down_slot(&s,-1,0)<0);
        /* Sleep: SQ_SLEP once (unless already current), SQ_WAIT on expiry, no wake on damage. */
        dw4_status_init(&s,0);
        assert(!dw4_status_message(&s,"SETSLEEP","I<60>",&r) && dw4_status_check(&s,"SLEEP")==1);
        dw4_status_tick(&s,f,"SQ_WAIT",&hp,&r);assert(r.sequence && !strcmp(r.sequence,"SQ_SLEP"));
        hp=90;dw4_status_tick(&s,f,"SQ_SDMG",&hp,&r);assert(dw4_status_is_set(&s,DW4_STATUS_SLEEP) && !r.sequence);
        for(int i=0;i<62;i++){dw4_status_tick(&s,f,"SQ_SLEP",&hp,&r);if(r.sequence)break;}
        assert(r.sequence && !strcmp(r.sequence,"SQ_WAIT") && (r.expired>>DW4_STATUS_SLEEP&1) && !dw4_status_is_set(&s,DW4_STATUS_SLEEP));
        dw4_status_init(&s,0);dw4_status_message(&s,"SETSLEEP","I<60>",&r);dw4_status_tick(&s,f,"SQ_SLEP",&hp,&r);assert(!r.sequence);
        /* Stun: the block runs only while the current sequence is SQ_STUN (the script sets it before SETSTUN). */
        dw4_status_init(&s,0);
        assert(!dw4_status_message(&s,"SETSTUN","I<30>",&r));
        for(int i=0;i<100;i++)dw4_status_tick(&s,f,"SQ_SDMG",&hp,&r);
        assert(dw4_status_is_set(&s,DW4_STATUS_STUN) && s.first[DW4_STATUS_STUN]==1);
        int n=0;for(;n<100;n++){dw4_status_tick(&s,f,"SQ_STUN",&hp,&r);if(r.sequence)break;}
        assert(n==30 && !strcmp(r.sequence,"SQ_WAIT") && !dw4_status_is_set(&s,DW4_STATUS_STUN));
        /* Bind: timed lock that ends with SQ_WAIT; CHECKSTATUS (MDLisStatus) reports it. */
        dw4_status_init(&s,0);dw4_status_message(&s,"SETBIND","I<10>",&r);assert(dw4_status_check(&s,"BIND")==1);
        for(n=0;n<50;n++){dw4_status_tick(&s,f,"SQ_WAIT",&hp,&r);if(r.sequence)break;}
        assert(n==10 && !dw4_status_check(&s,"BIND"));
        /* CLEARSTATUS clears sleep/stun/bind and asks for SQ_WAIT; ALLCLEARSTATUS also the stat lists and the poison. */
        dw4_status_init(&s,1);
        dw4_status_message(&s,"SETSLEEP","I<600>",&r);dw4_status_message(&s,"SETBIND","I<600>",&r);dw4_status_message(&s,"SETPOISON","I<600>/I<5>/I<2>",&r);
        dw4_status_message(&s,"SETATTACKDOWN","I<600>/I<1>/I<2>/I<3>/I<4>",&r);assert(r.recalc_player);
        dw4_status_message(&s,"CLEARSTATUS",NULL,&r);assert(!strcmp(r.sequence,"SQ_WAIT") && !dw4_status_is_set(&s,DW4_STATUS_SLEEP) && dw4_status_is_set(&s,DW4_STATUS_POISON) && dw4_status_down(&s,3)==4);
        dw4_status_message(&s,"ALLCLEARSTATUS",NULL,&r);assert(r.recalc_player && !dw4_status_is_set(&s,DW4_STATUS_POISON) && !dw4_status_is_set(&s,DW4_STATUS_ATTACKDOWN) && dw4_status_down(&s,3)==0);
        /* Up lists: SPEEDUP up[0..3], POWERUP up[4..6]; a REFRACT write beyond the 7-entry list is dropped but the timer is set. */
        dw4_status_init(&s,0);
        dw4_status_message(&s,"SETSPEEDUP","I<60>/I<1>/I<2>/I<3>/I<4>",&r);dw4_status_message(&s,"SETPOWERUP","I<60>/I<5>/I<6>/I<7>",&r);
        dw4_status_message(&s,"SETREFRACT","I<60>/I<8>/I<9>/I<10>/I<11>",&r);
        assert(dw4_status_up(&s,0)==1 && dw4_status_up(&s,3)==4 && dw4_status_up(&s,4)==5 && dw4_status_up(&s,6)==7 && dw4_status_up(&s,7)==0 && dw4_status_check(&s,"REFRACT")==1);
        /* Poison: timer = frames/120 + 1 two-second ticks, the first is consumed when the status starts, one tick every 2 s costs
         * poison_damage HP. 300 frames -> timer 3, two damage ticks, at 2 s and 4 s. */
        dw4_status_init(&s,0);hp=100;
        assert(!dw4_status_message(&s,"SETPOISON","I<300>/I<7>",&r) && s.timer[DW4_STATUS_POISON]==3 && s.poison_damage==7 && s.poison_endurance==0);
        int ticks=0;int64_t at[8];
        for(int i=1;i<=500;i++){dw4_status_tick(&s,f*1,"SQ_WAIT",&hp,&r);if(r.poison_ticks){at[ticks++]=i;assert(r.poison_damage_taken==7);}}
        assert(ticks==2 && hp==86 && !dw4_status_is_set(&s,DW4_STATUS_POISON) && at[0]>=120 && at[0]<=122 && at[1]>=240 && at[1]<=243);
        /* A model with a status set at frame < 120 never ticks: the start consumes its single tick. */
        dw4_status_init(&s,0);hp=100;dw4_status_message(&s,"SETPOISON","I<100>/I<7>",&r);
        for(int i=0;i<400;i++)dw4_status_tick(&s,f,"SQ_WAIT",&hp,&r);
        assert(hp==100 && !dw4_status_is_set(&s,DW4_STATUS_POISON));
        /* Three arguments (a player) store the endurance. */
        dw4_status_init(&s,0);dw4_status_message(&s,"SETPOISON","I<240>/I<4>/I<9>",&r);assert(s.poison_endurance==9 && s.poison_damage==4);
        /* Poison cannot kill an enemy (HP floor 1) but KOs a player (SQ_DEAD). */
        dw4_status_init(&s,0);hp=5;dw4_status_message(&s,"SETPOISON","I<600>/I<50>",&r);
        for(n=0;n<200;n++){dw4_status_tick(&s,f,"SQ_WAIT",&hp,&r);if(r.poison_ticks)break;}
        assert(hp==1 && !r.killed && !dw4_status_is_set(&s,DW4_STATUS_POISON) && r.poison_damage_taken==4);
        dw4_status_init(&s,1);hp=5;dw4_status_message(&s,"SETPOISON","I<600>/I<50>/I<1>",&r);
        for(n=0;n<200;n++){dw4_status_tick(&s,f,"SQ_WAIT",&hp,&r);if(r.poison_ticks)break;}
        assert(hp==0 && r.killed && !strcmp(r.sequence,"SQ_DEAD") && !dw4_status_is_set(&s,DW4_STATUS_POISON));
        /* A KO'd model loses every timer. */
        dw4_status_init(&s,0);hp=10;dw4_status_message(&s,"SETSLEEP","I<600>",&r);dw4_status_message(&s,"SETBIND","I<600>",&r);hp=0;
        dw4_status_tick(&s,f,"SQ_DEAD",&hp,&r);assert(!dw4_status_is_set(&s,DW4_STATUS_SLEEP) && !dw4_status_is_set(&s,DW4_STATUS_BIND));
        /* Icons: statuses 0..7 take consecutive positions in enum order; timer[11] (frame) mirrors "any of them". */
        dw4_status_init(&s,0);hp=100;dw4_status_message(&s,"SETBIND","I<600>",&r);dw4_status_message(&s,"SETATTACKDOWN","I<600>/I<1>/I<1>/I<1>/I<1>",&r);
        dw4_status_message(&s,"SETSLEEP","I<600>",&r);dw4_status_tick(&s,f,"SQ_SLEP",&hp,&r);
        assert(s.icon_shown[DW4_STATUS_ATTACKDOWN] && s.icon_position[DW4_STATUS_ATTACKDOWN]==0 && s.icon_position[DW4_STATUS_BIND]==1 &&
               s.icon_shown[DW4_STATUS_SLEEP] && s.timer[DW4_STATUS_FRAME]==1);
        /* Sequence-change hook (FUN_00445200, after every by-name sequence set and JUMP). Sleep: anything but SQ_SLEP wakes the sleeper, damage included. */
        dw4_status_init(&s,0);hp=100;
        dw4_status_message(&s,"SETSLEEP","I<600>",&r);dw4_status_tick(&s,f,"SQ_WAIT",&hp,&r);assert(s.named[DW4_STATUS_SLEEP].armed);
        dw4_status_sequence_changed(&s,"SQ_SLEP",hp,&r);assert(dw4_status_is_set(&s,DW4_STATUS_SLEEP) && !r.sequence && !r.expired);
        dw4_status_sequence_changed(&s,"SQ_SDMG",hp,&r);
        assert(!dw4_status_is_set(&s,DW4_STATUS_SLEEP) && (r.expired>>DW4_STATUS_SLEEP&1) && !s.named[DW4_STATUS_SLEEP].armed && !s.first[DW4_STATUS_SLEEP] && !r.sequence);
        /* Stun: the damage path. SETSTUN arrives during SQ_MDMG (no hook call), the tick leaves it alone (its block runs in SQ_STUN only), the damage sequence's JUMP SQ_WAIT is
         * turned into SQ_STUN, and the status then runs and ends with SQ_WAIT. */
        dw4_status_init(&s,0);hp=100;dw4_status_message(&s,"SETSTUN","I<30>",&r);
        for(int i=0;i<50;i++)dw4_status_tick(&s,f,"SQ_MDMG",&hp,&r);
        assert(dw4_status_is_set(&s,DW4_STATUS_STUN) && s.first[DW4_STATUS_STUN]);
        dw4_status_sequence_changed(&s,"SQ_WAIT",hp,&r);assert(r.sequence && !strcmp(r.sequence,"SQ_STUN") && dw4_status_is_set(&s,DW4_STATUS_STUN));
        dw4_status_sequence_changed(&s,"SQ_STUN",hp,&r);assert(!r.sequence && dw4_status_is_set(&s,DW4_STATUS_STUN));
        for(n=0;n<100;n++){dw4_status_tick(&s,f,"SQ_STUN",&hp,&r);if(r.sequence)break;}
        assert(n==30 && !strcmp(r.sequence,"SQ_WAIT") && !dw4_status_is_set(&s,DW4_STATUS_STUN));
        dw4_status_sequence_changed(&s,"SQ_WAIT",hp,&r);assert(!r.sequence);   /* nothing left to hold */
        /* Any other sequence ends a stun (a second hit, an attack, the AI), with its timers. */
        for(int k=0;k<2;k++){
            dw4_status_init(&s,0);dw4_status_message(&s,"SETSTUN","I<30>",&r);dw4_status_tick(&s,f,"SQ_STUN",&hp,&r);assert(s.named[DW4_STATUS_STUN].armed);
            dw4_status_sequence_changed(&s,k?"SQ_ATCK1":"SQ_SDMG",hp,&r);
            assert(!dw4_status_is_set(&s,DW4_STATUS_STUN) && !s.named[DW4_STATUS_STUN].armed && (r.expired>>DW4_STATUS_STUN&1) && !r.sequence);
        }
        /* A KO clears every timer and icon; the other statuses survive any other sequence change. */
        dw4_status_init(&s,0);hp=100;
        dw4_status_message(&s,"SETBIND","I<600>",&r);dw4_status_message(&s,"SETPOISON","I<600>/I<5>",&r);dw4_status_tick(&s,f,"SQ_WAIT",&hp,&r);
        dw4_status_sequence_changed(&s,"SQ_SDMG",hp,&r);assert(dw4_status_is_set(&s,DW4_STATUS_BIND) && dw4_status_is_set(&s,DW4_STATUS_POISON));
        dw4_status_sequence_changed(&s,"SQ_DDMG",0,&r);
        for(int i=0;i<DW4_STATUS_TIMER_SLOTS;i++)assert(!s.timer[i] && !s.icon_shown[i]);
        /* List sizes: 6 and 7 entries for an enemy (the REFRACT slots and slot 6 are dropped), the record's 7 and 11 for a player. */
        {
            dw4_status e,p;dw4_status_init(&e,0);dw4_status_init(&p,1);
            assert(e.down_count==6 && e.up_count==7 && p.down_count==7 && p.up_count==11);
            dw4_status_message(&e,"SETREFRACT","I<60>/I<8>/I<9>/I<10>/I<11>",&r);dw4_status_message(&p,"SETREFRACT","I<60>/I<8>/I<9>/I<10>/I<11>",&r);
            assert(dw4_status_up(&e,7)==0 && dw4_status_up(&p,7)==8 && dw4_status_up(&p,10)==11 && r.recalc_player);
            assert(!dw4_status_apply_down_slot(&e,6,9) && dw4_status_down(&e,6)==0 && !dw4_status_apply_down_slot(&p,6,9) && dw4_status_down(&p,6)==9);
            /* lists_dirty marks a change for the record mirror; load/store move the 7 + 11 values */
            dw4_status_init(&p,1);assert(!p.lists_dirty);
            dw4_status_message(&p,"SETATTACKDOWN","I<60>/I<1>/I<2>/I<3>/I<4>",&r);assert(p.lists_dirty);
            int32_t dn[7],upl[11];dw4_status_store_lists(&p,dn,upl);assert(!p.lists_dirty && dn[0]==1 && dn[3]==4 && dn[6]==0);
            dw4_status_message(&p,"SETATTACKDOWN","I<60>/I<1>/I<2>/I<3>/I<4>",&r);assert(!p.lists_dirty && r.recalc_player);   /* the same values: the record is not rewritten, the recalculation still runs */
            for(int i=0;i<7;i++)dn[i]=10+i;
            for(int i=0;i<11;i++)upl[i]=20+i;
            dw4_status_init(&p,1);dw4_status_load_lists(&p,dn,upl);
            assert(!p.lists_dirty && dw4_status_down(&p,6)==16 && dw4_status_up(&p,10)==30 && dw4_status_down(&p,3)==13);
            dw4_status_message(&p,"SETPOWERDOWN","I<60>/I<9>/I<8>",&r);assert(p.lists_dirty);
            dw4_status_store_lists(&p,dn,upl);assert(dn[4]==9 && dn[5]==8 && dn[6]==16 && upl[3]==23);
            dw4_status_message(&p,"ALLCLEARSTATUS",NULL,&r);assert(p.lists_dirty && r.recalc_player && dw4_status_down(&p,6)==0);
        }
        /* Ready gating (InfoWork+0x44 = _isOnCtrl): while it is clear nothing arms or expires; the named-timer clock keeps running, so an elapsed status ends on the first tick after. */
        dw4_status_init(&s,0);hp=100;dw4_status_message(&s,"SETBIND","I<10>",&r);s.ready=0;
        for(int i=0;i<100;i++){dw4_status_tick(&s,f,"SQ_WAIT",&hp,&r);assert(!r.sequence);}
        assert(dw4_status_is_set(&s,DW4_STATUS_BIND) && s.first[DW4_STATUS_BIND] && !s.named[DW4_STATUS_BIND].armed);
        s.ready=1;dw4_status_tick(&s,f,"SQ_WAIT",&hp,&r);assert(s.named[DW4_STATUS_BIND].armed && !s.first[DW4_STATUS_BIND] && !r.sequence);
        s.ready=0;for(int i=0;i<100;i++){dw4_status_tick(&s,f,"SQ_WAIT",&hp,&r);assert(!r.sequence && dw4_status_is_set(&s,DW4_STATUS_BIND));}
        s.ready=1;dw4_status_tick(&s,f,"SQ_WAIT",&hp,&r);assert(r.sequence && !strcmp(r.sequence,"SQ_WAIT") && !dw4_status_is_set(&s,DW4_STATUS_BIND));
        /* The BLT / BLP contact wrappers (modelcontact.c) against a fake combat owner. BLT status times: the technique's own base number or an answer of 0 with no call at all;
         * BLP: routed with the argument shapes of the Lua bindings; the receiver's / attacker's status reaches the down-list readers. */
        {
            struct fake fk={0};dw4_status recv,att;dw4_status_init(&recv,0);dw4_status_init(&att,0);
            dw4_model_fight fight={.user=&fk,.is_hit=fk_hit,.damage=fk_dmg,.e2p_is_hit=fk_e2p_hit,.e2p_damage=fk_e2p_dmg,.e2p_stun=fk_e2p_stun,.p2e_status=fk_p2e,.e2p_status=fk_e2p};
            dw4_model_contact c={.fight=&fight,.shoot_ram_no=2,.target_row=5,.target_slot=0,.source_row=3,.receiver_status=&recv,.source_status=&att};
            dw4_script_value time_arg[1]={{DW4_SCRIPT_STRING,0,"TIME",4}},num2[2]={{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_NUMBER,0,NULL,0}},res;char err[128];
            static const struct {const char *method;int base,args;} timing[]={{"BLTgetPoisonTime",20,1},{"BLTgetSleepTime",90,0},{"BLTgetBindTime",95,0},{"BLTgetAttackDownTime",70,1},{"BLTgetPowerDownTime",85,1}};
            unsigned calls=0;
            for(unsigned m=0;m<5;m++)for(unsigned b=0;b<5;b++){
                c.bullet_kind=40000+timing[b].base;
                assert(!dw4_model_contact_call(&c,timing[m].method,time_arg,timing[m].args,&res,err,sizeof err) && res.type==DW4_SCRIPT_NUMBER);
                if(m==b){
                    calls++;assert(res.number==77 && fk.p2e==calls && !strcmp(fk.p2e_method,timing[m].method) && fk.p2e_attack==c.bullet_kind && fk.p2e_row==5 && fk.p2e_shooter==2);
                    assert(!strcmp(fk.p2e_what,timing[m].args?"TIME":"-"));
                }else assert(res.number==0 && fk.p2e==calls);   /* another technique: 0, FIGHTCALC is not called */
            }
            for(unsigned m=0;m<5;m++){   /* weapon hits, other technique classes and a base number in another class never reach the rule */
                static const int32_t other[]={10000+90,40000+91,80000+90,140000+90,40001};
                for(unsigned k=0;k<5;k++){c.bullet_kind=other[k];assert(!dw4_model_contact_call(&c,timing[m].method,time_arg,timing[m].args,&res,err,sizeof err) && res.number==0 && fk.p2e==calls);}
            }
            c.bullet_kind=40090;   /* a selector where none belongs, or none where one is needed, is a malformed call */
            assert(dw4_model_contact_call(&c,"BLTgetSleepTime",time_arg,1,&res,err,sizeof err)<0 && dw4_model_contact_call(&c,"BLTgetPoisonTime",NULL,0,&res,err,sizeof err)<0 && fk.p2e==calls);
            c.bullet_kind=40070;assert(!dw4_model_contact_call(&c,"BLTgetAttackDownTime",(dw4_script_value[]){{DW4_SCRIPT_STRING,0,"KAIHIRITSU",10}},1,&res,err,sizeof err) && !strcmp(fk.p2e_what,"KAIHIRITSU") && fk.p2e==calls+1);
            /* the receiver's status reaches the P2E hit and damage readers, the attacker's the E2P ones */
            assert(!dw4_model_contact_call(&c,"BLTisHitCheck",NULL,0,&res,err,sizeof err) && fk.hit_target==&recv);
            assert(!dw4_model_contact_call(&c,"BLTgetDamageValue",num2,1,&res,err,sizeof err) && fk.dmg_target==&recv);
            c.bullet_kind=70017;
            assert(!dw4_model_contact_call(&c,"BLPgetDamageValue",NULL,0,&res,err,sizeof err) && fk.e2p_dmg_attacker==&att);
            assert(!dw4_model_contact_call(&c,"BLPgetStunTime",num2,2,&res,err,sizeof err) && fk.stun_attacker==&att && res.number==9);
            /* BLP wrappers: (player, enemy row, attack) for sleep / bind, mode strings for the others, no gate on the attack */
            assert(!dw4_model_contact_call(&c,"BLPgetSleepTime",NULL,0,&res,err,sizeof err) && res.number==-1 && fk.e2p==1 && !strcmp(fk.e2p_method,"BLPgetSleepTime") && fk.e2p_player==0 && fk.e2p_row==3 && fk.e2p_attack==70017 && !strcmp(fk.e2p_what,"-"));
            assert(!dw4_model_contact_call(&c,"BLPgetBindTime",NULL,0,&res,err,sizeof err) && fk.e2p==2);
            assert(!dw4_model_contact_call(&c,"BLPgetPoisonTime",(dw4_script_value[]){{DW4_SCRIPT_STRING,0,"GEDOKU",6}},1,&res,err,sizeof err) && !strcmp(fk.e2p_what,"GEDOKU") && fk.e2p==3);
            assert(!dw4_model_contact_call(&c,"BLPgetAttackDownTime",time_arg,1,&res,err,sizeof err) && !strcmp(fk.e2p_what,"TIME") && fk.e2p==4);
            assert(!dw4_model_contact_call(&c,"BLPgetPowerDownTime",time_arg,1,&res,err,sizeof err) && !strcmp(fk.e2p_method,"BLPgetPowerDownTime") && fk.e2p==5);
            assert(dw4_model_contact_call(&c,"BLPgetBindTime",time_arg,1,&res,err,sizeof err)<0 && dw4_model_contact_call(&c,"BLPgetPoisonTime",NULL,0,&res,err,sizeof err)<0 && fk.e2p==5);
            /* MDLisStatus is not answered here any more: it is an SD query to the model (hubruntime.c binding / MODELCTRL CHECKSTATUS) */
            assert(dw4_model_contact_call(&c,"MDLisStatus",(dw4_script_value[]){{DW4_SCRIPT_STRING,0,"e_goburi",8},{DW4_SCRIPT_NUMBER,5,NULL,0},{DW4_SCRIPT_STRING,0,"BIND",4}},3,&res,err,sizeof err)==1);
        }
        printf("statusapply: apply, refresh, tick, expiry, poison, clear and list slots match the recovered manager; sequence hook, list sizes, ready gate, contact wrappers\n");
        return 0;
    }
    if(!strcmp(mode,"exit")) {
        /* The original way out of a field stage is gatedisc.lua (Gate Disc / escape): players SQ_EXIT, the STCHANGE fade, then
         * PLAYERPOINT I<3> + STAGECTL NEXTSTAGE stagML11. The pending request must hand off to a Terminal runtime at point 3. */
        const int revisit[]={2,355,503};
        h=enter(&mount,revisit,3);run(h,&frame,600,0,0);assert(control(h));
        assert(!dw4_hubruntime_run_chunk(h,"gatedisc.lua"));
        for(unsigned i=0;i<900 && !dw4_hubruntime_travel(h)->pending;i++)run(h,&frame,1,0,0);
        const dw4_stagetravel *t=dw4_hubruntime_travel(h);
        assert(t->pending && !strcmp(t->destination,"stagML11") && t->generate_pos==3);
        dw4_stageinput in=*dw4_hubruntime_input_state(h);char error[512];
        dw4_hubruntime_source prior={dw4_hubruntime_records(h),dw4_hubruntime_state(h),&in,dw4_hubruntime_time(h)};
        dw4_hubruntime *terminal=dw4_hubruntime_prepare(&mount,&prior,t->destination,t->generate_pos,1,error,sizeof error);
        if(!terminal){fprintf(stderr,"return to %s: %s\n",t->destination,error);exit(1);}
        unsigned f2=frame;run(terminal,&f2,120,0,0);
        dw4_lobby_world_state info;assert(!dw4_lobby_world_info(dw4_hubruntime_world(terminal),&info) && !strcmp(info.stage,"stagML11"));
        dw4_hubruntime_close(terminal);dw4_hubruntime_close(h);
        printf("field stage stag0101 exit: gatedisc.lua requests stagML11 point 3 and the Terminal prepares from the field record\n");
        return 0;
    }
    if(!strcmp(mode,"damagelive")) {
        /* The live measurements recorded in docs/systems/combat-damage.md (retail savestate, Goblin row 5, strength 2000): normal hit ~96 / ~146 / 247-260
         * and critical hit 117-124 / 270-276 / 559-568 for skill S = 0 / 1500 / 5000. Each recorded observation must lie inside the range the port
         * produces (the live samples were few, so the check is containment, not equality). */
        const int revisit[]={2,355,503};
        h=enter(&mount,revisit,3);
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
        const dw4_database *enemy=dw4_databases_get(dw4_hubruntime_databases(h),"enemy");assert(p0 && enemy);
        int32_t mamori,skill_no;assert(!dw4_database_number(enemy,5,"MAMORI",&mamori) && !dw4_property_number(p0,"WEAPONSKILLNO",&skill_no));
        fprintf(stderr,"row 5 MAMORI %d\n",mamori);
        assert(!dw4_property_set_number(p0,"TSUYOSA",2000) && !dw4_property_set_number(p0,"ATTACKZOKUSEI",-1));
        size_t ns;const int32_t *old=dw4_property_array(p0,"SKILL",&ns);assert(old && ns>=9);int32_t skill[16];memcpy(skill,old,ns*sizeof *skill);
        static const struct {int32_t s;int lo,hi,clo,chi;} live[]={{0,96,96,117,124},{1500,146,146,270,276},{5000,247,260,559,568}};   /* the recorded observations */
        for(unsigned c=0;c<3;c++){
            skill[skill_no]=live[c].s;assert(!dw4_property_set_array(p0,"SKILL",skill,ns));
            dw4_random rng=dw4_hubruntime_state(h)->random;dw4_fight_ctx ctx={p0,dw4_database_typed(enemy),&rng};
            int32_t nlo=1<<30,nhi=0,clo=1<<30,chi=0;
            for(int i=0;i<3000;i++){dw4_fight_damage d;assert(!dw4_fight_p2e_damage(&ctx,5,0,i&1,(dw4_fight_down){0,3},&d));   /* the live note puts the defence term near 125: row MAMORI 128 minus 3 (its source in that state is unidentified) */
                if(i&1){if(d.damage<clo)clo=d.damage;if(d.damage>chi)chi=d.damage;}else{if(d.damage<nlo)nlo=d.damage;if(d.damage>nhi)nhi=d.damage;}}
            fprintf(stderr,"S=%d: normal %d..%d (live %d..%d), critical %d..%d (live %d..%d)\n",live[c].s,nlo,nhi,live[c].lo,live[c].hi,clo,chi,live[c].clo,live[c].chi);
            assert(nlo<=live[c].lo && nhi>=live[c].hi && clo<=live[c].clo && chi>=live[c].chi);   /* every observed value lies inside the range the port produces */
        }
        dw4_hubruntime_close(h);
        printf("field stage stag0101 damagelive: P2E damage inside the recorded live retail bands for S = 0, 1500, 5000\n");
        return 0;
    }
    if(!strcmp(mode,"hurt")) {
        /* An enemy with its authored AI next to the starter: its attack volumes reach the player's body, the original hit_p_<species>.lua runs through the
         * E2P rules (hit check, damage, rank, stun), HP drops and the HUD sink receives the meter values. */
        const int revisit[]={2,355,503};
        h=enter(&mount,revisit,3);run(h,&frame,600,0,0);assert(control(h));
        dw4_modelctrl *player=dw4_lobby_player_model(dw4_hubruntime_world(h));
        dw4_modelctrl_actor pa;dw4_modelctrl_actor_state(player,&pa);float pm[16];dw4_modelctrl_actor_matrix(&pa,pm);
        char where[96],error[512];dw4_script_value r;
        snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,%g,0>/SQ_ENTR",pa.position[0]+pm[8]*7,pa.position[1],pa.position[2]+pm[10]*7,pa.rotation[1]+180);
        dw4_script_value gen[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"e_goburi",8},{DW4_SCRIPT_NUMBER,5,NULL,0},{DW4_SCRIPT_STRING,0,"GENERATE",8},{DW4_SCRIPT_STRING,0,where,strlen(where)}};
        assert(!dw4_hubruntime_sd(h,gen,5,&r,error,sizeof error));
        dw4_script_model *goblin=dw4_hubruntime_enemy_state(h,"e_goburi",5);assert(goblin);goblin->rec_no=0;goblin->hp=goblin->max_hp=50;
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
        int32_t hp0,mhp;assert(!dw4_property_number(p0,"HP",&hp0) && !dw4_property_number(p0,"MHP",&mhp));
        unsigned i=0;for(;i<1800;i++){
            dw4_hubruntime_input(h,0,0,0,0,0);
            if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
            if(dw4_hubruntime_combat(h)->player_hits)break;
        }
        int32_t hp1;assert(!dw4_property_number(p0,"HP",&hp1));
        const dw4_combat_stats *st=dw4_hubruntime_combat(h);const dw4_hubruntime_hud *hud=dw4_hubruntime_hud_state(h);
        fprintf(stderr,"after %u ticks: player hits %u, HP %d -> %d of %d (last damage %d), HUD updates %u percent %g value %d\n",i,st->player_hits,hp0,hp1,mhp,st->player_last_damage,hud->updates,hud->hp_percent[0],hud->hp_value[0]);
        assert(st->player_hits>=1 && hp1<hp0 && hp0-hp1==st->player_last_damage && hud->updates>=2 && hud->hp_value[0]==hp1);
        /* Keep fighting: the player never retaliates, so the Goblin wears the HP down to the KO (SQ_DDMG on rank 3). */
        char home[96];snprintf(home,sizeof home,"V<%g,%g,%g>/V<0,%g,0>",pa.position[0],pa.position[1],pa.position[2],pa.rotation[1]);
        for(i=0;i<20000 && hp1>0;i++){
            if(!strcmp(dw4_modelctrl_sequence(player),"SQ_FALL")){   /* fixture: the knock-back carries the player off the start platform; put it back */
                dw4_script_value mv[5]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,home,strlen(home)}};
                assert(!dw4_hubruntime_sd(h,mv,5,&r,error,sizeof error));
                dw4_script_value wt[4]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"SQ_WAIT",7}};
                assert(!dw4_hubruntime_sd(h,wt,4,&r,error,sizeof error));
            }
            dw4_hubruntime_input(h,0,0,0,0,0);
            if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
            assert(!dw4_property_number(p0,"HP",&hp1));
        }
        fprintf(stderr,"KO after %u more ticks: HP %d, hits %u, damage total %u, player sequence %s\n",i,hp1,st->player_hits,st->player_damage_total,dw4_modelctrl_sequence(player));
        assert(hp1==0 && st->player_damage_total>=(unsigned)hp0 && st->player_damage_total<hp0+200u);   /* the last hit may overkill */
        for(i=0;i<240;i++){dw4_hubruntime_input(h,0,0,0,0,0);if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}}
        fprintf(stderr,"240 ticks later: player sequence %s, HUD value %d\n",dw4_modelctrl_sequence(player),hud->hp_value[0]);
        /* The end chunk shows its GAMEOVER message; Cross confirms it and the Terminal is requested at point 0. */
        for(i=0;i<3000 && !dw4_hubruntime_travel(h)->pending;i++){
            dw4_hubruntime_input(h,0,0,0,i%40<4?0x4000:0,i%40==0?0x4000:0);
            if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
        }
        assert(dw4_hubruntime_travel(h)->pending && !strcmp(dw4_hubruntime_travel(h)->destination,"stagML11") && dw4_hubruntime_travel(h)->generate_pos==0);
        fprintf(stderr,"game over: Terminal requested after %u more ticks\n",i);
        sound_stats(h,"hurt");
        dw4_hubruntime_close(h);
        printf("field stage stag0101 hurt: enemy attack volume -> hit_p script -> E2P rules -> player HP -> KO -> game over -> Terminal request\n");
        return 0;
    }
    if(!strcmp(mode,"guard")) {
        /* The Square guard (beNDMWMdlPlayer::vfunc_38: outside the main lobby, not in SQ_JUMP, the edge word 0x8000 requests SQ_GUARD; findings #3040, #3031). Three phases
         * on the hurt fixture (a Goblin with its authored AI next to the starter, the original hit_p script through the E2P rules):
         *  1. no enemy: one Square press; count the ticks the player stays in SQ_GUARD and SQ_GUARD2 (the model's own GURD motions) until SQ_WAIT; Square in SQ_JUMP is refused;
         *  2. a player that guards (Square pressed whenever it is out of SQ_GUARD) is hit by the Goblin's volumes: every hit that finds the player in SQ_GUARD runs the chunk's
         *     guard branch -- no damage, SQ_GUARDR;
         *  3. the same player, not guarding, takes damage from the same Goblin. */
        const int revisit[]={2,355,503};
        h=enter(&mount,revisit,3);run(h,&frame,600,0,0);assert(control(h));
        dw4_modelctrl *player=dw4_lobby_player_model(dw4_hubruntime_world(h));
        dw4_modelctrl_actor pa;dw4_modelctrl_actor_state(player,&pa);float pm[16];dw4_modelctrl_actor_matrix(&pa,pm);
        char error[512];dw4_script_value r;
        assert(dw4_modelctrl_has_sequence(player,"SQ_GUARD") && dw4_modelctrl_has_sequence(player,"SQ_GUARD2"));
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
        int32_t hp0,mhp;assert(!dw4_property_number(p0,"HP",&hp0) && !dw4_property_number(p0,"MHP",&mhp));
        unsigned guard1=0,guard2=0,i;
        assert(strcmp(player_seq(h),"SQ_GUARD"));
        for(i=0;i<600;i++){   /* phase 1 */
            dw4_hubruntime_input(h,0,0,0,i==0?0x8000:0,i==0?0x8000:0);
            const char *seq=player_seq(h);if(!strcmp(seq,"SQ_GUARD"))guard1++;else if(!strcmp(seq,"SQ_GUARD2"))guard2++;else if(i>0)break;
            if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
        }
        fprintf(stderr,"guard press: SQ_GUARD %u ticks, SQ_GUARD2 %u ticks, then %s\n",guard1,guard2,player_seq(h));
        assert(guard1>0 && guard2>0 && !strcmp(player_seq(h),"SQ_WAIT"));
        dw4_hubruntime_input(h,0,0,0,0x2000,0x2000);assert(!dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60));   /* a jump: Square must not interrupt it */
        for(i=0;i<10 && strcmp(player_seq(h),"SQ_JUMP");i++){dw4_hubruntime_input(h,0,0,0,0,0);assert(!dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60));}
        assert(!strcmp(player_seq(h),"SQ_JUMP"));
        dw4_hubruntime_input(h,0,0,0,0x8000,0x8000);assert(!strcmp(player_seq(h),"SQ_JUMP"));assert(!dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60));
        for(i=0;i<600 && strcmp(player_seq(h),"SQ_WAIT");i++){dw4_hubruntime_input(h,0,0,0,0,0);assert(!dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60));}
        assert(!strcmp(player_seq(h),"SQ_WAIT"));
        dw4_modelctrl_actor_state(player,&pa);dw4_modelctrl_actor_matrix(&pa,pm);
        char home[96],where[96];snprintf(home,sizeof home,"V<%g,%g,%g>/V<0,%g,0>",pa.position[0],pa.position[1],pa.position[2],pa.rotation[1]);
        snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,%g,0>/SQ_ENTR",pa.position[0]+pm[8]*7,pa.position[1],pa.position[2]+pm[10]*7,pa.rotation[1]+180);
        dw4_script_value gen[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"e_goburi",8},{DW4_SCRIPT_NUMBER,5,NULL,0},{DW4_SCRIPT_STRING,0,"GENERATE",8},{DW4_SCRIPT_STRING,0,where,strlen(where)}};
        assert(!dw4_hubruntime_sd(h,gen,5,&r,error,sizeof error));
        dw4_script_model *goblin=dw4_hubruntime_enemy_state(h,"e_goburi",5);assert(goblin);goblin->rec_no=0;goblin->hp=goblin->max_hp=50;
        const dw4_combat_stats *st=dw4_hubruntime_combat(h);
        for(int guarding=1;guarding>=0;guarding--){   /* phase 2 (guard), then phase 3 (no guard) */
            unsigned guarded_hits=0,open_hits=0,damaging=0,last_hits=st->player_hits;int32_t hp=hp0,hp_prev=hp0;
            assert(!dw4_property_set_number(p0,"HP",hp0));
            for(i=0;i<3000 && (guarding?guarded_hits<3:open_hits<2);i++){
                if(!strcmp(player_seq(h),"SQ_FALL")){   /* fixture: the knock-back carries the player off the start platform; put it back */
                    dw4_script_value mv[5]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,home,strlen(home)}};
                    assert(!dw4_hubruntime_sd(h,mv,5,&r,error,sizeof error));
                    dw4_script_value wt[4]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"SQ_WAIT",7}};
                    assert(!dw4_hubruntime_sd(h,wt,4,&r,error,sizeof error));
                }
                const int press=guarding && strcmp(player_seq(h),"SQ_GUARD") && (i&1);   /* an edge: pressed on one tick, released on the next */
                dw4_hubruntime_input(h,0,0,0,press?0x8000:0,press?0x8000:0);
                const int in_guard=!strcmp(player_seq(h),"SQ_GUARD");   /* the sequence the combat tick of this frame finds */
                if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
                assert(!dw4_property_number(p0,"HP",&hp));
                if(hp<hp_prev)assert(!in_guard);   /* HP only falls on a tick where the player was not in SQ_GUARD */
                if(st->player_hits!=last_hits){
                    if(in_guard){guarded_hits++;assert(hp==hp_prev && !strcmp(player_seq(h),"SQ_GUARDR"));}   /* the chunk's guard branch: nothing taken, SQ_GUARDR */
                    else{open_hits++;if(hp<hp_prev)damaging++;}
                    last_hits=st->player_hits;
                }
                hp_prev=hp;
            }
            fprintf(stderr,"%s: %u ticks, hits on SQ_GUARD %u, other hits %u (damaging %u), HP %d -> %d\n",guarding?"guarding":"not guarding",i,guarded_hits,open_hits,damaging,hp0,hp);
            if(guarding)assert(guarded_hits>=3);
            else assert(open_hits>=2 && damaging>=1 && hp<hp0);
        }
        dw4_hubruntime_close(h);
        printf("field stage stag0101 guard: Square requests SQ_GUARD (%u + %u ticks), a hit on a guarding player does no damage and ends in SQ_GUARDR, the same player unguarded takes damage\n",guard1,guard2);
        return 0;
    }
    if(!strcmp(mode,"statusflow")) {
        /* Status wiring end to end on the Goblin Pass goblin (docs/combat.md "Status wiring"): a synthetic technique bullet (kind 4xxxx, the number a technique volume would carry;
         * no technique can be fired yet) goes through dw4_controllers_enemy_bullet into the original hit chunk, whose BLT*Time calls reach the P2E status rules and whose
         * MDLsetSD SETxxx messages reach the goblin's status work; the status manager (poison, sleep, stun, bind), the sequence-change hook and MDLisStatus run on the
         * real model. Frame counts are the port's own (not retail-measured). */
        const int revisit[]={2,355,503};
        h=enter(&mount,revisit,3);run(h,&frame,600,0,0);assert(control(h));
        dw4_modelctrl *player=dw4_lobby_player_model(dw4_hubruntime_world(h));assert(player && dw4_hubruntime_combat_owner(h));
        dw4_modelctrl_actor pa;dw4_modelctrl_actor_state(player,&pa);float pm[16];dw4_modelctrl_actor_matrix(&pa,pm);
        char where[96],error[512];dw4_script_value r;
        snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,%g,0>/SQ_WAIT",pa.position[0]+pm[8]*9,pa.position[1],pa.position[2]+pm[10]*9,pa.rotation[1]+180);
        dw4_script_value gen[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"e_goburi",8},{DW4_SCRIPT_NUMBER,5,NULL,0},{DW4_SCRIPT_STRING,0,"GENERATE",8},{DW4_SCRIPT_STRING,0,where,strlen(where)}};
        assert(!dw4_hubruntime_sd(h,gen,5,&r,error,sizeof error));
        dw4_script_model *goblin=dw4_hubruntime_enemy_state(h,"e_goburi",5);assert(goblin);
        const int32_t BIG=100000;
        goblin->rec_no=0;goblin->hp=goblin->max_hp=BIG;
        assert(!dw4_hubruntime_enemy_ai_off(h,"e_goburi",5));   /* fixture: the goblin keeps to SQ_WAIT unless a status or a hit moves it */
        run(h,&frame,5,0,0);
        assert(goblin_status(h) && !strcmp(goblin_seq(h),"SQ_WAIT"));
        /* The player's side: the five status techniques at tier 0 (pcTech rows 20 venom, 70 freeze, 85 power down, 90 sleep, 95 bind), full skill, KASHIKOSA 100. */
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
        const dw4_databases *dbs=dw4_hubruntime_databases(h);const dw4_database *enemy=dw4_databases_get(dbs,"enemy"),*tech=dw4_databases_get(dbs,"pcTech");
        size_t ns=0;const int32_t *old=dw4_property_array(p0,"SKILL",&ns);assert(old && ns>=9 && ns<=16);
        int32_t sk[16];for(size_t i=0;i<ns;i++)sk[i]=9999;
        const dw4_item_record waza[5]={{9,20,0,20,0},{9,70,0,70,0},{9,85,0,85,0},{9,90,0,90,0},{9,95,0,95,0}};
        assert(!dw4_property_set_array(p0,"SKILL",sk,ns) && !dw4_property_set_items(p0,"WAZALIST",waza,5) && !dw4_property_set_number(p0,"KASHIKOSA",100));
        int32_t sei=0,res_stun=0;assert(!dw4_database_number(enemy,0,"SEISHIN",&sei) && !dw4_database_number(enemy,0,"RES_STUN",&res_stun));
        fprintf(stderr,"goblin row 0: SEISHIN %d RES_STUN %d\n",sei,res_stun);
        int32_t t_sleep,t_bind;assert(!dw4_database_number(tech,90,"TIME",&t_sleep) && !dw4_database_number(tech,95,"TIME",&t_bind));
        const dw4_combat_stats *st=dw4_hubruntime_combat(h);(void)st;

        /* SLEEP: the roll may fail (-1 stops the chain), a landed one sets SETSLEEP I<TIME+KASHIKOSA/2>; the manager puts the goblin in SQ_SLEP on its next frame. */
        unsigned tries=0;
        for(;tries<80 && !dw4_status_is_set(goblin_status(h),DW4_STATUS_SLEEP);tries++){assert(fire(h,frame,40090)==1);run(h,&frame,3,0,0);}
        const dw4_status *gs=goblin_status(h);
        fprintf(stderr,"sleep landed after %u casts: timer %d (pcTech TIME %d + 50)\n",tries,gs->timer[DW4_STATUS_SLEEP],t_sleep);
        assert(dw4_status_is_set(gs,DW4_STATUS_SLEEP) && goblin_check(h,"SLEEP")==1 && goblin_check(h,"BIND")==0 && goblin_check(h,"STUN")==0);
        /* a technique of another base number applies nothing (the retail wrappers answer 0 without calling FIGHTCALC) */
        assert(!dw4_status_is_set(gs,DW4_STATUS_BIND) && !dw4_status_is_set(gs,DW4_STATUS_POISON));
        assert(!strcmp(goblin_seq(h),"SQ_SLEP"));
        int32_t left=gs->timer[DW4_STATUS_SLEEP];
        unsigned slept=0;
        while(slept<(unsigned)left+60 && dw4_status_is_set(gs,DW4_STATUS_SLEEP)){run(h,&frame,1,0,0);slept++;}
        fprintf(stderr,"sleeper woke after %u more frames (timer was %d), sequence %s\n",slept,left,goblin_seq(h));
        assert(!dw4_status_is_set(gs,DW4_STATUS_SLEEP) && goblin_check(h,"SLEEP")==0 && slept+4>=(unsigned)left-6 && slept<=(unsigned)left+6);
        assert(!strcmp(goblin_seq(h),"SQ_WAIT"));

        /* A weapon hit (kind 10000) on a sleeper: the damage reaction MDLsetSeq(SQ_xDMG) runs the sequence-change hook, which ends the sleep. */
        for(tries=0;tries<80 && !dw4_status_is_set(goblin_status(h),DW4_STATUS_SLEEP);tries++){assert(fire(h,frame,40090)==1);run(h,&frame,3,0,0);}
        assert(dw4_status_is_set(goblin_status(h),DW4_STATUS_SLEEP) && !strcmp(goblin_seq(h),"SQ_SLEP"));
        run(h,&frame,20,0,0);
        assert(dw4_status_is_set(goblin_status(h),DW4_STATUS_SLEEP));
        assert(fire(h,frame,10000)==1);
        fprintf(stderr,"after a weapon hit on the sleeper: sequence %s, sleep %d\n",goblin_seq(h),goblin_check(h,"SLEEP"));
        assert(goblin_check(h,"SLEEP")==0 && strcmp(goblin_seq(h),"SQ_SLEP"));
        run(h,&frame,240,0,0);goblin->hp=goblin->max_hp=BIG;
        assert(!strcmp(goblin_seq(h),"SQ_WAIT"));

        /* STUN: a weapon hit of rank 1 or 2 with a raised MAHIRITSU. The goblin's HP is set so the (replayed) damage is 25..100 % of it; BLTgetStunTime then lands (chance >= 100). The hit
         * script picks SQ_MDMG/SQ_LDMG and sends SETSTUN WITHOUT setting SQ_STUN: the damage sequence's JUMP SQ_WAIT runs the sequence-change hook, which holds the goblin in SQ_STUN. */
        int32_t lo=1<<30,hi=0;
        {
            dw4_random rng=dw4_hubruntime_state(h)->random;dw4_fight_ctx ctx={p0,dw4_database_typed(enemy),&rng,dw4_database_typed(tech)};
            for(int i=0;i<3000;i++){dw4_fight_damage d;assert(!dw4_fight_p2e_damage(&ctx,0,10000,i&1,(dw4_fight_down){0,0},&d));if(d.damage<lo)lo=d.damage;if(d.damage>hi)hi=d.damage;}
        }
        const int32_t H=hi+1;fprintf(stderr,"weapon damage %d..%d, goblin HP set to %d\n",lo,hi,H);
        assert(lo>0 && H<4*lo);   /* every hit is more than a quarter of the HP (rank >= 1) and none kills */
        assert(!dw4_property_set_number(p0,"MAHIRITSU",res_stun+110));
        unsigned landed=0;
        for(tries=0;tries<30 && !landed;tries++){
            goblin->hp=goblin->max_hp=H;
            fire(h,frame,10000);
            if(goblin->hp<H)landed=1;else run(h,&frame,90,0,0);   /* a miss sends it to SQ_GUARD */
        }
        assert(landed);
        const char *first=goblin_seq(h);
        int32_t stun_frames=gs->timer[DW4_STATUS_STUN];
        fprintf(stderr,"weapon hit: HP %d -> %d, sequence %s, SETSTUN %d frames\n",H,goblin->hp,first,stun_frames);
        assert((!strcmp(first,"SQ_MDMG") || !strcmp(first,"SQ_LDMG")) && stun_frames>0 && goblin_check(h,"STUN")==1);
        unsigned enter=0,leave=0,k=0;
        for(;k<1200 && !enter;k++){run(h,&frame,1,0,0);if(!strcmp(goblin_seq(h),"SQ_STUN"))enter=k+1;}
        assert(enter>0 && enter<150);
        for(;k<2400 && !leave;k++){
            run(h,&frame,1,0,0);
            if(strcmp(goblin_seq(h),"SQ_STUN")){leave=k+1;break;}
            assert(goblin_check(h,"STUN")==1);
        }
        fprintf(stderr,"SQ_STUN from tick %u to %u (%u frames for a %d-frame stun)\n",enter,leave,leave-enter,stun_frames);
        assert(leave && leave-enter+4>=(unsigned)stun_frames && leave-enter<=(unsigned)stun_frames+4 && goblin_check(h,"STUN")==0 && !strcmp(goblin_seq(h),"SQ_WAIT"));
        run(h,&frame,60,0,0);
        assert(!strcmp(goblin_seq(h),"SQ_WAIT"));
        assert(!dw4_property_set_number(p0,"MAHIRITSU",0));

        /* BIND: MDLisStatus(name, ram, "BIND") answers 1 through the CHECKSTATUS query, and a hit below rank 3 then forces SQ_SDMG (the script's flinch rule) instead of SQ_MDMG. */
        goblin->hp=goblin->max_hp=H;
        for(tries=0;tries<80 && !dw4_status_is_set(goblin_status(h),DW4_STATUS_BIND);tries++){assert(fire(h,frame,40095)==1);run(h,&frame,3,0,0);}
        assert(dw4_status_is_set(gs,DW4_STATUS_BIND) && goblin_check(h,"BIND")==1 && gs->timer[DW4_STATUS_BIND]==t_bind+50);
        run(h,&frame,30,0,0);
        landed=0;
        for(tries=0;tries<30 && !landed;tries++){
            goblin->hp=goblin->max_hp=H;
            fire(h,frame,10000);
            if(goblin->hp<H)landed=1;else run(h,&frame,90,0,0);
        }
        fprintf(stderr,"bound goblin hit: sequence %s (unbound it was %s)\n",goblin_seq(h),first);
        assert(landed && !strcmp(goblin_seq(h),"SQ_SDMG") && goblin_check(h,"BIND")==1);
        unsigned bound=30;
        while(bound<(unsigned)t_bind+200 && goblin_check(h,"BIND")==1){run(h,&frame,1,0,0);bound++;}
        fprintf(stderr,"bind ended after %u frames (timer %d)\n",bound,t_bind+50);
        assert(goblin_check(h,"BIND")==0 && bound+10>=(unsigned)t_bind+50 && bound<=(unsigned)t_bind+50+10);
        run(h,&frame,400,0,0);   /* a stun from the same hit may still be running */
        assert(goblin_check(h,"STUN")==0 && !strcmp(goblin_seq(h),"SQ_WAIT"));

        /* POISON: venom (a damaging technique) lands SETPOISON I<TIME+KASHIKOSA/2>/I<damage per tick>; one tick per 120 frames, the status ends with HP floored at 1. */
        int32_t t_venom,hp_venom;assert(!dw4_database_number(tech,20,"TIME",&t_venom) && !dw4_database_number(tech,20,"HP",&hp_venom));
        for(tries=0;tries<80 && !dw4_status_is_set(goblin_status(h),DW4_STATUS_POISON);tries++){goblin->hp=goblin->max_hp=BIG;assert(fire(h,frame,40020)==1);run(h,&frame,100,0,0);}
        fprintf(stderr,"venom landed after %u casts: poison timer %d damage %d (pcTech TIME %d HP %d)\n",tries,gs->timer[DW4_STATUS_POISON],gs->poison_damage,t_venom,hp_venom);
        assert(dw4_status_is_set(gs,DW4_STATUS_POISON) && goblin_check(h,"POISON")==1 && gs->poison_damage==-(hp_venom/5));
        {
            /* poison cannot kill an enemy: with 20 HP the ticks leave 4, then the floor of 1 ends the status */
            goblin->hp=20;int32_t seen[8];unsigned ticks=0;
            for(unsigned i=0;i<1500 && dw4_status_is_set(gs,DW4_STATUS_POISON) && ticks<8;i++){int32_t before=goblin->hp;run(h,&frame,1,0,0);if(goblin->hp!=before)seen[ticks++]=goblin->hp;}
            fprintf(stderr,"poison ticks left HP %d then %d (status %s)\n",ticks>0?seen[0]:-1,ticks>1?seen[1]:-1,dw4_status_is_set(gs,DW4_STATUS_POISON)?"set":"ended");
            assert(ticks==2 && seen[0]==20-gs->poison_damage && seen[1]==1 && !dw4_status_is_set(gs,DW4_STATUS_POISON) && goblin_check(h,"POISON")==0);
            assert(dw4_controllers_enemies_alive(dw4_hubruntime_models(h),"e_goburi")==1 && goblin->hp==1);
            goblin->hp=goblin->max_hp=BIG;run(h,&frame,100,0,0);
        }

        /* ATTACK DOWN (freeze, base 70) and POWER DOWN (base 85): SETATTACKDOWN writes _downDataList[0..3] = SUBAYASA, CHIMEIRITSU, MAHIRITSU, KAIHIRITSU and SETPOWERDOWN [4..5] =
         * TSUYOSA, MAMORI from the BLT selector replies (no draw). The P2E hit and damage rules read [3] and [5] of the RECEIVER. */
        for(tries=0;tries<80 && !dw4_status_is_set(goblin_status(h),DW4_STATUS_ATTACKDOWN);tries++){assert(fire(h,frame,40070)==1);run(h,&frame,3,0,0);}
        for(tries=0;tries<80 && !dw4_status_is_set(goblin_status(h),DW4_STATUS_POWERDOWN);tries++){assert(fire(h,frame,40085)==1);run(h,&frame,3,0,0);}
        assert(dw4_status_is_set(gs,DW4_STATUS_ATTACKDOWN) && dw4_status_is_set(gs,DW4_STATUS_POWERDOWN));
        fprintf(stderr,"goblin down list: %d %d %d %d | %d %d\n",dw4_status_down(gs,0),dw4_status_down(gs,1),dw4_status_down(gs,2),dw4_status_down(gs,3),dw4_status_down(gs,4),dw4_status_down(gs,5));
        {
            int32_t ts,tc,tm,tk,ta,td,es,ea,ed;
            assert(!dw4_database_number(tech,70,"SUBAYASA",&ts) && !dw4_database_number(tech,70,"CHIMEIRITSU",&tc) && !dw4_database_number(tech,70,"MHIRITSU",&tm) && !dw4_database_number(tech,70,"KAIHIRITSU",&tk) &&
                   !dw4_database_number(tech,85,"TSUYOSA",&ta) && !dw4_database_number(tech,85,"MAMORI",&td) &&
                   !dw4_database_number(enemy,0,"SUBAYASA",&es) && !dw4_database_number(enemy,0,"TSUYOSA",&ea) && !dw4_database_number(enemy,0,"MAMORI",&ed));
            int32_t vs=ts-9999/20,vl=-es*80/100,va=ta-9999/20,vla=-ea*80/100,vd=td-9999/20,vld=-ed*80/100;   /* the strength replies: -max(pcTech - SKILL/20, -(enemy * 80 / 100)) */
            assert(dw4_status_down(gs,DW4_DOWN_SUBAYASA)==-(vs<vl?vl:vs) && dw4_status_down(gs,DW4_DOWN_CRITICAL)==-tc && dw4_status_down(gs,DW4_DOWN_PARALYSIS)==-tm && dw4_status_down(gs,DW4_DOWN_EVASION)==-tk);
            assert(dw4_status_down(gs,DW4_DOWN_ATTACK)==-(va<vla?vla:va) && dw4_status_down(gs,DW4_DOWN_DEFENSE)==-(vd<vld?vld:vd));
        }
        {
            dw4_fight_down with={dw4_status_down(gs,DW4_DOWN_EVASION),dw4_status_down(gs,DW4_DOWN_DEFENSE)};
            assert(with.defense_down>0 && with.evasion_down>0);
            int32_t plain=0,dealt=weapon_hit_checked(h,&frame,p0,enemy,tech,goblin,with,&plain);
            fprintf(stderr,"weapon hit on the debuffed goblin: %d damage (the same draws with no down values: %d)\n",dealt,plain);
            assert(dealt>plain);   /* the defense reduction (down[5]) lifts the damage */
        }
        /* both statuses end on their own: the lists they wrote return to 0 and the rules to the baseline */
        for(unsigned i=0;i<4000 && (dw4_status_is_set(gs,DW4_STATUS_ATTACKDOWN) || dw4_status_is_set(gs,DW4_STATUS_POWERDOWN));i++)run(h,&frame,1,0,0);
        assert(!dw4_status_is_set(gs,DW4_STATUS_ATTACKDOWN) && !dw4_status_is_set(gs,DW4_STATUS_POWERDOWN));
        for(int i=0;i<6;i++)assert(dw4_status_down(gs,i)==0);
        {
            int32_t plain=0,dealt=weapon_hit_checked(h,&frame,p0,enemy,tech,goblin,(dw4_fight_down){0,0},&plain);
            assert(dealt==plain);
        }

        /* An erased enemy keeps none of its ailments: REMOVE resets the status work, a status message to the inactive slot is ignored (like the other direct messages) and the
         * respawn (GENERATE) starts clean. */
        {
            dw4_script_value mset[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"e_goburi",8},{DW4_SCRIPT_NUMBER,5,NULL,0},{DW4_SCRIPT_STRING,0,"SETBIND",7},{DW4_SCRIPT_STRING,0,"I<600>",6}};
            assert(!dw4_hubruntime_sd(h,mset,5,&r,error,sizeof error) && goblin_check(h,"BIND")==1);
            mset[3]=(dw4_script_value){DW4_SCRIPT_STRING,0,"SETPOISON",9};mset[4]=(dw4_script_value){DW4_SCRIPT_STRING,0,"I<600>/I<5>",11};
            assert(!dw4_hubruntime_sd(h,mset,5,&r,error,sizeof error) && goblin_check(h,"POISON")==1);
            dw4_script_value mrm[4]={mset[0],mset[1],mset[2],{DW4_SCRIPT_STRING,0,"REMOVE",6}};
            assert(!dw4_hubruntime_sd(h,mrm,4,&r,error,sizeof error) && dw4_controllers_live(dw4_hubruntime_models(h),"e_goburi",5)==0);
            assert(goblin_check(h,"BIND")==0 && goblin_check(h,"POISON")==0);
            mset[3]=(dw4_script_value){DW4_SCRIPT_STRING,0,"SETSLEEP",8};mset[4]=(dw4_script_value){DW4_SCRIPT_STRING,0,"I<600>",6};
            assert(!dw4_hubruntime_sd(h,mset,5,&r,error,sizeof error) && goblin_check(h,"SLEEP")==0);
            dw4_script_value mgen[4]={mset[0],mset[1],mset[2],{DW4_SCRIPT_STRING,0,"GENERATE",8}};
            assert(!dw4_hubruntime_sd(h,mgen,4,&r,error,sizeof error) && dw4_controllers_live(dw4_hubruntime_models(h),"e_goburi",5)==1);
            for(int i=0;i<DW4_STATUS_TIMER_SLOTS;i++)assert(!gs->timer[i]);
            run(h,&frame,5,0,0);
            assert(!strcmp(goblin_seq(h),"SQ_WAIT"));
        }

        dw4_hubruntime_close(h);
        printf("field stage stag0101 statusflow: status technique bullet -> hit chunk -> P2E status rules -> goblin status work\n");
        return 0;
    }
    if(!strcmp(mode,"statusflow_e2p")) {
        /* Enemy to player: synthetic enemy bullets 70000+row (eneatk rows whose KOUKA is doku / sleep / ashidome / freeze / powerdown) through the REAL hit_p chunk of the starter
         * (dw4_combat_hit_player skips only the geometry). Every BLPget*Time call answers through the E2P status rules instead of failing, the SETxxx messages reach the player model's
         * status, whose lists are the record's DOWNDATA / UPDATA (the stat recalculation follows), and the sleep and stun sequences take the stick away. Port frame counts. */
        const int revisit[]={2,355,503};
        h=enter(&mount,revisit,3);run(h,&frame,600,0,0);assert(control(h));
        dw4_modelctrl *player=dw4_lobby_player_model(dw4_hubruntime_world(h));assert(player && dw4_hubruntime_combat_owner(h));
        dw4_combat *combat=dw4_hubruntime_combat_owner(h);
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
        const dw4_databases *dbs=dw4_hubruntime_databases(h);const dw4_database *eneatk=dw4_databases_get(dbs,"eneatk");
        static const char *const kinds[]={"doku","sleep","ashidome","freeze","powerdown"};
        int row[5]={-1,-1,-1,-1,-1};
        for(int a=0;a<2000;a++){const char *k=dw4_database_string(eneatk,a,"KOUKA");if(!k)continue;for(int i=0;i<5;i++)if(!strcmp(k,kinds[i]) && row[i]<0)row[i]=a;}
        for(int i=0;i<5;i++)assert(row[i]>=0);
        const dw4_status *ps=dw4_modelctrl_status(player);assert(ps);
        int32_t mhp,hp;assert(!dw4_property_number(p0,"MHP",&mhp));
        char error[256];dw4_script_value r;
        /* The shooting enemy: a goblin (row 0, RAM slot 5) in front of the player, its AI off. */
        dw4_modelctrl_actor pa;dw4_modelctrl_actor_state(player,&pa);float pm[16];dw4_modelctrl_actor_matrix(&pa,pm);
        char where[96],spot[96];
        snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,%g,0>/SQ_WAIT",pa.position[0]+pm[8]*9,pa.position[1],pa.position[2]+pm[10]*9,pa.rotation[1]+180);
        snprintf(spot,sizeof spot,"V<%g,%g,%g>/V<0,%g,0>",pa.position[0]+pm[8]*9,pa.position[1],pa.position[2]+pm[10]*9,pa.rotation[1]+180);
        dw4_script_value gen[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"e_goburi",8},{DW4_SCRIPT_NUMBER,5,NULL,0},{DW4_SCRIPT_STRING,0,"GENERATE",8},{DW4_SCRIPT_STRING,0,where,strlen(where)}};
        assert(!dw4_hubruntime_sd(h,gen,5,&r,error,sizeof error));
        dw4_script_model *goblin=dw4_hubruntime_enemy_state(h,"e_goburi",5);assert(goblin);
        const int32_t BIG=100000;goblin->rec_no=0;goblin->hp=goblin->max_hp=BIG;
        assert(!dw4_hubruntime_enemy_ai_off(h,"e_goburi",5));
        run(h,&frame,5,0,0);
        const dw4_status *gs=goblin_status(h);assert(gs);
        dw4_script_value clear[4]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,-1,NULL,0},{DW4_SCRIPT_STRING,0,"ALLCLEARSTATUS",14}};
        dw4_script_value ofctrl[4]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,-1,NULL,0},{DW4_SCRIPT_STRING,0,"OFCTRL",6}};
        dw4_script_value onctrl[4]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,-1,NULL,0},{DW4_SCRIPT_STRING,0,"ONCTRL",6}};
        /* One bullet of eneatk row `row` from the goblin until `done` holds (a failed roll answers 0 / -1 and applies nothing); the player is topped up first. */
#define E2P_LAND(rowi,cond) do{unsigned t_=0;for(;t_<80 && !(cond);t_++){assert(!dw4_property_set_number(p0,"HP",mhp));\
            int rc_=dw4_combat_hit_player(combat,0,player,(int64_t)frame*1000000000LL/60,70000+row[rowi],0,5,gs,error,sizeof error);\
            if(rc_<0){fprintf(stderr,"hit %d: %s\n",row[rowi],error);return 1;} assert(rc_==1);run(h,&frame,2,0,0);}assert(cond);}while(0)
        int32_t sub0,tsu0,mam0,chi0;
        assert(!dw4_property_number(p0,"SUBAYASA",&sub0) && !dw4_property_number(p0,"TSUYOSA",&tsu0) && !dw4_property_number(p0,"MAMORI",&mam0) && !dw4_property_number(p0,"CHIMEIRITSU",&chi0));
        fprintf(stderr,"player stats: HP %d SUBAYASA %d TSUYOSA %d MAMORI %d CHIMEIRITSU %d\n",mhp,sub0,tsu0,mam0,chi0);

        /* SLEEP: SETSLEEP on the player's status puts it in SQ_SLEP, whose program has no CTRL: the stick moves nothing. */
        E2P_LAND(1,ps->timer[DW4_STATUS_SLEEP]>0);
        int32_t sleep_frames=ps->timer[DW4_STATUS_SLEEP];
        fprintf(stderr,"sleep landed: %d frames, player sequence %s\n",sleep_frames,dw4_modelctrl_sequence(player));
        assert(!strcmp(dw4_modelctrl_sequence(player),"SQ_SLEP"));
        {
            dw4_modelctrl_actor a0,a1;dw4_modelctrl_actor_state(player,&a0);
            for(unsigned i=0;i<60;i++){dw4_hubruntime_input(h,0,-1,0,0,0);assert(!dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60));}
            dw4_modelctrl_actor_state(player,&a1);
            float dx=a1.position[0]-a0.position[0],dz=a1.position[2]-a0.position[2];
            fprintf(stderr,"stick held for 60 ticks while asleep: moved %.3f, sequence %s\n",sqrtf(dx*dx+dz*dz),dw4_modelctrl_sequence(player));
            assert(sqrtf(dx*dx+dz*dz)<0.5f && !strcmp(dw4_modelctrl_sequence(player),"SQ_SLEP"));
        }
        /* OFCTRL (a script took control away): the status manager's blocks are guarded by the control flag, so the sleep neither expires nor re-arms; the named-timer clock keeps
         * running (assumption), so a sleep that would have ended meanwhile ends on the first tick after ONCTRL. */
        assert(!dw4_hubruntime_sd(h,ofctrl,4,&r,error,sizeof error));
        run(h,&frame,(unsigned)sleep_frames+120,0,0);
        assert(ps->timer[DW4_STATUS_SLEEP]>0 && !strcmp(dw4_modelctrl_sequence(player),"SQ_SLEP"));
        assert(!dw4_hubruntime_sd(h,onctrl,4,&r,error,sizeof error));
        run(h,&frame,4,0,0);
        fprintf(stderr,"control back: sleep %d, sequence %s\n",ps->timer[DW4_STATUS_SLEEP],dw4_modelctrl_sequence(player));
        assert(!ps->timer[DW4_STATUS_SLEEP] && strcmp(dw4_modelctrl_sequence(player),"SQ_SLEP"));
        run(h,&frame,30,0,0);
        {
            dw4_modelctrl_actor a0,a1;dw4_modelctrl_actor_state(player,&a0);
            for(unsigned i=0;i<30;i++){dw4_hubruntime_input(h,0,-1,0,0,0);assert(!dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60));}
            dw4_modelctrl_actor_state(player,&a1);
            float dx=a1.position[0]-a0.position[0],dz=a1.position[2]-a0.position[2];
            fprintf(stderr,"awake again: stick moved %.3f\n",sqrtf(dx*dx+dz*dz));
            assert(sqrtf(dx*dx+dz*dz)>1.0f);
        }

        /* BIND stops horizontal channels after control, preserves HITBOX
         * delivery, and ALLCLEARSTATUS releases the movement gate. */
        place(h,spot);   /* walking moved the player: stand where the goblin is 9 units ahead again */
        {
            dw4_script_value mv[5]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,"",0}};
            char home[96];snprintf(home,sizeof home,"V<%g,%g,%g>/V<0,%g,0>",pa.position[0],pa.position[1],pa.position[2],pa.rotation[1]);
            mv[4].string=home;mv[4].length=strlen(home);
            assert(!dw4_hubruntime_sd(h,mv,5,&r,error,sizeof error));
            run(h,&frame,30,0,0);
            E2P_LAND(2,ps->timer[DW4_STATUS_BIND]>0);
            fprintf(stderr,"bind landed: %d frames, player sequence %s\n",ps->timer[DW4_STATUS_BIND],dw4_modelctrl_sequence(player));
            /* Keep the status through retries of the real attack/contact path. */
            dw4_script_value bind[5]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},
                {DW4_SCRIPT_STRING,0,"SETBIND",7},{DW4_SCRIPT_STRING,0,"I<6000>",7}};
            assert(!dw4_hubruntime_sd(h,bind,5,&r,error,sizeof error));
            run(h,&frame,30,0,0);
            dw4_modelctrl_actor bound0,bound1;dw4_modelctrl_actor_state(player,&bound0);
            for(unsigned i=0;i<30;i++){dw4_hubruntime_input(h,0,-1,0,0,0);assert(!dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60));}
            dw4_modelctrl_actor_state(player,&bound1);
            assert(fabsf(bound1.position[0]-bound0.position[0])<0.001f && fabsf(bound1.position[2]-bound0.position[2])<0.001f);
            for(unsigned swing=0;swing<2;swing++){
                const unsigned hits0=dw4_hubruntime_combat(h)->hits;
                if(swing){assert(!dw4_hubruntime_sd(h,clear,4,&r,error,sizeof error));assert(!ps->timer[DW4_STATUS_BIND]);}
                for(unsigned attempt=0;attempt<12;attempt++){
                    assert(!dw4_hubruntime_sd(h,mv,5,&r,error,sizeof error));
                    char gspot[96];snprintf(gspot,sizeof gspot,"%s",spot);
                    dw4_script_value gm[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"e_goburi",8},{DW4_SCRIPT_NUMBER,5,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,gspot,strlen(gspot)}};
                    assert(!dw4_hubruntime_sd(h,gm,5,&r,error,sizeof error));
                    goblin->hp=goblin->max_hp=BIG;
                    for(unsigned i=0;i<90;i++){dw4_hubruntime_input(h,0,0,0,i<3?0x4000:0,i==0?0x4000:0);assert(!dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60));}
                    run(h,&frame,60,0,0);
                    if(dw4_hubruntime_combat(h)->hits>hits0 && goblin->hp<BIG)break;
                }
                fprintf(stderr,"%s: combat hits %u -> %u, goblin HP %d\n",swing?"after ALLCLEARSTATUS":"while bound",hits0,dw4_hubruntime_combat(h)->hits,goblin->hp);
                assert(dw4_hubruntime_combat(h)->hits>hits0 && goblin->hp<BIG);
                if(!swing)assert(dw4_modelctrl_status(player)->timer[DW4_STATUS_BIND]);
            }
        }
        goblin->hp=goblin->max_hp=BIG;
        run(h,&frame,120,0,0);

        /* ATTACK DOWN / POWER DOWN: the E2P rules write the record's DOWNDATA and recalculate before reading the stat, SETATTACKDOWN / SETPOWERDOWN then put the reply values
         * into the lists (record-backed, 7 entries) and the recalculation lowers the stats; ALLCLEARSTATUS restores them. */
        E2P_LAND(3,ps->timer[DW4_STATUS_ATTACKDOWN]>0);
        E2P_LAND(4,ps->timer[DW4_STATUS_POWERDOWN]>0);
        {
            size_t nd=0,nu=0;const int32_t *down=dw4_property_array(p0,"DOWNDATA",&nd),*up=dw4_property_array(p0,"UPDATA",&nu);assert(down && nd==7 && up && nu==11);
            int32_t sub1,tsu1,mam1,chi1;
            assert(!dw4_property_number(p0,"SUBAYASA",&sub1) && !dw4_property_number(p0,"TSUYOSA",&tsu1) && !dw4_property_number(p0,"MAMORI",&mam1) && !dw4_property_number(p0,"CHIMEIRITSU",&chi1));
            fprintf(stderr,"DOWNDATA %d %d %d %d %d %d %d; SUBAYASA %d -> %d, TSUYOSA %d -> %d, MAMORI %d -> %d, CHIMEIRITSU %d -> %d\n",down[0],down[1],down[2],down[3],down[4],down[5],down[6],sub0,sub1,tsu0,tsu1,mam0,mam1,chi0,chi1);
            assert(down[0]>0 && down[4]>0 && down[5]>0 && down[0]==dw4_status_down(ps,0) && down[4]==dw4_status_down(ps,4) && down[5]==dw4_status_down(ps,5));
            assert(sub1==(sub0-down[0]<1?1:sub0-down[0]) && tsu1==(tsu0-down[4]<1?1:tsu0-down[4]) && mam1==(mam0-down[5]<1?1:mam0-down[5]));
            assert(sub1<sub0 && tsu1<tsu0 && mam1<mam0);
        }
        assert(!dw4_hubruntime_sd(h,clear,4,&r,error,sizeof error));
        {
            size_t nd=0;const int32_t *down=dw4_property_array(p0,"DOWNDATA",&nd);int32_t sub2,tsu2,mam2,chi2;
            assert(down && nd==7 && !dw4_property_number(p0,"SUBAYASA",&sub2) && !dw4_property_number(p0,"TSUYOSA",&tsu2) && !dw4_property_number(p0,"MAMORI",&mam2) && !dw4_property_number(p0,"CHIMEIRITSU",&chi2));
            for(int i=0;i<7;i++)assert(down[i]==0);
            assert(sub2==sub0 && tsu2==tsu0 && mam2==mam0 && chi2==chi0 && !ps->timer[DW4_STATUS_ATTACKDOWN] && !ps->timer[DW4_STATUS_POWERDOWN]);
        }

        /* An attack-down on the ATTACKER lowers the E2P damage: the same draws, replayed with the goblin's down[4] (strength) and [1] (critical), give the HP the hit took. */
        {
            int plain_row=-1;int32_t dmg_col=0;
            for(int a=0;a<2000 && plain_row<0;a++){const char *k=dw4_database_string(eneatk,a,"KOUKA");int32_t t;
                if(k && (!*k || !strcmp(k,"none")) && !dw4_database_number(eneatk,a,"TYPE",&t) && t==0 && !dw4_database_number(eneatk,a,"TSUYOSA",&dmg_col) && dmg_col>0)plain_row=a;}
            assert(plain_row>=0);
            const dw4_database *enemy=dw4_databases_get(dbs,"enemy");
            int32_t gstr=0;assert(!dw4_database_number(enemy,0,"TSUYOSA",&gstr) && gstr>=8);
            char pdtext[48];snprintf(pdtext,sizeof pdtext,"I<3000>/I<%d>/I<0>",gstr/4);
            dw4_script_value pd[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"e_goburi",8},{DW4_SCRIPT_NUMBER,5,NULL,0},{DW4_SCRIPT_STRING,0,"SETPOWERDOWN",12},{DW4_SCRIPT_STRING,0,pdtext,strlen(pdtext)}};
            assert(!dw4_hubruntime_sd(h,pd,5,&r,error,sizeof error) && dw4_status_down(gs,DW4_DOWN_ATTACK)==gstr/4);
            int32_t dealt_with=0,dealt_plain=0;
            for(unsigned tries=0;tries<60 && !dealt_with;tries++){
                assert(!dw4_property_set_number(p0,"HP",mhp));
                dw4_random a=dw4_hubruntime_state(h)->random,b;dw4_fight_e2p_ctx ca={p0,dw4_database_typed(enemy),dw4_database_typed(eneatk),&a},cb={p0,dw4_database_typed(enemy),dw4_database_typed(eneatk),&b};
                int hit=0;dw4_fight_damage da={0},db={0};
                assert(!dw4_fight_e2p_is_hit(&ca,0,70000+plain_row,&hit));
                if(hit){b=a;
                    assert(!dw4_fight_e2p_damage(&ca,0,70000+plain_row,(dw4_fight_e2p_down){dw4_status_down(gs,DW4_DOWN_CRITICAL),dw4_status_down(gs,DW4_DOWN_ATTACK)},&da) &&
                           !dw4_fight_e2p_damage(&cb,0,70000+plain_row,(dw4_fight_e2p_down){0,0},&db));}
                assert(dw4_combat_hit_player(combat,0,player,(int64_t)frame*1000000000LL/60,70000+plain_row,0,5,gs,error,sizeof error)>=0);
                dw4_property_number(p0,"HP",&hp);
                run(h,&frame,150,0,0);
                if(hit){
                    assert(mhp-hp==da.damage);   /* the replay with the attacker's down values is what the hit script applied */
                    if(da.damage<db.damage){dealt_with=mhp-hp;dealt_plain=db.damage;
                        fprintf(stderr,"enemy hit with the goblin's strength down %d: %d damage (replay %d; the same draws without the down: %d)\n",gstr/4,dealt_with,da.damage,dealt_plain);}
                }else assert(hp==mhp);
            }
            assert(dealt_with>0);
            assert(!dw4_hubruntime_sd(h,(dw4_script_value[4]){{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"e_goburi",8},{DW4_SCRIPT_NUMBER,5,NULL,0},{DW4_SCRIPT_STRING,0,"ALLCLEARSTATUS",14}},4,&r,error,sizeof error));
            assert(dw4_status_down(gs,DW4_DOWN_ATTACK)==0 && !dw4_status_is_set(gs,DW4_STATUS_POWERDOWN));
        }

        /* POISON: SETPOISON I<t>/I<MHP*KR/100>/I<GEDOKU> (the third argument is a player's endurance); one tick of that damage per 120 frames comes off the RECORD's HP;
         * a tick that would reach 0 KOs the player (SQ_DEAD) and the game-over path takes over. */
        E2P_LAND(0,ps->timer[DW4_STATUS_POISON]>0);
        {
            int32_t gedoku=0,kr=0;assert(!dw4_database_number(eneatk,row[0],"GEDOKU",&gedoku) && !dw4_database_number(eneatk,row[0],"KOUKARANK",&kr));
            fprintf(stderr,"poison landed: timer %d, damage %d (MHP %d * rank %d / 100), endurance %d (GEDOKU)\n",ps->timer[DW4_STATUS_POISON],ps->poison_damage,mhp,kr,ps->poison_endurance);
            assert(ps->poison_damage==mhp*kr/100 && ps->poison_endurance==gedoku && ps->poison_damage>0);
            run(h,&frame,200,0,0);   /* the damage sequence and the stun of the same hit are over */
            assert(!dw4_property_set_number(p0,"HP",mhp));
            int32_t seen[4];unsigned ticks=0;
            for(unsigned i=0;i<260 && ticks<2;i++){int32_t before;dw4_property_number(p0,"HP",&before);run(h,&frame,1,0,0);dw4_property_number(p0,"HP",&hp);if(hp!=before){seen[ticks++]=hp;}}
            fprintf(stderr,"poison ticks: HP %d then %d of %d\n",ticks>0?seen[0]:-1,ticks>1?seen[1]:-1,mhp);
            assert(ticks==2 && seen[0]==mhp-ps->poison_damage && seen[1]==mhp-2*ps->poison_damage);
            /* the KO: HP just above one tick */
            assert(!dw4_property_set_number(p0,"HP",ps->poison_damage));
            for(unsigned i=0;i<400 && ps->timer[DW4_STATUS_POISON];i++)run(h,&frame,1,0,0);
            dw4_property_number(p0,"HP",&hp);
            fprintf(stderr,"poison KO: HP %d, player sequence %s, poison %d\n",hp,dw4_modelctrl_sequence(player),ps->timer[DW4_STATUS_POISON]);
            assert(hp==0 && !ps->timer[DW4_STATUS_POISON] && !strcmp(dw4_modelctrl_sequence(player),"SQ_DEAD"));
            unsigned i=0;
            for(;i<3000 && !dw4_hubruntime_travel(h)->pending;i++){
                dw4_hubruntime_input(h,0,0,0,i%40<4?0x4000:0,i%40==0?0x4000:0);
                if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
            }
            assert(dw4_hubruntime_travel(h)->pending && !strcmp(dw4_hubruntime_travel(h)->destination,"stagML11"));
            fprintf(stderr,"game over: Terminal requested after %u more ticks\n",i);
        }
        dw4_hubruntime_close(h);
        printf("field stage stag0101 statusflow_e2p: enemy bullet -> hit_p chunk -> E2P status rules -> player status work and record lists, KO and game over\n");
        return 0;
    }
    if(!strcmp(mode,"room") || !strcmp(mode,"route")) {
        /* Goblin Fortress Leomon room (stagGF03): the e_mecha4 of GENE-00 against a progressed-save fixture (stats set below). "route" first walks the
         * original exits stag0101 -> stagGF01 -> stagGF02 -> stagGF03 (each exit region's own script and prompt, confirmed with Cross). */
        unsigned until=0;
        if(!strcmp(mode,"route")){
            if(getenv("FRESH")){
                /* A fresh save (story flag 2 only; 503 clear): the Terminal gate sends it to the practice stage stag0001, its lessons are played with the pilot,
                 * and the practice exit region (matz00) leads on to stag0101's first visit. */
                const int fl[]={2,500,501};setenv("STAGE","stagML11",1);h=enter(&mount,fl,3);unsetenv("STAGE");
                for(;until<4000 && !control(h);until++){dw4_hubruntime_input(h,0,0,0,0,until%10==0?0x4000:0);if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"terminal tick: %s\n",dw4_hubruntime_error(h));return 1;}}
                h=take_exit(&mount,h,&frame,"stagML11","mate00","stag0001",0);
                /* the introduction: Cross through the dialogue until control returns */
                for(until=0;until<6000 && !control(h);until++){dw4_hubruntime_input(h,0,0,0,until%90<4?0x4000:0,until%90==0?0x4000:0);if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"practice tick: %s\n",dw4_hubruntime_error(h));return 1;}}
                assert(control(h));
                practice_lessons(h,&frame);
                h=take_exit(&mount,h,&frame,"stag0001","matz00","stag0101",0);
                const dw4_fieldgen *fg0=dw4_hubruntime_fieldgen(h);assert(dw4_fieldgen_find(fg0,"GENE-21"));   /* first visit: flag 355 is still clear */
                for(until=0;until<4000 && !control(h);until++)run(h,&frame,1,0,0);
                assert(control(h));fprintf(stderr,"stag0101 first visit: control after %u ticks\n",until);
                {const uint8_t *fl2=dw4_property_bytes(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0),"FLAG",NULL);assert(fl2[503]==1);}
            }else if(getenv("TERMINAL")){
                /* From the Terminal: its Outside World gate (mate00) with story flag 2 and 503 set offers stag0101 first. */
                const int fl[]={2,355,503,500,501};setenv("STAGE","stagML11",1);h=enter(&mount,fl,5);unsetenv("STAGE");
                for(;until<4000 && !control(h);until++){dw4_hubruntime_input(h,0,0,0,0,until%10==0?0x4000:0);if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"terminal tick: %s\n",dw4_hubruntime_error(h));return 1;}}
                fprintf(stderr,"terminal arrival: control after %u ticks\n",until);
                h=take_exit(&mount,h,&frame,"stagML11","mate00","stag0101",0);
            }else{const int fl[]={2,355,503};h=enter(&mount,fl,3);}
            for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
            h=take_exit(&mount,h,&frame,"stag0101","matz01","stagGF01",0);
            for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
            h=take_exit(&mount,h,&frame,"stagGF01","matz01","stagGF02",0);
            for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
            h=take_exit(&mount,h,&frame,"stagGF02","matz01","stagGF03",0);
            until=0;
        }else{const int fl[]={2,503};h=enter(&mount,fl,2);}
        for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        run(h,&frame,200,0,0);
        {   /* walk-in: enter the room region (matf00 spans the room), then let the entrance scene run, tapping Cross through any prompt */
            char error[512];dw4_script_value r;
            dw4_script_value mv[5]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,"V<5,40,-60>/V<0,0,0>",20}};
            assert(!dw4_hubruntime_sd(h,mv,5,&r,error,sizeof error));
            for(unsigned i=0;i<1500;i++){
                dw4_hubruntime_input(h,0,0,0,i%40<4?0x4000:0,i%40==0?0x4000:0);
                if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
            }
            fprintf(stderr,"after entrance: control %d, flag 20 -> see below\n",control(h));
        }
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
        {   /* Progressed-save fixture: the starter at LEVEL (default 40, the lowest tested level that beats the boss with real damage taken) with every stat derived by the recovered recalculation (no hand-set stats), full HP/MP. */
            int lvl=getenv("FIXLEVEL")?atoi(getenv("FIXLEVEL")):40;int32_t mhp=0,mmp=0,nx=0;
            assert(!dw4_property_set_number(p0,"LEVEL",lvl) && !dw4_playerstats_recalculate((void *)dw4_hubruntime_databases(h),p0));
            assert(!dw4_property_number(p0,"MHP",&mhp) && !dw4_property_number(p0,"MMP",&mmp) && !dw4_property_number(p0,"NEXTEXP",&nx));
            assert(!dw4_property_set_number(p0,"HP",mhp) && !dw4_property_set_number(p0,"MP",mmp) && !dw4_property_set_number(p0,"EXP",lvl>1?(lvl-1)*200+(lvl+139)*(lvl-1)*(lvl-1):0));
            int32_t t=0,m=0;dw4_property_number(p0,"TSUYOSA",&t);dw4_property_number(p0,"MAMORI",&m);fprintf(stderr,"fixture: level %d HP %d MP %d strength %d defence %d\n",lvl,mhp,mmp,t,m);
        }
        {int32_t a=-1,b=-1,c=-1,d=-1;dw4_property_number(p0,"MEICHURITSU",&a);dw4_property_number(p0,"SUBAYASA",&b);dw4_property_number(p0,"WEAPONSKILLNO",&c);dw4_property_number(p0,"CHIMEIRITSU",&d);
            size_t ns=0;const int32_t *sk=dw4_property_array(p0,"SKILL",&ns);fprintf(stderr,"player MEICHURITSU %d SUBAYASA %d WEAPONSKILLNO %d CHIMEIRITSU %d SKILL[%d]=%d\n",a,b,c,d,c,sk&&c>=0&&(size_t)c<ns?sk[c]:-1);}
        dw4_modelctrl *player=dw4_lobby_player_model(dw4_hubruntime_world(h));
        const dw4_modelctrl *boss=NULL;int32_t bslot=-1;
        for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
            if(!strcmp(dw4_stageobject_name(info),"e_mecha4") && dw4_modelctrl_active(mc)){boss=mc;bslot=slot;}}
        if(!boss)for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
            if(!strncmp(dw4_stageobject_name(info),"e_mecha4",8))fprintf(stderr,"%s[%d] active %d seq %s\n",dw4_stageobject_name(info),slot,dw4_modelctrl_active(mc),dw4_modelctrl_sequence(mc));}
        assert(boss);dw4_script_model *bs=dw4_hubruntime_enemy_state(h,"e_mecha4",bslot);
        fprintf(stderr,"boss slot %d row %d hp %d/%d, player control after %u ticks\n",bslot,bs->rec_no,bs->hp,bs->max_hp,until);
        if(getenv("RNGSKIP"))for(int i=atoi(getenv("RNGSKIP"));i>0;i--)dw4_random_next(&dw4_hubruntime_state(h)->random);   /* explore other random streams */
        int xdata_dropped=0;unsigned cycles=0;int32_t hp=1;assert(!dw4_property_number(p0,"HP",&hp));
        for(;cycles<400 && dw4_modelctrl_active(boss) && hp>0;cycles++){
            for(unsigned w=0;w<1500 && !control(h) && hp>0;w++){   /* a script (the gate closing behind the player) may hold control for a while */
                dw4_hubruntime_input(h,0,0,0,0,0);
                if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
                assert(!dw4_property_number(p0,"HP",&hp));
            }
            dw4_modelctrl_actor ba,pa;dw4_modelctrl_actor_state(boss,&ba);dw4_modelctrl_actor_state(player,&pa);
            float dx=ba.position[0]-pa.position[0],dz=ba.position[2]-pa.position[2],len=sqrtf(dx*dx+dz*dz)+1e-3f;
            char where[96],error[512];dw4_script_value r;
            if(ba.position[2]>100){   /* the boss chased a knocked-back player toward Leomon (no arena wall in the port yet): go back to the arrival spot and let it come; the math00 strip (z 150..160) must not be entered before the boss is down */
                dw4_script_value home[5]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,"V<5,12.5,26>/V<0,0,0>",21}};
                dw4_script_value r0;char e0[256];assert(!dw4_hubruntime_sd(h,home,5,&r0,e0,sizeof e0));
                run(h,&frame,90,0,0);assert(!dw4_property_number(p0,"HP",&hp));continue;
            }
            float stand_z=ba.position[2]-dz/len*9;
            snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,%g,0>",ba.position[0]-dx/len*9,ba.position[1],stand_z,atan2f(dx,stand_z>ba.position[2]-dz/len*9-0.01f?dz:dz)*57.29578f);
            dw4_script_value mv[5]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,where,strlen(where)}};
            if(len>13 || len<5)assert(!dw4_hubruntime_sd(h,mv,5,&r,error,sizeof error));   /* re-position only when out of reach: every MOVETRANS can re-trigger the room's regions */
            for(unsigned i=0;i<90;i++){
                dw4_hubruntime_input(h,0,0,0,i<3?0x4000:0,i==0?0x4000:0);
                if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
                {static int32_t last=-1;if(last>=0 && bs->hp>last)fprintf(stderr,"boss hp rose %d -> %d at cycle %u i %u seq %s\n",last,bs->hp,cycles,i,dw4_modelctrl_sequence(boss));last=bs->hp;}
                if(getenv("ATKDEBUG") && cycles<2 && i%8==0){unsigned nb;const dw4_modelctrl_hitbox *hb=dw4_modelctrl_hitboxes(player,&nb);dw4_modelctrl_actor q;dw4_modelctrl_actor_state(player,&q);
                    fprintf(stderr,"c%u i%u player seq %s boxes %u first kind %d ctl %d pos %.1f %.1f %.1f boss pos %.1f %.1f %.1f\n",cycles,i,dw4_modelctrl_sequence(player),nb,nb?hb[0].kind:0,control(h),q.position[0],q.position[1],q.position[2],ba.position[0],ba.position[1],ba.position[2]);}
            }
            assert(!dw4_property_number(p0,"HP",&hp));
            if(cycles%10==0){dw4_modelctrl_actor q1,q2;dw4_modelctrl_actor_state(boss,&q1);dw4_modelctrl_actor_state(player,&q2);fprintf(stderr,"cycle %u: boss hp %d seq %s at %.0f %.0f %.0f, player hp %d seq %s at %.0f %.0f %.0f\n",cycles,bs->hp,dw4_modelctrl_sequence(boss),q1.position[0],q1.position[1],q1.position[2],hp,dw4_modelctrl_sequence(player),q2.position[0],q2.position[1],q2.position[2]);}
        }
        for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t sl;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&sl);dw4_script_model st;
            if(!strcmp(dw4_stageobject_name(info),"e_mecha4") && !dw4_controllers_model_state(dw4_hubruntime_models(h),k,&st))fprintf(stderr,"receiver %zu e_mecha4[%d] active %d hp %d/%d row %d\n",k,sl,dw4_modelctrl_active(mc),st.hp,st.max_hp,st.rec_no);}
        fprintf(stderr,"end: boss hp %d active %d, player hp %d after %u cycles; combat hits %u / player hits %u\n",bs->hp,dw4_modelctrl_active(boss),hp,cycles,dw4_hubruntime_combat(h)->hits,dw4_hubruntime_combat(h)->player_hits);
        if(dw4_modelctrl_active(boss)){fprintf(stderr,"boss survived\n");return 1;}
        run(h,&frame,600,0,0);
        const uint8_t *flags=dw4_property_bytes(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0),"FLAG",NULL);
        fprintf(stderr,"boss dead: flag383 %u flag20 %u control %d\n",flags[383],flags[20],control(h));
        {   /* the boss's x-data drop is a model that blinks out about 1030 frames after it lands (docs/dungeon-floors.md "Drop models"): walk onto it now, five per pickup, before the Leomon scene */
            size_t nd=0;const dw4_drop *dr=dw4_fieldgen_drops(dw4_hubruntime_fieldgen(h),&nd);
            for(size_t i=0;i<nd;i++)if(!strcmp(dr[i].entry.category,"insItem") && dr[i].entry.id==1){xdata_dropped=1;
                assert(dr[i].model_live && !dr[i].collected && !strcmp(dr[i].model,"g_000xdata1"));   /* 600 frames after the kill it is still lying there */
                char where[96];snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",dr[i].position[0],dr[i].position[1],dr[i].position[2]);place(h,where);run(h,&frame,30,0,0);
                int32_t xd=-1;assert(!dw4_property_number(p0,"XDATA",&xd));fprintf(stderr,"x-data after the pickup: %d (pickups %u)\n",xd,dw4_hubruntime_pickups(h));assert(xd==5 && dw4_hubruntime_pickups(h)==1);}
        }
        /* Leomon: stand next to him facing him and press Cross (the talk probe at the head of SQ_ATCK1), then tap through the scene. */
        const dw4_modelctrl *leo=NULL;
        for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
            if(!strcmp(dw4_stageobject_name(info),"n_leomon") && slot==0)leo=mc;}
        assert(leo);dw4_modelctrl_actor la,pa2;dw4_modelctrl_actor_state(leo,&la);
        fprintf(stderr,"Leomon active %d at %.1f %.1f %.1f seq %s\n",dw4_modelctrl_active(leo),la.position[0],la.position[1],la.position[2],dw4_modelctrl_sequence(leo));
        {
            char where[96],error[512];dw4_script_value r;
            snprintf(where,sizeof where,"V<5,40,155>/V<0,0,0>");   /* the math00 strip (z 150..160) in front of Leomon triggers the scene */
            dw4_script_value mv[5]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,where,strlen(where)}};
            assert(!dw4_hubruntime_sd(h,mv,5,&r,error,sizeof error));
        }
        if(getenv("MARKZ")){   /* leave every region, wait for the DMs to idle, then step into the region at MARKZ with a marker in the trace */
            char where[96],error[512];dw4_script_value r;
            snprintf(where,sizeof where,"V<5,40,-300>/V<0,0,0>");
            dw4_script_value mv[5]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,where,strlen(where)}};
            assert(!dw4_hubruntime_sd(h,mv,5,&r,error,sizeof error));
            run(h,&frame,300,0,0);
            fprintf(stderr,"MARK step into z=%s\n",getenv("MARKZ"));
            snprintf(where,sizeof where,"V<5,40,%s>/V<0,0,0>",getenv("MARKZ"));
            dw4_script_value mv2[5]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,where,strlen(where)}};
            assert(!dw4_hubruntime_sd(h,mv2,5,&r,error,sizeof error));
            run(h,&frame,60,0,0);
            {dw4_modelctrl_actor pa3;dw4_modelctrl_actor_state(dw4_lobby_player_model(dw4_hubruntime_world(h)),&pa3);fprintf(stderr,"player now %.1f %.1f %.1f seq %s\n",pa3.position[0],pa3.position[1],pa3.position[2],dw4_modelctrl_sequence(dw4_lobby_player_model(dw4_hubruntime_world(h))));}
            fprintf(stderr,"MARK end\n");
        }
        if(getenv("SWEEP"))for(int z=-190;z<=190 && !dw4_hubruntime_travel(h)->pending;z+=10){
            char where[96],error[512];dw4_script_value r;snprintf(where,sizeof where,"V<5,40,%d>/V<0,0,0>",z);
            dw4_script_value mv[5]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,where,strlen(where)}};
            assert(!dw4_hubruntime_sd(h,mv,5,&r,error,sizeof error));
            for(unsigned i=0;i<45;i++){dw4_hubruntime_input(h,0,0,0,0,0);if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}}
            const uint8_t *fg=dw4_property_bytes(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0),"FLAG",NULL);
            if(fg[20])fprintf(stderr,"flag 20 set at z=%d\n",z);
        }
        unsigned t=0;for(;t<6000 && !dw4_hubruntime_travel(h)->pending;t++){
            dw4_hubruntime_input(h,0,0,0,t%40<4?0x4000:0,t%40==0?0x4000:0);
            if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
        }
        (void)pa2;
        flags=dw4_property_bytes(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0),"FLAG",NULL);
        fprintf(stderr,"Leomon scene: pending %d dest %s point %d after %u ticks, flag20 %u\n",dw4_hubruntime_travel(h)->pending,dw4_hubruntime_travel(h)->destination,dw4_hubruntime_travel(h)->generate_pos,t,flags[20]);
        {size_t nd=0;const dw4_drop *dr=dw4_fieldgen_drops(dw4_hubruntime_fieldgen(h),&nd);
            fprintf(stderr,"drops rolled in the room: %zu\n",nd);for(size_t i=0;i<nd;i++)fprintf(stderr,"  %s: %s id %d rate %d at %.1f %.1f %.1f\n",dr[i].generator,dr[i].entry.category,dr[i].entry.id,dr[i].entry.rate,dr[i].position[0],dr[i].position[1],dr[i].position[2]);
            assert(nd<=dw4_fieldgen_spawned(dw4_hubruntime_fieldgen(h)));}
        assert(flags[383]==1 && flags[20]==1 && dw4_hubruntime_travel(h)->pending && !strcmp(dw4_hubruntime_travel(h)->destination,"stagML02") && dw4_hubruntime_travel(h)->generate_pos==1);
        /* The Commander Room prepares from this record and keeps flag 20. */
        {
            dw4_stageinput in=*dw4_hubruntime_input_state(h);char error[512];
            dw4_hubruntime_source prior={dw4_hubruntime_records(h),dw4_hubruntime_state(h),&in,dw4_hubruntime_time(h)};
            dw4_hubruntime *room=dw4_hubruntime_prepare(&mount,&prior,"stagML02",1,1,error,sizeof error);
            if(!room){fprintf(stderr,"stagML02: %s\n",error);return 1;}
            const uint8_t *f2=dw4_property_bytes(dw4_playerrecords_get(dw4_hubruntime_records(room),"GETCOMMON",0),"FLAG",NULL);
            assert(f2[20]==1);
            {   /* the record that arrives in the Commander Room carries the whole run: flag 20, the x-data picked up, the EXP earned */
                dw4_property_folder *q=dw4_playerrecords_get(dw4_hubruntime_records(room),"GETPLAYER",0);int32_t xd=-1,ex=-1,lv=-1;
                assert(!dw4_property_number(q,"XDATA",&xd) && !dw4_property_number(q,"EXP",&ex) && !dw4_property_number(q,"LEVEL",&lv));
                fprintf(stderr,"stagML02 record: LEVEL %d EXP %d XDATA %d flag20 %u\n",lv,ex,xd,f2[20]);assert(ex>0 && xd==(xdata_dropped?5:0));   /* the boss list drops x-data 70 % of the time (the draw depends on every earlier random number) */
            }
            dw4_hubruntime_close(room);
        }
        sound_stats(h,!strcmp(mode,"route")?"route":"room");
        dw4_hubruntime_close(h);
        printf(!strcmp(mode,"route")?"field route stag0101 -> stagGF01 -> stagGF02 -> stagGF03: boss defeated, Leomon scene sets flag 20, stagML02 point 1\n":"field stage stagGF03: Machinedramon (e_mecha4) defeated, Leomon scene sets flag 20 and requests stagML02 point 1\n");
        return 0;
    }
    if(!strcmp(mode,"enemyrow")) {
        h=enter(&mount,(const int[]){2,503},2);const dw4_database *d=dw4_databases_get(dw4_hubruntime_databases(h),"enemy");
        for(int row=0;row<649;row++){int32_t hp=0,t=0,m=0,e=0;if(dw4_database_number(d,row,"HPMAX",&hp) || !hp)continue;
            dw4_database_number(d,row,"TSUYOSA",&t);dw4_database_number(d,row,"MAMORI",&m);dw4_database_number(d,row,"EXP",&e);
            const char *model=dw4_database_string(d,row,"MODEL");int32_t sb=0;dw4_database_number(d,row,"SUBAYASA",&sb);printf("ROW %d %s hp %d tsuyosa %d mamori %d exp %d subayasa %d\n",row,model?model:"",hp,t,m,e,sb);}
        return 0;
    }
    if(!strcmp(mode,"eneatk")) {
        const int revisit[]={2,355,503};
        h=enter(&mount,revisit,3);const dw4_database *d=dw4_databases_get(dw4_hubruntime_databases(h),"eneatk");
        for(int row=0;row<60;row++){int32_t t,m,c,kr,ge,sq,ts,mh,kt;
            dw4_database_number(d,row,"TYPE",&t);dw4_database_number(d,row,"MEICHURITSU",&m);dw4_database_number(d,row,"CHIMEIRITSU",&c);dw4_database_number(d,row,"KOUKARANK",&kr);
            dw4_database_number(d,row,"GEDOKU",&ge);dw4_database_number(d,row,"SEQUENCE",&sq);dw4_database_number(d,row,"TSUYOSA",&ts);dw4_database_number(d,row,"MAHIRITSU",&mh);dw4_database_number(d,row,"KOUKATIME",&kt);
            const char *z=dw4_database_string(d,row,"ZOKUSEI"),*k=dw4_database_string(d,row,"KOUKA");
            printf("ATK %d type %d mei %d chi %d tsu %d mahi %d seq %d zok '%s' kouka '%s' rank %d time %d gedoku %d\n",row,t,m,c,ts,mh,sq,z?z:"",k?k:"",kr,kt,ge);}
        return 0;
    }
    if(!strcmp(mode,"mate")) {
        /* Walk-in test of one authored material region (MATE env): teleport to its centre, tap Cross through the prompt, report the stage it requests. */
        int fl[32],nf=0;if(getenv("FLAGS")){char *t=strdup(getenv("FLAGS"));for(char *q=strtok(t,",");q && nf<32;q=strtok(NULL,","))fl[nf++]=atoi(q);}
        h=enter(&mount,fl,nf);run(h,&frame,300,0,0);
        const char *stage=getenv("STAGE")?getenv("STAGE"):"stag0101";
        dw4_igfile file={0};dw4_igb g={0};assert(!dw4_igfile_open_stage_pack(&file,&mount,stage,0,0) && !dw4_igb_open(&g,file.data,file.len,0) && !dw4_igb_refs_open(&g));
        float lo[3]={0},hi[3]={0};int found=0;
        for(uint32_t id=0;id<g.table_n && !found;id++)if(g.id_kind[id]==2){
            dw4_igb_record r={0};if(!dw4_igb_decode(&g,g.id_off[id],&r))continue;
            if(!strcmp(r.class_name,"beMatCtrlData") && r.name && !strcmp(r.name,getenv("MATE"))){
                uint32_t box=0;for(unsigned v=0;v<r.nvalues;v++)if(r.values[v].ordinal==3)box=r.values[v].raw;
                dw4_igb_record b={0};assert(box<g.table_n && dw4_igb_decode(&g,g.id_off[box],&b));
                for(unsigned v=0;v<b.nvalues;v++){if(b.values[v].ordinal==2)memcpy(lo,g.data+b.values[v].voff,12);if(b.values[v].ordinal==3)memcpy(hi,g.data+b.values[v].voff,12);}
                dw4_igb_record_free(&b);found=1;}
            dw4_igb_record_free(&r);}
        assert(found);
        char where[96],error[512];dw4_script_value r;
        snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",(lo[0]+hi[0])/2,hi[1]>lo[1]?lo[1]+(getenv("RISE")?atof(getenv("RISE")):2):lo[1],(lo[2]+hi[2])/2);
        dw4_script_value mv[5]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,where,strlen(where)}};
        assert(!dw4_hubruntime_sd(h,mv,5,&r,error,sizeof error));
        fprintf(stderr,"%s box (%g %g %g)-(%g %g %g) placed %s\n",getenv("MATE"),lo[0],lo[1],lo[2],hi[0],hi[1],hi[2],where);
        unsigned i=0;for(;i<1500 && !dw4_hubruntime_travel(h)->pending;i++){
            dw4_hubruntime_input(h,0,0,0,i%40<4?0x4000:0,i>60 && i%40==0?0x4000:0);
            if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
        }
        const dw4_stagetravel *t=dw4_hubruntime_travel(h);
        printf("mate %s: pending %d dest %s point %d after %u ticks\n",getenv("MATE"),t->pending,t->destination,t->generate_pos,i);
        return 0;
    }
    if(!strcmp(mode,"probe")) {
        /* Bring-up probe for another field stage: STAGE/POINT/FLAGS env; reports when control returns and which generators started. */
        int fl[32],nf=0;if(getenv("FLAGS")){char *t=strdup(getenv("FLAGS"));for(char *q=strtok(t,",");q && nf<32;q=strtok(NULL,","))fl[nf++]=atoi(q);}
        h=enter(&mount,fl,nf);unsigned until=0;
        for(;until<5000 && !control(h);until++)run(h,&frame,1,0,0);
        run(h,&frame,getenv("MORE")?atoi(getenv("MORE")):0,0,0);
        const dw4_fieldgen *g=dw4_hubruntime_fieldgen(h);unsigned started=0;
        for(size_t i=0;i<dw4_fieldgen_count(g);i++){const dw4_gene *e=dw4_fieldgen_at(g,i);if(e->state==DW4_GENE_STARTED){started++;printf("started %s row %d spawned %u\n",e->name,e->enemy_row,e->spawned_total);}}
        dw4_lobby_walk_state w;dw4_lobby_walk(dw4_hubruntime_world(h),&w);
        {size_t n=0;for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
            if(!strncmp(dw4_stageobject_name(info),"e_",2)||!strncmp(dw4_stageobject_name(info),"n_",2)||getenv("ALLMODELS")){printf("model %s[%d]\n",dw4_stageobject_name(info),slot);n++;}}(void)n;}
        {dw4_lobby_control_state cs;if(!dw4_lobby_control(dw4_hubruntime_world(h),&cs))fprintf(stderr,"camera region %u pos %.1f %.1f %.1f axes x %.3f %.3f %.3f y %.3f %.3f %.3f z %.3f %.3f %.3f; player %.1f %.1f %.1f\n",cs.camera_region,cs.camera_world[12],cs.camera_world[13],cs.camera_world[14],cs.camera_world[0],cs.camera_world[1],cs.camera_world[2],cs.camera_world[4],cs.camera_world[5],cs.camera_world[6],cs.camera_world[8],cs.camera_world[9],cs.camera_world[10],w.position[0],w.position[1],w.position[2]);}
        printf("probe: control %d after %u ticks, generators %zu started %u, player %g %g %g\n",control(h),until,dw4_fieldgen_count(g),started,w.position[0],w.position[1],w.position[2]);
        return 0;
    }
    if(!strcmp(mode,"dungeon")) {
        /* The first dungeon floor (Humid Cave, dng101b1): entered through stag0101's own exit region (matz00, funcStageChange "dng101b1" point 0), it
         * opens as a field world whose box rig and "entry" demo camera come from the floor's separate camera packs, returns control to the player, and
         * runs its generators and models. Near/Far Dungeon camera options pick aaacamera/aaacameral. */
        const int fl[]={2,355,503};h=enter(&mount,fl,3);
        unsigned until=0;
        for(;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        h=take_exit(&mount,h,&frame,"stag0101","matz00","dng101b1",0);
        for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        assert(control(h));
        run(h,&frame,600,0,0);
        dw4_lobby_world_state info;assert(!dw4_lobby_world_info(dw4_hubruntime_world(h),&info) && !strcmp(info.stage,"dng101b1") && info.arrival_point==0);
        dw4_lobby_control_state cs;assert(!dw4_lobby_control(dw4_hubruntime_world(h),&cs));
        assert(cs.box_camera && info.camera_regions>1 && info.materials>0 && info.floor_triangles>0);   /* the floor's own aaacamera box rig is selected */
        const dw4_fieldgen *g=dw4_hubruntime_fieldgen(h);assert(dw4_fieldgen_count(g)>0);
        unsigned started=0,enemies=0,saves=0;
        for(size_t i=0;i<dw4_fieldgen_count(g);i++)if(dw4_fieldgen_at(g,i)->state==DW4_GENE_STARTED)started++;
        for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){
            const dw4_stageobject *obj;int32_t slot;dw4_controllers_model(dw4_hubruntime_models(h),k,&obj,&slot);
            if(!strncmp(dw4_stageobject_name(obj),"e_",2))enemies++;
            if(!strcmp(dw4_stageobject_name(obj),"n_recorderdng"))saves++;}
        if(getenv("MATDBG")){
            float lo[3],hi[3];char where[96];mat_region(&mount,"dng101b1",getenv("MATDBG"),lo,hi);
            fprintf(stderr,"%s box (%g %g %g)-(%g %g %g)\n",getenv("MATDBG"),lo[0],lo[1],lo[2],hi[0],hi[1],hi[2]);
            snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",(lo[0]+hi[0])/2,lo[1]+(getenv("RISE")?atof(getenv("RISE")):20),(lo[2]+hi[2])/2);place(h,where);
            for(unsigned i=0;i<400;i++){run(h,&frame,1,0,0);if(i%50==0){dw4_lobby_walk_state ww;dw4_lobby_walk(dw4_hubruntime_world(h),&ww);dw4_lobby_control_state c2;dw4_lobby_control(dw4_hubruntime_world(h),&c2);
                fprintf(stderr,"  t%u player %g %g %g mask %x pending %d\n",i,ww.position[0],ww.position[1],ww.position[2],c2.material_mask,dw4_hubruntime_travel(h)->pending);}}
            return 0;
        }
        if(getenv("MAT")){h=take_exit(&mount,h,&frame,"dng101b1",getenv("MAT"),getenv("EXPECT")?getenv("EXPECT"):"dng101b2",0);return 0;}
        dw4_lobby_walk_state w;dw4_lobby_walk(dw4_hubruntime_world(h),&w);
        {   /* the floor's closed doors are in the walking collision (their names resolve in a dungeon pack) */
            dw4_lobby *wd=dw4_hubruntime_world(h);unsigned wt,ft;assert(!dw4_lobby_collision_counts(wd,&wt,&ft));
            assert(dw4_lobby_hit_state(wd,"doorwall01")==1 && dw4_lobby_hit_state(wd,"doorwall02")==1 && dw4_lobby_hit_state(wd,"doorwall03")==1 && dw4_hubruntime_hitland_missing(h)==0);}
        assert(started>0 && enemies>0 && saves>0 && isfinite(w.position[0]) && isfinite(w.position[1]) && isfinite(w.position[2]));
        printf("dungeon dng101b1: control after %u ticks, %u camera regions, %zu generators (%u started), %u enemy models, %u save points, player %g %g %g\n",until,info.camera_regions,dw4_fieldgen_count(g),started,enemies,saves,w.position[0],w.position[1],w.position[2]);
        /* Its matz02 region leads on to the second floor (funcStageChange "dng101b2" point 0): the Blossomon boss floor, whose Blossomon rig
         * has 67 bones over 52 joints (more than the earlier 64-bone limit). */
        h=take_exit(&mount,h,&frame,"dng101b1","matz02","dng101b2",0);
        for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        assert(control(h));run(h,&frame,600,0,0);
        assert(!dw4_lobby_world_info(dw4_hubruntime_world(h),&info) && !strcmp(info.stage,"dng101b2") && info.camera_regions>1);
        g=dw4_hubruntime_fieldgen(h);started=0;enemies=0;unsigned boss=0;
        for(size_t i=0;i<dw4_fieldgen_count(g);i++)if(dw4_fieldgen_at(g,i)->state==DW4_GENE_STARTED)started++;
        for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){
            const dw4_stageobject *obj;int32_t slot;dw4_controllers_model(dw4_hubruntime_models(h),k,&obj,&slot);
            if(!strncmp(dw4_stageobject_name(obj),"e_",2))enemies++;
            if(!strcmp(dw4_stageobject_name(obj),"e_blosso"))boss++;}
        assert(started>0 && enemies>0 && boss==1);
        {   /* doors 1-4 and the exit door are solid; the boss door is open until the intro closes it; no HITLANDMODEL name went unanswered */
            dw4_lobby *wd=dw4_hubruntime_world(h);static const int solid[6]={1,1,1,1,0,1};
            for(unsigned d=0;d<6;d++){char n[16];snprintf(n,sizeof n,"doorwall%02u",d+1);assert(dw4_lobby_hit_state(wd,n)==solid[d]);}
            assert(dw4_hubruntime_hitland_missing(h)==0);}
        printf("dungeon dng101b2: control after %u ticks, %u camera regions, %zu generators (%u started), %u enemy models, Blossomon %u\n",until,info.camera_regions,dw4_fieldgen_count(g),started,enemies,boss);
        return 0;
    }
    if(!strcmp(mode,"dungeonopen")) {
        /* A dungeon floor opened directly by name (FLOOR, default dng102b1; the generalised `dungeon` open, docs/dungeon-floors.md "The next dungeon"): the
         * route into dng102b1 runs through stag0102, which is not ported, so the runtime is prepared on the floor itself (point 0) with the same Humid
         * Cave progress flags. DOORS lists the doorwall names expected solid at arrival (comma separated; DOORSHOW prints doorwall01..09). */
        const char *floor_stage=getenv("FLOOR")?getenv("FLOOR"):"dng102b1";
        const int fl[]={2,355,503};setenv("STAGE",floor_stage,1);h=enter(&mount,fl,3);unsetenv("STAGE");
        unsigned until=0;
        for(;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        assert(control(h));
        run(h,&frame,600,0,0);
        dw4_lobby_world_state info;assert(!dw4_lobby_world_info(dw4_hubruntime_world(h),&info) && !strcasecmp(info.stage,floor_stage));
        dw4_lobby_control_state cs;assert(!dw4_lobby_control(dw4_hubruntime_world(h),&cs));
        assert(cs.box_camera && info.camera_regions>1 && info.materials>0 && info.floor_triangles>0);
        const dw4_fieldgen *g=dw4_hubruntime_fieldgen(h);assert(dw4_fieldgen_count(g)>0);
        unsigned started=0,enemies=0,saves=0;
        for(size_t i=0;i<dw4_fieldgen_count(g);i++)if(dw4_fieldgen_at(g,i)->state==DW4_GENE_STARTED)started++;
        for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){
            const dw4_stageobject *obj;int32_t slot;dw4_controllers_model(dw4_hubruntime_models(h),k,&obj,&slot);
            if(!strncmp(dw4_stageobject_name(obj),"e_",2))enemies++;
            if(!strcmp(dw4_stageobject_name(obj),"n_recorderdng"))saves++;}
        dw4_lobby_walk_state w;dw4_lobby_walk(dw4_hubruntime_world(h),&w);
        assert(isfinite(w.position[0]) && isfinite(w.position[1]) && isfinite(w.position[2]) && dw4_hubruntime_hitland_missing(h)==0);
        {   dw4_lobby *wd=dw4_hubruntime_world(h);char dl[256];snprintf(dl,sizeof dl,"%s",getenv("DOORS")?getenv("DOORS"):"");
            for(char *n=strtok(dl,",");n;n=strtok(NULL,","))assert(dw4_lobby_hit_state(wd,n)==1);
            if(getenv("DOORSHOW"))for(unsigned d=1;d<=9;d++){char n[16];snprintf(n,sizeof n,"doorwall%02u",d);fprintf(stderr,"  %s hit state %d\n",n,dw4_lobby_hit_state(wd,n));}}
        assert(started>0 && enemies>0);
        if(!strcmp(floor_stage,"dng102b3")) {   /* CAMERA SHAKE "37/F<0.3>/F<3.0>/F<60.0>" (Mammothmon's SQ_ATCK3, FUN_00378ed0): +x / -x by 0.3 every 3 frames for 60 frames, then the rig is back */
            dw4_lobby_control_state c0,c1;assert(!dw4_lobby_control(dw4_hubruntime_world(h),&c0));
            float rest[16];memcpy(rest,c0.camera_world,sizeof rest);
            char error[512];dw4_script_value r;const char *shake="37/F<0.3>/F<3.0>/F<60.0>";
            dw4_script_value sv[5]={{DW4_SCRIPT_STRING,0,"CAMERA",6},{0},{DW4_SCRIPT_NUMBER,-1,NULL,0},{DW4_SCRIPT_STRING,0,"SHAKE",5},{DW4_SCRIPT_STRING,0,shake,strlen(shake)}};
            assert(!dw4_hubruntime_sd(h,sv,5,&r,error,sizeof error));
            int moved=0;
            for(unsigned i=0;i<64;i++){run(h,&frame,1,0,0);assert(!dw4_lobby_control(dw4_hubruntime_world(h),&c1));
                for(unsigned e=12;e<15;e++)if(fabsf(c1.camera_world[e]-rest[e])>0.01f)moved=1;}
            assert(moved);
            run(h,&frame,12,0,0);assert(!dw4_lobby_control(dw4_hubruntime_world(h),&c1));
            for(unsigned e=12;e<15;e++)assert(fabsf(c1.camera_world[e]-rest[e])<0.5f);   /* the player stood still, so only the shake moved the rig */
            fprintf(stderr,"dng102b3: CAMERA SHAKE moved the box camera and released it\n");
        }
        printf("dungeon %s: control after %u ticks, %u camera regions, %zu generators (%u started), %u enemy models, %u save points, player %g %g %g\n",floor_stage,until,info.camera_regions,dw4_fieldgen_count(g),started,enemies,saves,w.position[0],w.position[1],w.position[2]);
        return 0;
    }
    if(!strcmp(mode,"enemyfall")) {
        /* Enemies fall off ledges that have no wall (owner-reported, not a retail trace; findings #3107-#3110): no floor edge holds a walking or hopping enemy, the
         * floor query's support drives the retail floor response (3926d0: unsupported and not rising or falling -> SQ_FALL, a landing ends the fall), and the wall infos
         * of the enemy's check flag (kind 2, 8, 0x802, the dynamic 0x402 props) keep it where retail has walls.
         * dng102b3: a corridor (x 370..390, kind-2 walls on both sides, void beyond) whose y 35 walkway ends at z -126 in a drop to the y 10 floor, no wall across it.
         * stag0001: the practice arena is a floating square closed by kind-0x802 walls only. stag0101: live bushes and rocks (kind 0x402 props) block an enemy. */
        pilot_confirm=1;
        if(!getenv("FIXLEVEL"))setenv("FIXLEVEL","60",1);
        const int fl[]={2,355,503};
        unsigned until;
        /* every shipped enemy pack (KIND_ENEMY e_*) has the SQ_FALL the response starts */
        {   unsigned models=0;
            for(int pt=0;pt<mount.nparts;pt++)for(uint32_t entry=0;entry<mount.parts[pt].count;entry++){
                uint32_t size=0,bytes=0;const uint8_t *blob=dw4_mount_entry(&mount,pt,(int)entry,&size,&bytes);if(!blob || size<64)continue;
                dw4_igb g={0};if(dw4_igb_open(&g,blob,size,0))continue;
                if(dw4_igb_refs_open(&g) || !g.id_kind){dw4_igb_close(&g);continue;}
                for(uint32_t i=0;i<g.table_n;i++){
                    dw4_igb_record r={0};if(g.id_kind[i]!=2 || !dw4_igb_decode(&g,g.id_off[i],&r))continue;
                    int enemy=!strcmp(r.class_name,"beModelCtrlInfo") && r.name && !strncmp(r.name,"e_",2);char name[64]="";if(enemy)snprintf(name,sizeof name,"%s",r.name);
                    dw4_igb_record_free(&r);if(!enemy)continue;
                    dw4_modelctrl *c=dw4_modelctrl_open_info(&g,i);if(!c)continue;
                    if(!dw4_modelctrl_has_sequence(c,"SQ_FALL")){fprintf(stderr,"%s has no SQ_FALL\n",name);return 1;}
                    models++;dw4_modelctrl_close(c);
                }
                dw4_igb_close(&g);
            }
            fprintf(stderr,"enemyfall: %u e_* model infos, every one has SQ_FALL\n",models);assert(models>=31);
        }
        setenv("STAGE","dng102b3",1);h=enter(&mount,fl,3);unsetenv("STAGE");
        for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        run(h,&frame,600,0,0);assert(control(h));
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
        int32_t mhp=0;
        {   int lvl=atoi(getenv("FIXLEVEL"));int32_t mmp=0;
            assert(!dw4_property_set_number(p0,"LEVEL",lvl) && !dw4_playerstats_recalculate((void *)dw4_hubruntime_databases(h),p0));
            assert(!dw4_property_number(p0,"MHP",&mhp) && !dw4_property_number(p0,"MMP",&mmp) && !dw4_property_set_number(p0,"HP",mhp) && !dw4_property_set_number(p0,"MP",mmp));}
        const char *trace_env=getenv("EFTRACE");int trace=trace_env?atoi(trace_env):0;
        struct ef_obs o;int32_t slot=-1;
        for(int32_t k=0;k<64;k++)if(dw4_controllers_live(dw4_hubruntime_models(h),"e_mecha1",k)>=0)slot=k;   /* the last receiver: the generators fill the low ones */
        assert(slot>=6);fprintf(stderr,"enemyfall: e_mecha1 slot %d\n",slot);
        const float lower[3]={378,10,-95};
        /* 1. walks off: the AI chases the player standing on the lower floor, down the corridor; no wall stops it at the end of the walkway */
        ef_follow(h,&frame,p0,mhp,"e_mecha1",slot,(float[]){378,35,-150},0,0,lower,900,&o,trace);
        fprintf(stderr,"walk off the ledge: %u ticks, y %.2f..%.2f, ends %s at %.2f %.2f %.2f, SQ_FALL seen %d\n",o.ticks,o.miny,o.maxy,o.last_seq,o.last[0],o.last[1],o.last[2],o.sq_fall);
        assert(o.sq_fall && o.maxy<35.5f && fabsf(o.last[1]-10)<.05f && o.last[2]>-126 && !strcmp(o.last_seq,"SQ_WAIT"));   /* it fell, landed on the y 10 floor beyond the drop and went on to SQ_WAIT */
        /* 2. the knockback hop (SQ_DDMG: Back, Jump, Fall, Landing twice) carries a victim over the same edge: it lands on the floor below, no edge holds it */
        ef_follow(h,&frame,p0,mhp,"e_mecha1",slot,(float[]){378,35,-135},180,1,lower,400,&o,trace);
        fprintf(stderr,"hop over the ledge: %u ticks, y %.2f..%.2f, ends at %.2f %.2f %.2f (%s)\n",o.ticks,o.miny,o.maxy,o.last[0],o.last[1],o.last[2],o.ended?"instance ended":"still running");
        assert(o.ended && o.miny<10.5f && o.last[2]>-126 && fabsf(o.last[1]-10)<.05f);
        /* 3. the same hop sideways into the corridor's kind-2 wall: the wall stops the victim on the walkway, it does not fall into the void beyond */
        ef_follow(h,&frame,p0,mhp,"e_mecha1",slot,(float[]){380,35,-150},90,1,lower,400,&o,trace);
        fprintf(stderr,"hop against the kind-2 wall: %u ticks, y %.2f..%.2f, x %.2f..%.2f, ends at %.2f %.2f %.2f (%s)\n",o.ticks,o.miny,o.maxy,o.minx,o.maxx,o.last[0],o.last[1],o.last[2],o.ended?"instance ended":"still running");
        assert(o.ended && o.miny>34.95f && o.minx>371 && !o.sq_fall);
        dw4_hubruntime_close(h);
        /* 4. the practice arena's boundary is kind-0x802 walls (the kind-2 graphs have two triangles): the same sideways hop from beside the east wall is stopped at it. The
         * floor runs on past the wall, so without the 0x802 walls the victim would slide through to x 108 and carry on to the floor's end. */
        setenv("STAGE","stag0001",1);h=enter(&mount,NULL,0);unsetenv("STAGE");
        for(until=0;until<6000 && !(until>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)));until++){   /* the introduction's messages are confirmed with Cross */
            dw4_hubruntime_input(h,0,0,0,0,until%45==44?0x4000:0);
            if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
        }
        assert(until<6000);run(h,&frame,60,0,0);
        p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);assert(!dw4_property_number(p0,"MHP",&mhp));
        slot=-1;for(int32_t k=0;k<64;k++)if(dw4_controllers_live(dw4_hubruntime_models(h),"e_goburi",k)>=0)slot=k;
        assert(slot>=1);
        ef_follow(h,&frame,p0,mhp,"e_goburi",slot,(float[]){92,10,60},270,1,(float[]){0,10,60},400,&o,trace);
        fprintf(stderr,"hop against the 0x802 arena wall: %u ticks, x %.2f..%.2f, y %.2f..%.2f, ends at %.2f %.2f %.2f (%s)\n",o.ticks,o.minx,o.maxx,o.miny,o.maxy,o.last[0],o.last[1],o.last[2],o.ended?"instance ended":"still running");
        assert(o.ended && o.maxx<104 && o.miny>9.95f && !o.sq_fall);   /* 108.3 without the walls: the unobstructed slide is 16.35 units */
        dw4_hubruntime_close(h);
        /* 5. props (kind-0x402 dynamic walls) block an enemy while their model instance runs, like the player's (mode propwalls): the valley's bush and rock, the AI
         * chasing a player who stands behind the prop. The proxy is a 10 unit box, so the enemy (half width 3, r = 4.26) stops about 9.3 from the centre; without the
         * props it walks through the centre (the bush is met head on: its centre is passed within 3 units when nothing blocks). */
        h=enter(&mount,fl,3);
        for(until=0;until<5000 && !control(h);until++)run(h,&frame,1,0,0);
        run(h,&frame,300,0,0);assert(control(h));
        p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);assert(!dw4_property_number(p0,"MHP",&mhp));
        slot=-1;for(int32_t k=0;k<64;k++)if(dw4_controllers_live(dw4_hubruntime_models(h),"e_goburi",k)>=0)slot=k;
        assert(slot>=1);
        static const struct {const char *name;int32_t slot;float dx,dz;} props[]={{"g_bush01z01",4,-1,0},{"g_rock02z01",1,0,-1}};
        for(unsigned q=0;q<sizeof props/sizeof *props;q++){
            const dw4_modelctrl *pm=ef_find(h,props[q].name,props[q].slot);assert(pm && dw4_modelctrl_active(pm));
            dw4_modelctrl_actor pa;dw4_modelctrl_actor_state(pm,&pa);
            float at[3]={pa.position[0]+24*props[q].dx,pa.position[1],pa.position[2]+24*props[q].dz};
            float player[3]={pa.position[0]-16*props[q].dx,pa.position[1],pa.position[2]-16*props[q].dz};
            float yaw=atan2f(-props[q].dx,-props[q].dz)*57.29578f;
            o.focus[0]=pa.position[0];o.focus[1]=pa.position[2];
            ef_follow(h,&frame,p0,mhp,"e_goburi",slot,at,yaw,0,player,300,&o,trace);
            fprintf(stderr,"%s[%d] live: the enemy came no nearer than %.2f to the centre (%.1f %.1f), ends %.1f %.1f\n",props[q].name,props[q].slot,o.nearest,pa.position[0],pa.position[2],o.last[0],o.last[2]);
            assert(o.nearest>=8.5f);   /* stopped at the box: 4.26 + 5 from the centre, a little more on a diagonal approach */
        }
        dw4_hubruntime_close(h);
        printf("enemy fall: an unprotected ledge drops a walking and a hopping enemy to the floor below (SQ_FALL, landing), kind-2 and 0x802 walls hold them, props block the chase, every e_* pack has SQ_FALL\n");
        return 0;
    }
    if(!strcmp(mode,"startmenu")) {
        /* The Start (STATUS) menu of a dungeon floor (dng101b1): Start opens the status screen once control is back, with enemies alive; the world is frozen while it is open
         * (no enemy moves, no wave spawns, the generators' clock stops) and runs on after Circle closes it. The practice stage has none (no beNDMWStatusInfo). */
        const int fl[]={2,355,503};
        setenv("STAGE","dng101b1",1);h=enter(&mount,fl,3);unsetenv("STAGE");
        unsigned until=0;for(;until<4000 && !control(h);until++)run(h,&frame,1,0,0);
        assert(control(h));
        {float lo[3],hi[3];char where[96];mat_region(&mount,"dng101b1","matg01",lo,hi);
         snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",(lo[0]+hi[0])/2,lo[1]+20,(lo[2]+hi[2])/2);place(h,where);}
        run(h,&frame,150,0,0);
        for(unsigned cycle=0;cycle<2;cycle++) {
            float before=0,open=0,held=0,after=0;unsigned n0=0,n1=0,n2=0;
            #define ENEMIES(n,sum) do{n=0;sum=0;for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot); \
                if(mc && info && !strncmp(dw4_stageobject_name(info),"e_",2) && dw4_modelctrl_active(mc)){dw4_modelctrl_actor ea;dw4_modelctrl_actor_state(mc,&ea);n++;sum+=ea.position[0]+ea.position[1]+ea.position[2];}}}while(0)
            ENEMIES(n0,before);assert(n0>0);
            dw4_hubruntime_input(h,0,0,0,0,8);assert(!dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60));
            for(unsigned t=0;t<300 && dw4_hubruntime_status_active(h)!=2;t++)run(h,&frame,1,0,0);
            if(dw4_hubruntime_status_active(h)!=2){fprintf(stderr,"Start in dng101b1: status phase %d (%s)\n",dw4_hubruntime_status_active(h),dw4_hubruntime_error(h));assert(0);}
            ENEMIES(n1,open);
            const dw4_fieldgen *g=dw4_hubruntime_fieldgen(h);unsigned spawned=dw4_fieldgen_spawned(g);
            run(h,&frame,200,0,0);
            ENEMIES(n2,held);unsigned spawned2=dw4_fieldgen_spawned(g);
            fprintf(stderr,"  cycle %u: %u enemies at Start, %u when open, %u after 200 ticks (position sums %.2f %.2f %.2f); spawned %u -> %u\n",cycle,n0,n1,n2,before,open,held,spawned,spawned2);
            assert(n2==n1 && fabsf(held-open)<0.01f && spawned2==spawned);
            {dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));assert(dw4_hubruntime_draw(h,&fb,NULL)>0);if(getenv("STARTSHOT")&&!cycle)assert(!dw4_png_write(getenv("STARTSHOT"),fb.rgba,fb.w,fb.h));dw4_fb_free(&fb);}
            dw4_hubruntime_input(h,0,0,0,0,0x2000);assert(!dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60));
            for(unsigned t=0;t<300 && dw4_hubruntime_status_active(h);t++)run(h,&frame,1,0,0);
            assert(!dw4_hubruntime_status_active(h));
            run(h,&frame,90,0,0);
            unsigned n3;ENEMIES(n3,after);
            assert(n3>0 && fabsf(after-held)>0.001f);   /* the world runs on after it closes */
            #undef ENEMIES
        }
        dw4_hubruntime_close(h);
        puts("field Start menu: dng101b1 opens the status screen with the world frozen and closes it with Circle");
        return 0;
    }
    if(!strcmp(mode,"propwalls")) {
        /* Retail's dynamic wall infos (beHitLandModelInfo kind 0x402, FUN_00388640): a prop is solid for a model whose check flag selects them (the player's 7)
         * exactly while its model instance runs. The Valley entrance (stag0101) generates its bushes, rocks and boxes from the stage script. The stick is held
         * toward a prop from 24 units away: the live prop stops the player at its proxy box (a 10 unit cube, so about 9.3 from the centre; without the walls the
         * player walks through the centre), and once the script has erased it the same walk goes through. A slot the script never generated keeps its authored
         * preview matrix, (15*i,0,0): it must be no wall. */
        h=enter(&mount,NULL,0);unsigned until=0;
        for(;until<5000 && !control(h);until++)run(h,&frame,1,0,0);
        run(h,&frame,120,0,0);
        static const struct {const char *name;int32_t slot;unsigned dir;float lo,hi;} walls[]={
            {"g_bush01z01",4,6,8.5f,12},{"g_bush01z01",4,5,8.5f,12},{"g_rock02z01",1,2,10,16},{"g_rock02z01",1,6,10,16},{"g_bush01z01",7,6,8.5f,12}};
        float centre[sizeof walls/sizeof *walls][3];
        for(unsigned pass=0;pass<2;pass++){
            if(pass){   /* erase the two bushes of the first trial: SQ_ERAS ends in REMOVE, the instance goes inactive */
                for(int32_t slot=4;slot<=5;slot++){
                    char error[256];dw4_script_value r,a[4]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"g_bush01z01",11},{DW4_SCRIPT_NUMBER,slot,NULL,0},{DW4_SCRIPT_STRING,0,"SQ_ERAS",7}};
                    assert(!dw4_hubruntime_sd(h,a,4,&r,error,sizeof error));
                }
                for(unsigned t=0;t<300 && (dw4_controllers_live(dw4_hubruntime_models(h),"g_bush01z01",4)>0 || dw4_controllers_live(dw4_hubruntime_models(h),"g_bush01z01",5)>0);t++)run(h,&frame,1,0,0);
                assert(dw4_controllers_live(dw4_hubruntime_models(h),"g_bush01z01",4)==0 && dw4_controllers_live(dw4_hubruntime_models(h),"g_bush01z01",5)==0);
            }
            for(unsigned q=0;q<(pass?2u:sizeof walls/sizeof *walls);q++){
                const dw4_modelctrl *mc=NULL;
                for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *m=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
                    if(m && info && slot==walls[q].slot && !strcmp(dw4_stageobject_name(info),walls[q].name))mc=m;}
                assert(mc);
                if(!pass){assert(dw4_modelctrl_active(mc));dw4_modelctrl_actor a;dw4_modelctrl_actor_state(mc,&a);memcpy(centre[q],a.position,12);}
                float ax=sinf(walls[q].dir*0.785398f),az=cosf(walls[q].dir*0.785398f);
                char where[96];snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",centre[q][0]+24*ax,centre[q][1],centre[q][2]+24*az);place(h,where);run(h,&frame,20,0,0);
                dw4_lobby_walk_state w;assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w));
                assert(fabsf(w.position[1]-centre[q][1])<3);   /* standing on the floor beside the prop */
                float mind=1e9f;
                for(unsigned t=0;t<(pass?240u:120u);t++){
                    dw4_lobby_control_state c;assert(!dw4_lobby_control(dw4_hubruntime_world(h),&c));assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w));
                    float dx=centre[q][0]-w.position[0],dz=centre[q][2]-w.position[2];float d=sqrtf(dx*dx+dz*dz);if(d<mind)mind=d;
                    float yaw=atan2f(dx,dz)-atan2f(c.camera_world[8],c.camera_world[10]);
                    dw4_hubruntime_input(h,sinf(yaw),-cosf(yaw),0,0,0);
                    if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));return 1;}
                }
                assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w));
                fprintf(stderr,"%s[%d] at %.1f %.1f %.1f, approached from direction %u (%s): closest %.2f, ended at %.1f %.1f %.1f\n",walls[q].name,walls[q].slot,centre[q][0],centre[q][1],centre[q][2],walls[q].dir,pass?"erased":"live",mind,w.position[0],w.position[1],w.position[2]);
                if(pass)assert(mind<4);                       /* the erased prop is no wall: the walk goes through its centre */
                else assert(mind>=walls[q].lo && mind<=walls[q].hi);   /* a live prop stops the player at its box */
            }
        }
        /* The slots the script never generated stand at the authored preview matrices (15*i,0,0): no ghost walls there, while a live prop's face is solid. */
        dw4_lobby *world=dw4_hubruntime_world(h);
        for(int32_t slot=12;slot<20;slot++){
            assert(dw4_controllers_live(dw4_hubruntime_models(h),"g_bush01z01",slot)==0);
            float old[3]={15.0f*slot-9,1,0},pos[3]={15.0f*slot-1,1,0};
            assert(!(dw4_lobby_walk_probe(world,old,pos)&1));
        }
        assert(dw4_controllers_live(dw4_hubruntime_models(h),"g_rock02z01",1)>0);   /* the control: a step into the live rock02[1] (centre -30, 90) is stopped */
        {float old[3]={-50,50,90},pos[3]={-42,50,90};assert(dw4_lobby_walk_probe(world,old,pos)&1);}
        dw4_hubruntime_close(h);
        printf("prop walls: live bushes and rocks stop the player at their proxy boxes, an erased prop and the never generated slots do not\n");
        return 0;
    }
    if(!strcmp(mode,"hitgraph")) {   /* diagnostic: the static collision graphs of a stage (STAGE), their nodes and triangle spans */
        dw4_igfile file={0};dw4_scene sc;const char *st=getenv("STAGE")?getenv("STAGE"):"dng101b1";
        assert(!dw4_igfile_open_stage_pack(&file,&mount,st,0,0) && !dw4_scene_load_world(&sc,file.data,file.len));
        for(unsigned k=0;k<sc.ncollision;k++){
            const dw4_scene_collision *g=sc.collision+k;
            fprintf(stderr,"collision %u: info %u kind %u root node %u\n",k,g->info_id,g->kind,g->node);
            for(unsigned i=g->node;i<sc.nnode && (i==g->node || sc.node[i].depth>sc.node[g->node].depth);i++){
                uint32_t mi=dw4_scene_node_mesh(&sc,i);
                fprintf(stderr,"   node %u depth %u class %s name %s mesh %s",i,sc.node[i].depth,sc.node[i].class_name?sc.node[i].class_name:"-",sc.node[i].name?sc.node[i].name:"-",mi==UINT32_MAX?"no":"yes");
                if(mi!=UINT32_MAX){float world[16];const float *p=dw4_scene_host(&sc,sc.mesh[mi].positions);
                    if(!dw4_scene_node_world(&sc,i,world) && p){float lo[3]={1e9f,1e9f,1e9f},hi[3]={-1e9f,-1e9f,-1e9f};
                        for(uint32_t v=0;v<sc.mesh[mi].num_verts;v++)for(unsigned a=0;a<3;a++){float x=p[3*v]*world[a]+p[3*v+1]*world[4+a]+p[3*v+2]*world[8+a]+world[12+a];if(x<lo[a])lo[a]=x;if(x>hi[a])hi[a]=x;}
                        fprintf(stderr," verts %u box (%.0f %.0f %.0f)-(%.0f %.0f %.0f)",sc.mesh[mi].num_verts,lo[0],lo[1],lo[2],hi[0],hi[1],hi[2]);}}
                fputc(10,stderr);}
        }
        return 0;
    }
    if(!strcmp(mode,"dungeondoors")) {
        /* The Humid Cave walked with the stick alone (no MOVETRANS inside the floors, exits included): a breadth-first route over the live walking
         * collision, the pad pointed at the next cell every tick under the camera of that tick, Cross for what blocks the way. The doors are proved by
         * walking. (1) A closed door: the far side is unreachable in the route, and pushing into the door for 120 ticks leaves the player on the near
         * side with a wall push on almost every tick. (2) The floor script opens it (flag set, its collision mesh removed, fewer wall triangles) and the
         * same walk crosses. (5) The boss door closes behind the player at Blossomon's intro and opens on the kill. (6) The button door opens by a
         * swing at g_dbutton1. FLOOR2=1 starts on the second floor (the hop from the first floor is placed); FLOORS=1 stops after the first. */
        pilot_confirm=1;
        const int fl[]={2,355,503};h=enter(&mount,fl,3);
        unsigned until=0;
        for(;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        h=take_exit(&mount,h,&frame,"stag0101","matz00","dng101b1",0);
        for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        run(h,&frame,600,0,0);assert(control(h));
        if(getenv("FLOOR2")){h=take_exit(&mount,h,&frame,"dng101b1","matz02","dng101b2",0);for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);run(h,&frame,600,0,0);assert(control(h));}
        {   dw4_property_folder *pq=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);int32_t mhp=0,mmp=0;
            assert(!dw4_property_set_number(pq,"LEVEL",40) && !dw4_playerstats_recalculate((void *)dw4_hubruntime_databases(h),pq));
            assert(!dw4_property_number(pq,"MHP",&mhp) && !dw4_property_number(pq,"MMP",&mmp) && !dw4_property_set_number(pq,"HP",mhp) && !dw4_property_set_number(pq,"MP",mmp));}
        if(getenv("DBGEXIT")){   /* development aid: open the doors, stand before the exit and walk into it */
            dw4_lobby *wd=dw4_hubruntime_world(h);for(unsigned d=1;d<=3;d++){char n[16];snprintf(n,sizeof n,"doorwall%02u",d);dw4_lobby_collision_hit(wd,n,0);}
            place(h,"V<216,40,-360>/V<0,0,0>");run(h,&frame,60,0,0);
            float lo[3],hi[3],gap=0;mat_region(&mount,"dng101b1","matz02",lo,hi);
            int ok=walk_box(h,&frame,lo[0]+3,hi[0]-3,lo[2]+3,hi[2]-3,3000,1,&gap);float pp[3];player_pos(h,pp);
            fprintf(stderr,"debug exit walk: %d at %.1f %.1f %.1f, gap %.1f\n",ok,pp[0],pp[1],pp[2],gap);return 0;}
        static const char *const regs1[]={"matg01","matg02","matg03","matg04","matg05","matg06","matg07"};
        static const char *const regs2[]={"matg01","matg02","matg03","matg04","matg05","matg06","matg07","matg08"};
        exit_by_stick=1;
        unsigned total_pushed=0,total_crossed=0;
        for(unsigned f=getenv("FLOOR2")?1:0;f<(getenv("FLOORS")?1u:2u);f++){
            const char *floor_stage=f?"dng101b2":"dng101b1";
            struct door doors1[]={{"doorwall01",-180,-20,102},{"doorwall02",120,-320,106},{"doorwall03",220,-380,106}};
            struct door doors2[]={{"doorwall01",-580,-40,112},{"doorwall02",-300,-40,113},{"doorwall03",-220,-160,128},{"doorwall04",220,-240,118},{"doorwall05",540,-240,-1},{"doorwall06",740,-240,119}};
            struct door *doors=f?doors2:doors1;unsigned ndoors=f?6:3;const char *const *regs=f?regs2:regs1;unsigned nregs=f?8:7;
            dw4_lobby *wd=dw4_hubruntime_world(h);
            const uint8_t *fb=dw4_property_bytes(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0),"FLAG",NULL);
            dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
            fprintf(stderr,"== %s ==\n",floor_stage);
            for(unsigned d=0;d<ndoors;d++)assert(dw4_lobby_hit_state(wd,doors[d].name)==(doors[d].flag<0?0:flagnow(h)[doors[d].flag]?0:1));   /* the names resolve in a dungeon pack; a clear flag means a solid door */
            assert(dw4_hubruntime_hitland_missing(h)==0);
            for(unsigned pass=0;pass<4;pass++){
                int pending=0;for(unsigned d=0;d<ndoors;d++)pending|=doors[d].tested==1 && !flagnow(h)[doors[d].flag];
                if(pass && !pending)break;
                for(unsigned r=0;r<nregs;r++){
                    if(pass && r==nregs-1 && f)continue;   /* the arena is entered once */
                    if(f){int32_t cur=0,top=0;assert(!dw4_property_number(p0,"HP",&cur) && !dw4_property_number(p0,"MHP",&top));
                        if(cur<top*6/10){float lo[3],hi[3],gap=0;mat_region(&mount,floor_stage,"matc02",lo,hi);walk_box(h,&frame,lo[0]+4,hi[0]-4,lo[2]+4,hi[2]-4,5000,0,&gap);for(unsigned t=0;t<120;t++)wtick(h,&frame,0,0,0,0);}}   /* the heal circle beside the boss door */
                    float lo[3],hi[3],gap=0;mat_region(&mount,floor_stage,regs[r],lo,hi);
                    int ok=walk_box(h,&frame,lo[0]+4,hi[0]-4,lo[2]+4,hi[2]-4,6000,1,&gap);
                    for(unsigned retry=0;!ok && retry<5;retry++){   /* a door still shuts the way: fight on where the player stands until the wave opens it */
                        hunt(h,&frame,6000);doors_settle(h,&frame,doors,ndoors,fb,&total_crossed);
                        ok=walk_box(h,&frame,lo[0]+4,hi[0]-4,lo[2]+4,hi[2]-4,6000,1,&gap);}
                    float pp[3];player_pos(h,pp);
                    fprintf(stderr,"region %s: %s (player %.0f %.0f, gap %.0f, %u ticks so far, %u wall-contact ticks, max step %.2f, %u kills)\n",regs[r],ok?"walked in":"NOT reachable",pp[0],pp[2],gap,wstat.ticks,wstat.wall_ticks,wstat.max_step,wstat.kills);
                    assert(ok);
                    if(f && r==7 && !pass){   /* the arena: the intro runs, the boss door closes behind the player */
                        struct door *bd=doors+4;
                        for(unsigned t=0;t<3000 && dw4_lobby_hit_state(wd,bd->name)!=1;t++){if(control(h))wtick(h,&frame,0,0,0,0);else wtick(h,&frame,0,0,t%90<4?0x4000:0,t%90==0?0x4000:0);}
                        fprintf(stderr,"  boss intro: %s hit state %d after the intro\n",bd->name,dw4_lobby_hit_state(wd,bd->name));
                        assert(dw4_lobby_hit_state(wd,bd->name)==1);
                        for(unsigned t=0;t<600 && !control(h);t++)wtick(h,&frame,0,0,t%90<4?0x4000:0,t%90==0?0x4000:0);
                        if(door_probe(h,bd))door_push(h,&frame,bd);   /* (5) the boss door holds the player in */
                        if(door_probe(h,doors+5))door_push(h,&frame,doors+5);   /* the exit door is solid until the kill */
                        {   /* Blossomon itself: keep at it (the generic hunt gives up on an enemy it cannot finish in one go) */
                            long bk=-1;for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
                                if(mc && info && !strcmp(dw4_stageobject_name(info),"e_blosso"))bk=(long)k;}
                            assert(bk>=0);float bp3[3];unsigned t0=wstat.ticks;
                            while(wstat.ticks-t0<40000 && enemy_alive(h,bk,bp3)){
                                int32_t hp=0;if(dw4_property_number(p0,"HP",&hp) || hp<=0)break;
                                if(!control(h)){wtick(h,&frame,0,0,0,0);continue;}
                                stick_fight(h,&frame,bk,1500);}
                            fprintf(stderr,"  Blossomon %s after %u ticks\n",enemy_alive(h,bk,bp3)?"still up":"down",wstat.ticks-t0);}
                        hunt(h,&frame,20000);
                        for(unsigned t=0;t<900 && dw4_lobby_hit_state(wd,bd->name)!=0;t++)wtick(h,&frame,0,0,0,0);
                        if(doors[5].tested==1){for(unsigned t=0;t<900 && dw4_lobby_hit_state(wd,doors[5].name)!=0;t++)wtick(h,&frame,0,0,0,0);door_cross(h,&frame,doors+5,fb);total_crossed++;}
                        fprintf(stderr,"  boss down: flag 119 %d, %s %d, %s %d\n",flagnow(h)[119],bd->name,dw4_lobby_hit_state(wd,bd->name),doors[5].name,dw4_lobby_hit_state(wd,doors[5].name));
                        assert(flagnow(h)[119] && dw4_lobby_hit_state(wd,bd->name)==0);
                        bd->tested=2;total_crossed++;
                        continue;
                    }
                    for(unsigned d=0;d<(f?4u:ndoors);d++)if(!doors[d].tested && doors[d].flag>=0 && !flagnow(h)[doors[d].flag] && door_probe(h,doors+d)){
                        door_push(h,&frame,doors+d);if(doors[d].tested!=1)continue;
                        if(getenv("FIRSTDOOR")){printf("dungeon doors: %s held closed under a 120-tick stick push on the near side (%u wall-contact ticks over %u ticks, max step %.2f, hitland_missing %u)\n",doors[d].name,wstat.wall_ticks,wstat.ticks,wstat.max_step,dw4_hubruntime_hitland_missing(h));assert(wstat.max_step<5.0f && dw4_hubruntime_hitland_missing(h)==0);return 0;}
                        if(f && d==2){   /* the button door: a swing at g_dbutton1 sets flag 128 */
                            for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){
                                const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
                                if(mc && info && !flagnow(h)[128] && !strcmp(dw4_stageobject_name(info),"g_dbutton1")){dw4_modelctrl_actor ba;dw4_modelctrl_actor_state(mc,&ba);if(ba.position[0]!=0||ba.position[2]!=0)hit_target(h,&frame,ba.position,fb,128);}}
                            fprintf(stderr,"  button g_dbutton1: flag 128 = %d\n",flagnow(h)[128]);
                        }
                    }
                    hunt(h,&frame,pass?6000:3500);   /* fight what the region sends, as a player does (the wave-cleared flags open the doors) */
                    doors_settle(h,&frame,doors,ndoors,fb,&total_crossed);
                }
            }
            unsigned crossed=0,pushed=0,early=0;for(unsigned d=0;d<ndoors;d++){crossed+=doors[d].tested==2;pushed+=doors[d].tested==1||doors[d].tested==2;early+=doors[d].tested>=3;}
            total_pushed+=pushed;
            fprintf(stderr,"%s: doors pushed closed %u, crossed open %u, opened by the wave before the player arrived %u (of %u); flags 101-128:",floor_stage,pushed,crossed,early,ndoors);for(unsigned x=101;x<=128;x++)if(flagnow(h)[x])fprintf(stderr," %u",x);fputc(10,stderr);
            assert(pushed+early==ndoors && crossed==pushed && pushed>=2 && (!f || doors[4].tested==2) && dw4_hubruntime_hitland_missing(h)==0);
            h=take_exit(&mount,h,&frame,floor_stage,"matz02",f?"stagML11":"dng101b2",0);
            for(until=0;until<4000 && !control(h);until++){dw4_hubruntime_input(h,0,0,0,until%90<4?0x4000:0,until%90==0?0x4000:0);dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60);}
            if(!f){run(h,&frame,600,0,0);assert(control(h));}
            else{dw4_lobby_world_state wi;assert(!dw4_lobby_world_info(dw4_hubruntime_world(h),&wi) && !strcmp(wi.stage,"stagML11") && control(h));}   /* back at the Terminal */
        }
        assert(wstat.max_step<5.0f);
        printf("dungeon doors: Humid Cave walked by stick (no placement inside the floors), %u doors held closed under a 120-tick push, %u crossed once open, %u kills, max step %.2f, %u wall-contact ticks, %u scripted placements\n",total_pushed,total_crossed,wstat.kills,wstat.max_step,wstat.wall_ticks,wstat.placed);
        return 0;
    }
    if(!strcmp(mode,"dungeondoors2")) {
        /* The second dungeon (dng102b1..b3) walked with the stick alone, like `dungeondoors` does for the Humid Cave: no MOVETRANS inside the floors, exits
         * included (exit_by_stick). Per floor the wave regions matg01.. are walked in order (hunt fights what spawns; doors_settle asserts every closed
         * door is solid while its flag is clear); every door met closed is probed (door_probe: the far side is reachable only with the door switched off),
         * pushed for 120 ticks (door_push) and, once the floor script opens it, crossed (door_cross). Button doors open by a swing at g_dbutton1 (hit_target;
         * btn[] is the button's ram number, bfl[] the flag its swing sets; ram 2 of dng102b3 starts the wave that opens doorwall08). dng102b3: the route walks
         * off a 25-unit ledge into the damage-floor room (plan_drop), Mammothmon's intro closes doorwall09, the kill (flag 150) opens doorwall09/10 and
         * doorwall10 lies between the arena and the exit. FLOOR=<dng102bN> runs that floor alone (default: all three in sequence; the first is opened directly,
         * stag0102 is not ported); FIXLEVEL (default 60) is the starter's level on every floor; FIRSTDOOR=1 stops after the first door held closed.
         * Development aids: DUMPPLAN=x0,x1,z0,z1 prints the reachable cells when a region cannot be reached (DUMPPROBE=x,z adds 2-unit probes south of that cell),
         * ARENADIRECT=1 starts dng102b3 in Mammothmon's arena, BOSSSTICK=<ticks> is the pure-stick budget of the boss fight. */
        pilot_confirm=1;exit_by_stick=1;plan_drop=0;
        static const char *const fnames[3]={"dng102b1","dng102b2","dng102b3"};
        static const unsigned nwaves[3]={8,12,11};
        unsigned f0=0,f1=3;
        if(getenv("FLOOR")){f0=3;for(unsigned i=0;i<3;i++)if(!strcmp(getenv("FLOOR"),fnames[i])){f0=i;f1=i+1;}assert(f0<3);}
        const int fl[]={2,355,503};setenv("STAGE",fnames[f0],1);h=enter(&mount,fl,3);unsetenv("STAGE");
        unsigned until=0;
        for(;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        run(h,&frame,600,0,0);assert(control(h));
        unsigned total_pushed=0,total_crossed=0,total_early=0,total_buttons=0,boss_places=0;
        for(unsigned f=f0;f<f1;f++){
            const char *floor_stage=fnames[f];
            plan_drop=f==2?100.0f:0.0f;
            boss_atck3.on=f==2;boss_atck3.run=boss_atck3.runs=boss_atck3.first=boss_atck3.clean=0;
            {   dw4_property_folder *pq=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);int32_t mhp=0,mmp=0;int lvl=getenv("FIXLEVEL")?atoi(getenv("FIXLEVEL")):60;
                assert(!dw4_property_set_number(pq,"LEVEL",lvl) && !dw4_playerstats_recalculate((void *)dw4_hubruntime_databases(h),pq));
                assert(!dw4_property_number(pq,"MHP",&mhp) && !dw4_property_number(pq,"MMP",&mmp) && !dw4_property_set_number(pq,"HP",mhp) && !dw4_property_set_number(pq,"MP",mmp));}
            struct door d1[]={{"doorwall01",120,240,101},{"doorwall02",-100,180,113},{"doorwall03",60,-180,104},{"doorwall04",-220,-180,114},{"doorwall05",-280,-480,108}};
            struct door d2[]={{"doorwall01",-160,-160,117},{"doorwall02",-60,-60,136},{"doorwall03",-260,-60,136},{"doorwall04",80,-200,118},{"doorwall05",240,-560,137},{"doorwall06",-260,500,126},{"doorwall07",-160,560,138}};
            struct door d3[]={{"doorwall01",540,-260,140},{"doorwall02",440,-160,140},{"doorwall03",340,258,141},{"doorwall04",522,360,144},{"doorwall05",-40,40,167},{"doorwall06",-40,120,147},{"doorwall07",-300,-18,168},{"doorwall08",-358,120,149},{"doorwall09",-560,120,-1},{"doorwall10",-760,120,150}};
            static const int bt1[]={-1,0,-1,1,-1},bt2[]={-1,0,-1,-1,1,-1,2},bt3[]={-1,-1,-1,-1,0,-1,1,2,-1,-1};   /* the g_dbutton1 ram number that opens (or, ram 2 of dng102b3, starts the wave that opens) the door, or -1 */
            static const int bf1[]={0,113,0,114,0},bf2[]={0,136,0,0,137,0,138},bf3[]={0,0,0,0,167,0,168,169,0,0};   /* the flag that button's swing sets */
            struct door *doors=f==0?d1:f==1?d2:d3;const unsigned ndoors=f==0?5:f==1?7:10;const int *btn=f==0?bt1:f==1?bt2:bt3,*bfl=f==0?bf1:f==1?bf2:bf3;
            const unsigned npush=f==2?8:ndoors;   /* dng102b3: doorwall09/10 belong to the boss arena */
            dw4_lobby *wd=dw4_hubruntime_world(h);
            const uint8_t *fb=dw4_property_bytes(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0),"FLAG",NULL);
            dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
            fprintf(stderr,"== %s ==\n",floor_stage);
            for(unsigned d=0;d<ndoors;d++){int st=dw4_lobby_hit_state(wd,doors[d].name);fprintf(stderr,"  %s hit state %d (flag %d)\n",doors[d].name,st,doors[d].flag);}
            for(unsigned d=0;d<ndoors;d++)assert(dw4_lobby_hit_state(wd,doors[d].name)==(doors[d].flag<0?(f==2?0:1):flagnow(h)[doors[d].flag]?0:1));   /* the names resolve in the pack; a clear flag means a solid door (the boss door is open until the intro) */
            assert(dw4_hubruntime_hitland_missing(h)==0);
            unsigned btn0=total_buttons;
            for(unsigned pass=0;pass<4;pass++){
                int pending=0;for(unsigned d=0;d<ndoors;d++)pending|=doors[d].tested==1 && !flagnow(h)[doors[d].flag];
                if(pass && !pending)break;
                if(f==2 && !pass && getenv("ARENADIRECT")){place(h,"V<-575,10,120>/V<0,-90,0>");run(h,&frame,30,0,0);}   /* development aid: start in the boss arena (the doors are not walked) */
                for(unsigned r=(f==2 && getenv("ARENADIRECT"))?10:0;r<nwaves[f];r++){
                    char rn[16];snprintf(rn,sizeof rn,"matg%02u",r+1);
                    if(pass && f==2 && r==10)continue;   /* the arena is entered once */
                    if(f){int32_t cur=0,top=0;assert(!dw4_property_number(p0,"HP",&cur) && !dw4_property_number(p0,"MHP",&top));
                        if(cur<top*6/10){float lo[3],hi[3],gap=0;mat_region(&mount,floor_stage,f==2 && r>=8?"matc02":"matc01",lo,hi);walk_box(h,&frame,lo[0]+4,hi[0]-4,lo[2]+4,hi[2]-4,5000,0,&gap);for(unsigned t=0;t<120;t++)wtick(h,&frame,0,0,0,0);}}   /* the heal circle */
                    float lo[3],hi[3],gap=0;mat_region(&mount,floor_stage,rn,lo,hi);
                    int ok=walk_box(h,&frame,lo[0]+4,hi[0]-4,lo[2]+4,hi[2]-4,6000,1,&gap);
                    for(unsigned retry=0;!ok && retry<5;retry++){   /* a door still shuts the way: push the ones whose far side opens up, fight on until a wave opens them */
                        for(unsigned d=0;d<npush;d++)if(!doors[d].tested && doors[d].flag>=0 && !flagnow(h)[doors[d].flag] && door_probe(h,doors+d))door_push(h,&frame,doors+d);
                        hunt(h,&frame,6000);doors_settle(h,&frame,doors,ndoors,fb,&total_crossed);
                        ok=walk_box(h,&frame,lo[0]+4,hi[0]-4,lo[2]+4,hi[2]-4,6000,1,&gap);}
                    float pp[3];player_pos(h,pp);
                    fprintf(stderr,"region %s: %s (player %.0f %.0f, gap %.0f, %u ticks so far, %u wall-contact ticks, max step %.2f, %u kills)\n",rn,ok?"walked in":"NOT reachable",pp[0],pp[2],gap,wstat.ticks,wstat.wall_ticks,wstat.max_step,wstat.kills);
                    if(!ok && getenv("DUMPPLAN"))plan_dump(wd,pp,lo,hi);
                    assert(ok);
                    if(f==2 && r==10 && !pass){   /* the arena: Mammothmon's intro runs, doorwall09 closes behind the player */
                        struct door *bd=doors+8,*xd=doors+9;
                        for(unsigned t=0;t<3000 && dw4_lobby_hit_state(wd,bd->name)!=1;t++){if(control(h))wtick(h,&frame,0,0,0,0);else wtick(h,&frame,0,0,t%90<4?0x4000:0,t%90==0?0x4000:0);}
                        fprintf(stderr,"  boss intro: %s hit state %d after the intro\n",bd->name,dw4_lobby_hit_state(wd,bd->name));
                        assert(dw4_lobby_hit_state(wd,bd->name)==1);
                        for(unsigned t=0;t<600 && !control(h);t++)wtick(h,&frame,0,0,t%90<4?0x4000:0,t%90==0?0x4000:0);
                        if(door_probe(h,bd))door_push(h,&frame,bd);   /* the boss door holds the player in */
                        if(door_probe(h,xd))door_push(h,&frame,xd);   /* the exit door is solid until the kill */
                        {   long bk=-1;for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
                                if(mc && info && !strcmp(dw4_stageobject_name(info),"e_mammos"))bk=(long)k;}
                            assert(bk>=0);float bp3[3];unsigned t0=wstat.ticks,swings=0,report=0;int32_t delay=26,hp_first=-1;dw4_property_number(p0,"ATTACKDELAY",&delay);
                            /* Mammothmon never leaves its spot. Its melee (SQ_ATCK1/2; SQ_FIRE at range) reaches the player at every stand-off and a hit flinches the player
                             * (SQ_GUARDR/SDMG/MDMG) before the weapon sweep (hit-boxes 9..15 frames after the press) starts, so a player who walks in and swings is stun-locked: no
                             * damage in 20,000 stick ticks at level 60. The stick phase therefore runs for BOSSSTICK ticks (default 3000); if the boss has not lost HP by then,
                             * the player is put back beside the boss before every swing (a scripted MOVETRANS, counted and printed), the swing itself staying pad input. */
                            if(getenv("BOSSSMART")){   /* the pad-only pilot of Mammothmon (smart_fight): BOSSSMART=1, BOSSSTRAT=<1..6> (default 4: R1 technique casts from range, the brawl when the MP is gone), BOSSBUDGET=<ticks> (default 6000); BOSSNOKILL=1 ends the test after it */
                                int won=smart_fight(h,&frame,bk,p0,getenv("BOSSSTRAT")?atoi(getenv("BOSSSTRAT")):4,getenv("BOSSBUDGET")?(unsigned)atoi(getenv("BOSSBUDGET")):6000);
                                if(getenv("BOSSREQUIRE") && !won){fprintf(stderr,"BOSSSMART: the pad-only pilot did not kill Mammothmon within its budget\n");return 1;}   /* the check target: the kill must be pad input alone */
                                if(!won && getenv("BOSSNOKILL")){printf("boss smart: no kill\n");return 0;}
                            }
                            const unsigned stick_budget=getenv("BOSSSTICK")?(unsigned)atoi(getenv("BOSSSTICK")):3000;int reposition=0;
                            while(wstat.ticks-t0<40000 && enemy_alive(h,bk,bp3)){
                                int32_t hp=0;float me[3];if(dw4_property_number(p0,"HP",&hp) || hp<=0 || player_pos(h,me))break;
                                if(!control(h)){wtick(h,&frame,0,0,0,0);continue;}
                                dw4_script_model bs={0};dw4_controllers_model_state(dw4_hubruntime_models(h),(size_t)bk,&bs);if(hp_first<0)hp_first=bs.hp;
                                if(wstat.ticks-t0>=report){report+=(getenv("BOSSREPORT")?(unsigned)atoi(getenv("BOSSREPORT")):1500);fprintf(stderr,"    boss fight t%u: player HP %d, Mammothmon HP %d/%d at %.1f %.1f, distance %.0f, %u swings, %u repositions\n",wstat.ticks-t0,hp,bs.hp,bs.max_hp,bp3[0],bp3[2],hypotf(bp3[0]-me[0],bp3[2]-me[2]),swings,boss_places);}
                                if(!reposition && wstat.ticks-t0>=stick_budget && bs.hp>=hp_first){reposition=1;fprintf(stderr,"  Mammothmon: no damage taken in %u stick ticks (%u swings, player HP %d); repositioning beside it between swings\n",wstat.ticks-t0,swings,hp);}
                                float sx=bp3[0]+7.0f,sz=bp3[2]-2.0f;   /* the stand point east of the boss, 7 units from its centre */
                                if(reposition){char wh[96];snprintf(wh,sizeof wh,"V<%g,%g,%g>/V<0,-90,0>",sx,bp3[1],sz);place(h,wh);boss_places++;player_pos(h,me);}
                                else if(hypotf(sx-me[0],sz-me[2])>3.0f){wstep(h,&frame,sx,sz,0,0);continue;}
                                for(unsigned i2=0;i2<14;i2++){if(!control(h)){wstep(h,&frame,0,0,0,0);continue;}float x,y,sc=i2<2?1.0f:0.0f;stick_dir(h,bp3[0],bp3[2],&x,&y);wtick(h,&frame,x*sc,y*sc,i2>=2&&i2<5?0x4000:0,i2==2?0x4000:0);}
                                swings++;for(unsigned i2=0;i2<(unsigned)delay*3/2;i2++)wtick(h,&frame,0,0,0,0);}
                            fprintf(stderr,"  Mammothmon %s after %u ticks (%u swings, %u scripted repositions)\n",enemy_alive(h,bk,bp3)?"still up":"down",wstat.ticks-t0,swings,boss_places);}
                        hunt(h,&frame,20000);
                        for(unsigned t=0;t<900 && (dw4_lobby_hit_state(wd,bd->name)!=0 || dw4_lobby_hit_state(wd,xd->name)!=0);t++)wtick(h,&frame,0,0,0,0);
                        fprintf(stderr,"  boss down: flag 150 %d, %s %d, %s %d\n",flagnow(h)[150],bd->name,dw4_lobby_hit_state(wd,bd->name),xd->name,dw4_lobby_hit_state(wd,xd->name));
                        assert(flagnow(h)[150] && dw4_lobby_hit_state(wd,bd->name)==0 && dw4_lobby_hit_state(wd,xd->name)==0);
                        bd->tested=2;total_crossed++;
                        if(xd->tested==1){door_cross(h,&frame,xd,fb);total_crossed++;}
                        continue;
                    }
                    for(unsigned d=0;d<npush;d++)if(!doors[d].tested && doors[d].flag>=0 && !flagnow(h)[doors[d].flag] && door_probe(h,doors+d)){
                        door_push(h,&frame,doors+d);if(doors[d].tested!=1)continue;
                        if(getenv("FIRSTDOOR")){printf("dungeon doors 2: %s %s held closed under a 120-tick stick push on the near side (%u wall-contact ticks over %u ticks, max step %.2f, hitland_missing %u)\n",floor_stage,doors[d].name,wstat.wall_ticks,wstat.ticks,wstat.max_step,dw4_hubruntime_hitland_missing(h));assert(wstat.max_step<5.0f && dw4_hubruntime_hitland_missing(h)==0);return 0;}
                    }
                    hunt(h,&frame,pass?6000:3500);   /* fight what the region sends, as a player does (the wave-cleared flags open the doors) */
                    doors_settle(h,&frame,doors,ndoors,fb,&total_crossed);
                    for(unsigned d=0;d<npush;d++)if(doors[d].tested==1 && btn[d]>=0 && !flagnow(h)[bfl[d]]){   /* a button door: a swing at g_dbutton1 (its ram number) sets the flag; the button may sit behind other doors, so it is tried at the end of every region and only when the walk reaches it */
                        for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){
                            const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
                            if(mc && info && !flagnow(h)[bfl[d]] && slot==btn[d] && !strcmp(dw4_stageobject_name(info),"g_dbutton1")){dw4_modelctrl_actor ba;dw4_modelctrl_actor_state(mc,&ba);
                                float bgap=0;int reach=walk_box(h,&frame,ba.position[0]-12,ba.position[0]+12,ba.position[2]-12,ba.position[2]+12,4000,1,&bgap);
                                fprintf(stderr,"  button g_dbutton1 ram %d at %.0f %.0f for %s: %s\n",btn[d],ba.position[0],ba.position[2],doors[d].name,reach?"reachable":"not reachable yet");
                                if(reach){hit_target(h,&frame,ba.position,fb,bfl[d]);fprintf(stderr,"  button g_dbutton1 ram %d: flag %d = %d\n",btn[d],bfl[d],flagnow(h)[bfl[d]]);if(flagnow(h)[bfl[d]])total_buttons++;}}}
                    }
                    doors_settle(h,&frame,doors,ndoors,fb,&total_crossed);
                }
            }
            unsigned crossed=0,pushed=0,early=0,untouched=0;for(unsigned d=0;d<ndoors;d++){crossed+=doors[d].tested==2;pushed+=doors[d].tested==1||doors[d].tested==2;early+=doors[d].tested>=3;untouched+=doors[d].tested==0;}
            total_pushed+=pushed;total_early+=early;
            fprintf(stderr,"%s: doors pushed closed %u, crossed open %u, opened before the player arrived %u, never probed %u (of %u); buttons swung %u; flags 100-171:",floor_stage,pushed,crossed,early,untouched,ndoors,total_buttons-btn0);for(unsigned x=100;x<=171;x++)if(flagnow(h)[x])fprintf(stderr," %u",x);fputc(10,stderr);
            assert(crossed==pushed && pushed>=1 && dw4_hubruntime_hitland_missing(h)==0);
            if(f==2)assert(flagnow(h)[150]);
            if(f==2) {   /* the intro charge and every later one: both motions of ACTN03 play (1.517 s + the 12 frame blend of actn04 = 103 ticks), never the 3-5 ticks of the last-motion-wins host */
                fprintf(stderr,"%s: Mammothmon SQ_ATCK3 ran %u time(s), the intro charge %u ticks\n",floor_stage,boss_atck3.runs,boss_atck3.first);
                assert(boss_atck3.runs>=1 && boss_atck3.first>=100 && boss_atck3.first<=106);boss_atck3.on=0;}
            const char *next=f<2?fnames[f+1]:"stagML11";
            {   float elo[3],ehi[3],egap=0,ep[3];mat_region(&mount,floor_stage,"matz02",elo,ehi);   /* walk into the exit region first so a failure can be mapped */
                int eok=walk_box(h,&frame,elo[0]+.75f,ehi[0]-.75f,elo[2]+.75f,ehi[2]-.75f,4000,1,&egap);player_pos(h,ep);if(!eok)eok=ep[0]>=elo[0] && ep[0]<=ehi[0] && ep[2]>=elo[2] && ep[2]<=ehi[2];   /* the region itself is the trigger */
                fprintf(stderr,"%s/matz02: %s (player %.0f %.0f, gap %.0f)\n",floor_stage,eok?"walked in":"NOT reachable",ep[0],ep[2],egap);
                if(!eok && getenv("DUMPPLAN"))plan_dump(wd,ep,elo,ehi);}
            h=take_exit(&mount,h,&frame,floor_stage,"matz02",next,0);
            if(f+1<f1 || f==2){
                for(until=0;until<4000 && !control(h);until++){dw4_hubruntime_input(h,0,0,0,until%90<4?0x4000:0,until%90==0?0x4000:0);dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60);}
                if(f<2)run(h,&frame,600,0,0);
                dw4_lobby_world_state wi;assert(!dw4_lobby_world_info(dw4_hubruntime_world(h),&wi) && !strcasecmp(wi.stage,next) && control(h));}
        }
        assert(wstat.max_step<5.0f);
        printf("dungeon doors 2: %s walked by stick (no placement inside the floors except %u in the boss fight), %u doors held closed under a 120-tick push, %u crossed once open, %u opened by their wave before the player arrived, %u buttons swung, %u kills, max step %.2f, %u wall-contact ticks, %u scripted placements\n",getenv("FLOOR")?getenv("FLOOR"):"dng102b1..b3",boss_places,total_pushed,total_crossed,total_early,total_buttons,wstat.kills,wstat.max_step,wstat.wall_ticks,wstat.placed);
        return 0;
    }
    if(!strcmp(mode,"dungeonwalk")) {
        if(getenv("CAMFAR"))dw4_options_get()->camera_far=1;   /* the Far Dungeon camera option: aaacameral.igb */
        pilot_sticky=getenv("STICKY")!=NULL;pilot_confirm=1;
        /* Walk a dungeon floor with the test pilot: the stage's authored regions are visited in FLOOR order (REGIONS, comma separated; default the Humid
         * Cave's first floor matg01..matg07), each region start/stop its generators, and the pilot fights what spawns. FIXLEVEL sets the starter's level
         * (default 6: the Humid Cave's recommended range is 2-4 for the dungeon, the boss around 5-6); everything else is the port's own state. */
        const char *floor_stage=getenv("FLOOR")?getenv("FLOOR"):"dng101b1";
        const char *regions=getenv("REGIONS")?getenv("REGIONS"):"matg01,matg02,matg03,matg04,matg05,matg06,matg07";
        const int fl[]={2,355,503};
        unsigned until=0;
        if(strncmp(floor_stage,"dng101",6)){   /* a floor with no route from stag0101 in this build (dng102b1: stag0102 is not ported): prepared on the floor itself */
            setenv("STAGE",floor_stage,1);h=enter(&mount,fl,3);unsetenv("STAGE");
        }else{
            h=enter(&mount,fl,3);
            for(;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
            h=take_exit(&mount,h,&frame,"stag0101","matz00","dng101b1",0);
            if(strcmp(floor_stage,"dng101b1")){for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);run(h,&frame,600,0,0);h=take_exit(&mount,h,&frame,"dng101b1","matz02","dng101b2",0);}
        }
        for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        assert(control(h));
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
        {int lvl=getenv("FIXLEVEL")?atoi(getenv("FIXLEVEL")):6;int32_t mhp=0,mmp=0;
            assert(!dw4_property_set_number(p0,"LEVEL",lvl) && !dw4_playerstats_recalculate((void *)dw4_hubruntime_databases(h),p0));
            assert(!dw4_property_number(p0,"MHP",&mhp) && !dw4_property_number(p0,"MMP",&mmp) && !dw4_property_set_number(p0,"HP",mhp) && !dw4_property_set_number(p0,"MP",mmp));
            fprintf(stderr,"fixture: level %d HP %d MP %d\n",lvl,mhp,mmp);}
        char list[256];snprintf(list,sizeof list,"%s",regions);unsigned total=0;
        for(char *name=strtok(list,",");name;name=strtok(NULL,",")) {
            float lo[3],hi[3];char where[96];mat_region(&mount,floor_stage,name,lo,hi);
            if(getenv("HURT"))assert(!dw4_property_set_number(p0,"HP",atoi(getenv("HURT"))));   /* start the region hurt (the heal circle) */
            snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",(lo[0]+hi[0])/2,lo[1]+20,(lo[2]+hi[2])/2);place(h,where);
            run(h,&frame,60,0,0);
            const dw4_fieldgen *g=dw4_hubruntime_fieldgen(h);unsigned started=0,alive=0;
            for(size_t i=0;i<dw4_fieldgen_count(g);i++)if(dw4_fieldgen_at(g,i)->state==DW4_GENE_STARTED)started++;
            for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
                if(!strncmp(dw4_stageobject_name(info),"e_",2) && dw4_modelctrl_active(mc))alive++;}
            if(getenv("IDLE")){   /* the player stands still: HP and the active enemies' sequences every 30 ticks (what damages a level-N starter, and how often) */
                for(unsigned i=0;i<(unsigned)atoi(getenv("IDLE"));i+=30){run(h,&frame,30,0,0);int32_t ih=0;dw4_property_number(p0,"HP",&ih);
                    fprintf(stderr,"  idle t%u: HP %d; combat enemy hits on player %u",i+30,ih,dw4_hubruntime_combat(h)->player_hits);
                    for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
                        if(!strncmp(dw4_stageobject_name(info),"e_",2) && dw4_modelctrl_active(mc)){dw4_modelctrl_actor ea;dw4_modelctrl_actor_state(mc,&ea);fprintf(stderr,"; %s[%d] %s",dw4_stageobject_name(info),slot,dw4_modelctrl_sequence(mc));}}
                    fputc(10,stderr);}
                return 0;}
            unsigned kills=pilot(h,&frame,getenv("TICKS")?(unsigned)atoi(getenv("TICKS")):3000,1);total+=kills;
            if(getenv("DESCRIBE_DM")){fprintf(stderr,"DM groups after %s: %zu\n",name,dw4_scriptengine_pending(dw4_hubruntime_scripts(h)));dw4_scriptengine_describe(dw4_hubruntime_scripts(h),stderr);}
            int32_t hp=0,lv=0,ex=0;dw4_property_number(p0,"HP",&hp);dw4_property_number(p0,"LEVEL",&lv);dw4_property_number(p0,"EXP",&ex);
            fprintf(stderr,"region %s: %u generators started, %u enemies active on entry, %u kills, HP %d level %d exp %d\n",name,started,alive,kills,hp,lv,ex);
            if(getenv("BOSSSEQ")){fprintf(stderr,"  %s sequences (ticks):",getenv("BOSSSEQ"));for(unsigned q=0;q<boss_seq_n;q++)fprintf(stderr," %s %u",boss_seq[q].name,boss_seq[q].n);fputc(10,stderr);}
            if(getenv("BOSS")){for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
                if(!strcmp(dw4_stageobject_name(info),getenv("BOSS"))){dw4_script_model st;int ok=!dw4_controllers_model_state(dw4_hubruntime_models(h),k,&st);fprintf(stderr,"  %s[%d] active %d seq %s hp %d/%d\n",getenv("BOSS"),slot,dw4_modelctrl_active(mc),dw4_modelctrl_sequence(mc),ok?st.hp:-1,ok?st.max_hp:-1);}}}
            {const uint8_t *fb=dw4_property_bytes(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0),"FLAG",NULL);fprintf(stderr,"  flags set:");
             for(unsigned f=100;f<135;f++)if(flagnow(h)[f])fprintf(stderr," %u",f);fputc(10,stderr);}
            if(hp<=0){fprintf(stderr,"player down\n");break;}
        }
        if(getenv("SOFT"))dw4_lobby_set_light(dw4_hubruntime_world(h),0);
        if(getenv("AT")) {   /* stand at x,y,z and let the pilot work there (the boss's chest room), then list the generators' states and the drops rolled */
            float ax=0,ay=0,az=0;sscanf(getenv("AT"),"%f,%f,%f",&ax,&ay,&az);char where[96];
            snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",ax,ay,az);place(h,where);run(h,&frame,120,0,0);
            unsigned kills=0;
            if(getenv("TICKS2") && atoi(getenv("TICKS2"))==0)run(h,&frame,getenv("SETTLE")?(unsigned)atoi(getenv("SETTLE")):300,0,0);   /* stand and let the box camera settle: the pilot would walk away to the generators */
            else kills=pilot(h,&frame,getenv("TICKS2")?(unsigned)atoi(getenv("TICKS2")):6000,1);
            const dw4_fieldgen *g=dw4_hubruntime_fieldgen(h);size_t nd=0;const dw4_drop *drops=dw4_fieldgen_drops(g,&nd);
            {dw4_lobby_control_state cs;if(!dw4_lobby_control(dw4_hubruntime_world(h),&cs))fprintf(stderr,"camera region %u world pos %.1f %.1f %.1f, fwd %.3f %.3f %.3f\n",cs.camera_region,cs.camera_world[12],cs.camera_world[13],cs.camera_world[14],cs.camera_world[8],cs.camera_world[9],cs.camera_world[10]);}
            fprintf(stderr,"at %s: %u kills, %zu drops rolled\n",getenv("AT"),kills,nd);
            for(size_t i=0;i<dw4_fieldgen_count(g);i++){const dw4_gene *e=dw4_fieldgen_at(g,i);if(!strncmp(e->name,"GBOX",4))fprintf(stderr,"  %s state %d spawned %u remaining %d\n",e->name,(int)e->state,e->spawned_total,e->remaining);}
            for(size_t i=0;i<nd;i++)fprintf(stderr,"  drop from %s: %s id %d at %.0f %.0f %.0f collected %d\n",drops[i].generator,drops[i].entry.category,drops[i].entry.id,drops[i].position[0],drops[i].position[1],drops[i].position[2],drops[i].collected);
        }
        if(getenv("SHOT")){dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));assert(dw4_hubruntime_draw(h,&fb,NULL)>0);assert(!dw4_png_write(getenv("SHOT"),fb.rgba,fb.w,fb.h));dw4_fb_free(&fb);}
        if(getenv("EXITMAT")) {   /* leave through an exit region once the regions above are done (EXPECT = the destination, EXPECTPT its arrival point) */
            for(until=0;until<3000 && !control(h);until++)run(h,&frame,1,0,0);
            h=take_exit(&mount,h,&frame,floor_stage,getenv("EXITMAT"),getenv("EXPECT"),getenv("EXPECTPT")?atoi(getenv("EXPECTPT")):0);
            for(until=0;until<4000 && !control(h);until++){dw4_hubruntime_input(h,0,0,0,until%90<4?0x4000:0,until%90==0?0x4000:0);dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60);}
            dw4_lobby_world_state info;assert(!dw4_lobby_world_info(dw4_hubruntime_world(h),&info));
            fprintf(stderr,"arrived at %s point %d, control %d\n",info.stage,info.arrival_point,control(h));
        }
        printf("dungeonwalk %s: %u kills\n",floor_stage,total);
        return 0;
    }
    if(!strcmp(mode,"dungeonroute")) {
        /* The Humid Cave end to end for one player: stag0101 matz00 -> dng101b1 (every authored wave region matg01..07, the pilot fights what spawns, the
         * door flags 101-104 follow) -> matz02 -> dng101b2 (waves matg01..07, then the arena region matg08: Blossomon's intro runs, the pilot kills it and the
         * floor script sets flag 119) -> matz02 -> the Terminal (stagML11 point 0). Fixture: the starter at FIXLEVEL (default 40, the owner-accepted
         * boss-fixture level; the port's own hit chance and enemy damage at lower levels are not retail-measured). */
        pilot_confirm=1;
        const int fl[]={2,355,503};h=enter(&mount,fl,3);
        unsigned until=0;
        const unsigned party=getenv("COOP")?(unsigned)atoi(getenv("COOP")):1;assert(party>=1 && party<=4);
        for(;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        if(party>1) {   /* local co-op: the mates join from the records, as the load screen would have them (an Agumon, a Girumon, a V-mon) */
            static const char *const mates[]={"p_agumon","p_girumon","p_vmon"};
            dw4_playerrecords *rec=dw4_hubruntime_records(h);const dw4_databases *db=dw4_hubruntime_databases(h);char error[256];
            for(unsigned q=1;q<party;q++)assert(!dw4_playerrecords_create(rec,db,(int)q,mates[q-1],"Mate",error,sizeof error) && !dw4_property_set_number(dw4_playerrecords_get(rec,"GETPLAYER",(int)q),"ISUSE",1));
            assert(!dw4_property_set_number(dw4_playerrecords_get(rec,"GETCOMMON",0),"NINZU",(int32_t)party));
            pilot_extra=party-1;
        }
        h=take_exit(&mount,h,&frame,"stag0101","matz00","dng101b1",0);
        for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        run(h,&frame,600,0,0);assert(control(h));
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
        for(unsigned q=0;q<party;q++){int lvl=getenv("FIXLEVEL")?atoi(getenv("FIXLEVEL")):40;int32_t mhp=0,mmp=0;
            dw4_property_folder *pq=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",(int)q);
            assert(!dw4_property_set_number(pq,"LEVEL",lvl) && !dw4_playerstats_recalculate((void *)dw4_hubruntime_databases(h),pq));
            assert(!dw4_property_number(pq,"MHP",&mhp) && !dw4_property_number(pq,"MMP",&mmp) && !dw4_property_set_number(pq,"HP",mhp) && !dw4_property_set_number(pq,"MP",mmp));}
        static const char *const floors[]={"dng101b1","dng101b2"};
        static const char *const waves[]={"matg01","matg02","matg03","matg04","matg05","matg06","matg07","matg08"};
        unsigned kills[2]={0,0};
        static const unsigned need[2][4]={{101,102,103,104},{114,116,117,118}};   /* the floor scripts' wave-cleared flags */
        for(unsigned f=0;f<2;f++) {
            for(unsigned pass=0;pass<3;pass++) {
              const uint8_t *fb0=dw4_property_bytes(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0),"FLAG",NULL);
              if(pass && fb0[need[f][0]] && fb0[need[f][1]] && fb0[need[f][2]] && fb0[need[f][3]])break;   /* a missed enemy: walk the regions again */
              for(unsigned w=0;w<(f?8u:7u);w++) {
                if(pass && w==7)continue;
                float lo[3],hi[3];char where[96];
                if(f){   /* the second floor's heal circle (matc02, beside the boss door): a hurt player walks back to it, as the guides advise */
                    int32_t cur=0,top=0;assert(!dw4_property_number(p0,"HP",&cur) && !dw4_property_number(p0,"MHP",&top));
                    if(cur<top*6/10 || w==7){
                        mat_region(&mount,floors[f],"matc02",lo,hi);
                        snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",(lo[0]+hi[0])/2,lo[1]+20,(lo[2]+hi[2])/2);place(h,where);
                        for(unsigned q=1;q<=pilot_extra;q++){char w2[96];snprintf(w2,sizeof w2,"V<%g,%g,%g>/V<0,0,0>",(lo[0]+hi[0])/2+(float)q*2.5f,lo[1]+20,(lo[2]+hi[2])/2);place_slot(h,q,w2);}
                        run(h,&frame,120,0,0);assert(!dw4_property_number(p0,"HP",&cur) && cur==top);
                    }
                }
                mat_region(&mount,floors[f],waves[w],lo,hi);
                snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",(lo[0]+hi[0])/2,lo[1]+20,(lo[2]+hi[2])/2);place(h,where);
                for(unsigned q=1;q<=pilot_extra;q++){   /* the arena scripts ask MATisAllPlayer: the mates enter the region too */
                    char w2[96];snprintf(w2,sizeof w2,"V<%g,%g,%g>/V<0,0,0>",(lo[0]+hi[0])/2+(float)q*2.5f,lo[1]+20,(lo[2]+hi[2])/2);place_slot(h,q,w2);}
                run(h,&frame,60,0,0);
                kills[f]+=pilot(h,&frame,w==7?20000:9000,0);
                int32_t hp=0;assert(!dw4_property_number(p0,"HP",&hp) && hp>0);
              }
            }
            const uint8_t *fb=dw4_property_bytes(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0),"FLAG",NULL);
            if(!f){
                fprintf(stderr,"dng101b1: %u kills, door flags 101 %d 102 %d 103 %d 104 %d\n",kills[0],flagnow(h)[101],flagnow(h)[102],flagnow(h)[103],flagnow(h)[104]);
                assert(flagnow(h)[101] && flagnow(h)[102] && flagnow(h)[103] && flagnow(h)[104] && kills[0]>=10);   /* the door-opening wave flags the floor script sets as waves finish */
                for(until=0;until<3000 && !control(h);until++)run(h,&frame,1,0,0);
                h=take_exit(&mount,h,&frame,"dng101b1","matz02","dng101b2",0);
                p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);   /* the destination owns its own snapshot of the player records */
                for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
                run(h,&frame,600,0,0);assert(control(h));
            }else{
                const dw4_modelctrl *boss=NULL;
                for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
                    if(!strcmp(dw4_stageobject_name(info),"e_blosso"))boss=mc;}
                fprintf(stderr,"dng101b2: %u kills, boss %s, flag 119 %d\n",kills[1],boss?(dw4_modelctrl_active(boss)?"alive":"down"):"missing",flagnow(h)[119]);
                assert(boss && !dw4_modelctrl_active(boss) && flagnow(h)[119] && kills[1]>=10);   /* Blossomon is down and the floor script has set its defeated flag */
                {   /* Blossomon's own generator (GENE-08, inferred) lists the ID Key, impItem 0 at rate 10000: Cross takes it and FLAGFOLDER[0] (the Blossomon key; flag 900 of stag0101 needs both) is set */
                    dw4_fieldgen *gen=(dw4_fieldgen *)dw4_hubruntime_fieldgen(h);int key=-1;size_t nd=0;dw4_drop *dr=NULL;
                    for(unsigned w=0;w<240 && key<0;w++){
                        run(h,&frame,1,0,0);dr=dw4_fieldgen_drops_mut(gen,&nd);
                        for(size_t i=0;i<nd;i++)if(!strcmp(dr[i].entry.category,"impItem") && dr[i].entry.id==0)key=(int)i;
                    }
                    assert(key>=0 && dr[key].loot_ready && dr[key].loot.model_kind==DW4_LOOT_KEY);
                    for(unsigned t=0;t<30 && !dr[key].collected;t++){   /* the pilot's swings may have taken it already; otherwise stand on it and press Cross */
                        char where[96];snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",dr[key].position[0],dr[key].position[1],dr[key].position[2]);place(h,where);
                        run(h,&frame,3,0,0);
                        dw4_hubruntime_input(h,0,0,0,0x4000,0x4000);if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));return 1;}
                        dr=dw4_fieldgen_drops_mut(gen,&nd);
                    }
                    const uint8_t *ff=dw4_property_bytes(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0),"FLAGFOLDER",NULL);
                    fprintf(stderr,"dng101b2: boss key drop collected %d, FLAGFOLDER[0] %d (drops rolled: %zu)\n",dr[key].collected,ff?ff[0]:-1,nd);
                    assert(dr[key].collected && ff && ff[0]==1);
                }
            }
        }
        for(until=0;until<3000 && !control(h);until++)run(h,&frame,1,0,0);
        sound_stats(h,"dng101b2");   /* the boss intro's BT_SBOSS/DG_CAVE1 and the floor's cues all resolve to prepared clips */
        h=take_exit(&mount,h,&frame,"dng101b2","matz02","stagML11",0);
        for(until=0;until<4000 && !control(h);until++){dw4_hubruntime_input(h,0,0,0,until%90<4?0x4000:0,until%90==0?0x4000:0);if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));return 1;}}
        dw4_lobby_world_state info;assert(!dw4_lobby_world_info(dw4_hubruntime_world(h),&info) && !strcmp(info.stage,"stagML11") && control(h));
        if(party>1) {   /* the whole party arrives in the Terminal: every joined slot exists, its model runs (SQ_ENTR per joined player) and the slots stand apart */
            dw4_lobby *w=dw4_hubruntime_world(h);assert(dw4_lobby_player_count(w)==party);
            float at[4][3];
            for(unsigned q=0;q<party;q++){
                dw4_lobby_walk_state ws;assert(dw4_lobby_player_joined(w,q) && !dw4_lobby_select_player(w,q) && !dw4_lobby_walk(w,&ws));
                assert(dw4_lobby_player_model(w) && dw4_modelctrl_active(dw4_lobby_player_model(w)));
                memcpy(at[q],ws.position,sizeof at[q]);
                for(unsigned o=0;o<q;o++)assert(fabsf(at[o][0]-at[q][0])+fabsf(at[o][2]-at[q][2])>1);
            }
            dw4_lobby_select_player(w,0);
            dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));assert(dw4_hubruntime_draw(h,&fb,NULL)>0);dw4_fb_free(&fb);
        }
        printf("dungeon route: Humid Cave cleared by %u player(s) (%u + %u kills, Blossomon down, flag 119), back at the Terminal\n",party,kills[0],kills[1]);
        return 0;
    }
    if(!strcmp(mode,"dungeonroute2")) {
        /* The second dungeon end to end for COOP=1..4 players: dng102b1 (the route in, stag0102, is not ported, so the runtime is prepared on the
         * floor itself with the Humid Cave progress flags) -> matz02 -> dng102b2 -> matz02 -> dng102b3 (arena region matg11: Mammothmon's intro and fight, the
         * pilot kills it and the floor script sets flag 150) -> the Terminal. Every floor's wave regions are placed in order (three passes); the player rests
         * at a heal circle when hurt. Fixture: FIXLEVEL (default 40, the owner-accepted boss-fixture level). */
        pilot_confirm=1;
        if(!getenv("FIXLEVEL"))setenv("FIXLEVEL","60",1);   /* the pilot does not dodge: at level 40 Mammothmon can down it (seen once the route shifted the random stream); level 60 is the fixture for this dungeon */
        const int fl[]={2,355,503};
        const int direct=getenv("START")!=NULL;   /* START=dng102b1: open the first floor directly, skipping the stag0101 -> stag0102 leg */
        if(direct){setenv("STAGE","dng102b1",1);h=enter(&mount,fl,3);unsetenv("STAGE");}else h=enter(&mount,fl,3);
        unsigned until=0;
        const unsigned party=getenv("COOP")?(unsigned)atoi(getenv("COOP")):1;assert(party>=1 && party<=4);
        for(;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        if(party>1) {
            static const char *const mates[]={"p_agumon","p_girumon","p_vmon"};
            dw4_playerrecords *rec=dw4_hubruntime_records(h);const dw4_databases *db=dw4_hubruntime_databases(h);char error[256];
            for(unsigned q=1;q<party;q++)assert(!dw4_playerrecords_create(rec,db,(int)q,mates[q-1],"Mate",error,sizeof error) && !dw4_property_set_number(dw4_playerrecords_get(rec,"GETPLAYER",(int)q),"ISUSE",1));
            assert(!dw4_property_set_number(dw4_playerrecords_get(rec,"GETCOMMON",0),"NINZU",(int32_t)party));
            pilot_extra=party-1;
        }
        run(h,&frame,600,0,0);assert(control(h));
        unsigned kills_field=0;
        if(!direct) {
            /* stag0101 -> stag0102 (Abyss of Grief, point 0), then the stick to matz00 -> dng102b1 point 0. The Blossomon gate (g_brossgatez01, z -300) sits in front
             * of mate01 (the way on to stag0103), not of matz00: flag 66 is not needed for the dungeon. */
            set_party_level(h,party);
            h=take_exit(&mount,h,&frame,"stag0101",getenv("EXIT1")?getenv("EXIT1"):"matz02","stag0102",0);
            for(until=0;until<3000 && !control(h);until++)run(h,&frame,1,0,0);
            run(h,&frame,300,0,0);assert(control(h));
            set_party_level(h,party);
            exit_by_stick=getenv("NOSTICK")==NULL;   /* the stag0102 leg is stick-walked from the arrival over the bridge to matz00 (NOSTICK=1 places the player in the region instead) */
            h=take_exit(&mount,h,&frame,"stag0102","matz00","dng102b1",0);exit_by_stick=0;
            for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
            run(h,&frame,600,0,0);assert(control(h));
        }
        static const char *const floors[]={"dng102b1","dng102b2","dng102b3"};
        static const unsigned nwaves[3]={8,12,11};
        static const char *const heal[3]={NULL,NULL,"matc02"};   /* dng102b3 matc02 is the heal circle beside the boss door (g_dhpheal); b1 and b2 have none (matc01 on b2 / b3 is the security gate), so the fixture refills there */
        unsigned kills[3]={0,0,0};
        for(unsigned f=0;f<3;f++) {
            dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
            set_party_level(h,party);
            boss_atck3.on=f==2;boss_atck3.run=boss_atck3.runs=boss_atck3.first=boss_atck3.clean=0;
            for(unsigned pass=0;pass<2;pass++)for(unsigned w=0;w<nwaves[f];w++) {
                float lo[3],hi[3];char where[96],name[16];
                if(pass && w==nwaves[f]-1 && f==2)continue;   /* the arena is entered once */
                {
                    int32_t cur=0,top=0;assert(!dw4_property_number(p0,"HP",&cur) && !dw4_property_number(p0,"MHP",&top));
                    if(cur<top*6/10 && heal[f]){
                        mat_region(&mount,floors[f],heal[f],lo,hi);
                        snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",(lo[0]+hi[0])/2,lo[1]+20,(lo[2]+hi[2])/2);place(h,where);
                        for(unsigned q=1;q<=pilot_extra;q++){char w2[96];snprintf(w2,sizeof w2,"V<%g,%g,%g>/V<0,0,0>",(lo[0]+hi[0])/2+(float)q*2.5f,lo[1]+20,(lo[2]+hi[2])/2);place_slot(h,q,w2);}
                        run(h,&frame,120,0,0);
                    } else if(cur<top*6/10) {   /* fixture refill (no heal circle on this floor) */
                        for(unsigned q=0;q<party;q++){int32_t mhp=0;dw4_property_folder *pq=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",(int)q);
                            assert(!dw4_property_number(pq,"MHP",&mhp) && !dw4_property_set_number(pq,"HP",mhp));}
                    }
                }
                snprintf(name,sizeof name,"matg%02u",w+1);
                mat_region(&mount,floors[f],name,lo,hi);
                snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",(lo[0]+hi[0])/2,lo[1]+20,(lo[2]+hi[2])/2);place(h,where);
                for(unsigned q=1;q<=pilot_extra;q++){char w2[96];snprintf(w2,sizeof w2,"V<%g,%g,%g>/V<0,0,0>",(lo[0]+hi[0])/2+(float)q*2.5f,lo[1]+20,(lo[2]+hi[2])/2);place_slot(h,q,w2);}
                run(h,&frame,60,0,0);
                kills[f]+=pilot(h,&frame,f==2 && w==nwaves[f]-1?30000:9000,0);
                int32_t hp=0;assert(!dw4_property_number(p0,"HP",&hp));if(hp<=0)fprintf(stderr,"route2: player down on %s %s pass %u (kills so far %u)\n",floors[f],name,pass,kills[f]);assert(hp>0);
                if(pass && !dw4_controllers_enemies_alive(dw4_hubruntime_models(h),NULL))break;
            }
            const uint8_t *fb=dw4_property_bytes(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0),"FLAG",NULL);
            fprintf(stderr,"%s: %u kills, flags 100-120 set:",floors[f],kills[f]);for(unsigned i=100;i<=120;i++)if(flagnow(h)[i])fprintf(stderr," %u",i);fputc(10,stderr);
            for(until=0;until<3000 && !control(h);until++)run(h,&frame,1,0,0);
            if(f==2) {
                const dw4_modelctrl *boss=NULL;
                for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
                    if(!strcmp(dw4_stageobject_name(info),"e_mammos"))boss=mc;}
                fprintf(stderr,"dng102b3: Mammothmon SQ_ATCK3 ran %u time(s), first run %u ticks, first uninterrupted run %u\n",boss_atck3.runs,boss_atck3.first,boss_atck3.clean);boss_atck3.on=0;
                assert(!boss_atck3.clean || (boss_atck3.clean>=100 && boss_atck3.clean<=106));   /* a run cut short by a hit (the pilots fight during the charge) is not measured */   /* both motions of ACTN03 (103 ticks with the blend wait); the last-motion-wins host gave 3-5 */
                fprintf(stderr,"dng102b3: boss %s, flag 150 %d\n",boss?(dw4_modelctrl_active(boss)?"alive":"down"):"missing",flagnow(h)[150]);
                assert(boss && !dw4_modelctrl_active(boss) && flagnow(h)[150]);
                {   /* the boss's key (retail: impItem 1 "Mammothmon ID", g_000key, FLAGFOLDER[1] 0 -> 1 on Cross, 2.5-3 s after flag 150): the port drops it and Cross sets the folder byte */
                    dw4_fieldgen *gen=(dw4_fieldgen *)dw4_hubruntime_fieldgen(h);int key=-1;size_t nd=0;dw4_drop *dr=NULL;
                    for(unsigned w=0;w<360 && key<0;w++){
                        run(h,&frame,1,0,0);dr=dw4_fieldgen_drops_mut(gen,&nd);
                        for(size_t i=0;i<nd;i++)if(!strcmp(dr[i].entry.category,"impItem") && dr[i].entry.id==1)key=(int)i;
                    }
                    assert(key>=0 && dr[key].loot_ready && dr[key].loot.model_kind==DW4_LOOT_KEY);
                    for(unsigned t=0;t<30 && !dr[key].collected;t++){
                        char where[96];snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",dr[key].position[0],dr[key].position[1],dr[key].position[2]);place(h,where);
                        run(h,&frame,3,0,0);
                        dw4_hubruntime_input(h,0,0,0,0x4000,0x4000);if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));return 1;}
                        dr=dw4_fieldgen_drops_mut(gen,&nd);
                    }
                    const uint8_t *ff=dw4_property_bytes(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0),"FLAGFOLDER",NULL);
                    fprintf(stderr,"dng102b3: boss key drop collected %d, FLAGFOLDER[1] %d\n",dr[key].collected,ff?ff[1]:-1);
                    assert(dr[key].collected && ff && ff[1]==1);
                }
                sound_stats(h,"dng102b3");
                h=take_exit(&mount,h,&frame,"dng102b3","matz02","stagML11",0);
            } else {
                assert(kills[f]>=5);
                h=take_exit(&mount,h,&frame,floors[f],"matz02",floors[f+1],0);
                for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
                run(h,&frame,600,0,0);assert(control(h));
            }
        }
        for(until=0;until<4000 && !control(h);until++){dw4_hubruntime_input(h,0,0,0,until%90<4?0x4000:0,until%90==0?0x4000:0);if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));return 1;}}
        dw4_lobby_world_state info;assert(!dw4_lobby_world_info(dw4_hubruntime_world(h),&info) && !strcmp(info.stage,"stagML11") && control(h));
        if(party>1){dw4_lobby *w=dw4_hubruntime_world(h);assert(dw4_lobby_player_count(w)==party);}
        printf("dungeon route 2: stag0102 and the second dungeon cleared by %u player(s) (%u field + %u + %u + %u kills, Mammothmon down, flag 150), back at the Terminal\n",party,kills_field,kills[0],kills[1],kills[2]);
        return 0;
    }
    if(!strcmp(mode,"gene09refill")) {
        /* dng102b3 GENE-09 (row 42, radar 6400, fill 'add', 10 total / 6 concurrent) against the retail reads of findings #2978, #3072 and #3073: the six spawn at once
         * when the player stands in matg09, a victim's InfoWork ends about 153-158 ticks after HP 0 on the flat floor, the refill follows within a tick, and refills happen only
         * while a player is inside the matg09 box (the region chunk's START/STOP pair): with the player outside the victim is destroyed but nothing spawns
         * until the player re-enters. The floor is prepared as dungeondoors2 does (opened directly, FIXLEVEL default 60, full HP). */
        pilot_confirm=1;
        if(!getenv("FIXLEVEL"))setenv("FIXLEVEL","60",1);
        const int fl[]={2,355,503};setenv("STAGE","dng102b3",1);h=enter(&mount,fl,3);unsetenv("STAGE");
        unsigned until=0;
        for(;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        run(h,&frame,600,0,0);assert(control(h));
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
        {   int lvl=atoi(getenv("FIXLEVEL"));int32_t mhp=0,mmp=0;
            assert(!dw4_property_set_number(p0,"LEVEL",lvl) && !dw4_playerstats_recalculate((void *)dw4_hubruntime_databases(h),p0));
            assert(!dw4_property_number(p0,"MHP",&mhp) && !dw4_property_number(p0,"MMP",&mmp) && !dw4_property_set_number(p0,"HP",mhp) && !dw4_property_set_number(p0,"MP",mmp));}
        const dw4_gene *g=dw4_fieldgen_find(dw4_hubruntime_fieldgen(h),"GENE-09");
        assert(g && g->enemy_row==42 && !strcmp(g->start_mode,"radar") && g->start_data==6400.0f && !strcmp(g->fill_mode,"add") && g->count[0]==10 && g->max_count[0]==6);
        const char *model=dw4_database_string(dw4_databases_get(dw4_hubruntime_databases(h),"enemy"),g->enemy_row,"MODEL");assert(model && *model);
        float lo[3],hi[3];mat_region(&mount,"dng102b3","matg09",lo,hi);
        assert(fabsf(lo[0]+35)<.5f && fabsf(lo[1]-24)<.5f && fabsf(lo[2]+15)<.5f && fabsf(hi[0]-75)<.5f && fabsf(hi[1]-125)<.5f && fabsf(hi[2]-175)<.5f);   /* the retail box */
        const float centre[3]={(lo[0]+hi[0])/2,lo[1]+20,(lo[2]+hi[2])/2};
        char inside[96],outside[96];
        snprintf(inside,sizeof inside,"V<%g,%g,%g>/V<0,0,0>",centre[0],centre[1],centre[2]);
        snprintf(outside,sizeof outside,"V<%g,%g,%g>/V<0,0,0>",hi[0]+55,centre[1],centre[2]);   /* x = 130, outside the box and clear of the radar */
        fprintf(stderr,"gene09: row %d model %s, box (%g,%g,%g)-(%g,%g,%g)\n",g->enemy_row,model,lo[0],lo[1],lo[2],hi[0],hi[1],hi[2]);
        assert(g->state==DW4_GENE_IDLE && !g->spawned_total);
        /* 1. arrival: the six spawn together, remaining 4 */
        place(h,inside);
        int t_first=-1,t_six=-1;
        for(int t=0;t<240;t++){
            run(h,&frame,1,0,0);
            if(t_first<0 && g->spawned_total)t_first=t;
            if(t_six<0 && g->spawned_total==6)t_six=t;
        }
        fprintf(stderr,"gene09: after placement in matg09 the first spawn at tick %d, six by tick %d (retail: all six within 18-60 ms, one wave), spawned %u, live %u, remaining %u, state %d\n",t_first,t_six,g->spawned_total,g->nlive,g->remaining,g->state);
        assert(t_first>=0 && t_six>=0 && t_six==t_first && t_six<=3 && g->spawned_total==6 && running_models(h,model)==6 && g->remaining==4);
        /* 2. a kill with the player inside: the end of the instance and the refill (retail: 153-158 ticks after HP 0 on the flat floor, the refill within one tick) */
        struct g9obs o;
        const int32_t v1=g->live_id[0];
        g9_kill(h,&frame,g,model,v1,centre,NULL,&o,900,1);
        fprintf(stderr,"gene09 inside: HP 0 at tick %d, instance ended %d ticks later, refill %d ticks after the end (retail: end 153-158 ticks after HP 0 on the flat floor, refill within 1 tick)\n",o.hp0,o.end-o.hp0,o.refill-o.end);
        assert(o.hp0>=0 && o.end>o.hp0 && o.refill>=o.end);
        const int in_end=o.end-o.hp0,in_refill=o.refill-o.end;
        assert(o.drift<.01f);   /* no turning during the knockback hop */
        assert(in_end>=150 && in_end<=158);   /* two 39-tick knockback hops (Jump 1.7/6.3 up, Fall down to the floor) plus the Ldmg03..05 tail; retail SQ_DDMG to SQ_ERAS 153.1-157.4 on the flat floor (#3081) */
        assert(g->spawned_total==7 && g->remaining==3 && running_models(h,model)==6);
        run(h,&frame,60,0,0);assert(g->spawned_total==7);
        /* 3. a kill with the player moved outside the box at HP 0: the victim ends, nothing spawns until the player is back */
        {   int32_t mhp=0;assert(!dw4_property_number(p0,"MHP",&mhp) && !dw4_property_set_number(p0,"HP",mhp));}
        const int32_t v2=g->live_id[0];
        g9_kill(h,&frame,g,model,v2,centre,outside,&o,600,0);
        fprintf(stderr,"gene09 outside: HP 0 at tick %d, instance ended %d ticks later, refill %s over 600 ticks, spawned %u, live %u, remaining %u (retail: destroyed, no spawn while outside)\n",o.hp0,o.end-o.hp0,o.refill<0?"none":"yes",g->spawned_total,g->nlive,g->remaining);
        assert(o.hp0>=0 && o.end>o.hp0 && o.refill<0 && g->spawned_total==7 && running_models(h,model)==5 && g->remaining==3 && g->nlive==5);   /* the instance is gone and the generator's live list trimmed in the same tick, region or not (#3082) */
        place(h,inside);
        int back=-1;
        for(int t=0;t<120 && back<0;t++){run(h,&frame,1,0,0);if(g->spawned_total>7)back=t;}
        fprintf(stderr,"gene09: player back in the box, refill after %d ticks (retail 41 ms = about 2-3 ticks), spawned %u, live %u, remaining %u\n",back,g->spawned_total,g->nlive,g->remaining);
        assert(back>=0 && back<=6 && g->spawned_total==8 && running_models(h,model)==6 && g->remaining==2);
        /* 4. the rest: 6 + 4 refills = 10 in all, never more than 6 live, then the generator is released and flag 147 is set */
        unsigned peak=running_models(h,model);
        for(unsigned k=0;k<4 && running_models(h,model);k++){
            {int32_t mhp=0;assert(!dw4_property_number(p0,"MHP",&mhp) && !dw4_property_set_number(p0,"HP",mhp));}
            g9_kill(h,&frame,g,model,g->live_id[0],centre,NULL,&o,900,2);if(running_models(h,model)>peak)peak=running_models(h,model);
            assert(o.hp0>=0 && o.end>o.hp0);fprintf(stderr,"gene09 kill %u: HP 0 to end %d ticks\n",k+3,o.end-o.hp0);
        }
        for(unsigned guard=0;guard<8 && running_models(h,model);guard++){
            {int32_t mhp=0;assert(!dw4_property_number(p0,"MHP",&mhp) && !dw4_property_set_number(p0,"HP",mhp));}
            g9_kill(h,&frame,g,model,g->live_id[0],centre,NULL,&o,900,2);if(running_models(h,model)>peak)peak=running_models(h,model);
        }
        run(h,&frame,120,0,0);
        fprintf(stderr,"gene09: spawned %u in all, peak live %u, remaining %u, finished %d, state %d, flag 147 %d\n",g->spawned_total,peak,g->remaining,g->finished,g->state,flagnow(h)[147]);
        assert(g->spawned_total==10 && peak<=6 && !g->remaining && !running_models(h,model));
        assert(flagnow(h)[147]);
        printf("gene09 refill: 6 spawned by tick %d, instance ended %d ticks after HP 0 and refilled %d tick(s) later (retail 153-158 and <=1), no refill while outside the matg09 box (refilled %d ticks after re-entry), 10 in all\n",t_six,in_end,in_refill,back);
        return 0;
    }
    if(!strcmp(mode,"loot")) {
        /* Loot delivery in a real dungeon floor (src/loot.c): dng101b2's own generator drop lists are rolled with their own tables and the drops laid at the
         * player's feet. Unnamed models (BIT, x-data, UPCNT items) are taken by standing there; named ones (the boss key, weapons, armour, chips, disks)
         * show a label and wait for Cross. The item rolls draw from the world stream in the drop's own step: the expected pocket / revision are computed
         * from a copy of that stream. Fixture: level 40 (the owner-accepted boss-fixture level). */
        pilot_confirm=1;
        const int fl[]={2,355,503};h=enter(&mount,fl,3);
        unsigned until=0;
        for(;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        h=take_exit(&mount,h,&frame,"stag0101","matz00","dng101b1",0);
        for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        run(h,&frame,600,0,0);
        h=take_exit(&mount,h,&frame,"dng101b1","matz02","dng101b2",0);
        for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        run(h,&frame,600,0,0);assert(control(h));
        dw4_playerrecords *rec=dw4_hubruntime_records(h);
        dw4_property_folder *p0=dw4_playerrecords_get(rec,"GETPLAYER",0);
        {int32_t mhp=0,mmp=0;assert(!dw4_property_set_number(p0,"LEVEL",40) && !dw4_playerstats_recalculate((void *)dw4_hubruntime_databases(h),p0));
         assert(!dw4_property_number(p0,"MHP",&mhp) && !dw4_property_number(p0,"MMP",&mmp) && !dw4_property_set_number(p0,"HP",mhp) && !dw4_property_set_number(p0,"MP",mmp));}
        dw4_fieldgen *g=(dw4_fieldgen *)dw4_hubruntime_fieldgen(h);assert(g);
        dw4_modelctrl_actor pa;dw4_modelctrl_actor_state(dw4_lobby_player_model(dw4_hubruntime_world(h)),&pa);
        float at[3];memcpy(at,pa.position,12);
        size_t nd0=0;dw4_fieldgen_drops(g,&nd0);
        if(getenv("DW4_LOOT_BLINK")){   /* frames of uncollected drops blinking out (SQ_BODING), a few frames apart; nothing is picked up (12..28 units away); images are not committed */
            static const struct {const char *category;int id;float dx,dz;} row[]={{"insItem",0,-24,-14},{"insItem",1,22,-14},{"weapon",2,-22,14},{"conItem",10,22,12},{"abChip",1,0,-22},{"insItem",8,0,24}};
            for(unsigned i=0;i<sizeof row/sizeof *row;i++){dw4_drop_entry en={0};float where[3]={at[0]+row[i].dx,at[1],at[2]+row[i].dz};
                snprintf(en.category,sizeof en.category,"%s",row[i].category);en.id=row[i].id;en.rate=1;assert(dw4_fieldgen_inject_drop(g,"GENE-08",&en,where));}
            unsigned shots=0;const char *prefix=getenv("DW4_LOOT_BLINK");
            for(unsigned f=0;f<1500 && shots<8;f++){
                int boding=0;
                for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t sl;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&sl);
                    const char *sq=mc && info && !strncmp(dw4_stageobject_name(info),"g_000",5) && dw4_modelctrl_active(mc)?dw4_modelctrl_sequence(mc):NULL;if(sq && !strcmp(sq,"SQ_BODING"))boding=1;}
                if(boding){dw4_fb fb;char path[512];assert(!dw4_fb_init(&fb,640,448));assert(dw4_hubruntime_draw(h,&fb,NULL)>0);snprintf(path,sizeof path,"%s-blink%u.png",prefix,shots++);
                    assert(!dw4_png_write(path,fb.rgba,fb.w,fb.h));dw4_fb_free(&fb);run(h,&frame,13,0,0);}
                else run(h,&frame,1,0,0);
            }
            fprintf(stderr,"blink frames written: %u\n",shots);return shots==8?0:1;
        }
        /* a drop of the floor's own list, found by category (the draw that lands on it is one past the sum of the rates before it: a remainder <= 0 selects) */
        #define FIND_DROP(CAT,OUT) do{ int found_=0; for(size_t gi_=0;gi_<dw4_fieldgen_count(g) && !found_;gi_++){const dw4_gene *e_=dw4_fieldgen_at(g,gi_);\
            for(unsigned l_=0;l_<2 && !found_;l_++){int32_t sum_=0;for(unsigned k_=0;k_<e_->ndrops[l_] && !found_;k_++){\
                if(!strcmp(e_->drops[l_][k_].category,CAT)){dw4_drop_entry t_;assert(dw4_fieldgen_roll_drop(e_,(int)l_,(uint32_t)sum_+1,&t_) && !strcmp(t_.category,CAT));OUT=t_;found_=1;}\
                sum_+=e_->drops[l_][k_].rate;}}} if(!found_){memset(&OUT,0,sizeof OUT);snprintf(OUT.category,sizeof OUT.category,"%s",CAT);OUT.id=-1;} }while(0)
        const dw4_hubruntime_loot *lf=dw4_hubruntime_loot_stats(h);
        {   /* every model name the drop spawn can ask for has a controller in this floor's pack (FUN_00384800: g_000key / weapon / armor / access, and the MODEL column of conItem / insItem) */
            for(int k=0;k<DW4_LOOT_MODELS;k++){
                int pool=0;for(int32_t sl=0;sl<16;sl++)if(dw4_controllers_live(dw4_hubruntime_models(h),dw4_loot_model_name(k),sl)>=0)pool++;
                fprintf(stderr,"dng101b2 drop model %s: %d instances\n",dw4_loot_model_name(k),pool);
                assert(pool>=1);
            }
            assert(running_models(h,"g_000key")==0 && lf->spawned==0 && lf->unmodelled==0);
        }
        /* ---- the boss key: GENE-08 (Blossomon's own generator) lists impItem 0 at rate 10000 ---- */
        {
            const dw4_gene *e=dw4_fieldgen_find(g,"GENE-08");dw4_drop_entry key;assert(e && e->ndrops[1]==1 && dw4_fieldgen_roll_drop(e,1,0,&key) && dw4_fieldgen_roll_drop(e,1,9999,&(dw4_drop_entry){0}));
            assert(!strcmp(key.category,"impItem") && key.id==0);
            const uint8_t *fb=dw4_property_bytes(dw4_playerrecords_get(rec,"GETCOMMON",0),"FLAGFOLDER",NULL);assert(fb && !fb[0] && !fb[1]);
            float keyat[3]={at[0]+4,at[1],at[2]+3};   /* beside the player, within 8 units: its label shows and the model is not hidden by the player's body */
            dw4_drop *d=dw4_fieldgen_inject_drop(g,"GENE-08",&key,keyat);assert(d && d->loot_ready && d->loot.model_kind==DW4_LOOT_KEY && d->loot.category==DW4_LOOT_IMP);
            /* the drop is a MODELCTRL model: g_000key on its pool's first instance, running at the drop's position */
            assert(!strcmp(d->model,"g_000key") && d->model_slot==0 && d->model_live && lf->spawned==1 && running_models(h,"g_000key")==1);
            run(h,&frame,30,0,0);
            {   /* the label: the first player stands within 8 units, so ITNAMEFONT font00 shows the item's NAME, centred */
                const char *name=dw4_database_string(dw4_databases_get(dw4_hubruntime_databases(h),"impItem"),0,"NAME");
                const dw4_dialogue_text *t=label_text(h,0);
                assert(name && t && t->visible && t->align==2 && t->count>0 && lf->labels_on==1 && lf->labels_off==0 && !strcmp(lf->last_label,name) && lf->last_label_slot==0);
                assert(!label_text(h,1)->visible);   /* nobody else holds a label */
                fprintf(stderr,"boss key label: '%s' (%zu glyphs) at (%g,%g)\n",name,t->count,t->x,t->y);
                if(getenv("DW4_LOOT_SHOT")){dw4_fb fb;char path[512];assert(!dw4_fb_init(&fb,640,448));assert(dw4_hubruntime_draw(h,&fb,NULL)>0);snprintf(path,sizeof path,"%s-key.png",getenv("DW4_LOOT_SHOT"));assert(!dw4_png_write(path,fb.rgba,fb.w,fb.h));dw4_fb_free(&fb);}
            }
            fb=dw4_property_bytes(dw4_playerrecords_get(rec,"GETCOMMON",0),"FLAGFOLDER",NULL);
            size_t nd;d=dw4_fieldgen_drops_mut(g,&nd)+nd-1;
            assert(!d->collected && !fb[0] && dw4_hubruntime_pickups(h)==0);   /* standing on a named drop only shows its label */
            {   /* beNDMWMdlPlayer::vfunc_38: the Cross press that a pickup takes does not also swing (the branch swings only when no bool came back) */
                const char *seq=dw4_modelctrl_sequence(dw4_lobby_player_model(dw4_hubruntime_world(h)));assert(!seq || strcmp(seq,"SQ_ATCK1"));
                dw4_hubruntime_input(h,0,0,0,0x4000,0x4000);
                seq=dw4_modelctrl_sequence(dw4_lobby_player_model(dw4_hubruntime_world(h)));assert(!seq || strcmp(seq,"SQ_ATCK1"));
                assert(dw4_hubruntime_pickups(h)==1);   /* delivered when the press arrived */
            }
            assert(!dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60));
            {const char *seq=dw4_modelctrl_sequence(dw4_lobby_player_model(dw4_hubruntime_world(h)));fprintf(stderr,"after the key press the player is in %s\n",seq?seq:"-");assert(!seq || strcmp(seq,"SQ_ATCK1"));}
            fb=dw4_property_bytes(dw4_playerrecords_get(rec,"GETCOMMON",0),"FLAGFOLDER",NULL);
            d=dw4_fieldgen_drops_mut(g,&nd)+nd-1;
            fprintf(stderr,"boss key: FLAGFOLDER[0] %d, collected %d, pickups %u\n",fb[0],d->collected,dw4_hubruntime_pickups(h));
            assert(d->collected && fb[0]==1 && !fb[1] && dw4_hubruntime_pickups(h)==1);
            /* DROPITEM answered: the label is dropped, the model plays SQ_DDMG and is erased (its instance is free again) */
            assert(lf->dropitems==1 && lf->labels_off==1 && lf->erased==1 && !label_text(h,0)->visible);
            run(h,&frame,120,0,0);
            assert(!d->model_live && running_models(h,"g_000key")==0 && lf->expired==0);
            {   /* a plain press, with nothing to pick up, swings */
                dw4_hubruntime_input(h,0,0,0,0x4000,0x4000);
                const char *seq=dw4_modelctrl_sequence(dw4_lobby_player_model(dw4_hubruntime_world(h)));assert(seq && !strcmp(seq,"SQ_ATCK1"));
                assert(!dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60));
                run(h,&frame,120,0,0);
                seq=dw4_modelctrl_sequence(dw4_lobby_player_model(dw4_hubruntime_world(h)));assert(!seq || strcmp(seq,"SQ_ATCK1"));   /* the swing is over */
                dw4_modelctrl_actor_state(dw4_lobby_player_model(dw4_hubruntime_world(h)),&pa);memcpy(at,pa.position,12);   /* the swing moved the player: later drops go where it stands */
            }
        }
        /* ---- a weapon, an armour and a chip: DEVICEFOLDER grows by the rolled item ---- */
        {
            static const char *const cats[]={"weapon","armor1","armor2","abChip"};
            for(unsigned c=0;c<4;c++){
                dw4_drop_entry en;FIND_DROP(cats[c],en);if(en.id<0)en.id=2;   /* no generator of this floor lists it: an authored-looking row */
                size_t before=0;assert(!dw4_property_item_count(p0,"DEVICEFOLDER",&before));
                dw4_random expect=dw4_hubruntime_state(h)->random;   /* the stream before the injection; the item draws after the drop's own */
                dw4_drop *d=dw4_fieldgen_inject_drop(g,"GENE-08",&en,at);assert(d && d->loot_ready);
                int32_t pocket=0,revision=0;
                if(c<3){
                    uint32_t a=dw4_random_next(&expect),b=dw4_random_next(&expect),cc=c==2?0:dw4_random_next(&expect);
                    if(c==2){revision=1;(void)a;(void)b;(void)cc;}
                    uint32_t level=40,p1=a,r1=b,r2=cc;
                    if(c==2){ /* yellow armour: revision only, draws a and b */
                        int first=(int)(a%6000u)+1,second=(int)(b%level)+1;revision=first==1?(int)level+1:first<3001?second-first/10:0;if(revision<0)revision=0;
                    }else{
                        int v=(int)(p1%620u)+1-((int)(level/10+10)/10);pocket=v==1?5:v<4?4:v<8?3:v<16?2:v<32?1:0;
                        int first=(int)(r1%6000u)+1,second=(int)(r2%level)+1;revision=first==1?(int)level+1:first<3001?second-first/10:0;if(revision<0)revision=0;
                    }
                }
                assert(d->loot.item.kind==(c<3?(int)c:3) && d->loot.item.pocket==pocket && d->loot.item.revision==revision && d->loot.model_kind>=DW4_LOOT_ACCESS);
                {   static const char *const model[4]={"g_000weapon","g_000armor","g_000armor","g_000access"};
                    assert(!strcmp(d->model,model[c]) && d->model_live && running_models(h,model[c])==1);}
                run(h,&frame,5,0,0);
                {   const dw4_dialogue_text *t=label_text(h,0);   /* the NAME of the weapon / armour / chip row, in the colour its revision gives */
                    const char *name=dw4_database_string(dw4_databases_get(dw4_hubruntime_databases(h),cats[c]),en.id,"NAME");
                    assert(t && t->visible && name && !strcmp(lf->last_label,name));
                    float want[3];dw4_loot_label_color(&d->loot,want);
                    assert(fabsf(t->color[0]-want[0])<1e-5f && fabsf(t->color[1]-want[1])<1e-5f && fabsf(t->color[2]-want[2])<1e-5f);}
                size_t after=0;assert(!dw4_property_item_count(p0,"DEVICEFOLDER",&after) && after==before);   /* no pickup without Cross */
                dw4_hubruntime_input(h,0,0,0,0x4000,0x4000);assert(!dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60));
                const dw4_item_record *items=dw4_property_items(p0,"DEVICEFOLDER",&after);
                fprintf(stderr,"%s id %d: DEVICEFOLDER %zu -> %zu, item kind %d record %d pocket %d revision %d\n",cats[c],en.id,before,after,after?items[after-1].kind:-1,after?items[after-1].record:-1,after?items[after-1].pocket:-1,after?items[after-1].revision:-1);
                assert(after==before+1 && items[after-1].kind==d->loot.item.kind && items[after-1].record==en.id && items[after-1].pocket==pocket && items[after-1].revision==revision && !items[after-1].equipped);
                assert(!label_text(h,0)->visible);
                run(h,&frame,120,0,0);
                {size_t nd2;d=dw4_fieldgen_drops_mut(g,&nd2)+nd2-1;}
                assert(d->collected && !d->model_live && running_models(h,cats[c][0]=='w'?"g_000weapon":cats[c][0]=='a' && cats[c][3]=='C'?"g_000access":"g_000armor")==0);
            }
        }
        /* ---- BIT, x-data and a UPCNT item: taken by standing there ---- */
        {
            dw4_drop_entry en;int32_t x0=0,bit0=0,mhp0=0;size_t n;
            assert(!dw4_property_number(p0,"XDATA",&x0) && !dw4_property_number(p0,"BIT",&bit0) && !dw4_property_number(p0,"MHP",&mhp0));
            unsigned popups0=dw4_hubruntime_popup_stats(h)->spawned[4];
            dw4_modelctrl_actor_state(dw4_lobby_player_model(dw4_hubruntime_world(h)),&pa);memcpy(at,pa.position,12);   /* the floor's enemies push the player about: drops go where it stands now */
            snprintf(en.category,sizeof en.category,"insItem");en.id=3;en.rank=0;en.rate=1;   /* x-data3: UP 100 */
            assert(dw4_fieldgen_inject_drop(g,"GENE-08",&en,at));run(h,&frame,3,0,0);
            int32_t x1=0;assert(!dw4_property_number(p0,"XDATA",&x1) && x1==x0+100);
            /* the 'got item' effect of FUN_004412c0 on the receiving player: panel i_getitempnl02, sequence SQ_X100UP (record 3); the panel runs, then ends */
            assert(lf->effects==1 && lf->last_effect_slot==0 && !strcmp(lf->last_effect_panel,"i_getitempnl02") && !strcmp(lf->last_effect_sequence,"SQ_X100UP"));
            {unsigned seen=0;for(unsigned f=0;f<240 && !seen;f++){run(h,&frame,1,0,0);seen=running_models(h,"i_getitempnl02");}
             fprintf(stderr,"x-data effect panel running: %u\n",seen);assert(seen>=1);
             if(getenv("DW4_LOOT_SHOT")){   /* the panel's first frames: it plays X100UP on the receiving player */
                 for(unsigned shot=0;shot<5;shot++){dw4_fb fb;char path[512];assert(!dw4_fb_init(&fb,640,448));assert(dw4_hubruntime_draw(h,&fb,NULL)>0);
                     snprintf(path,sizeof path,"%s-xdata%u.png",getenv("DW4_LOOT_SHOT"),shot);assert(!dw4_png_write(path,fb.rgba,fb.w,fb.h));dw4_fb_free(&fb);run(h,&frame,8,0,0);}}
             run(h,&frame,400,0,0);assert(running_models(h,"i_getitempnl02")==0 && running_models(h,"g_000xdata2")==0);
             dw4_modelctrl_actor_state(dw4_lobby_player_model(dw4_hubruntime_world(h)),&pa);memcpy(at,pa.position,12);}   /* the floor's enemies pushed the player about: drops go where it stands now */
            en.id=0;assert(dw4_fieldgen_inject_drop(g,"GENE-08",&en,at));run(h,&frame,3,0,0);
            int32_t bit1=0;assert(!dw4_property_number(p0,"BIT",&bit1));
            {int32_t hp=-1;dw4_modelctrl_actor pq;dw4_modelctrl_actor_state(dw4_lobby_player_model(dw4_hubruntime_world(h)),&pq);dw4_property_number(p0,"HP",&hp);fprintf(stderr,"BIT drop: player HP %d at (%g,%g,%g), drop at (%g,%g,%g)\n",hp,pq.position[0],pq.position[1],pq.position[2],at[0],at[1],at[2]);}
            fprintf(stderr,"BIT drop at level 40: %d -> %d\n",bit0,bit1);
            int32_t ritsu=0;assert(!dw4_property_number(p0,"BITRITSU",&ritsu));
            assert(bit1>=bit0+87*(ritsu+100)/100 && bit1<bit0+195*(ritsu+100)/100 && dw4_hubruntime_popup_stats(h)->spawned[4]==popups0+1);   /* the level 40 band, 87..194, with the player's BITRITSU percent */
            const int32_t *up=dw4_property_array(p0,"UPCNT",&n);int32_t u0[11];assert(up && n==11);memcpy(u0,up,sizeof u0);
            en.id=8;assert(dw4_fieldgen_inject_drop(g,"GENE-08",&en,at));run(h,&frame,3,0,0);   /* record 8: UP 1, UPCNT slot 0 (max HP) */
            assert(lf->effects==2 && !strcmp(lf->last_effect_panel,"i_getitempnl03") && !strcmp(lf->last_effect_sequence,"SQ_MHPUP"));   /* record 8 is the table's MHPUP row */
            up=dw4_property_array(p0,"UPCNT",&n);int32_t mhp1=0;assert(up && !dw4_property_number(p0,"MHP",&mhp1));
            fprintf(stderr,"UPCNT item 8: slot 0 %d -> %d, MHP %d -> %d\n",u0[0],up[0],mhp0,mhp1);
            assert(up[0]==u0[0]+1 && mhp1>mhp0);   /* the player was recalculated: the extra point of max HP counts */
            size_t nd;dw4_drop *dr=dw4_fieldgen_drops_mut(g,&nd);
            for(size_t i=nd0;i<nd;i++)assert(dr[i].collected);
        }
        /* ---- a disk: boost1 (conItem 10) +1, refused at nine ---- */
        {
            dw4_modelctrl_actor_state(dw4_lobby_player_model(dw4_hubruntime_world(h)),&pa);memcpy(at,pa.position,12);
            dw4_drop_entry en;snprintf(en.category,sizeof en.category,"conItem");en.id=10;en.rank=0;en.rate=1;
            size_t n;const dw4_item_record *dk=dw4_property_items(p0,"DISKFOLDER",&n);assert(dk && n==12);int32_t c0=-1;for(size_t i=0;i<n;i++)if(dk[i].record==10)c0=dk[i].revision;assert(c0>=0);
            for(int round=0;round<12;round++){
                assert(dw4_fieldgen_inject_drop(g,"GENE-08",&en,at));run(h,&frame,2,0,0);
                dw4_hubruntime_input(h,0,0,0,0x4000,0x4000);assert(!dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60));
                dk=dw4_property_items(p0,"DISKFOLDER",&n);int32_t c1=-1;for(size_t i=0;i<n;i++)if(dk[i].record==10)c1=dk[i].revision;
                size_t nd;dw4_drop *dr=dw4_fieldgen_drops_mut(g,&nd);
                const char *seq=dw4_modelctrl_sequence(dw4_lobby_player_model(dw4_hubruntime_world(h)));
                if(c0<9){assert(c1==c0+1 && dr[nd-1].collected);c0=c1;assert(!seq || strcmp(seq,"SQ_ATCK1"));}   /* a delivered disk takes the press: no swing */
                else{assert(c1==9 && !dr[nd-1].collected);assert(seq && !strcmp(seq,"SQ_ATCK1"));break;}   /* the tenth stays on the ground and the refused press swings */
                if(c0==9){assert(dw4_fieldgen_inject_drop(g,"GENE-08",&en,at));run(h,&frame,2,0,0);dw4_hubruntime_input(h,0,0,0,0x4000,0x4000);assert(!dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60));
                    dr=dw4_fieldgen_drops_mut(g,&nd);dk=dw4_property_items(p0,"DISKFOLDER",&n);for(size_t i=0;i<n;i++)if(dk[i].record==10)c1=dk[i].revision;assert(c1==9 && !dr[nd-1].collected);
                    seq=dw4_modelctrl_sequence(dw4_lobby_player_model(dw4_hubruntime_world(h)));assert(seq && !strcmp(seq,"SQ_ATCK1"));break;}
            }
            fprintf(stderr,"boost1 disks held: %d (a tenth stays on the ground)\n",(int)c0);
        }
        if(getenv("DW4_LOOT_SHOT")){   /* a frame with drop models standing around the player (not picked up: 12..28 units away; the camera is close, about 7 pixels per unit) */
            dw4_modelctrl_actor_state(dw4_lobby_player_model(dw4_hubruntime_world(h)),&pa);memcpy(at,pa.position,12);
            static const struct {const char *category;int id;float dx,dz;} row[]={{"insItem",0,-24,-14},{"insItem",1,22,-14},{"weapon",2,-22,14},{"conItem",10,22,12},{"abChip",1,0,-22},{"insItem",8,0,24}};
            for(unsigned i=0;i<sizeof row/sizeof *row;i++){dw4_drop_entry en={0};float where[3]={at[0]+row[i].dx,at[1],at[2]+row[i].dz};
                snprintf(en.category,sizeof en.category,"%s",row[i].category);en.id=row[i].id;en.rate=1;assert(dw4_fieldgen_inject_drop(g,"GENE-08",&en,where));}
            run(h,&frame,90,0,0);
            dw4_fb fb;char path[512];assert(!dw4_fb_init(&fb,640,448));assert(dw4_hubruntime_draw(h,&fb,NULL)>0);snprintf(path,sizeof path,"%s-field.png",getenv("DW4_LOOT_SHOT"));assert(!dw4_png_write(path,fb.rgba,fb.w,fb.h));dw4_fb_free(&fb);
            return 0;
        }
        {   /* the pool: g_000bit has eight instances; a ninth BIT drop finds none, so GENERATE builds no item (nothing rolled, nothing to pick up) */
            run(h,&frame,60,0,0);
            dw4_drop_entry en;snprintf(en.category,sizeof en.category,"insItem");en.id=0;en.rank=0;en.rate=1;
            float far[3]={at[0]+400,at[1],at[2]};unsigned lost0=lf->lost,spawned0=lf->spawned,expired0=lf->expired;
            dw4_random before=dw4_hubruntime_state(h)->random;
            for(unsigned i=0;i<8;i++){dw4_drop *d=dw4_fieldgen_inject_drop(g,"GENE-08",&en,far);assert(d && d->model_live && d->loot_ready);far[0]+=20;}
            assert(running_models(h,"g_000bit")==8 && lf->spawned==spawned0+8);
            dw4_random mid=dw4_hubruntime_state(h)->random;(void)before;
            dw4_drop *ninth=dw4_fieldgen_inject_drop(g,"GENE-08",&en,far);
            assert(ninth && ninth->collected && !ninth->loot_ready && !ninth->model_live && lf->lost==lost0+1 && lf->spawned==spawned0+8);
            assert(!memcmp(&mid,&dw4_hubruntime_state(h)->random,sizeof mid));   /* the lost drop rolled nothing */
            /* uncollected, the unnamed models blink out after their 960-frame wait (SQ_BODING: the authored 23-component FLASH1, ten fade-outs of 10 frames) and end: the items go with them */
            unsigned f=0,boding0=0,boding1=0,dark=0,bright=0,toggles=0,end_frame=0;float low=1,prev=1;int in_boding=0;
            for(;f<1500 && running_models(h,"g_000bit");f++){
                run(h,&frame,1,0,0);
                const dw4_modelctrl *watch=NULL;   /* the first running BIT model stands for the eight (they were generated in one step) */
                for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h)) && !watch;k++){const dw4_stageobject *info;int32_t sl;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&sl);
                    if(mc && info && !strcmp(dw4_stageobject_name(info),"g_000bit") && dw4_modelctrl_active(mc))watch=mc;}
                if(!watch)break;
                const char *sq=dw4_modelctrl_sequence(watch);int boding=sq && !strcmp(sq,"SQ_BODING");float a=dw4_modelctrl_alpha(watch);
                if(boding){if(!in_boding){in_boding=1;boding0=f;}boding1=f;
                    if(a<0.5f)dark++;if(a>0.9f)bright++;if(a<low)low=a;if(a>prev+0.3f)toggles++;   /* a restarted fade-out */}
                prev=a;
            }
            end_frame=f;
            fprintf(stderr,"eight uncollected BIT models ended after %u frames; expired %u; blink-out SQ_BODING frames %u..%u: %u dark, %u bright, %u restarts, lowest alpha %g\n",
                end_frame,lf->expired-expired0,boding0,boding1,dark,bright,toggles,low);
            assert(running_models(h,"g_000bit")==0 && lf->expired==expired0+9 && f>1000 && f<1200);   /* the eight BIT models and the refused tenth disk (g_000boost1 blinks out too: it also lies uncollected) */
            /* the blink runs in the last part of the wait: the model is dark in places and bright in others, ten fade-outs restart it */
            assert(in_boding && boding0>=900 && boding1>boding0+100 && dark>=20 && bright>=20 && toggles>=8 && low<0.2f);
            size_t nd;dw4_drop *dr=dw4_fieldgen_drops_mut(g,&nd);for(size_t i=0;i<nd;i++)assert(dr[i].collected && !dr[i].model_live);
            assert(lf->failed==0);
            {   /* no model skipped its blink-out: the Action2 host holds the 23-component FLASH1 */
                unsigned skipped=0;
                for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t sl;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&sl);
                    if(mc && info && !strncmp(dw4_stageobject_name(info),"g_000",5))skipped+=dw4_modelctrl_long_actions(mc);}
                fprintf(stderr,"blink-out actions skipped: %u\n",skipped);assert(skipped==0);
            }
        }
        #undef FIND_DROP
        dw4_hubruntime_close(h);
        printf("loot: dng101b2 boss key sets FLAGFOLDER[0]; weapon/armour/chip land in DEVICEFOLDER with the rolled pocket and revision; BIT, x-data and UPCNT items walk-over; disks stop at nine\n");
        return 0;
    }
    if(!strcmp(mode,"lootmodels")) {
        /* Which drop models each playable field / dungeon stage carries (FUN_00384800 asks for one of the ten g_000* names): a name without a controller keeps its drops
         * record-only (dw4_hubruntime_loot.unmodelled). The key has one instance everywhere; every other model has eight. */
        static const struct {const char *stage;int32_t point;} stages[]={{"stag0101",0},{"stagGF01",0},{"stagGF02",0},{"stagGF03",0}};
        for(unsigned i=0;i<sizeof stages/sizeof *stages;i++){
            const int fl[]={2,355,503};setenv("STAGE",stages[i].stage,1);dw4_hubruntime *hh=enter(&mount,fl,3);
            fprintf(stderr,"%s drop models:",stages[i].stage);
            for(int k=0;k<DW4_LOOT_MODELS;k++){int pool=0;for(int32_t sl=0;sl<16;sl++)if(dw4_controllers_live(dw4_hubruntime_models(hh),dw4_loot_model_name(k),sl)>=0)pool++;
                fprintf(stderr," %s=%d",dw4_loot_model_name(k)+6,pool);}
            fputc(10,stderr);
            {   /* every drop model of the stage opened its 23-component FLASH1 (and every other action) within the Action2 host's storage */
                unsigned long_actions=0,models=0;
                for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(hh));k++){const dw4_stageobject *info;int32_t sl;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(hh),k,&info,&sl);
                    if(mc && info && !strncmp(dw4_stageobject_name(info),"g_000",5)){models++;long_actions+=dw4_modelctrl_long_actions(mc);}}
                fprintf(stderr,"%s: %u drop model instances, %u actions over the host's storage\n",stages[i].stage,models,long_actions);assert(models>=10 && !long_actions);
            }
            dw4_hubruntime_close(hh);
        }
        unsetenv("STAGE");
        return 0;
    }
    if(!strcmp(mode,"genediff")) {
        /* The generator sets by difficulty (generator<n|h|v>.igb) against a retail read: with the common DIFFICULTY record at 1 (Hard) the seven dng101b1 generators
         * spawned enemy row 17 (Numemon) with HPMAX 624, where the Normal set spawns row 13 with HPMAX 54. The hub runtime picks the set from that record. */
        static const int32_t rows[3]={13,17,-1};
        for(int d=0;d<2;d++){
            dw4_fieldgen *g=dw4_fieldgen_open(&mount,"dng101b1",d);assert(g);
            for(unsigned i=1;i<=7;i++){char name[16];snprintf(name,sizeof name,"GENE-%02u",i);const dw4_gene *e=dw4_fieldgen_find(g,name);assert(e && e->enemy_row==rows[d]);}
            printf("dng101b1 difficulty %d: seven generators on row %d\n",d,rows[d]);dw4_fieldgen_close(g);
        }
        {   const int fl[]={2,355,503};setenv("STAGE","dng101b1",1);h=enter(&mount,fl,3);
            dw4_property_folder *common=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0);int32_t before=-1;
            assert(common && !dw4_property_number(common,"DIFFICULTY",&before) && before==0);
            const dw4_gene *e=dw4_fieldgen_find(dw4_hubruntime_fieldgen(h),"GENE-01");assert(e && e->enemy_row==13);dw4_hubruntime_close(h);unsetenv("STAGE");
        }
        {   /* a Hard save: the hub runtime opens generatorh.igb */
            const int fl[]={2,355,503};setenv("STAGE","dng101b1",1);setenv("DW4_TEST_DIFFICULTY","1",1);h=enter(&mount,fl,3);unsetenv("DW4_TEST_DIFFICULTY");unsetenv("STAGE");
            const dw4_gene *e=dw4_fieldgen_find(dw4_hubruntime_fieldgen(h),"GENE-01");assert(e && e->enemy_row==17);
            int32_t hp=0;const dw4_database *enemy=dw4_databases_get(dw4_hubruntime_databases(h),"enemy");
            assert(enemy && !dw4_database_number(enemy,17,"HPMAX",&hp) && hp==624);
            printf("a Hard save opens generatorh: GENE-01 row 17, HPMAX %d (retail read: 624)\n",hp);dw4_hubruntime_close(h);
        }
        return 0;
    }
    if(!strcmp(mode,"matregion")) {   /* STAGE=<stage> NAME=<mat name>: print the box of a beMatCtrlData region (for placing a retail player with emu_state teleport) */
        float lo[3],hi[3];mat_region(&mount,getenv("STAGE")?getenv("STAGE"):"stagML11",getenv("NAME")?getenv("NAME"):"mate00",lo,hi);
        printf("region %s/%s: lo %.1f %.1f %.1f hi %.1f %.1f %.1f\n",getenv("STAGE")?getenv("STAGE"):"stagML11",getenv("NAME")?getenv("NAME"):"mate00",lo[0],lo[1],lo[2],hi[0],hi[1],hi[2]);
        return 0;
    }
    if(!strcmp(mode,"gendrops")) {
        /* The decoded drop lists of every generator of a stage (STAGE, DIFF 0..2): the first list and the last-kill list. */
        dw4_fieldgen *g=dw4_fieldgen_open(&mount,getenv("STAGE")?getenv("STAGE"):"dng101b2",getenv("DIFF")?atoi(getenv("DIFF")):0);assert(g);
        for(size_t i=0;i<dw4_fieldgen_count(g);i++){const dw4_gene *e=dw4_fieldgen_at(g,i);
            printf("%s row %d: item list %u entries, last list %u entries\n",e->name,e->enemy_row,e->ndrops[0],e->ndrops[1]);
            if(getenv("POINTS")){printf("   start %s/%g fill %s/%g global %d pos %.0f %.0f %.0f points %u count %d",e->start_mode,e->start_data,e->fill_mode,e->fill_data,e->global,e->pos[0],e->pos[1],e->pos[2],e->npoints,e->count[0]);if(e->npoints)printf(" first %.0f %.0f %.0f",e->points[0],e->points[1],e->points[2]);printf("\n");}
            for(unsigned l=0;l<2;l++)for(unsigned k=0;k<e->ndrops[l] && k<12;k++)printf("   [%u] %s id %d rank %d rate %d\n",l,e->drops[l][k].category,e->drops[l][k].id,e->drops[l][k].rank,e->drops[l][k].rate);}
        return 0;
    }
    if(!strcmp(mode,"dungeoncoop")) {
        /* Two local players enter the Humid Cave together: the second joins from stag0101's records (an Agumon "Mate"), both appear at their authored arrival
         * points, both walk under their own pad, and the camera frames their centre. */
        const int fl[]={2,355,503};h=enter(&mount,fl,3);
        unsigned until=0;
        for(;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        {   dw4_playerrecords *rec=dw4_hubruntime_records(h);const dw4_databases *db=dw4_hubruntime_databases(h);char error[256];
            assert(!dw4_playerrecords_create(rec,db,1,"p_agumon","Mate",error,sizeof error));
            assert(!dw4_property_set_number(dw4_playerrecords_get(rec,"GETCOMMON",0),"NINZU",2) && !dw4_property_set_number(dw4_playerrecords_get(rec,"GETPLAYER",1),"ISUSE",1));}
        h=take_exit(&mount,h,&frame,"stag0101","matz00","dng101b1",0);
        assert(dw4_lobby_player_count(dw4_hubruntime_world(h))==2);
        for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        run(h,&frame,600,0,0);
        if(getenv("HUDMODELS")){for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
            if((!strncmp(dw4_stageobject_name(info),"i_",2)||!strncmp(dw4_stageobject_name(info),"g_",2)) && (!strncmp(dw4_stageobject_name(info),getenv("HUDMODELS"),strlen(getenv("HUDMODELS"))))){dw4_modelctrl_actor ha;dw4_modelctrl_actor_state(mc,&ha);fprintf(stderr,"hud time %lld pos %g %g %g motion_ns %lld\n",(long long)dw4_modelctrl_time(mc),ha.position[0],ha.position[1],ha.position[2],(long long)ha.motion_ns);fprintf(stderr,"hud %s[%d] kind %s active %d seq %s\n",dw4_stageobject_name(info),slot,dw4_stageobject_kind_string(info)?dw4_stageobject_kind_string(info):"-",dw4_modelctrl_active(mc),dw4_modelctrl_sequence(mc)?dw4_modelctrl_sequence(mc):"-");}}}
        if(getenv("DESCRIBE_DM")){fprintf(stderr,"DM groups: %zu\n",dw4_scriptengine_pending(dw4_hubruntime_scripts(h)));dw4_scriptengine_describe(dw4_hubruntime_scripts(h),stderr);}
        dw4_lobby_walk_state w0,w1;
        assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w0) && !dw4_lobby_select_player(dw4_hubruntime_world(h),1) && !dw4_lobby_walk(dw4_hubruntime_world(h),&w1));
        dw4_lobby_select_player(dw4_hubruntime_world(h),0);
        fprintf(stderr,"player 0 at %g %g %g, player 1 at %g %g %g\n",w0.position[0],w0.position[1],w0.position[2],w1.position[0],w1.position[1],w1.position[2]);
        assert(fabsf(w0.position[0]-w1.position[0])+fabsf(w0.position[2]-w1.position[2])>1);
        /* Each pad drives its own player: slot 1's stick moves only slot 1; slot 0's stick moves only slot 0. */
        for(unsigned t=0;t<90;t++){
            dw4_hubruntime_input(h,0,0,0,0,0);dw4_hubruntime_input_slot(h,1,0,1,0,0,0);
            if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));return 1;}
        }
        dw4_lobby_walk_state m0,m1;assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&m0) && !dw4_lobby_select_player(dw4_hubruntime_world(h),1) && !dw4_lobby_walk(dw4_hubruntime_world(h),&m1));
        dw4_lobby_select_player(dw4_hubruntime_world(h),0);
        float moved1=fabsf(m1.position[0]-w1.position[0])+fabsf(m1.position[2]-w1.position[2]),moved0=fabsf(m0.position[0]-w0.position[0])+fabsf(m0.position[2]-w0.position[2]);
        fprintf(stderr,"after slot 1's stick: player 0 moved %g, player 1 moved %g (motion %s)\n",moved0,moved1,m1.motion?m1.motion:"-");
        assert(moved1>5 && moved0<0.5f);
        for(unsigned t=0;t<90;t++){
            dw4_hubruntime_input(h,0,1,0,0,0);dw4_hubruntime_input_slot(h,1,0,0,0,0,0);
            if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));return 1;}
        }
        dw4_lobby_walk_state n0,n1;assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&n0) && !dw4_lobby_select_player(dw4_hubruntime_world(h),1) && !dw4_lobby_walk(dw4_hubruntime_world(h),&n1));
        dw4_lobby_select_player(dw4_hubruntime_world(h),0);
        float moved0b=fabsf(n0.position[0]-m0.position[0])+fabsf(n0.position[2]-m0.position[2]),moved1b=fabsf(n1.position[0]-m1.position[0])+fabsf(n1.position[2]-m1.position[2]);
        fprintf(stderr,"after slot 0's stick: player 0 moved %g, player 1 moved %g\n",moved0b,moved1b);
        assert(moved0b>5 && moved1b<3);
        {   /* the presentation path draws every joined player (body, shadow caster, weapon) from its own slot; DW4_COOP_SHOT=<png> keeps the frame */
            dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));
            dw4_fefont font;int have_font=!dw4_fefont_load(&font,"../../local/extracted");
            int drawn=dw4_hubruntime_draw(h,&fb,getenv("DW4_COOP_FONT") && have_font?&font:NULL);assert(drawn>0);
            {   /* the field HUD: each joined player's panel shows its gauge ring at the bottom left (a bright green HP arc inside the first panel's box) */
                unsigned green=0;
                for(unsigned y=350;y<420;y++)for(unsigned x=30;x<100;x++){const uint8_t *px=fb.rgba+4*((size_t)y*fb.w+x);if(px[1]>180 && px[0]<120 && px[2]<140)green++;}
                assert(green>20);
            }
            if(getenv("DW4_COOP_SHOT"))assert(!dw4_png_write(getenv("DW4_COOP_SHOT"),fb.rgba,fb.w,fb.h));
            dw4_fb_free(&fb);if(have_font)dw4_fefont_free(&font);
        }
        printf("dungeon co-op: 2 players in dng101b1, each pad drives its own player\n");
        return 0;
    }
    if(!strcmp(mode,"coopmenus")) {
        /* Local co-op talk and selectors on pads 2-4 (a field world; the hubs open one player). Two players stand in stag0101: slot 1 (pad 2) presses Cross at an NPC.
         * Retail (hub NPC scripts, 058-model-seq-7.lua and the stag0101 recorders): the talk script stores g_messPlayerNo = BLTgetShootRamNo() (the pressing
         * slot), g_npcRamNo = MDLgetRamNo(), locks every player (PLAYER nil -1 OFCTRL) and only the talker's model is set to SQ_WAIT; the message and its
         * selectors then read the pad of g_messPlayerNo. The page waits for the talker's pad: pad 1 cannot advance it. */
        const int fl[]={2,355,503};h=enter(&mount,fl,3);
        unsigned until=0;
        for(;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        h=rejoin_party(&mount,h,"stag0101",2);
        for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        run(h,&frame,300,0,0);
        assert(dw4_lobby_player_count(dw4_hubruntime_world(h))==2 && control(h) && slot_control(h,1));
        {   /* Square on pad 2 requests SQ_GUARD on slot 1's model only (vfunc_38's guard request, issued per slot; findings #3040) */
            dw4_lobby *wd=dw4_hubruntime_world(h);struct padw idle[4]={{0}},sq1[4]={{0},{0,0x8000,0x8000}};
            coop_tick(h,&frame,2,sq1);
            assert(!dw4_lobby_select_player(wd,1));const char *s1=dw4_modelctrl_sequence(dw4_lobby_player_model(wd));assert(s1 && !strcmp(s1,"SQ_GUARD"));
            assert(!dw4_lobby_select_player(wd,0));const char *s0=dw4_modelctrl_sequence(dw4_lobby_player_model(wd));assert(s0 && strcmp(s0,"SQ_GUARD"));
            for(unsigned t=0;t<60;t++)coop_tick(h,&frame,2,idle);   /* SQ_GUARD (15 frames) and SQ_GUARD2 (7) are over */
            assert(!dw4_lobby_select_player(wd,1));s1=dw4_modelctrl_sequence(dw4_lobby_player_model(wd));assert(s1 && !strcmp(s1,"SQ_WAIT"));dw4_lobby_select_player(wd,0);
        }
        {   /* The R1 technique panel on pad 2 (field worlds): R1 on pad 2 opens slot 1's own panel, Cross there spends only slot 1's MP and starts its SQ_WAZA; pad 1 neither
             * opens nor fires it, and a Cross on pad 1 while only slot 1's panel is open swings slot 0 (its own, closed panel) without touching slot 1's MP. */
            dw4_playerrecords *rec=dw4_hubruntime_records(h);dw4_property_folder *q0=dw4_playerrecords_get(rec,"GETPLAYER",0),*q1=dw4_playerrecords_get(rec,"GETPLAYER",1);
            const dw4_technique *tech=dw4_hubruntime_technique(h);const dw4_database *tdb=dw4_databases_get(dw4_hubruntime_databases(h),"pcTech");assert(tech && tdb && q0 && q1);
            struct padw idle0[4]={{0}};
            for(unsigned t=0;t<30;t++)coop_tick(h,&frame,2,idle0);
            assert(!dw4_property_set_number(q0,"MP",60) && !dw4_property_set_number(q1,"MP",60) && !tech_panel(tech,1).open);
            struct padw r1_slot1[4]={{0},{0,0x800,0x800}};
            coop_tick(h,&frame,2,r1_slot1);
            dw4_technique_panel pv=tech_panel(tech,1);
            fprintf(stderr,"slot 1 panel after R1 on pad 2: open %d count %d row %d; slot 0 open %d\n",pv.open,pv.count,pv.row[0],tech_panel(tech,0).open);
            assert(pv.open && pv.count>=1 && !tech_panel(tech,0).open);
            int32_t cost=0,delay=0;assert(!dw4_database_number(tdb,pv.row[0],"MP",&cost) && !dw4_database_number(tdb,pv.row[0],"DELAY",&delay) && cost>0 && cost<=60 && delay>0);
            for(unsigned t=0;t<4;t++)coop_tick(h,&frame,2,idle0);   /* the 2-frame debounce */
            {   /* Cross on pad 1 is slot 0's swing: its panel is closed, so slot 1's list and MP are untouched */
                struct padw cross_slot0[4]={{0,0x4000,0x4000}};coop_tick(h,&frame,2,cross_slot0);
                assert(tech_prop(q1,"MP")==60 && tech_prop(q0,"MP")==60 && tech_panel(tech,1).open && !tech_panel(tech,0).open);
                for(unsigned t=0;t<150;t++)coop_tick(h,&frame,2,idle0);
            }
            dw4_lobby *w=dw4_hubruntime_world(h);dw4_lobby_select_player(w,1);dw4_modelctrl *m1=dw4_lobby_player_model(w);dw4_lobby_select_player(w,0);
            struct padw cross_slot1[4]={{0},{0,0x4000,0x4000}};
            coop_tick(h,&frame,2,cross_slot1);
            fprintf(stderr,"slot 1 fires: MP %d -> %d (cost %d), slot 0 MP %d, slot 1 seq %s action %s\n",60,tech_prop(q1,"MP"),cost,tech_prop(q0,"MP"),dw4_modelctrl_sequence(m1),dw4_modelctrl_action(m1)?dw4_modelctrl_action(m1):"-");
            assert(tech_prop(q1,"MP")==60-cost && tech_prop(q0,"MP")==60 && !strcmp(dw4_modelctrl_sequence(m1),"SQ_WAZA") && !tech_panel(tech,0).open);
            for(unsigned t=0;t<(unsigned)delay+10;t++)coop_tick(h,&frame,2,idle0);   /* past the cast and its DELAY lock */
            struct padw r1_slot0[4]={{0,0x800,0x800}};   /* R1 on pad 1 opens slot 0's panel only */
            coop_tick(h,&frame,2,r1_slot0);
            assert(tech_panel(tech,0).open && tech_panel(tech,1).open);
            for(unsigned t=0;t<4;t++)coop_tick(h,&frame,2,idle0);
            coop_tick(h,&frame,2,r1_slot0);assert(!tech_panel(tech,0).open && tech_panel(tech,1).open && tech_prop(q0,"MP")==60);   /* R1 on pad 1 again closes slot 0's */
            coop_tick(h,&frame,2,r1_slot1);assert(!tech_panel(tech,1).open);   /* and R1 on pad 2 closes slot 1's */
            for(unsigned t=0;t<60;t++)coop_tick(h,&frame,2,idle0);
            printf("coop menus: each pad opens and fires only its own technique panel (slot 1 spent %d MP, slot 0 none)\n",cost);
        }
        const dw4_modelctrl *npc=NULL;int32_t npc_slot=-1;
        for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t sl;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&sl);
            if(!strcmp(dw4_stageobject_name(info),"n_recorder") && dw4_modelctrl_active(mc) && !npc){npc=mc;npc_slot=sl;}}
        assert(npc);
        dw4_modelctrl_actor na;dw4_modelctrl_actor_state(npc,&na);
        fprintf(stderr,"n_recorder[%d] at %g %g %g yaw %g seq %s\n",npc_slot,na.position[0],na.position[1],na.position[2],na.rotation[1],dw4_modelctrl_sequence(npc));
        float r=na.rotation[1]*0.0174533f;char where[96];
        /* Slot 1 stands 12 units in front of the NPC facing it; slot 0 stays where it arrived. */
        snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,%g,0>",na.position[0]+12*sinf(r),na.position[1]+30,na.position[2]+12*cosf(r),na.rotation[1]+180);
        place_slot(h,1,where);
        struct padw idle[4]={{0}};
        for(unsigned t=0;t<150;t++)coop_tick(h,&frame,2,idle);
        assert(control(h) && slot_control(h,1) && !dw4_scriptengine_pending(dw4_hubruntime_scripts(h)));
        {   /* Cross on pad 2 talks as slot 1: the probe's shooter is the pressing slot, not the first player */
            struct padw cross_slot1[4]={{0},{0,0x4000,0x4000}};
            coop_tick(h,&frame,2,cross_slot1);
            struct padw hold1[4]={{0},{0,0x4000,0}};
            for(unsigned t=0;t<3;t++)coop_tick(h,&frame,2,hold1);
            for(unsigned t=0;t<60 && !dw4_scriptengine_pending(dw4_hubruntime_scripts(h));t++)coop_tick(h,&frame,2,idle);
        }
        fprintf(stderr,"after slot 1's Cross: DM groups %zu, g_messPlayerNo %d, g_npcRamNo %d, npc seq %s, slot0 control %d slot1 control %d\n",
            dw4_scriptengine_pending(dw4_hubruntime_scripts(h)),lua_number(h,"g_messPlayerNo"),lua_number(h,"g_npcRamNo"),dw4_modelctrl_sequence(npc),slot_control(h,0),slot_control(h,1));
        assert(dw4_scriptengine_pending(dw4_hubruntime_scripts(h)) && lua_number(h,"g_messPlayerNo")==1 && lua_number(h,"g_npcRamNo")==npc_slot);
        assert(!slot_control(h,0) && !slot_control(h,1));   /* PLAYER nil -1 OFCTRL: every player is locked while the talk runs */
        /* The message waits for its talker's pad: Cross on pad 1 does not turn the page, Cross on pad 2 does (SELECTCTRL i_messky reads slot g_messPlayerNo). */
        unsigned open_at=0;for(;open_at<400 && !dw4_dialogue_talk_open(dw4_hubruntime_dialogue(h));open_at++)coop_tick(h,&frame,2,idle);
        assert(open_at<400);
        for(unsigned t=0;t<120;t++)coop_tick(h,&frame,2,idle);
        uint32_t page0=talk_text_hash(h);size_t pending0=dw4_scriptengine_pending(dw4_hubruntime_scripts(h));
        fprintf(stderr,"talk open after %u ticks, text hash %08x, DM groups %zu\n",open_at,page0,pending0);
        for(unsigned t=0;t<240;t++){struct padw tap0[4]={{0,t%12<3?0x4000:0,t%12==0?0x4000:0}};coop_tick(h,&frame,2,tap0);}
        assert(dw4_dialogue_talk_open(dw4_hubruntime_dialogue(h)) && talk_text_hash(h)==page0 && dw4_scriptengine_pending(dw4_hubruntime_scripts(h))==pending0 && !control(h));
        unsigned turned=0;
        for(unsigned t=0;t<240 && !turned;t++){struct padw tap1[4]={{0},{0,t%12<3?0x4000:0,t%12==0?0x4000:0}};coop_tick(h,&frame,2,tap1);turned=talk_text_hash(h)!=page0;}
        fprintf(stderr,"pad 2's Cross turned the page: %u (hash %08x)\n",turned,talk_text_hash(h));
        assert(turned);
        for(unsigned t=0;t<1500 && dw4_scriptengine_pending(dw4_hubruntime_scripts(h));t++){struct padw tap1[4]={{0},{0,t%12<3?0x4000:0,t%12==0?0x4000:0}};coop_tick(h,&frame,2,tap1);}
        for(unsigned t=0;t<120;t++)coop_tick(h,&frame,2,idle);
        assert(!dw4_scriptengine_pending(dw4_hubruntime_scripts(h)) && control(h) && slot_control(h,1));
        printf("coop menus: slot 1's Cross talks (g_messPlayerNo 1), every player is locked, only pad 2 answers the message, control returns\n");
        return 0;
    }
    if(!strcmp(mode,"chunk")) {
        const int revisit[]={2,355,503};
        h=enter(&mount,revisit,3);run(h,&frame,600,0,0);
        int rc=dw4_hubruntime_run_chunk(h,getenv("CHUNK"));fprintf(stderr,"run %s rc %d\n",getenv("CHUNK"),rc);
        for(unsigned i=0;i<3000 && !dw4_hubruntime_travel(h)->pending;i++){   /* tap Cross every 40 ticks to confirm prompts */
            dw4_hubruntime_input(h,0,0,0,i%40<4?0x4000:0,i%40==0?0x4000:0);
            if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
        }
        const dw4_stagetravel *t=dw4_hubruntime_travel(h);fprintf(stderr,"pending %d dest %s point %d\n",t->pending,t->destination,t->generate_pos);
        return 0;
    }
    if(!strcmp(mode,"genpos")) {
        const int revisit[]={2,355,503};
        h=enter(&mount,revisit,3);const dw4_fieldgen *g=dw4_hubruntime_fieldgen(h);
        for(size_t i=0;i<dw4_fieldgen_count(g);i++){const dw4_gene *e=dw4_fieldgen_at(g,i);
            printf("%s row %d %s data %g pos %g %g %g global %d points %u count %d/%d fill %s\n",e->name,e->enemy_row,e->start_mode,e->start_data,e->pos[0],e->pos[1],e->pos[2],e->global,e->npoints,e->count[0],e->max_count[0],e->fill_mode);}
        return 0;
    }
    if(!strcmp(mode,"attack")) {
        /* The starter's Cross attack against an enemy placed in front of it: HITBOX volumes -> body boxes -> the original
         * hit_e_goburi.lua -> FIGHTCALC hit/critical/damage -> MDLaddHp -> damage sequences. Bring-up fixture: the attack is started by an SD
         * command (the Cross-press start condition is not ported) and the enemy is generated directly. */
        const int revisit[]={2,355,503};
        h=enter(&mount,revisit,3);run(h,&frame,600,0,0);assert(control(h));
        dw4_modelctrl *player=dw4_lobby_player_model(dw4_hubruntime_world(h));assert(player);
        dw4_modelctrl_actor pa;dw4_modelctrl_actor_state(player,&pa);float pm[16];dw4_modelctrl_actor_matrix(&pa,pm);
        float yaw=pa.rotation[1];
        char where[96],spot[96];snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,%g,0>/SQ_WAIT",pa.position[0]+pm[8]*9,pa.position[1],pa.position[2]+pm[10]*9,yaw+180);
        snprintf(spot,sizeof spot,"V<%g,%g,%g>/V<0,%g,0>",pa.position[0]+pm[8]*9,pa.position[1],pa.position[2]+pm[10]*9,yaw+180);
        char error[512];dw4_script_value r;
        dw4_script_value gen[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"e_goburi",8},{DW4_SCRIPT_NUMBER,5,NULL,0},{DW4_SCRIPT_STRING,0,"GENERATE",8},{DW4_SCRIPT_STRING,0,where,strlen(where)}};
        assert(!dw4_hubruntime_sd(h,gen,5,&r,error,sizeof error));
        dw4_script_model *goblin=dw4_hubruntime_enemy_state(h,"e_goburi",5);assert(goblin);
        goblin->rec_no=0;goblin->hp=goblin->max_hp=50;
        /* Fixture: no AI target, so the Goblin stands where it was placed (its authored AI would walk and attack; enemy attacks on the player
         * are not ported). */
        assert(!dw4_hubruntime_enemy_ai_off(h,"e_goburi",5));
        if(getenv("ATKDEBUG"))dw4_modelctrl_observe(player,atk_trace,NULL);

        /* Swing until the Goblin has taken damage: a miss (BLTisHitCheck) sends it to SQ_GUARD and costs the attempt. Cross is held through the
         * swing, then released so the chain ends, and the ATDELAY cooldown runs before the next press. */
        int32_t delay=0;dw4_property_number(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0),"ATTACKDELAY",&delay);
        fprintf(stderr,"ATTACKDELAY %d -> cooldown %d frames\n",delay,delay*5);
        int32_t hp_before=goblin->hp;unsigned attempts=0,swing_frames=0,popwait=0;int popshot=0;dw4_fb prev;assert(!dw4_fb_init(&prev,640,448));   /* prev: the frame before the first damage number spawned */
        for(;attempts<12 && goblin->hp==hp_before && goblin->hp>0;attempts++){
            replace_goblin(h,spot);
            for(unsigned i=0;i<90;i++){
                /* Cross is tapped: released before the first action ends, so the chain ends at SQ_WAIT (held, it would continue into the jump-slash finisher, which carries the player forward) */
                dw4_hubruntime_input(h,0,0,0,i<3?0x4000:0,i==0?0x4000:0);
                if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
                swing_frames++;
                if(!popshot && !dw4_hubruntime_popup_stats(h)->spawned[0])assert(dw4_hubruntime_draw(h,&prev,NULL)>0);
                if(!popshot && dw4_hubruntime_popup_stats(h)->spawned[0]){   /* a frame twelve ticks after the first damage number spawned (POPTICKS); POPSHOT=<png> keeps it */
                    popwait++;
                    if(popwait==12){   /* the number once its 12-frame fade-in is done (OPEN01: FADESET IN 12, wait 20, OUT 20; the fade-out starts 20 frames later) and while it is still opaque: the texture's own orange-to-white gradient (no vertex colours exist, see popup_digit_colour) */
                        dw4_fb cfb;unsigned orange=0,pale=0;int oy=0,py=0;assert(!dw4_fb_init(&cfb,640,448));assert(dw4_hubruntime_draw(h,&cfb,NULL)>0);
                        int found=popup_digit_colour(&cfb,&prev,&orange,&pale,&oy,&py);
                        fprintf(stderr,"popup digit colour (tick 12): %s, %u orange px (mean y %d), %u pale px (mean y %d)\n",found?"found":"missing",orange,oy,pale,py);
                        if(getenv("POPCOLOR"))assert(!dw4_png_write(getenv("POPCOLOR"),cfb.rgba,cfb.w,cfb.h));
                        assert(found && orange>=10 && pale>=8);   /* orange fill and pale body with the dark outline: the numdmg.png palette reaches the screen */
                        assert(oy<py);   /* gradient direction (#2900): orange on the upper part of the upright glyph, pale below; the retail capture of "728" measures orange (248,157,72) at the top rows and pale (234,224,217) at the bottom */
                        dw4_fb_free(&cfb);dw4_fb_free(&prev);
                    }
                    if(popwait==(getenv("POPTICKS")?(unsigned)atoi(getenv("POPTICKS")):12u)){dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));assert(dw4_hubruntime_draw(h,&fb,NULL)>0);if(getenv("POPSHOT"))assert(!dw4_png_write(getenv("POPSHOT"),fb.rgba,fb.w,fb.h));dw4_fb_free(&fb);popshot=1;
                        fprintf(stderr,"popup digit vertices drawn: %u\n",dw4_hubruntime_popup_stats(h)->digit_vertices);assert(dw4_hubruntime_popup_stats(h)->digit_vertices>0);
                    }
                }
            }
            for(unsigned i=0;i<(unsigned)delay*5+30;i++){
                dw4_hubruntime_input(h,0,0,0,0,0);
                if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
            }
        }
        const dw4_combat_stats *st=dw4_hubruntime_combat(h);
        fprintf(stderr,"attempts %u: hits %u damage total %u last %d goblin hp %d -> %d\n",attempts,st->hits,st->damage_total,st->last_damage,hp_before,goblin->hp);
        assert(st->hits>=1 && goblin->hp<hp_before && st->last_damage>0 && hp_before-goblin->hp==(int32_t)st->damage_total);   /* a swing can hit twice (live note in docs/systems/combat-damage.md) */
        {const dw4_hubruntime_popups *pp=dw4_hubruntime_popup_stats(h);fprintf(stderr,"damage popups: spawned %u refused %u, last %s value %d\n",pp->spawned[0],pp->refused,pp->last_sequence,pp->last_value);assert(pp->spawned[0]>=1 && pp->last_value>0);}
        assert(goblin->hp>=0);
        /* Keep swinging until it dies: SQ_DDMG ends in SQ_ERAS (the receiver goes inactive), BLTcalcEXPUp pays EXP once. */
        int32_t exp0=0;dw4_property_number(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0),"EXP",&exp0);
        for(;attempts<80 && dw4_controllers_enemies_alive(dw4_hubruntime_models(h),"e_goburi") && goblin->hp>0;attempts++){
            replace_goblin(h,spot);
            if(getenv("ATKDEBUG")){
                dw4_modelctrl_actor ga;float gm[16];
                for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
                    if(!strcmp(dw4_stageobject_name(info),"e_goburi") && slot==5){dw4_modelctrl_actor_state(mc,&ga);fprintf(stderr,"attempt %u: player seq %s goblin hp %d seq %s active %d enabled %d muteki %g pos %.1f %.1f %.1f; hits %u\n",attempts,dw4_modelctrl_sequence(player),goblin->hp,dw4_modelctrl_sequence(mc),dw4_modelctrl_active(mc),ga.enabled,ga.muteki,ga.position[0],ga.position[1],ga.position[2],dw4_hubruntime_combat(h)->hits);(void)gm;}}
            }
            for(unsigned i=0;i<90;i++){
                /* Cross is tapped: released before the first action ends, so the chain ends at SQ_WAIT (held, it would continue into the jump-slash finisher, which carries the player forward) */
                dw4_hubruntime_input(h,0,0,0,i<3?0x4000:0,i==0?0x4000:0);
                if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
            }
            for(unsigned i=0;i<(unsigned)delay*5+30;i++){
                dw4_hubruntime_input(h,0,0,0,0,0);
                if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
            }
        }
        for(unsigned i=0;i<600 && dw4_controllers_enemies_alive(dw4_hubruntime_models(h),"e_goburi");i++){   /* let SQ_DDMG finish */
            dw4_hubruntime_input(h,0,0,0,0,0);
            if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
        }
        int32_t exp1=0;dw4_property_number(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0),"EXP",&exp1);
        fprintf(stderr,"after %u swings: goblin hp %d alive %zu, EXP %d -> %d (combat exp %u), damage total %u\n",attempts,goblin->hp,
            dw4_controllers_enemies_alive(dw4_hubruntime_models(h),"e_goburi"),exp0,exp1,st->exp_total,st->damage_total);
        for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
            if(!strcmp(dw4_stageobject_name(info),"e_goburi") && dw4_modelctrl_active(mc)){dw4_modelctrl_actor ga;dw4_modelctrl_actor_state(mc,&ga);fprintf(stderr,"goblin[%d] seq %s pos %.1f %.1f %.1f muteki %g\n",slot,dw4_modelctrl_sequence(mc),ga.position[0],ga.position[1],ga.position[2],ga.muteki);}}
        assert(goblin->hp==0 && !dw4_controllers_enemies_alive(dw4_hubruntime_models(h),"e_goburi") && exp1>exp0 && exp1-exp0==(int32_t)st->exp_total);
        {   /* The kill spawned the exp popup (row 1, value = the exp share) and the popups end with their sequence: none stays active after a second. */
            const dw4_hubruntime_popups *pp=dw4_hubruntime_popup_stats(h);
            fprintf(stderr,"popups: damage %u exp %u refused %u\n",pp->spawned[0],pp->spawned[1],pp->refused);
            assert(pp->spawned[1]>=1 && pp->refused==0);
            for(unsigned t=0;t<120;t++){dw4_hubruntime_input(h,0,0,0,0,0);if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60))break;}
            unsigned live=0;
            for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
                if(info && !strcmp(dw4_stageobject_name(info),"i_dmgnum") && dw4_modelctrl_active(mc)){live++;fprintf(stderr,"popup[%d] still active, seq %s\n",slot,dw4_modelctrl_sequence(mc));}}
            assert(live==0);
        }
        dw4_hubruntime_close(h);
        printf("field stage stag0101 attack: Cross swing -> HITBOX volume -> hit_e_goburi.lua -> FIGHTCALC -> HP\n");
        return 0;
    }
    if(!strcmp(mode,"technique")) {
        /* The R1 technique panel and cast (docs/combat.md "Technique firing"): R1 opens/closes the panel, Cross does not swing while it is open, the fire
         * charges exactly the pcTech MP and enters SQ_WAZA with the LABEL, a short-MP press refuses without a state change, the debounce / DELAY / NG locks
         * block input for their recorded lengths, and the bullet volume takes a class-4 hit on an enemy in front. Frame counts are the port's reading of
         * the recorded retail rules; the bullet geometry is an ASSUMPTION (technique.c). Not compared against a running retail game. */
        const int revisit[]={2,355,503};
        h=enter(&mount,revisit,3);run(h,&frame,600,0,0);assert(control(h));
        dw4_playerrecords *rec=dw4_hubruntime_records(h);const dw4_databases *dbs=dw4_hubruntime_databases(h);
        dw4_property_folder *p0=dw4_playerrecords_get(rec,"GETPLAYER",0);const dw4_database *tdb=dw4_databases_get(dbs,"pcTech");assert(p0 && tdb);
        dw4_modelctrl *player=dw4_lobby_player_model(dw4_hubruntime_world(h));assert(player);
        const dw4_technique *tech=dw4_hubruntime_technique(h);assert(tech);
        /* (a) the level-1 Dorumon's list: Petty Ice (row 5) once SKILL[6] >= 1, and its recorded costs */
        size_t n=0,sn=0;const dw4_item_record *w=dw4_property_items(p0,"WAZALIST",&n);const int32_t *skill=dw4_property_array(p0,"SKILL",&sn);
        assert(n==1 && w[0].record==5 && w[0].revision==5 && sn>6 && skill[6]>=1);
        int32_t cost=0,delay=0;
        assert(!dw4_database_number(tdb,5,"MP",&cost) && !dw4_database_number(tdb,5,"DELAY",&delay) && cost==16 && delay==75 && tech_prop(p0,"MMP")>=60);
        const char *label=dw4_database_string(tdb,5,"LABEL");assert(label && !strcmp(label,"ice1"));
        assert(!dw4_property_set_number(p0,"MP",60));
        dw4_technique_panel pv=tech_panel(tech,0);assert(!pv.open);
        /* (b) R1 opens the panel on the list's first row */
        tech_step(h,&frame,0x800,0);
        pv=tech_panel(tech,0);assert(pv.open && pv.cursor==0 && pv.offset==0 && pv.count==1 && pv.row[0]==5 && pv.base[0]==5 && !pv.color[0]);
        /* (c) the 2-frame debounce: a Cross on the next frame is swallowed (no fire, no swing) */
        tech_step(h,&frame,0,0x4000);
        assert(tech_prop(p0,"MP")==60 && !strcmp(dw4_modelctrl_sequence(player),"SQ_WAIT"));
        /* (d) short MP: a press refuses without spending or entering a sequence, and locks the panel for the NG lockout (16 frames) */
        assert(!dw4_property_set_number(p0,"MP",cost-1));
        unsigned ng=frame;tech_step(h,&frame,0,0x4000);
        assert(tech_prop(p0,"MP")==cost-1 && !strcmp(dw4_modelctrl_sequence(player),"SQ_WAIT"));
        pv=tech_panel(tech,0);assert(pv.open && pv.color[0]==1);
        assert(!dw4_property_set_number(p0,"MP",60));
        tech_frames(h,&frame,ng+15-frame);tech_step(h,&frame,0,0x4000);      /* 15 frames after the refused press: still locked */
        assert(tech_prop(p0,"MP")==60 && !strcmp(dw4_modelctrl_sequence(player),"SQ_WAIT"));
        /* (e) MP 60 and the lock over (16 frames): Cross fires: exactly the pcTech MP is spent and the player enters SQ_WAZA with the label's action */
        unsigned cast=frame;tech_step(h,&frame,0,0x4000);
        assert(tech_prop(p0,"MP")==60-cost && !strcmp(dw4_modelctrl_sequence(player),"SQ_WAZA"));
        fprintf(stderr,"cast: sequence %s action %s, MP %d -> %d\n",dw4_modelctrl_sequence(player),dw4_modelctrl_action(player),60,tech_prop(p0,"MP"));
        assert(dw4_modelctrl_action(player) && !strcmp(dw4_modelctrl_action(player),"HICEE1"));
        assert(dw4_technique_flying(tech,0)>=0);
        unsigned waza=0;
        while(!strcmp(dw4_modelctrl_sequence(player),"SQ_WAZA") && waza<60){waza++;tech_step(h,&frame,0,0);}
        fprintf(stderr,"SQ_WAZA lasted %u ticks (recorded about 18-20)\n",waza);
        assert(waza>=15 && waza<=25 && !strcmp(dw4_modelctrl_sequence(player),"SQ_WAIT"));
        /* (f) the DELAY lock blocks every panel input, closing included, and a second cast, for exactly DELAY frames from the press */
        tech_step(h,&frame,0,0x4000);assert(tech_prop(p0,"MP")==60-cost);
        tech_frames(h,&frame,cast+30-frame);tech_step(h,&frame,0x800,0);pv=tech_panel(tech,0);assert(pv.open);     /* R1 is swallowed too */
        tech_frames(h,&frame,cast+(unsigned)delay-1-frame);tech_step(h,&frame,0,0x4000);                            /* DELAY-1 frames after: locked */
        assert(tech_prop(p0,"MP")==60-cost && !strcmp(dw4_modelctrl_sequence(player),"SQ_WAIT"));
        tech_step(h,&frame,0,0x4000);                                                                               /* DELAY frames after: accepted */
        assert(tech_prop(p0,"MP")==60-2*cost && !strcmp(dw4_modelctrl_sequence(player),"SQ_WAZA"));
        unsigned cast2=frame-1;
        pv=tech_panel(tech,0);assert(pv.open);                                                                       /* the list stays open after a cast */
        /* (g) R1 closes once the lock is over; a closed panel lets Cross swing again */
        tech_frames(h,&frame,cast2+(unsigned)delay+1-frame);tech_step(h,&frame,0x800,0);
        pv=tech_panel(tech,0);assert(!pv.open);
        tech_frames(h,&frame,3);tech_step(h,&frame,0,0x4000);
        assert(!strncmp(dw4_modelctrl_sequence(player),"SQ_ATCK",7));
        tech_frames(h,&frame,120);assert(control(h) && !strcmp(dw4_modelctrl_sequence(player),"SQ_WAIT"));
        /* (h) a cast fired in the air waits for the landing with its MP already spent (ISCHECK is not polled in SQ_JUMP/SQ_FALL) */
        assert(!dw4_property_set_number(p0,"MP",60));
        tech_step(h,&frame,0x800,0);tech_frames(h,&frame,2);
        tech_step(h,&frame,0,0x2000);
        assert(!strcmp(dw4_modelctrl_sequence(player),"SQ_JUMP"));
        tech_step(h,&frame,0,0x4000);
        assert(tech_prop(p0,"MP")==60-cost && strcmp(dw4_modelctrl_sequence(player),"SQ_WAZA"));
        unsigned air=0;
        while(strcmp(dw4_modelctrl_sequence(player),"SQ_WAZA") && air<200){air++;tech_step(h,&frame,0,0);}
        fprintf(stderr,"airborne cast started SQ_WAZA %u ticks later\n",air);
        assert(air<200 && tech_prop(p0,"MP")==60-cost);
        tech_frames(h,&frame,120);
        /* (i) the bullet takes a class-4 hit on an enemy in front: the damage comes from the existing technique rules (attack number 40000 + base) */
        dw4_modelctrl_actor pa;dw4_modelctrl_actor_state(player,&pa);float pm[16];dw4_modelctrl_actor_matrix(&pa,pm);
        char where[96];
        snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,%g,0>/SQ_WAIT",pa.position[0]+pm[8]*9,pa.position[1],pa.position[2]+pm[10]*9,pa.rotation[1]+180);
        char error[512];dw4_script_value r;
        dw4_script_value gen[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"e_goburi",8},{DW4_SCRIPT_NUMBER,5,NULL,0},{DW4_SCRIPT_STRING,0,"GENERATE",8},{DW4_SCRIPT_STRING,0,where,strlen(where)}};
        assert(!dw4_hubruntime_sd(h,gen,5,&r,error,sizeof error));
        dw4_script_model *goblin=dw4_hubruntime_enemy_state(h,"e_goburi",5);assert(goblin);
        goblin->rec_no=0;goblin->hp=goblin->max_hp=1000;assert(!dw4_hubruntime_enemy_ai_off(h,"e_goburi",5));
        assert(!dw4_property_set_number(p0,"MP",60));
        assert(tech_panel(tech,0).open);                                       /* still open after the airborne cast */
        const dw4_combat_stats *st=dw4_hubruntime_combat(h);unsigned hits0=st->hits;int32_t last0=st->last_damage;
        int32_t hp0=goblin->hp,hp_after=hp0;int tick_failed=0;
        tech_step(h,&frame,0,0x4000);
        for(unsigned i=0;i<90 && !tick_failed;i++){
            if(tech_frame(h,&frame,0,0)){tick_failed=1;break;}
            hp_after=goblin->hp;
            if(getenv("TECHDEBUG") && i<30){for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);
                if(!strcmp(dw4_stageobject_name(info),"e_goburi") && slot==5)fprintf(stderr,"t%u goblin seq %s hits %u flying %d\n",i,dw4_modelctrl_sequence(mc),st->hits,dw4_technique_flying(tech,0));}}
        }
        if(tick_failed)fprintf(stderr,"technique hit leg: tick stopped: %.200s\n",dw4_hubruntime_error(h));
        assert(!tick_failed);
        int32_t dmg=hp0-goblin->hp;
        fprintf(stderr,"technique hit: hits %u -> %u, goblin hp %d -> %d, last damage %d, bullets in flight %d\n",hits0,st->hits,hp0,goblin->hp,st->last_damage,dw4_technique_flying(tech,0));
        assert(st->hits==hits0+1 && dmg>0 && st->last_damage!=last0 && dmg==st->last_damage && dw4_technique_flying(tech,0)==0);   /* one contact consumes the bullet */
        {   /* the damage lies in the range of the existing technique rules (normal and critical rolls of attack 40005 against enemy row 0) */
            dw4_random rng=dw4_hubruntime_state(h)->random;dw4_fight_ctx ctx={p0,dw4_database_typed(dw4_databases_get(dbs,"enemy")),&rng,dw4_database_typed(tdb)};int lo=1<<30,hi=0;
            for(int i=0;i<4000;i++){dw4_fight_damage d;assert(!dw4_fight_p2e_damage(&ctx,0,40005,i&1,(dw4_fight_down){0,0},&d));if(d.damage<lo)lo=d.damage;if(d.damage>hi)hi=d.damage;}
            fprintf(stderr,"technique rules range for row 0: %d..%d (damage taken %d)\n",lo,hi,dmg);
            assert(dmg>=lo && dmg<=hi);
        }
        /* a volume that meets nothing runs out: the goblin is gone from its path, so the next cast ends by lifetime without a contact */
        char away[96];snprintf(away,sizeof away,"V<%g,%g,%g>/V<0,0,0>",pa.position[0]+pm[8]*400,pa.position[1],pa.position[2]+pm[10]*400);
        replace_goblin(h,away);tech_frames(h,&frame,80);
        unsigned hits1=st->hits;
        tech_step(h,&frame,0,0x4000);assert(dw4_technique_flying(tech,0)==1);
        tech_frames(h,&frame,90);assert(dw4_technique_flying(tech,0)==0 && st->hits==hits1);
        tech_slots(rec,dbs,tdb,p0,cost,delay);
        dw4_hubruntime_close(h);
        printf("field stage stag0101 technique: R1 panel, Cross swallowed while open, MP charge, SQ_WAZA label, DEBOUNCE/DELAY/NG locks, class-4 bullet hit, per-slot panels (port reading, not retail-measured)\n");
        return 0;
    }
    if(!strcmp(mode,"grind")) {
        /* A fresh level-1 starter fights stag0101's own enemies with real stats and live AI: no HP or stat fixture. */
        const int revisit[]={2,355,503};h=enter(&mount,revisit,3);run(h,&frame,600,0,0);assert(control(h));
        unsigned kills=pilot(h,&frame,getenv("TICKS")?atoi(getenv("TICKS")):20000,1);
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);int32_t level=0,hp=0,mhp=0;
        dw4_property_number(p0,"LEVEL",&level);dw4_property_number(p0,"HP",&hp);dw4_property_number(p0,"MHP",&mhp);
        const dw4_combat_stats *st=dw4_hubruntime_combat(h);
        fprintf(stderr,"grind: kills %u level %d hp %d/%d; combat hits %u, player hits %u, damage %u, drops?\n",kills,level,hp,mhp,st->hits,st->player_hits,st->damage_total);
        return 0;
    }
    if(!strcmp(mode,"coop")) {
        /* Two to four local players in the combat state: the EXP split of P2EEXPUP (attacker share /50, mates /100 of value*{140/3,160/4,200/5}), per-slot
         * attribution (the shooter's slot picks the record), and the generators' per-player-count rows. Arithmetic from the matched source; NOT retail-measured. */
        const int revisit[]={2,355,503};h=enter(&mount,revisit,3);
        dw4_playerrecords *rec=dw4_hubruntime_records(h);const dw4_databases *db=dw4_hubruntime_databases(h);char error[256];
        for(int slot=1;slot<4;slot++)assert(!dw4_playerrecords_create(rec,db,slot,"p_agumon","Mate",error,sizeof error));
        dw4_property_folder *c0=dw4_playerrecords_get(rec,"GETCOMMON",0);
        for(int players=2;players<=4;players++){
            assert(!dw4_property_set_number(c0,"NINZU",players));
            int32_t before[4],after[4],share=0;
            for(int i=0;i<4;i++){dw4_property_folder *f=dw4_playerrecords_get(rec,"GETPLAYER",i);assert(!dw4_property_set_number(f,"ISUSE",i<players) && !dw4_property_set_number(f,"EXP",0) && !dw4_property_set_number(f,"LEVEL",1) && !dw4_property_set_number(f,"HP",100));}
            for(int attacker=0;attacker<players;attacker++){
                for(int i=0;i<4;i++)assert(!dw4_property_set_number(dw4_playerrecords_get(rec,"GETPLAYER",i),"EXP",0));
                assert(!dw4_fight_p2e_expup(rec,db,388,attacker,&share));
                int32_t value=133,split=players==2?value*140/3:players==3?value*160/4:value*200/5;
                for(int i=0;i<4;i++){dw4_property_number(dw4_playerrecords_get(rec,"GETPLAYER",i),"EXP",&after[i]);before[i]=i==attacker?split/50:i<players?split/100:0;
                    if(after[i]!=before[i]){fprintf(stderr,"players %d attacker %d slot %d: EXP %d, expected %d\n",players,attacker,i,after[i],before[i]);}
                    assert(after[i]==before[i]);}
                assert(share==split/50);
            }
            fprintf(stderr,"%d players: attacker share %d, mates %d\n",players,share,after[players>1?(0==players-1?1:0):0]);
        }
        {   /* Retail (four players, practice stage, e_goburi row 638 EXP 3, four kills by player 2's pad): each kill gave the shooter +2 and each mate +1. */
            assert(!dw4_property_set_number(c0,"NINZU",4));int32_t share=0;
            for(int i=0;i<4;i++){dw4_property_folder *f=dw4_playerrecords_get(rec,"GETPLAYER",i);assert(!dw4_property_set_number(f,"ISUSE",1) && !dw4_property_set_number(f,"EXP",0));}
            assert(!dw4_fight_p2e_expup(rec,db,638,1,&share) && share==2);
            for(int i=0;i<4;i++){int32_t x=0;dw4_property_number(dw4_playerrecords_get(rec,"GETPLAYER",i),"EXP",&x);assert(x==(i==1?2:1));}
            fprintf(stderr,"retail 4-player EXP (row 638): attacker +2, mates +1: port matches\n");
        }
        {   /* Retail (two players, practice stage, base EXP 3 with both players'"'"' EXPRITSU poked to 4333 so the value is 3*4433/100 = 132): the shooter got +123 and the mate +61 per award. */
            assert(!dw4_property_set_number(c0,"NINZU",2));int32_t share=0;
            for(int i=0;i<4;i++){dw4_property_folder *f=dw4_playerrecords_get(rec,"GETPLAYER",i);assert(!dw4_property_set_number(f,"ISUSE",i<2) && !dw4_property_set_number(f,"EXP",0) && !dw4_property_set_number(f,"EXPRITSU",4333));}
            assert(!dw4_fight_p2e_expup(rec,db,638,1,&share) && share==123);
            for(int i=0;i<2;i++){int32_t x=0;dw4_property_number(dw4_playerrecords_get(rec,"GETPLAYER",i),"EXP",&x);assert(x==(i==1?123:61));}
            for(int i=0;i<4;i++)assert(!dw4_property_set_number(dw4_playerrecords_get(rec,"GETPLAYER",i),"EXPRITSU",0));
            fprintf(stderr,"retail 2-player EXP at value 132: shooter +123, mate +61: port matches\n");
        }
        {   /* Retail (three players, practice stage, value 132 as above): the shooter got +105 and each mate +52 per kill. */
            assert(!dw4_property_set_number(c0,"NINZU",3));int32_t share=0;
            for(int i=0;i<4;i++){dw4_property_folder *f=dw4_playerrecords_get(rec,"GETPLAYER",i);assert(!dw4_property_set_number(f,"ISUSE",i<3) && !dw4_property_set_number(f,"EXP",0) && !dw4_property_set_number(f,"EXPRITSU",4333));}
            assert(!dw4_fight_p2e_expup(rec,db,638,0,&share) && share==105);
            for(int i=0;i<3;i++){int32_t x=0;dw4_property_number(dw4_playerrecords_get(rec,"GETPLAYER",i),"EXP",&x);assert(x==(i==0?105:52));}
            for(int i=0;i<4;i++)assert(!dw4_property_set_number(dw4_playerrecords_get(rec,"GETPLAYER",i),"EXPRITSU",0));
            fprintf(stderr,"retail 3-player EXP at value 132: shooter +105, mates +52: port matches\n");
        }
        {   /* generators serve 1..4 players with their per-count rows */
            dw4_fieldgen *g=dw4_fieldgen_open(&mount,"stagGF01",0);assert(g);int varied=0;
            for(size_t i=0;i<dw4_fieldgen_count(g);i++){const dw4_gene *e=dw4_fieldgen_at(g,i);if(e->count[0]!=e->count[3])varied++;}
            fprintf(stderr,"stagGF01: %d of %zu generators change their wave size with the player count\n",varied,dw4_fieldgen_count(g));
            dw4_fieldgen_close(g);
        }
        printf("co-op: EXP split and per-slot attribution for 2, 3 and 4 players (arithmetic from matched source, not retail-measured)\n");
        return 0;
    }
    if(!strcmp(mode,"practice")) {
        /* The practice stage (stag0001, the Terminal gate's destination while flag 503 is clear): original scripts from a fresh save (flag 2 only). */
        if(getenv("LISTMAT")){mat_list(&mount,getenv("LISTMAT")[0]==49?"stag0001":getenv("LISTMAT"));return 0;}
        const int fresh[]={2};setenv("STAGE","stag0001",1);h=enter(&mount,fresh,1);
        const dw4_fieldgen *gen=dw4_hubruntime_fieldgen(h);
        fprintf(stderr,"practice: %zu generators\n",gen?dw4_fieldgen_count(gen):0);
        unsigned limit=getenv("TICKS")?atoi(getenv("TICKS")):3000;
        if(getenv("EXITTEST")){
            if(!strcmp(getenv("EXITTEST"),"2")){unsigned u=0;for(;u<6000 && !control(h);u++){dw4_hubruntime_input(h,0,0,0,u%90<4?0x4000:0,u%90==0?0x4000:0);if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));return 1;}}practice_lessons(h,&frame);}
            unsigned u=0;for(;u<4000 && !control(h);u++)run(h,&frame,1,0,0);
            fprintf(stderr,"control after %u\n",u);
            if(getenv("DESCRIBE_DM")){fprintf(stderr,"DM groups before exit: %zu\n",dw4_scriptengine_pending(dw4_hubruntime_scripts(h)));dw4_scriptengine_describe(dw4_hubruntime_scripts(h),stderr);}
            if(getenv("OUTFIRST")){place(h,"V<0,10,100>/V<0,0,0>");run(h,&frame,90,0,0);}
            place(h,"V<0,10,163>/V<0,0,0>");
            for(unsigned i=0;i<3000 && !dw4_hubruntime_travel(h)->pending;i++){
                dw4_hubruntime_input(h,0,0,0,i%40<4?0x4000:0,i>60 && i%40==0?0x4000:0);
                if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));return 1;}
                if(i%500==0)fprintf(stderr,"i %u control %d\n",i,control(h));
            }
            fprintf(stderr,"exit: pending %d -> %s point %d\n",dw4_hubruntime_travel(h)->pending,dw4_hubruntime_travel(h)->destination,dw4_hubruntime_travel(h)->generate_pos);
            return 0;
        }
        for(unsigned done=0;done<limit;){
            unsigned chunk=300;
            if(control(h))pilot(h,&frame,chunk,0);else{for(unsigned i=0;i<chunk;i++){dw4_hubruntime_input(h,0,0,0,i%90<4?0x4000:0,i%90==0?0x4000:0);   /* prompts: Cross */
                if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",done,dw4_hubruntime_error(h));return 1;}}}
            done+=chunk;
            const uint8_t *fl=dw4_property_bytes(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0),"FLAG",NULL);
            int32_t lv=0,hp=0,exp=0;dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);dw4_property_number(p0,"LEVEL",&lv);dw4_property_number(p0,"HP",&hp);dw4_property_number(p0,"EXP",&exp);
            fprintf(stderr,"t %u: control %d pending %d(%s) spawned %u enemies %zu level %d hp %d exp %d\n",done,control(h),dw4_hubruntime_travel(h)->pending,dw4_hubruntime_travel(h)->destination,dw4_fieldgen_spawned(gen),dw4_controllers_enemies_alive(dw4_hubruntime_models(h),NULL),lv,hp,exp);
            (void)fl;
            if(getenv("DIAG"))for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);dw4_script_model st;
                if(mc && info && (!strncmp(dw4_stageobject_name(info),"e_",2) || (getenv("DIAGG") && !strncmp(dw4_stageobject_name(info),"g_",2))) && dw4_modelctrl_active(mc) && !dw4_controllers_model_state(dw4_hubruntime_models(h),k,&st)){dw4_modelctrl_actor ea,pa;dw4_modelctrl_actor_state(mc,&ea);dw4_modelctrl_actor_state(dw4_lobby_player_model(dw4_hubruntime_world(h)),&pa);
                    fprintf(stderr,"   %s[%d] row %d hp %d/%d seq %s at %.1f %.1f %.1f; player %.1f %.1f %.1f seq %s; hits %u player_hits %u\n",dw4_stageobject_name(info),slot,st.rec_no,st.hp,st.max_hp,dw4_modelctrl_sequence(mc),ea.position[0],ea.position[1],ea.position[2],pa.position[0],pa.position[1],pa.position[2],dw4_modelctrl_sequence(dw4_lobby_player_model(dw4_hubruntime_world(h))),dw4_hubruntime_combat(h)->hits,dw4_hubruntime_combat(h)->player_hits);}}
            if(dw4_hubruntime_travel(h)->pending)break;
        }
        return 0;
    }
    if(!strcmp(mode,"lesson4")) {
        /* Practice lesson 4 ('Break the rocks and bushes'): the Lua-placed g_bush/g_rock props are KIND_OBJECT receivers whose bullet hit runs the
         * pack's own hit script (a fixed MDLaddHp of -20 / -34 / -50 per hit, SQ_SDMG while HP remains, SQ_DDMG -> SQ_ERAS at zero). The pilot's Cross
         * swings must drain them, destroyed props must go inactive, and the script must go on to the free-practice arena (generators beyond GBOX). */
        const int fresh[]={2};setenv("STAGE","stag0001",1);h=enter(&mount,fresh,1);
        const dw4_fieldgen *gen=dw4_hubruntime_fieldgen(h);
        unsigned seen_max=0,seen_hurt=0,done=0,destroyed=0;int arena=0;
        static const int32_t legal[]={100,80,60,40,20,0,66,32,50};   /* 100 minus whole numbers of the three authored steps */
        for(;done<40000 && !arena;done+=300){
            if(control(h))pilot(h,&frame,300,0);else{for(unsigned i=0;i<300;i++){dw4_hubruntime_input(h,0,0,0,i%90<4?0x4000:0,i%90==0?0x4000:0);
                if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",done,dw4_hubruntime_error(h));return 1;}}}
            unsigned alive=0;destroyed=0;
            for(size_t k=0;k<dw4_controllers_count(dw4_hubruntime_models(h));k++){const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *mc=dw4_controllers_model(dw4_hubruntime_models(h),k,&info,&slot);dw4_script_model st;
                if(!mc || !info || (strncmp(dw4_stageobject_name(info),"g_rock",6) && strncmp(dw4_stageobject_name(info),"g_bush",6)) || dw4_controllers_model_state(dw4_hubruntime_models(h),k,&st))continue;
                if(!dw4_modelctrl_active(mc)){if(st.hp<=0)destroyed++;continue;}   /* SQ_DDMG ends in SQ_ERAS: a dead prop is inactive with no HP left */
                alive++;
                if(st.hp<100){   /* a damaged, still standing prop must sit on a reachable HP value */
                    int ok=0;for(unsigned q=0;q<sizeof legal/sizeof *legal;q++)ok|=st.hp==legal[q];
                    if(!ok)fprintf(stderr,"%s[%d]: unexpected hp %d\n",dw4_stageobject_name(info),slot,st.hp);
                    assert(ok);seen_hurt++;
                }
            }
            if(alive>seen_max)seen_max=alive;
            if(seen_max>=30 && destroyed && dw4_fieldgen_spawned(gen)>=8)arena=1;   /* the arena generators (GENE-a/b) start once the lesson ends */
        }
        fprintf(stderr,"lesson4: props at most %u, damaged samples %u, player hits %u, destroyed %u, ticks %u, generator spawns %u\n",seen_max,seen_hurt,dw4_hubruntime_combat(h)->player_hits,destroyed,done,dw4_fieldgen_spawned(gen));
        assert(seen_max>=30);                  /* 15 bushes + 14 rocks + 4 rock02, less duplicate slots */
        assert(seen_hurt>0);                   /* swings drained props they did not destroy at once */
        assert(destroyed>=1);                  /* destroyed props went through SQ_DDMG -> SQ_ERAS */
        assert(arena);                         /* the lesson ended on its own and the free-practice arena's waves started */
        dw4_hubruntime_close(h);
        printf("practice lesson 4: Cross swings drain and destroy the Lua-placed props, then the arena loop starts\n");
        return 0;
    }
    if(!strcmp(mode,"techrows")) {
        h=enter(&mount,(const int[]){2,503},2);const dw4_database *t=dw4_databases_get(dw4_hubruntime_databases(h),"pcTech");assert(t);
        dw4_database_describe(t,stderr);
        for(int r=0;r<400;r++){const char *n=dw4_database_string(t,r,"NAME");int32_t hp=0,sk=0,ch=0,mp=0,kind=0;dw4_database_number(t,r,"HP",&hp);dw4_database_number(t,r,"SKILL",&sk);dw4_database_number(t,r,"CHIMEIRITSU",&ch);dw4_database_number(t,r,"MP",&mp);const char *z=dw4_database_string(t,r,"ZOKUSEI");
            if(n && *n && (strstr(n,"Fire")||strstr(n,"Heal")||strstr(n,"Speed")||strstr(n,"Cure")||strstr(n,"Resist")||strstr(n,"Power")||strstr(n,"Raise")||strstr(n,"Rev")))printf("row %d %s hp %d skill %d crit %d mp %d zokusei %s\n",r,n,hp,sk,ch,mp,z?z:"");}
        return 0;
    }
    if(!strcmp(mode,"gencounts")) {
        const char *stage=getenv("STAGE")?getenv("STAGE"):"stag0001";
        dw4_fieldgen *g=dw4_fieldgen_open(&mount,stage,0);assert(g);
        for(size_t i=0;i<dw4_fieldgen_count(g);i++){const dw4_gene *e=dw4_fieldgen_at(g,i);
            printf("%s row %d count %d/%d/%d/%d max %d/%d/%d/%d\n",e->name,e->enemy_row,e->count[0],e->count[1],e->count[2],e->count[3],e->max_count[0],e->max_count[1],e->max_count[2],e->max_count[3]);}
        dw4_fieldgen_close(g);return 0;
    }
    if(!strcmp(mode,"techall")) {
        h=enter(&mount,(const int[]){2,503},2);const dw4_database *t=dw4_databases_get(dw4_hubruntime_databases(h),"pcTech");
        for(int r=0;r<400;r+=5){const char *n=dw4_database_string(t,r,"NAME");if(!n || !*n)continue;int32_t hp=0,sk=0,tm=0,sub=0,mp=0;dw4_database_number(t,r,"HP",&hp);dw4_database_number(t,r,"SKILL",&sk);dw4_database_number(t,r,"TIME",&tm);dw4_database_number(t,r,"SUBAYASA",&sub);dw4_database_number(t,r,"MP",&mp);
            const char *z=dw4_database_string(t,r,"ZOKUSEI");printf("rows %d-%d %s skill %d hp %d time %d mp %d zokusei %s\n",r,r+4,n+((unsigned char)n[0]>=0x80?0:0),sk,hp,tm,mp,z?z:"");}
        return 0;
    }
    if(!strcmp(mode,"techunlock")) {
        h=enter(&mount,(const int[]){2,503},2);const dw4_database *sh=dw4_databases_get(dw4_hubruntime_databases(h),"shinka"),*t=dw4_databases_get(dw4_hubruntime_databases(h),"pcTech");
        int sp=getenv("SPECIES")?atoi(getenv("SPECIES")):15;
        for(int k=1;k<=6;k++){char key[32];int32_t base=0,lvl=0,sk[5]={0};snprintf(key,sizeof key,"TECH%d",k);dw4_database_number(sh,sp,key,&base);snprintf(key,sizeof key,"TECH%d_LEVEL",k);dw4_database_number(sh,sp,key,&lvl);
            for(int q=0;q<5;q++){snprintf(key,sizeof key,"TECH%d_SKILL%d",k,q+1);dw4_database_number(sh,sp,key,&sk[q]);}
            int32_t sidx=-1;dw4_database_number(t,base,"SKILL",&sidx);
            printf("species %d TECH%d base %d (%s) needs level %d, skill index %d thresholds %d %d %d %d %d\n",sp,k,base,dw4_database_string(t,base,"NAME"),lvl,sidx,sk[0],sk[1],sk[2],sk[3],sk[4]);}
        return 0;
    }
    if(!strcmp(mode,"growrows")) {
        h=enter(&mount,(const int[]){2,503},2);const dw4_database *sh=dw4_databases_get(dw4_hubruntime_databases(h),"shinka");
        for(int r=0;r<16;r++){int32_t v[6]={0};const char *c[6]={"BLUNT_GROW","SLASH_GROW","STAB_GROW","BASH_GROW","SHOT_GROW","CRUSH_GROW"};for(int k=0;k<6;k++)dw4_database_number(sh,r,c[k],&v[k]);
            printf("shinka %d %s: blunt %d slash %d stab %d bash %d shot %d crush %d\n",r,dw4_database_string(sh,r,"MODEL_NAME"),v[0],v[1],v[2],v[3],v[4],v[5]);}
        return 0;
    }
    if(!strcmp(mode,"swingtime")) {
        /* How long a Cross swing keeps the player out of SQ_WAIT (retail, Susanomon slash: 0.517 s read from the player's sequence field), and whether a second press at
         * a gap restarts it. */
        const int revisit[]={2,355,503};h=enter(&mount,revisit,3);run(h,&frame,600,0,0);assert(control(h));
        dw4_modelctrl *pl=dw4_lobby_player_model(dw4_hubruntime_world(h));
        for(unsigned i=0;i<20;i++){dw4_hubruntime_input(h,0,0,0,0,0);dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60);}
        unsigned ticks=0,started=0;
        for(unsigned i=0;i<400;i++){
            dw4_hubruntime_input(h,0,0,0,i<3?0x4000:0,i==0?0x4000:0);dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60);
            const char *q=dw4_modelctrl_sequence(pl);
            if(!strncmp(q,"SQ_ATCK",7)){started=1;ticks++;}else if(started)break;
        }
        printf("swing: %u ticks (%.3f s) in an SQ_ATCK sequence\n",ticks,ticks/60.0);
        return 0;
    }
    if(!strcmp(mode,"techcheck")) {
        const int revisit[]={2,355,503};h=enter(&mount,revisit,3);
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
        const dw4_databases *dbs=dw4_hubruntime_databases(h);const dw4_database *enemy=dw4_databases_get(dbs,"enemy"),*tech=dw4_databases_get(dbs,"pcTech");
        int32_t sk[9];for(int i=0;i<9;i++)sk[i]=9999;
        assert(!dw4_property_set_number(p0,"DIGIMONNO",15) && !dw4_property_set_number(p0,"LEVEL",999) && !dw4_property_set_array(p0,"SKILL",sk,9) && !dw4_playerstats_recalculate((void *)dbs,p0));
        assert(!dw4_property_set_number(p0,"KASHIKOSA",getenv("KASH")?atoi(getenv("KASH")):9999));
        size_t n=0;const dw4_item_record *w=dw4_property_items(p0,"WAZALIST",&n);
        for(size_t i=0;i<n;i++)fprintf(stderr,"waza %zu: base %d row %d %s\n",i,w[i].revision,w[i].record,dw4_database_string(tech,w[i].record,"NAME"));
        int base=-1;for(size_t i=0;i<n;i++){const char *nm=dw4_database_string(tech,w[i].record,"NAME");if(nm && strstr(nm,"Fire"))base=w[i].revision;}
        assert(base>=0);
        int32_t sei=0,rf=0;dw4_database_number(enemy,60,"SEISHIN",&sei);dw4_database_number(enemy,60,"RES_FIRE",&rf);fprintf(stderr,"boss row 60 SEISHIN %d RES_FIRE %d\n",sei,rf);
        dw4_random rng=dw4_hubruntime_state(h)->random;dw4_fight_ctx ctx={p0,dw4_database_typed(enemy),&rng,dw4_database_typed(tech)};
        double sum=0,csum=0;unsigned cn=0,n0=4000;int lo=1<<30,hi=0;
        for(unsigned i=0;i<n0;i++){dw4_fight_damage d,c;assert(!dw4_fight_p2e_damage(&ctx,60,40000+base,0,(dw4_fight_down){0,0},&d) && !dw4_fight_p2e_damage(&ctx,60,40000+base,1,(dw4_fight_down){0,0},&c));sum+=d.damage;csum+=c.damage;cn++;if(d.damage<lo)lo=d.damage;if(d.damage>hi)hi=d.damage;}
        int cr=0,ncr=0;for(unsigned i=0;i<n0;i++){int c2;assert(!dw4_fight_p2e_is_critical(&ctx,60,40000+base,&c2));cr+=c2;ncr++;}
        {const char *z=dw4_database_string(tech,29,"ZOKUSEI");int32_t hp=0,sk2=0,ch=0;dw4_database_number(tech,29,"HP",&hp);dw4_database_number(tech,29,"SKILL",&sk2);dw4_database_number(tech,29,"CHIMEIRITSU",&ch);fprintf(stderr,"pcTech row 29 %s: hp %d skill %d crit %d zokusei %s\n",dw4_database_string(tech,29,"NAME"),hp,sk2,ch,z?z:"");
            double sI=0;for(unsigned i=0;i<n0;i++){dw4_fight_damage d;int bI=-1;for(size_t q=0;q<n;q++)if(w[q].record==29)bI=w[q].revision;assert(bI>=0 && !dw4_fight_p2e_damage(&ctx,60,40000+bI,0,(dw4_fight_down){0,0},&d));sI+=d.damage;}fprintf(stderr,"impact damage mean %.1f\n",sI/n0);}
        printf("fire damage mean %.1f (%d..%d), critical mean %.1f (x%.3f), port critical rate %.4f\n",sum/n0,lo,hi,csum/cn,csum/sum,(double)cr/ncr);
        return 0;
    }
    if(!strcmp(mode,"jumpstop")) {
        /* Retail parity (owner note 2026-10-20): when a prompt takes control away (PLAYER OFCTRL: the area-change dialogue) while the player is running and jumping, its horizontal
         * momentum stops and it falls straight down. */
        const int revisit[]={2,355,503};h=enter(&mount,revisit,3);run(h,&frame,600,0,0);assert(control(h));
        dw4_modelctrl *pl=dw4_lobby_player_model(dw4_hubruntime_world(h));
        for(unsigned i=0;i<40;i++){dw4_hubruntime_input(h,0,-1,0,0,0);dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60);}   /* running */
        dw4_hubruntime_input(h,0,-1,0,0x2000,0x2000);dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60);                      /* jump */
        for(unsigned i=0;i<4;i++){dw4_hubruntime_input(h,0,-1,0,0,0);dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60);}
        dw4_modelctrl_actor a0;dw4_modelctrl_actor_state(pl,&a0);
        const char *seq0=dw4_modelctrl_sequence(pl);fprintf(stderr,"airborne sequence %s at %.2f %.2f %.2f\n",seq0,a0.position[0],a0.position[1],a0.position[2]);
        assert(!strcmp(seq0,"SQ_JUMP") || !strcmp(seq0,"SQ_FALL"));
        char error[256];dw4_script_value off[4]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,-1,NULL,0},{DW4_SCRIPT_STRING,0,"OFCTRL",6}},r;
        assert(!dw4_hubruntime_sd(h,off,4,&r,error,sizeof error));
        float moved=0,y_start=a0.position[1],y_end=y_start;
        for(unsigned i=0;i<40;i++){
            dw4_modelctrl_actor b0;dw4_modelctrl_actor_state(pl,&b0);
            dw4_hubruntime_input(h,0,-1,0,0,0);dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60);
            dw4_modelctrl_actor b1;dw4_modelctrl_actor_state(pl,&b1);
            float dx=b1.position[0]-b0.position[0],dz=b1.position[2]-b0.position[2];if(i>=2)moved+=sqrtf(dx*dx+dz*dz);y_end=b1.position[1];
        }
        fprintf(stderr,"after OFCTRL: horizontal travel %.3f over 38 ticks, height %.2f -> %.2f, sequence %s\n",moved,y_start,y_end,dw4_modelctrl_sequence(pl));
        assert(moved<0.5f && y_end<y_start+0.01f);
        printf("jump stop: control taken away mid-jump removes the horizontal momentum (%.3f units) and the player falls in place\n",moved);
        return 0;
    }
    if(!strcmp(mode,"fightmagic")) {
        /* Support techniques (FIGHTCALC cases 20/21): arithmetic checked against the source formulas by hand; not a retail comparison. */
        const int revisit[]={2,355,503};h=enter(&mount,revisit,3);
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
        const dw4_databases *dbs=dw4_hubruntime_databases(h);const dw4_database *enemy=dw4_databases_get(dbs,"enemy"),*tech=dw4_databases_get(dbs,"pcTech");
        int32_t sk[9];for(int i=0;i<9;i++)sk[i]=9999;
        assert(!dw4_property_set_number(p0,"DIGIMONNO",15) && !dw4_property_set_number(p0,"LEVEL",999) && !dw4_property_set_array(p0,"SKILL",sk,9) && !dw4_playerstats_recalculate((void *)dbs,p0));
        assert(!dw4_property_set_number(p0,"KASHIKOSA",9999));
        size_t n=0;const dw4_item_record *w=dw4_property_items(p0,"WAZALIST",&n);
        int rowof[100];for(int i=0;i<100;i++)rowof[i]=-1;
        for(size_t i=0;i<n;i++)if(w[i].revision>=0 && w[i].revision<100)rowof[w[i].revision]=w[i].record;
        fprintf(stderr,"fightmagic rows: heal lt %d heal %d cure lt %d cure %d raise %d speed %d resist %d power %d\n",rowof[40],rowof[45],rowof[55],rowof[60],rowof[50],rowof[65],rowof[75],rowof[80]);
        dw4_random rng=dw4_hubruntime_state(h)->random;dw4_fight_ctx ctx={p0,dw4_database_typed(enemy),&rng,dw4_database_typed(tech)};
        dw4_magic m;
        /* GETPATKZOKUSEI: a technique attack uses the row's ZOKUSEI, anything else ATTACKZOKUSEI */
        {int32_t e=99;int fire=-1;for(size_t i=0;i<n;i++){const char *z=dw4_database_string(tech,w[i].record,"ZOKUSEI");if(z && !strcmp(z,"fire"))fire=w[i].revision;}
         assert(fire>=0 && !dw4_fight_attack_element(&ctx,40000+fire,&e) && e==0);
         assert(rowof[40]>=0 && !dw4_fight_attack_element(&ctx,40000+40,&e) && e==-1);   /* "none" */
         assert(!dw4_property_set_number(p0,"ATTACKZOKUSEI",2) && !dw4_fight_attack_element(&ctx,10001,&e) && e==2);
         assert(!dw4_property_set_number(p0,"ATTACKZOKUSEI",-1) && !dw4_fight_attack_element(&ctx,10001,&e) && e==-1);}
        /* gate: the target argument must equal the caster */
        assert(!dw4_fight_p2p_magic(&ctx,0,1,40040,&m) && m.kind==DW4_MAGIC_NONE);
        /* Heal Lt / Heal: row HP + SKILL[7] + KASHIKOSA */
        {int32_t hp=0;dw4_database_number(tech,rowof[40],"HP",&hp);
         assert(!dw4_fight_p2p_magic(&ctx,0,0,40040,&m) && m.kind==DW4_MAGIC_HEAL && m.row==rowof[40] && m.self && !m.area && m.v[0]==hp+9999+9999);
         fprintf(stderr,"heal lt row %d: %d\n",m.row,m.v[0]);
         if(rowof[45]>=0){assert(!dw4_fight_p2p_magic(&ctx,0,0,40045,&m) && m.kind==DW4_MAGIC_HEAL && m.self && m.area);}
         int32_t mhp=0,v;assert(!dw4_property_number(p0,"MHP",&mhp) && mhp>0);
         assert(!dw4_property_set_number(p0,"HP",1) && dw4_fight_apply_hp(p0,39198)==1 && !dw4_property_number(p0,"HP",&v) && v==(mhp<39199?mhp:39199) && !dw4_property_set_number(p0,"HP",1) && dw4_fight_apply_hp(p0,mhp+5)==1 && !dw4_property_number(p0,"HP",&v) && v==mhp);   /* added, then clamped to MHP */
         assert(!dw4_property_set_number(p0,"HP",10) && dw4_fight_apply_hp(p0,-50)==1 && !dw4_property_number(p0,"HP",&v) && v==0);
         assert(dw4_fight_apply_hp(p0,500)==0 && !dw4_property_number(p0,"HP",&v) && v==0);   /* dead players are not healed */
         assert(!dw4_property_set_number(p0,"HP",mhp));}
        /* Cure Lt: (row - base + 5 - endurance) >= rand % 10, one draw per poisoned target */
        assert(rowof[55]>=0 && !dw4_fight_p2p_magic(&ctx,0,0,40055,&m) && m.kind==DW4_MAGIC_CURE && m.self && !m.area && m.v[0]==rowof[55]-55+5);
        {dw4_random predict=rng;int cured,hits=0;
         for(int i=0;i<2000;i++){unsigned r=dw4_random_next(&predict)%10;assert(!dw4_fight_p2p_cure_poison(&ctx,&m,3,&cured) && cured==(m.v[0]-3>=(int)r));hits+=cured;}
         double rate=hits/2000.0;fprintf(stderr,"cure lt rate at endurance 3: %.3f (numerator %d)\n",rate,m.v[0]);assert(fabs(rate-(m.v[0]-3+1)/10.0)<0.04);
         assert(!dw4_fight_p2p_cure_poison(&ctx,&m,0,&cured) && cured);      /* numerator 9 beats every draw 0..9 at endurance 0 */
         assert(!dw4_fight_p2p_cure_poison(&ctx,&m,10,&cured) && !cured);}   /* 9 - 10 < 0 */
        if(rowof[60]>=0){assert(!dw4_fight_p2p_magic(&ctx,0,0,40060,&m) && m.kind==DW4_MAGIC_CURE && m.area);}
        /* Speed: {TIME + KASHIKOSA, SKILL[8]/5 + SUBAYASA, CHIMEIRITSU, MHIRITSU, KAIHIRITSU} of the row */
        {int32_t t=0,su=0,c1=0,c2=0,c3=0;int r=rowof[65];assert(r>=0);
         dw4_database_number(tech,r,"TIME",&t);dw4_database_number(tech,r,"SUBAYASA",&su);dw4_database_number(tech,r,"CHIMEIRITSU",&c1);dw4_database_number(tech,r,"MHIRITSU",&c2);dw4_database_number(tech,r,"KAIHIRITSU",&c3);
         assert(!dw4_fight_p2p_magic(&ctx,2,2,40065,&m) && m.kind==DW4_MAGIC_SPEEDUP && !m.self && m.area && m.area_has_caster && m.nv==5);
         assert(m.v[0]==t+9999 && m.v[1]==9999/5+su && m.v[2]==c1 && m.v[3]==c2 && m.v[4]==c3);
         fprintf(stderr,"speed row %d: %d %d %d %d %d (time col %d, subayasa col %d)\n",r,m.v[0],m.v[1],m.v[2],m.v[3],m.v[4],t,su);}
        /* Resist: {TIME, FIRE, ICE, THUNDER, DARK} of the row */
        {int32_t x[5]={0};const char *c[5]={"TIME","FIRE","ICE","THUNDER","DARK"};int r=rowof[75];assert(r>=0);for(int k=0;k<5;k++)dw4_database_number(tech,r,c[k],&x[k]);
         assert(!dw4_fight_p2p_magic(&ctx,0,0,40075,&m) && m.kind==DW4_MAGIC_REFRACT && m.area_has_caster);
         for(int k=0;k<5;k++)assert(m.v[k]==x[k]);
         fprintf(stderr,"resist row %d: %d %d %d %d %d\n",r,x[0],x[1],x[2],x[3],x[4]);}
        /* Power: {TIME + KASHIKOSA, SKILL/5 + TSUYOSA, SKILL/5 + MAMORI, SKILL/5 + MAXHP} */
        if(rowof[80]>=0){int32_t t=0,a=0,b=0,mx=0,r=rowof[80];dw4_database_number(tech,r,"TIME",&t);dw4_database_number(tech,r,"TSUYOSA",&a);dw4_database_number(tech,r,"MAMORI",&b);dw4_database_number(tech,r,"MAXHP",&mx);
         assert(!dw4_fight_p2p_magic(&ctx,0,0,40080,&m) && m.kind==DW4_MAGIC_POWERUP && m.v[0]==t+9999 && m.v[1]==1999+a && m.v[2]==1999+b && m.v[3]==1999+mx);}
        /* Raise: table pair by row (59..95 step 9 and 100..6400, the second equal to the row's HP column); the item version (-50) is the first pair */
        if(rowof[50]>=0){int32_t hp=0;dw4_database_number(tech,rowof[50],"HP",&hp);assert(!dw4_fight_p2p_magic(&ctx,0,0,40050,&m) && m.kind==DW4_MAGIC_RAISE && !m.self && m.area && m.v[0]==59+9*(rowof[50]-50) && m.v[1]==hp);}
        assert(!dw4_fight_p2p_magic(&ctx,0,0,-50,&m) && m.kind==DW4_MAGIC_RAISE && m.v[0]==59 && m.v[1]==100);
        /* an unrelated attack number does nothing */
        assert(!dw4_fight_p2p_magic(&ctx,0,0,40012,&m) && m.kind==DW4_MAGIC_NONE);
        printf("fightmagic: element, heal/cure/raise/speed/power/resist arithmetic self-consistent with the source formulas (not retail-compared)\n");
        return 0;
    }
    if(!strcmp(mode,"magicapply")) {
        /* Area query + heal/cure/raise application, hand-computed from 0x3fc780 / 0x3f9c80 / 0x447b00 / 0x3d50c0: dist^2 < 900 strict, 3D, caster excluded, HP 0 and non-members dropped */
        const int revisit[]={2,355,503};h=enter(&mount,revisit,3);
        dw4_playerrecords *rec=dw4_hubruntime_records(h);
        const dw4_databases *dbs=dw4_hubruntime_databases(h);
        dw4_random rng=dw4_hubruntime_state(h)->random;dw4_fight_ctx ctx={NULL,dw4_database_typed(dw4_databases_get(dbs,"enemy")),&rng,dw4_database_typed(dw4_databases_get(dbs,"pcTech"))};
        for(int i=0;i<4;i++){dw4_property_folder *p=dw4_playerrecords_get(rec,"GETPLAYER",i);assert(p && !dw4_property_set_number(p,"MHP",1000) && !dw4_property_set_number(p,"HP",100));}
        int joined[4]={1,1,1,1};
        /* caster 0 at origin; 1 at 29.9 (in); 2 at exactly 30 (out: strict); 3 in range but dead */
        float pos[4][3]={{0,0,0},{29.9f,0,0},{30.0f,0,0},{0,0,10}};
        assert(!dw4_property_set_number(dw4_playerrecords_get(rec,"GETPLAYER",3),"HP",0));
        dw4_magic_group g;assert(!dw4_magic_player_group(rec,joined,pos,&g));
        int32_t list[4],v;
        assert(dw4_magic_area_collect(&g,0,pos[0],list)==1 && list[0]==1);
        assert(dw4_magic_area_collect(&g,-1,pos[0],list)==2 && list[0]==0 && list[1]==1);   /* excluded -1: the caster itself is returned */
        pos[2][0]=29.99f;pos[2][1]=1.0f;   /* 3D: 29.99^2 + 1 > 900 */
        assert(!dw4_magic_player_group(rec,joined,pos,&g) && dw4_magic_area_collect(&g,0,pos[0],list)==1);
        pos[2][0]=20.0f;pos[2][1]=20.0f;   /* 800 < 900 */
        assert(!dw4_magic_player_group(rec,joined,pos,&g) && dw4_magic_area_collect(&g,0,pos[0],list)==2 && list[0]==1 && list[1]==2);
        joined[1]=0;assert(!dw4_magic_player_group(rec,joined,pos,&g) && dw4_magic_area_collect(&g,0,pos[0],list)==1 && list[0]==2);   /* not joined: no answer */
        joined[1]=1;
        /* Heal Lt: caster only; Heal: caster plus the area, the full delta each, clamped to MHP, the dead left alone */
        dw4_magic m={DW4_MAGIC_HEAL,0,1,0,0,1,{300,0,0,0,0}};int ap[4];
        assert(!dw4_magic_player_group(rec,joined,pos,&g));
        assert(dw4_magic_apply_heal(rec,&m,0,&g,ap)==0 && ap[0]==1 && !ap[1]);
        assert(!dw4_property_number(dw4_playerrecords_get(rec,"GETPLAYER",0),"HP",&v) && v==400 && !dw4_property_number(dw4_playerrecords_get(rec,"GETPLAYER",1),"HP",&v) && v==100);
        m.area=1;m.v[0]=950;
        assert(dw4_magic_apply_heal(rec,&m,0,&g,ap)==2 && ap[0] && ap[1] && ap[2] && !ap[3]);
        for(int i=0;i<3;i++)assert(!dw4_property_number(dw4_playerrecords_get(rec,"GETPLAYER",i),"HP",&v) && v==1000);
        assert(!dw4_property_number(dw4_playerrecords_get(rec,"GETPLAYER",3),"HP",&v) && v==0);
        /* a dead caster is left alone */
        assert(!dw4_property_set_number(dw4_playerrecords_get(rec,"GETPLAYER",0),"HP",0));
        assert(!dw4_magic_player_group(rec,joined,pos,&g) && dw4_magic_apply_heal(rec,&m,0,&g,ap)==2 && !ap[0] && ap[1] && ap[2]);
        /* Cure: a draw only per poisoned target, the caster first; Cure Lt is the caster only */
        dw4_magic c={DW4_MAGIC_CURE,0,1,1,0,1,{9,0,0,0,0}};
        for(int i=0;i<4;i++)assert(!dw4_property_set_number(dw4_playerrecords_get(rec,"GETPLAYER",i),"HP",500));
        assert(!dw4_magic_player_group(rec,joined,pos,&g));
        {int poi[4]={1,0,1,0};int32_t en[4]={0,0,10,0};int cu[4];
         dw4_random predict=rng;unsigned r0=dw4_random_next(&predict)%10,r1=dw4_random_next(&predict)%10;
         assert(dw4_magic_apply_cure(&ctx,&c,0,&g,poi,en,cu)==2);
         assert(cu[0]==(9>=(int)r0) && cu[0]==1 && cu[1]==0 && cu[2]==(9-10>=(int)r1) && cu[2]==0 && cu[3]==0);
         c.area=0;int cu2[4];
         assert(dw4_magic_apply_cure(&ctx,&c,0,&g,poi,en,cu2)==1 && cu2[0]==1 && !cu2[2]);}
        /* Raise: PLAYER2 group, excluded -1; HP set unclamped for a target whose model is not running */
        {dw4_magic ra={DW4_MAGIC_RAISE,50,0,1,0,2,{68,400,0,0,0}};dw4_magic_group g2;memset(&g2,0,sizeof g2);
         g2.member[2]=g2.member[3]=1;g2.answer[2]=g2.answer[3]=1;g2.pos[2][0]=10;g2.pos[3][0]=31;
         int run[4]={0,0,0,0};int32_t tg[4],pc[4];float cp[3]={0,0,0};
         assert(dw4_magic_apply_raise(rec,&ra,&g2,cp,run,tg,pc)==1 && tg[0]==2 && pc[0]==68);
         assert(!dw4_property_number(dw4_playerrecords_get(rec,"GETPLAYER",2),"HP",&v) && v==400);
         assert(!dw4_property_number(dw4_playerrecords_get(rec,"GETPLAYER",3),"HP",&v) && v==500);
         run[2]=1;ra.v[1]=6400;assert(dw4_magic_apply_raise(rec,&ra,&g2,cp,run,tg,pc)==1 && !dw4_property_number(dw4_playerrecords_get(rec,"GETPLAYER",2),"HP",&v) && v==400);}
        printf("magicapply: area (dist^2<900, 3D, strict, caster excluded, dead/non-joined dropped), heal, cure draw order and raise application consistent with the retail disassembly (not retail-measured)\n");
        return 0;
    }
    if(!strcmp(mode,"deathflow")) {
        /* GAMERAM BKCHIPBITEXP / DEADRESTART and the capsule start as record arithmetic, hand-computed from the matched source (beNDMWGameRam::vfunc_34 outer
         * case 20 and message 16, beNDMWMdlPlayer2::vfunc_36). g(d,x) = 200d + (x+139)d^2, so g(4,5) = 3104, g(3,4) = 1887 (span 1217, loss 1217*2/10 = 243),
         * g(1,2) = 341, g(0,1) = 0 (span 341, loss 68). Self-consistency only, not retail-measured. */
        const int revisit[]={2,355,503};h=enter(&mount,revisit,3);
        dw4_playerrecords *rec=dw4_hubruntime_records(h);const dw4_databases *dbs=dw4_hubruntime_databases(h);char error[256];
        assert(!dw4_playerrecords_create(rec,dbs,1,"p_agumon","Mate",error,sizeof error));
        dw4_property_folder *common=dw4_playerrecords_get(rec,"GETCOMMON",0),*p0=dw4_playerrecords_get(rec,"GETPLAYER",0),*p1=dw4_playerrecords_get(rec,"GETPLAYER",1);
        assert(common && p0 && p1);
        const char *name0=dw4_property_string(p0,"DIGIMONNAME"),*name1=dw4_property_string(p1,"DIGIMONNAME");assert(name0 && name1 && strcmp(name0,name1));
        #define BKDATA(i) ({size_t n_=0;const int32_t *d_=dw4_property_array(common,"BKCHIPDATA",&n_);assert(d_ && n_==8);d_[i];})
        #define STASH(slot_,pf,level_,exp_,bit_) do{assert(!dw4_property_set_number(pf,"LEVEL",level_) && !dw4_property_set_number(pf,"EXP",exp_) && !dw4_property_set_number(pf,"BIT",bit_) && !dw4_magic_bkchip_bitexp(rec,slot_));}while(0)
        /* level 5, EXP 3500, BIT 250: loses 243 (stays above the level base 3104), BIT 250 goes to the stash and the record is emptied */
        STASH(1,p1,5,3500,250);
        assert(rec_num(p1,"BIT")==0 && rec_num(p1,"EXP")==3257 && BKDATA(2)==250 && BKDATA(3)==243);
        assert(!BKDATA(0) && !BKDATA(1) && !BKDATA(4) && !BKDATA(5) && !BKDATA(6) && !BKDATA(7));
        {const char *nm=dw4_property_string_at(common,"BKCHIPNAME",1);assert(nm && !strcmp(nm,name1) && !dw4_property_string_at(common,"BKCHIPNAME",0));}
        /* the floor: EXP 3200 would drop to 2957, below g(4,5) = 3104, so it stops at 3104 and only 96 are lost */
        STASH(1,p1,5,3200,0);assert(rec_num(p1,"EXP")==3104 && BKDATA(2)==0 && BKDATA(3)==96);
        /* exactly the base: nothing to lose */
        STASH(1,p1,5,3104,5);assert(rec_num(p1,"EXP")==3104 && BKDATA(2)==5 && BKDATA(3)==0);
        /* level 2: loss 68; EXP 500 -> 432, EXP 400 -> floor 341 (loss 59) */
        STASH(1,p1,2,500,0);assert(rec_num(p1,"EXP")==432 && BKDATA(3)==68);
        STASH(1,p1,2,400,0);assert(rec_num(p1,"EXP")==341 && BKDATA(3)==59);
        /* levels 1 and 999 keep their EXP and leave the loss entry alone (the retail branch does not write it) */
        {const int32_t pre[8]={11,12,13,77,15,16,17,18};assert(!dw4_property_set_array(common,"BKCHIPDATA",pre,8));}
        STASH(1,p1,1,90,31);assert(rec_num(p1,"EXP")==90 && rec_num(p1,"BIT")==0 && BKDATA(2)==31 && BKDATA(3)==77 && BKDATA(0)==11 && BKDATA(1)==12 && BKDATA(7)==18);
        STASH(1,p1,999,123456,32);assert(rec_num(p1,"EXP")==123456 && BKDATA(2)==32 && BKDATA(3)==77);
        /* slots are independent: slot 0 level 5, EXP 4000 -> 3757, its own name */
        STASH(0,p0,5,4000,7);assert(rec_num(p0,"EXP")==3757 && BKDATA(0)==7 && BKDATA(1)==243 && BKDATA(2)==32 && BKDATA(3)==77);
        {const char *nm=dw4_property_string_at(common,"BKCHIPNAME",0),*nm1=dw4_property_string_at(common,"BKCHIPNAME",1);assert(nm && !strcmp(nm,name0) && nm1 && !strcmp(nm1,name1));}
        assert(dw4_magic_bkchip_bitexp(rec,4)==-1 && dw4_magic_bkchip_bitexp(rec,-1)==-1);
        /* the whole death and Raise: stash at level 5, then the 59 % Revive disc refund pays 243 * 59 / 100 = 143 back to the same digimon */
        STASH(1,p1,5,3500,250);assert(!dw4_magic_apply_raise_refund(rec,1,59));
        assert(rec_num(p1,"BIT")==250 && rec_num(p1,"EXP")==3257+143 && BKDATA(2)==0 && BKDATA(3)==0);
        /* the capsule's start writes the loaded stage and the capsule's translation for its own slot only */
        {const float where[3]={1.5f,2.5f,-3.5f};size_t nf=0;
         assert(!dw4_magic_capsule_start(rec,2,"dng101b1",where) && !dw4_magic_capsule_start(rec,1,"stag0101",(const float[3]){-4,5,6}));
         const char *s2=dw4_property_string_at(common,"BKCHIPSTAGE",2),*s1=dw4_property_string_at(common,"BKCHIPSTAGE",1);
         assert(s2 && !strcmp(s2,"dng101b1") && s1 && !strcmp(s1,"stag0101") && !dw4_property_string_at(common,"BKCHIPSTAGE",0) && !dw4_property_string_at(common,"BKCHIPSTAGE",3));
         const float *fp=dw4_property_floats(common,"BKCHIPPOS",&nf);assert(fp && nf==12);
         assert(fp[3]==-4 && fp[4]==5 && fp[5]==6 && fp[6]==1.5f && fp[7]==2.5f && fp[8]==-3.5f && !fp[0] && !fp[1] && !fp[2] && !fp[9] && !fp[10] && !fp[11]);}
        /* DEADRESTART: HP = MHP, MP = MMP for ISUSE slots only (the byte test) */
        assert(!dw4_property_set_number(p0,"ISUSE",1) && !dw4_property_set_number(p1,"ISUSE",0));
        assert(!dw4_property_set_number(p0,"MHP",300) && !dw4_property_set_number(p0,"HP",0) && !dw4_property_set_number(p0,"MMP",50) && !dw4_property_set_number(p0,"MP",3));
        assert(!dw4_property_set_number(p1,"MHP",900) && !dw4_property_set_number(p1,"HP",5) && !dw4_property_set_number(p1,"MMP",90) && !dw4_property_set_number(p1,"MP",6));
        assert(!dw4_magic_dead_restart(rec));
        assert(rec_num(p0,"HP")==300 && rec_num(p0,"MP")==50 && rec_num(p1,"HP")==5 && rec_num(p1,"MP")==6);
        assert(!dw4_property_set_number(p1,"ISUSE",1) && !dw4_magic_dead_restart(rec) && rec_num(p1,"HP")==900 && rec_num(p1,"MP")==90);
        printf("deathflow: BKCHIPBITEXP (BIT stash, 2/10 of the level span lost, floored at the level base, levels 1 and 999 untouched), capsule start records and DEADRESTART agree with hand-computed values from the matched source\n");
        return 0;
    }
    if(!strcmp(mode,"deathcoop")) {
        /* Two local players in the Humid Cave: one KO'd (the capsule appears after the measured 120 ticks and writes the BKCHIP stash), refused by a Raise while
         * the capsule's ONE counter is below 10, revived by the item Raise (HP 100, 59 % of the lost EXP back), KO'd again, then both down: the capsule rule
         * runs the end chunk (end_g_000bcaps.lua) and DEADRESTART refills the records when the hub is requested. */
        const int fl[]={2,355,503};h=enter(&mount,fl,3);
        unsigned until=0;
        for(;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        {   dw4_playerrecords *rec=dw4_hubruntime_records(h);const dw4_databases *db=dw4_hubruntime_databases(h);char error[256];
            assert(!dw4_playerrecords_create(rec,db,1,"p_agumon","Mate",error,sizeof error));
            assert(!dw4_property_set_number(dw4_playerrecords_get(rec,"GETCOMMON",0),"NINZU",2) && !dw4_property_set_number(dw4_playerrecords_get(rec,"GETPLAYER",1),"ISUSE",1));}
        h=take_exit(&mount,h,&frame,"stag0101","matz00","dng101b1",0);
        assert(dw4_lobby_player_count(dw4_hubruntime_world(h))==2);
        for(until=0;until<2000 && !control(h);until++)run(h,&frame,1,0,0);
        run(h,&frame,600,0,0);
        dw4_playerrecords *rec=dw4_hubruntime_records(h);
        dw4_property_folder *common=dw4_playerrecords_get(rec,"GETCOMMON",0),*p0=dw4_playerrecords_get(rec,"GETPLAYER",0),*p1=dw4_playerrecords_get(rec,"GETPLAYER",1);
        dw4_combat *cb=dw4_hubruntime_combat_owner(h);const dw4_combat_stats *st=dw4_hubruntime_combat(h);assert(cb && st);
        const char *name1=dw4_property_string(p1,"DIGIMONNAME");assert(name1);
        #define TICKS(n_) run(h,&frame,(n_),0,0)
        #define WALK(slot_,w_) do{assert(!dw4_lobby_select_player(dw4_hubruntime_world(h),(slot_)) && !dw4_lobby_walk(dw4_hubruntime_world(h),&(w_)));dw4_lobby_select_player(dw4_hubruntime_world(h),0);}while(0)
        assert(!dw4_property_set_number(p0,"MHP",9999) && !dw4_property_set_number(p0,"HP",9999));
        assert(!dw4_property_set_number(p1,"MHP",500) && !dw4_property_set_number(p1,"HP",500) && !dw4_property_set_number(p1,"LEVEL",5) &&
               !dw4_property_set_number(p1,"EXP",3500) && !dw4_property_set_number(p1,"BIT",250));
        dw4_lobby_walk_state w0,w1;WALK(0,w0);
        char where[96];snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",w0.position[0]+5,w0.position[1],w0.position[2]);place_slot(h,1,where);
        TICKS(5);   /* both seen alive: the KO trigger is armed */
        dw4_combat_capsule cap;
        assert(!dw4_combat_capsule_state(cb,1,&cap) && st->downs==0 && st->gameovers==0);
        /* KO: the capsule exists exactly DW4_KO_CAPSULE_DELAY ticks after HP reached 0, not before */
        assert(!dw4_property_set_number(p1,"HP",0));
        TICKS(DW4_KO_CAPSULE_DELAY-1);
        assert(!dw4_combat_capsule_state(cb,1,&cap) && st->downs==0 && !dw4_property_string_at(common,"BKCHIPSTAGE",1) && rec_num(p1,"BIT")==250);
        TICKS(1);
        WALK(1,w1);
        assert(dw4_combat_capsule_state(cb,1,&cap) && cap.downed && st->downs==1 && st->gameovers==0 && cap.age==0 && !cap.ready);
        assert(fabsf(cap.pos[0]-w1.position[0])+fabsf(cap.pos[2]-w1.position[2])<3.0f);
        /* the downed player's model is erased with the capsule (retail: SQ_DEAD ends in SQ_ERAS): not running, not drawn, no PLAYER at the slot; the survivor's is untouched */
        #define KO_SHOT(tag_) do{if(getenv("DW4_KO_SHOT")){dw4_fb fb_;char path_[512];assert(!dw4_fb_init(&fb_,640,448));assert(dw4_hubruntime_draw(h,&fb_,NULL)>0);\
            snprintf(path_,sizeof path_,"%s-%s.png",getenv("DW4_KO_SHOT"),(tag_));assert(!dw4_png_write(path_,fb_.rgba,fb_.w,fb_.h));dw4_fb_free(&fb_);}}while(0)
        KO_SHOT("capsule");
        {   dw4_lobby *wl=dw4_hubruntime_world(h);
            assert(!dw4_lobby_select_player(wl,1));dw4_modelctrl *m1=dw4_lobby_player_model(wl);
            assert(!dw4_modelctrl_active(m1) && !dw4_modelctrl_drawable(m1) && !dw4_modelctrl_sequence(m1));
            dw4_lobby_select_player(wl,0);
            assert(dw4_modelctrl_active(dw4_lobby_player_model(wl)) && dw4_modelctrl_drawable(dw4_lobby_player_model(wl)));}
        {const char *stg=dw4_property_string_at(common,"BKCHIPSTAGE",1),*nm=dw4_property_string_at(common,"BKCHIPNAME",1);size_t nf=0;const float *fp=dw4_property_floats(common,"BKCHIPPOS",&nf);
         assert(stg && !strcmp(stg,"dng101b1") && nm && !strcmp(nm,name1) && fp && nf==12 && fp[3]==cap.pos[0] && fp[4]==cap.pos[1] && fp[5]==cap.pos[2]);}
        {size_t nd=0;const int32_t *d=dw4_property_array(common,"BKCHIPDATA",&nd);assert(d && nd==8 && d[2]==250 && d[3]==243 && !d[0] && !d[1]);}
        assert(rec_num(p1,"BIT")==0 && rec_num(p1,"EXP")==3257 && rec_num(p1,"HP")==0);
        {dw4_combat_view v;dw4_combat_view_current(cb,&v);assert(v.joined[0] && v.running[0] && !v.joined[1] && !v.running[1] && v.downed[1] && v.young[1]);}
        /* Raise on a capsule whose ONE counter is below 10: the handler returns early, no revive and no refund */
        int32_t res=0;
        assert(!dw4_combat_cast_support(cb,0,0,-50,NULL,&res) && st->raises==0 && rec_num(p1,"HP")==0 && rec_num(p1,"EXP")==3257);
        TICKS(12);
        assert(dw4_combat_capsule_state(cb,1,&cap) && cap.ready && cap.age==DW4_CAPSULE_READY_TICKS && cap.near_player);   /* player 0 stands 5 units away: SQ_SWON */
        assert(st->gameovers==0);   /* player 0 lives: the capsule finds a PLAYER */
        /* the item Raise (Revive disc: 59 %, HP 100) from player 0 */
        assert(!dw4_combat_cast_support(cb,0,0,-50,NULL,&res) && st->raises==1);
        assert(rec_num(p1,"HP")==100 && rec_num(p1,"BIT")==250 && rec_num(p1,"EXP")==3257+143);   /* 243 * 59 / 100 */
        assert(!dw4_combat_capsule_state(cb,1,&cap) && !dw4_property_string_at(common,"BKCHIPSTAGE",1));
        {size_t nd=0;const int32_t *d=dw4_property_array(common,"BKCHIPDATA",&nd);assert(d && !d[2] && !d[3]);}
        /* the PLAYER model is generated again at the caster's position with SQ_CMBK (REVE*1: hidden for one frame, JUMP SQ_CMBK02: REVE*2 fades it in over 60
         * frames, then SQ_WAIT); the slot's receiver and the lobby draw it again */
        {   dw4_lobby *wl=dw4_hubruntime_world(h);
            assert(!dw4_lobby_select_player(wl,1));dw4_modelctrl *m1=dw4_lobby_player_model(wl);
            assert(dw4_modelctrl_active(m1) && dw4_modelctrl_sequence(m1) && !strcmp(dw4_modelctrl_sequence(m1),"SQ_CMBK"));
            dw4_lobby_select_player(wl,0);}
        TICKS(3);
        {   WALK(0,w0);WALK(1,w1);
            assert(fabsf(w0.position[0]-w1.position[0])+fabsf(w0.position[2]-w1.position[2])<8.0f);   /* the revived player stands at the caster */
            dw4_lobby *wl=dw4_hubruntime_world(h);
            assert(!dw4_lobby_select_player(wl,1));dw4_modelctrl *m1=dw4_lobby_player_model(wl);
            const char *seq=dw4_modelctrl_sequence(m1);
            assert(seq && (!strcmp(seq,"SQ_CMBK") || !strcmp(seq,"SQ_CMBK02")) && dw4_modelctrl_drawable(m1));
            fprintf(stderr,"revived player sequence %s alpha %g\n",seq,(double)dw4_modelctrl_alpha(m1));
            KO_SHOT("revive3");
            dw4_lobby_select_player(wl,0);}
        TICKS(30);
        {   dw4_lobby *wl=dw4_hubruntime_world(h);
            assert(!dw4_lobby_select_player(wl,1));dw4_modelctrl *m1=dw4_lobby_player_model(wl);
            const char *seq=dw4_modelctrl_sequence(m1);float alpha=dw4_modelctrl_alpha(m1);
            fprintf(stderr,"revived player sequence %s alpha %g\n",seq,(double)alpha);
            assert(seq && !strcmp(seq,"SQ_CMBK02") && alpha>0.0f && alpha<1.0f);   /* mid fade-in */
            KO_SHOT("revive33");
            dw4_lobby_select_player(wl,0);}
        TICKS(60);
        {   dw4_lobby *wl=dw4_hubruntime_world(h);
            assert(!dw4_lobby_select_player(wl,1));dw4_modelctrl *m1=dw4_lobby_player_model(wl);
            const char *seq=dw4_modelctrl_sequence(m1);
            fprintf(stderr,"revived player sequence %s alpha %g\n",seq,(double)dw4_modelctrl_alpha(m1));
            assert(seq && !strcmp(seq,"SQ_WAIT") && dw4_modelctrl_drawable(m1));
            KO_SHOT("revive93");
            dw4_lobby_select_player(wl,0);}
        TICKS(110);
        assert(st->downs==1 && st->gameovers==0 && !dw4_hubruntime_travel(h)->pending && rec_num(p1,"HP")>0);
        /* KO of the revived player again, then player 0 walks away from the capsule (SQ_SWOF) */
        assert(!dw4_property_set_number(p1,"HP",0));
        TICKS(DW4_KO_CAPSULE_DELAY+1);
        assert(dw4_combat_capsule_state(cb,1,&cap) && st->downs==2 && st->gameovers==0);
        WALK(0,w0);snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>",w0.position[0]+40,w0.position[1],w0.position[2]);place_slot(h,0,where);
        TICKS(3);
        assert(dw4_combat_capsule_state(cb,1,&cap) && !cap.near_player && st->gameovers==0);
        /* now player 0 goes down too: its capsule appears after the delay, and the next capsule tick finds no PLAYER: the end chunk runs once */
        assert(!dw4_property_set_number(p0,"HP",0));
        TICKS(DW4_KO_CAPSULE_DELAY-1);
        assert(!dw4_combat_capsule_state(cb,0,&cap) && st->gameovers==0);
        TICKS(1);
        assert(dw4_combat_capsule_state(cb,0,&cap) && st->downs==3 && st->gameovers==0 && !dw4_hubruntime_travel(h)->pending);
        TICKS(1);
        assert(st->gameovers==1);
        {const char *stg=dw4_property_string_at(common,"BKCHIPSTAGE",0);assert(stg && !strcmp(stg,"dng101b1"));}
        unsigned i;
        for(i=0;i<4000 && !dw4_hubruntime_travel(h)->pending;i++){
            dw4_hubruntime_input(h,0,0,0,i%40<4?0x4000:0,i%40==0?0x4000:0);
            if(dw4_hubruntime_tick(h,(uint64_t)frame++*1000000000ULL/60)){fprintf(stderr,"tick %u: %s\n",frame,dw4_hubruntime_error(h));return 1;}
        }
        assert(dw4_hubruntime_travel(h)->pending && !strcmp(dw4_hubruntime_travel(h)->destination,"stagML11") && dw4_hubruntime_travel(h)->generate_pos==0);
        assert(st->gameovers==1);
        /* DEADRESTART when the hub is requested: both ISUSE slots back to full HP and MP */
        TICKS(1);
        assert(rec_num(p0,"HP")==rec_num(p0,"MHP") && rec_num(p1,"HP")==rec_num(p1,"MHP") && rec_num(p1,"HP")==500 && rec_num(p1,"MP")==rec_num(p1,"MMP"));
        fprintf(stderr,"game over: Terminal requested after %u more ticks\n",i);
        dw4_hubruntime_close(h);
        printf("dungeon co-op KO: capsule after %d ticks (BKCHIP stash), Raise refused while young, item Raise revives (HP 100, EXP refund), both down -> end chunk -> stagML11, DEADRESTART\n",DW4_KO_CAPSULE_DELAY);
        return 0;
    }
    if(!strcmp(mode,"buffapply")) {
        /* Hand-computed from the retail disassembly of beNDMWMdlPEBase vfunc_47 (0x445d10) and vfunc_46 (0x443bd0); see docs/combat.md. */
        dw4_buffs b;dw4_magic sp={DW4_MAGIC_SPEEDUP,0,0,1,1,5,{600,41,7,8,9}},pw={DW4_MAGIC_POWERUP,0,0,1,1,4,{3000,10,20,30,0}},rs={DW4_MAGIC_REFRACT,0,0,1,1,5,{120,1,2,3,4}};
        assert(dw4_buff_duration_ns(60)==1000000000 && dw4_buff_duration_ns(600)==10000000000LL && dw4_buff_duration_ns(1)==16666666);
        dw4_buffs_init(&b,1);
        assert(dw4_buff_apply(&b,&sp)==1 && b.time[DW4_BUFF_SPEED]==600 && b.first[DW4_BUFF_SPEED] && b.up[0]==41 && b.up[1]==7 && b.up[2]==8 && b.up[3]==9 && !b.up[4]);
        assert(dw4_buff_apply(&b,&pw)==1 && b.time[DW4_BUFF_POWER]==3000 && b.up[4]==10 && b.up[5]==20 && b.up[6]==30 && !b.up[7]);
        assert(dw4_buff_apply(&b,&rs)==1 && b.time[DW4_BUFF_RESIST]==120 && b.up[7]==1 && b.up[8]==2 && b.up[9]==3 && b.up[10]==4);
        {dw4_magic bad={DW4_MAGIC_HEAL};assert(dw4_buff_apply(&b,&bad)==-1);}
        /* not on control: nothing armed, nothing expires */
        assert(dw4_buff_update(&b,0,1000000000000LL)==0 && b.first[DW4_BUFF_SPEED] && b.time[DW4_BUFF_SPEED]==600);
        /* t0: all three armed; Resist (2 s) expires strictly after 2 s, in 2^18 ns steps */
        int64_t t0=1<<20;
        assert(dw4_buff_update(&b,1,t0)==0 && !b.first[DW4_BUFF_SPEED] && b.duration_ns[DW4_BUFF_RESIST]==2000000000LL);
        assert(dw4_buff_update(&b,1,t0+2000000000LL)==0 && b.time[DW4_BUFF_RESIST]==120);        /* elapsed 7629 steps of 2^18 ns < duration */
        assert(dw4_buff_update(&b,1,t0+2000000000LL+(1<<18))==1 && !b.time[DW4_BUFF_RESIST] && !b.up[7] && !b.up[10] && b.up[0]==41 && b.up[4]==10);
        /* refresh while active: values replaced, timer restarted from the next update (no sum, no extension of the old deadline) */
        dw4_magic sp2={DW4_MAGIC_SPEEDUP,0,0,1,1,5,{60,5,0,0,0}};
        assert(dw4_buff_apply(&b,&sp2)==1 && b.up[0]==5 && b.up[1]==0 && b.time[DW4_BUFF_SPEED]==60);
        int64_t t1=t0+5000000000LL;
        assert(dw4_buff_update(&b,1,t1)==0 && b.start_ns[DW4_BUFF_SPEED]==t1 && b.duration_ns[DW4_BUFF_SPEED]==1000000000LL);
        assert(dw4_buff_update(&b,1,t1+1100000000LL)==1 && !b.time[DW4_BUFF_SPEED] && !b.up[0] && !b.up[3] && b.up[4]==10);
        /* an enemy's 7-entry list: Resist stores are skipped, no recalculation request */
        dw4_buffs e;dw4_buffs_init(&e,0);
        assert(dw4_buff_apply(&e,&rs)==0 && e.time[DW4_BUFF_RESIST]==120 && !e.up[7] && dw4_buff_apply(&e,&pw)==0 && e.up[4]==10 && e.up[6]==30);
        assert(dw4_buff_update(&e,1,0)==0 && dw4_buff_update(&e,1,3000000000LL)==0 && !e.time[DW4_BUFF_RESIST] && e.up[4]==10 && e.time[DW4_BUFF_POWER]==3000);
        assert(dw4_buff_update(&e,1,60000000000LL)==0 && !e.time[DW4_BUFF_POWER] && !e.up[4] && !e.up[6]);
        printf("buffapply: SET*UP receiver slots, 1/60 s durations on the engine clock, replace-and-restart refresh and expiry follow the retail disassembly (not run-time compared)\n");
        return 0;
    }
    if(!strcmp(mode,"supportheal")) {
        /* Heal Lt / Heal through the combat seam (dw4_combat_cast_support): the delta is row HP + SKILL[7] + KASHIKOSA, the area is the 3D sphere of radius 30 around the
         * caster (strict), the caster is handled first and separately, the dead are left alone, the HP gauge is republished. The delta is the one retail-measured number (the
         * four anchors); area, caster inclusion and order are the recovered rules, NOT measured. Also BLPcalcKoukaMagic / BLPgetAttackZokusei through the contact layer. */
        struct sup s;sup_open(&mount,&s,&frame,30,1);
        const dw4_hubruntime_hud *hud=dw4_hubruntime_hud_state(s.h);const dw4_combat_stats *st=dw4_combat_get_stats(s.c);
        const int32_t sk[9]={1,1,1,1,1,1,1,1234,500};
        sup_record(&s,0,sk,567,50000,1000);sup_record(&s,1,sk,0,50000,500);
        int row40=wazalist_row(s.p[0],40);assert(row40>=40 && row40<=44 && wazalist_row(s.p[0],45)<0);
        waza_add(s.p[0],45+(row40-40),45);   /* species 15 does not learn Heal: fabricated after the last recalculation (same tier as Heal Lt) */
        int row45=wazalist_row(s.p[0],45);
        const int32_t d40=tdb_num(s.tdb,row40,"HP")+1234+567,d45=tdb_num(s.tdb,row45,"HP")+1234+567;
        assert(tdb_num(s.tdb,row40,"SKILL")==7 && tdb_num(s.tdb,row45,"SKILL")==7);
        fprintf(stderr,"supportheal: Heal Lt row %d delta %d, Heal row %d delta %d\n",row40,d40,row45,d45);
        dw4_random rng0=dw4_hubruntime_state(s.h)->random;int32_t res=-5;
        #define HP_OF(slot) rec_num(s.p[slot],"HP")
        /* Heal Lt: the caster only; the mate (5 units away) is untouched; the result is the script's 1; nothing is drawn. */
        s.view.pos[1][0]=5;unsigned u0=hud->updates;
        assert(!dw4_combat_cast_support(s.c,0,0,80040,&s.view,&res) && res==1);
        assert(HP_OF(0)==1000+d40 && HP_OF(1)==500 && st->heals==1);
        assert(hud->hp_value[0]==1000+d40 && hud->updates==u0+2 && hud->hp_percent[0]==100.0f*(float)(1000+d40)/50000.0f);
        assert(rng_draws(&rng0,&dw4_hubruntime_state(s.h)->random)==0);
        /* Heal: caster and the mate inside 29.9 units (3D, strict), the same full delta each. */
        assert(!dw4_property_set_number(s.p[0],"HP",1000) && !dw4_property_set_number(s.p[1],"HP",500));
        s.view.pos[1][0]=29.9f;u0=hud->updates;
        assert(!dw4_combat_cast_support(s.c,0,0,80045,&s.view,&res) && res==1 && HP_OF(0)==1000+d45 && HP_OF(1)==500+d45 && st->heals==3 && hud->updates==u0+4);
        assert(hud->hp_value[1]==500+d45);
        /* The sphere is strict: exactly 30 is out, and so is (0,1,29.99): 1 + 29.99^2 > 900; (0,0,29.9) is in. */
        const float edge[3][3]={{30.0f,0,0},{0,1.0f,29.99f},{0,0,29.9f}};const int in[3]={0,0,1};
        for(int e=0;e<3;e++){
            assert(!dw4_property_set_number(s.p[0],"HP",1000) && !dw4_property_set_number(s.p[1],"HP",500));
            memcpy(s.view.pos[1],edge[e],sizeof edge[e]);
            assert(!dw4_combat_cast_support(s.c,0,0,80045,&s.view,&res) && HP_OF(0)==1000+d45 && HP_OF(1)==(in[e]?500+d45:500));
        }
        /* Clamped to MHP; a dead mate is not healed (and does not publish); a dead caster is left alone while the area is still healed. */
        s.view.pos[1][0]=10;s.view.pos[1][1]=s.view.pos[1][2]=0;
        assert(!dw4_property_set_number(s.p[0],"HP",50000-10) && !dw4_property_set_number(s.p[1],"HP",0));
        u0=hud->updates;
        assert(!dw4_combat_cast_support(s.c,0,0,80045,&s.view,&res) && HP_OF(0)==50000 && HP_OF(1)==0 && hud->updates==u0+2);
        assert(!dw4_property_set_number(s.p[0],"HP",0) && !dw4_property_set_number(s.p[1],"HP",500));
        assert(!dw4_combat_cast_support(s.c,0,0,80045,&s.view,&res) && HP_OF(0)==0 && HP_OF(1)==500+d45);
        /* The gate: receiver != shooter changes nothing and answers the receiver. */
        assert(!dw4_property_set_number(s.p[0],"HP",1000) && !dw4_property_set_number(s.p[1],"HP",500));
        assert(!dw4_combat_cast_support(s.c,0,1,80045,&s.view,&res) && res==0 && HP_OF(0)==1000 && HP_OF(1)==500);
        /* A number that matches no family is still a self hit and changes nothing. */
        assert(!dw4_combat_cast_support(s.c,0,0,80012,&s.view,&res) && res==1 && HP_OF(0)==1000);
        /* An unlearned family is a loud error, not a silent no-op. */
        assert(dw4_combat_cast_support(s.c,0,0,80080,&s.view,&res)==-1 && dw4_combat_error(s.c)[0]);
        /* The four retail anchors (Heal Lt row 44 = 19200): the same sums the live casts gave. */
        {
            const int32_t one[1][2]={{44,40}};const int32_t table[4][3]={{9999,9999,39198},{1234,567,21001},{0,100,19300},{5000,9999,34199}};
            assert(tdb_num(s.tdb,44,"HP")==19200);
            for(int i=0;i<4;i++){
                int32_t sk2[9];memcpy(sk2,sk,sizeof sk2);sk2[7]=table[i][0];
                waza_set(s.p[0],one,1);
                assert(!dw4_property_set_array(s.p[0],"SKILL",sk2,9) && !dw4_property_set_number(s.p[0],"KASHIKOSA",table[i][1]) && !dw4_property_set_number(s.p[0],"HP",1000) && !dw4_property_set_number(s.p[0],"MHP",99999));
                assert(!dw4_combat_cast_support(s.c,0,0,80040,&s.view,&res) && HP_OF(0)==1000+table[i][2]);
            }
        }
        /* The contact layer: BLPcalcKoukaMagic answers through p2p_magic with a number, BLPgetAttackZokusei through attack_element and feeds BLTgetAttributeStr. */
        {
            dw4_model_fight f;dw4_combat_fight(s.c,&f);assert(f.p2p_magic && f.attack_element);
            dw4_model_contact ct={.fight=&f,.target_slot=0,.shoot_ram_no=0,.bullet_kind=80040};
            dw4_script_value r;char error[256];
            assert(!dw4_property_set_number(s.p[0],"HP",1000) && !dw4_property_set_number(s.p[0],"MHP",99999));
            assert(!dw4_model_contact_call(&ct,"BLPcalcKoukaMagic",NULL,0,&r,error,sizeof error) && r.type==DW4_SCRIPT_NUMBER && r.number==1 && HP_OF(0)==1000+34199);
            ct.shoot_ram_no=1;   /* another player's volume on this body: receiver != shooter */
            assert(!dw4_property_set_number(s.p[0],"HP",1000));
            assert(!dw4_model_contact_call(&ct,"BLPcalcKoukaMagic",NULL,0,&r,error,sizeof error) && r.type==DW4_SCRIPT_NUMBER && r.number==0 && HP_OF(0)==1000);
            ct.shoot_ram_no=0;
            const int32_t two[2][2]={{44,40},{4,0}};   /* Heal Lt row 44 and Petty Fire (row 4, element fire) */
            waza_set(s.p[0],two,2);
            const struct {int32_t kind,prop;const char *name;} ze[]={{40000,0,"fire"},{40040,0,"common"},{10001,2,"thunder"},{10001,-1,"common"},{10001,4,"common"},{10001,0,"fire"},{10001,1,"ice"},{10001,3,"dark"}};
            for(unsigned i=0;i<sizeof ze/sizeof *ze;i++){
                assert(!dw4_property_set_number(s.p[0],"ATTACKZOKUSEI",ze[i].prop));ct.bullet_kind=ze[i].kind;
                assert(!dw4_model_contact_call(&ct,"BLPgetAttackZokusei",NULL,0,&r,error,sizeof error) && r.type==DW4_SCRIPT_STRING && r.length==strlen(ze[i].name) && !memcmp(r.string,ze[i].name,r.length));
                assert(ct.cached[1]==(ze[i].kind==40000?0:ze[i].kind==40040?-1:ze[i].prop));
                assert(!dw4_model_contact_call(&ct,"BLTgetAttributeStr",NULL,0,&r,error,sizeof error) && r.length==strlen(ze[i].name) && !memcmp(r.string,ze[i].name,r.length));
            }
            ct.fight=NULL;assert(dw4_model_contact_call(&ct,"BLPcalcKoukaMagic",NULL,0,&r,error,sizeof error)==1);   /* no combat owner: not this layer's call */
        }
        /* Membership derived from the models (no explicit view): joined = a model answers, positions = the feet; the mate 10 units away is healed, 31 units away is not. */
        {
            const int32_t two[2][2]={{44,40},{49,45}};
            assert(!dw4_property_set_array(s.p[0],"SKILL",sk,9) && !dw4_property_set_number(s.p[0],"KASHIKOSA",567));
            waza_set(s.p[0],two,2);int32_t dd=tdb_num(s.tdb,49,"HP")+1234+567;
            sup_place(&s,0,0,0,0);sup_place(&s,1,10,0,0);
            assert(!dw4_property_set_number(s.p[0],"HP",1000) && !dw4_property_set_number(s.p[1],"HP",500));
            assert(!dw4_combat_cast_support(s.c,0,0,80045,NULL,&res) && HP_OF(0)==1000+dd && HP_OF(1)==500+dd);
            sup_place(&s,1,31,0,0);assert(!dw4_property_set_number(s.p[0],"HP",1000) && !dw4_property_set_number(s.p[1],"HP",500));
            assert(!dw4_combat_cast_support(s.c,0,0,80045,NULL,&res) && HP_OF(0)==1000+dd && HP_OF(1)==500);
        }
        dw4_hubruntime_close(s.h);
        printf("supportheal: Heal Lt / Heal delta, 30-unit 3D strict area, caster separate, dead untouched, HUD publish, retail anchors, BLPcalcKoukaMagic / BLPgetAttackZokusei (port, delta retail-anchored)\n");
        return 0;
    }
    if(!strcmp(mode,"supportbuff")) {
        /* Speed / Power / Resist through the combat seam: the cast sends the retail SETSPEEDUP / SETPOWERUP / SETREFRACT message to the area around the caster and then to the
         * caster, the model's status (the single owner of the timers and of the record's UPDATA, docs/combat.md "Support technique wiring") stores the lists in the record and the
         * player is recalculated; the 1/60 s timer expires in 2^18 ns steps and zeroes the slots and recalculates again. Port output, self-consistent with the disassembly; NOT retail-measured. */
        struct sup s;sup_open(&mount,&s,&frame,40,1);
        const dw4_hubruntime_hud *hud=dw4_hubruntime_hud_state(s.h);const dw4_combat_stats *st=dw4_combat_get_stats(s.c);
        const int32_t sk[9]={1,1,1,1,1,1,1,1000,1000};
        sup_record(&s,0,sk,150,0,-1);sup_record(&s,1,sk,0,0,-1);
        for(int i=0;i<2;i++)assert(!dw4_property_set_number(s.p[i],"HP",rec_num(s.p[i],"MHP")/2));
        const int rs=wazalist_row(s.p[0],65),rr=wazalist_row(s.p[0],75),rp=80+(rs-65);
        assert(rs>=65 && rs<=69 && rr>=75 && rr<=79);
        /* Power Up is fabricated (species 15 has no Power family) after the last recalculation; every recalculation rebuilds the list, so it is set again before a Power cast. */
        const int32_t items[3][2]={{rs,65},{rr,75},{rp,80}};
        waza_set(s.p[0],items,3);
        dw4_random rng0=dw4_hubruntime_state(s.h)->random;
        sup_place(&s,1,10,0,0);sup_advance(&s,2);   /* binds the status hosts of both models */
        int32_t res=0,hp0[2],base_sub[2],base_chi[2],base_kai[2],base_mah[2],base_tsu[2],base_mam[2],base_mhp[2],base_res[2][4];
        const char *const rk[4]={"HONOOTEIKO","KOORITEIKO","KAMINARITEIKO","YAMITEIKO"};
        #define SNAP() do{for(int i_=0;i_<2;i_++){hp0[i_]=rec_num(s.p[i_],"HP");base_sub[i_]=rec_num(s.p[i_],"SUBAYASA");base_chi[i_]=rec_num(s.p[i_],"CHIMEIRITSU");base_kai[i_]=rec_num(s.p[i_],"KAIHIRITSU");\
            base_mah[i_]=rec_num(s.p[i_],"MAHITEIKOU");base_tsu[i_]=rec_num(s.p[i_],"TSUYOSA");base_mam[i_]=rec_num(s.p[i_],"MAMORI");base_mhp[i_]=rec_num(s.p[i_],"MHP");\
            for(int r_=0;r_<4;r_++)base_res[i_][r_]=rec_num(s.p[i_],rk[r_]);}}while(0)
        #define STATUS(i) dw4_modelctrl_status(s.m[i])
        #define TIMER(i,which) (STATUS(i)->timer[which])
        /* Frames from the first status tick after a cast (which arms the timer) until `which` is no longer set on model 0; at most `limit`. */
        #define RUN_TO_EXPIRY(which,limit,out) do{unsigned n_=1;sup_advance(&s,1);while(TIMER(0,which) && n_<(limit)){sup_advance(&s,1);n_++;}out=n_-1;}while(0)
        SNAP();
        /* ---- Speed: both players in range; the area first, the caster last ---- */
        {
            dw4_magic m=sup_magic(&s,0,80065);
            const int32_t time=m.v[0];
            assert(m.kind==DW4_MAGIC_SPEEDUP && m.nv==5 && time>=1800 && base_sub[0]+m.v[1]<9999);   /* the 9999 clamp must not hide the buff */
            char name[DW4_BUFF_NAME_CAP],args[DW4_BUFF_ARGS_CAP];
            assert(!dw4_buff_message(&m,name,args) && !strcmp(name,"SETSPEEDUP"));
            fprintf(stderr,"supportbuff: Speed row %d: time %d, SUBAYASA +%d, CHIMEIRITSU +%d, MHIRITSU %d, KAIHIRITSU +%d (args %s)\n",rs,time,m.v[1],m.v[2],m.v[3],m.v[4],args);
            unsigned recalcs0=st->recalcs,exp0=st->buff_expiries,applies0=st->buff_applies,u0=hud->updates;
            assert(!dw4_combat_cast_support(s.c,0,0,80065,&s.view,&res) && res==1);
            assert(st->buff_applies==applies0+2 && st->recalcs==recalcs0+2 && hud->updates==u0+4);
            dw4_buffs ref;dw4_buffs_init(&ref,1);assert(dw4_buff_apply(&ref,&m)==1);   /* the reference receiver of buffapply.c must agree with the owner */
            for(int i=0;i<2;i++){
                const int32_t *up=rec_up(s.p[i]);
                assert(TIMER(i,DW4_STATUS_SPEEDUP)==time && ref.time[DW4_BUFF_SPEED]==time);
                for(int k=0;k<4;k++)assert(up[k]==m.v[1+k] && up[k]==ref.up[k]);
                for(int k=4;k<11;k++)assert(up[k]==0);
                fprintf(stderr,"slot %d: SUBAYASA %d -> %d, CHIMEIRITSU %d -> %d, KAIHIRITSU %d -> %d, MAHITEIKOU %d -> %d\n",i,base_sub[i],rec_num(s.p[i],"SUBAYASA"),base_chi[i],rec_num(s.p[i],"CHIMEIRITSU"),base_kai[i],rec_num(s.p[i],"KAIHIRITSU"),base_mah[i],rec_num(s.p[i],"MAHITEIKOU"));
                /* SUBAYASA is a plain sum; the three rates have a floor of 1 in the recalculation (a stat that was below it reads 1 before the buff and the buff alone after). */
                assert(rec_num(s.p[i],"SUBAYASA")==base_sub[i]+m.v[1] && floored_sum(base_chi[i],m.v[2],rec_num(s.p[i],"CHIMEIRITSU")) && floored_sum(base_kai[i],m.v[4],rec_num(s.p[i],"KAIHIRITSU")));
                assert(floored_sum(base_mah[i],m.v[3],rec_num(s.p[i],"MAHITEIKOU")) && rec_num(s.p[i],"HP")==hp0[i] && rec_num(s.p[i],"TSUYOSA")==base_tsu[i]);
            }
            assert(hud->hp_value[0]==hp0[0] && hud->hp_value[1]==hp0[1]);
            unsigned n;RUN_TO_EXPIRY(DW4_STATUS_SPEEDUP,time+60,n);
            fprintf(stderr,"supportbuff: Speed (%d frames) ended %u frames after it was armed\n",time,n);
            assert(n+1>=(unsigned)time && n<=(unsigned)time+2);   /* 2^18 ns steps can move the edge by one frame */
            for(int i=0;i<2;i++){
                const int32_t *up=rec_up(s.p[i]);
                assert(!TIMER(i,DW4_STATUS_SPEEDUP));
                for(int k=0;k<11;k++)assert(up[k]==0);
                assert(rec_num(s.p[i],"SUBAYASA")==base_sub[i] && rec_num(s.p[i],"CHIMEIRITSU")==base_chi[i] && rec_num(s.p[i],"HP")==hp0[i]);
            }
            assert(st->buff_expiries==exp0+2 && st->recalcs==recalcs0+4 && hud->updates==u0+8);   /* exactly one recalculation (and gauge publish) per slot at the expiry */
        }
        /* ---- the mate outside 30 units gets nothing; the caster alone is buffed ---- */
        {
            s.view.pos[1][0]=31;unsigned recalcs0=st->recalcs;dw4_magic m=sup_magic(&s,0,80065);
            assert(!dw4_combat_cast_support(s.c,0,0,80065,&s.view,&res) && st->recalcs==recalcs0+1);
            for(int k=0;k<11;k++)assert(rec_up(s.p[1])[k]==0 && rec_up(s.p[0])[k]==(k<4?m.v[1+k]:0));
            assert(!TIMER(1,DW4_STATUS_SPEEDUP) && TIMER(0,DW4_STATUS_SPEEDUP)>0);
            s.view.pos[1][0]=10;
            sup_sd(s.m[0],0,"ALLCLEARSTATUS",NULL);   /* the stage-end clear: lists zeroed, recalculated */
            assert(!TIMER(0,DW4_STATUS_SPEEDUP));
            for(int k=0;k<11;k++)assert(rec_up(s.p[0])[k]==0);
            assert(rec_num(s.p[0],"SUBAYASA")==base_sub[0]);
        }
        /* ---- control off (the _isOnCtrl guard): nothing arms and nothing expires; control back, the full duration runs ---- */
        {
            dw4_magic m=sup_magic(&s,0,80065);const int32_t time=m.v[0];unsigned recalcs0=st->recalcs;
            s.view.pos[1][0]=31;
            sup_sd(s.m[0],0,"OFCTRL",NULL);
            assert(!dw4_combat_cast_support(s.c,0,0,80065,&s.view,&res));
            sup_advance(&s,3000);
            assert(TIMER(0,DW4_STATUS_SPEEDUP)==time && st->recalcs==recalcs0+1 && rec_up(s.p[0])[0]==m.v[1]);
            sup_sd(s.m[0],0,"ONCTRL",NULL);
            unsigned n;RUN_TO_EXPIRY(DW4_STATUS_SPEEDUP,time+60,n);
            assert(n+1>=(unsigned)time && n<=(unsigned)time+2 && rec_up(s.p[0])[0]==0);
            s.view.pos[1][0]=10;
        }
        /* ---- refresh at 50 %: values replaced, the full duration restarts (no summing, no old deadline) ---- */
        {
            dw4_magic m=sup_magic(&s,0,80065);s.view.pos[1][0]=31;
            assert(!dw4_combat_cast_support(s.c,0,0,80065,&s.view,&res));
            sup_advance(&s,(unsigned)m.v[0]/2);
            assert(TIMER(0,DW4_STATUS_SPEEDUP)>0);
            dw4_magic m2=sup_magic(&s,0,80065);   /* KASHIKOSA was recalculated: a new TIME */
            assert(!dw4_combat_cast_support(s.c,0,0,80065,&s.view,&res) && TIMER(0,DW4_STATUS_SPEEDUP)==m2.v[0] && rec_up(s.p[0])[0]==m2.v[1]);
            sup_advance(&s,(unsigned)m2.v[0]-4);assert(TIMER(0,DW4_STATUS_SPEEDUP)>0);   /* the first deadline (50 % ago + 50 %) has long passed */
            unsigned n;RUN_TO_EXPIRY(DW4_STATUS_SPEEDUP,100,n);
            assert(n>=3 && n<=6);   /* (time - 4) frames already run, so the duration from the recast's own first tick ends here: time - 1 .. time + 2 in all */
            s.view.pos[1][0]=10;
        }
        /* ---- Resist, Power and Speed run independent timers on the same player ---- */
        {
            const int32_t rtime=tdb_num(s.tdb,rr,"TIME");
            dw4_magic mr=sup_magic(&s,0,80075);s.view.pos[1][0]=31;SNAP();
            assert(mr.kind==DW4_MAGIC_REFRACT && mr.v[0]==rtime);
            for(int r=0;r<4;r++)assert(base_res[0][r]+mr.v[1+r]>=1 && base_res[0][r]+mr.v[1+r]<=9999);
            assert(!dw4_combat_cast_support(s.c,0,0,80075,&s.view,&res));
            for(int r=0;r<4;r++){assert(rec_up(s.p[0])[7+r]==mr.v[1+r] && rec_num(s.p[0],rk[r])==base_res[0][r]+mr.v[1+r]);}
            sup_advance(&s,600);
            waza_set(s.p[0],items,3);
            dw4_magic mp=sup_magic(&s,0,80080);
            assert(mp.kind==DW4_MAGIC_POWERUP && mp.nv==4 && base_tsu[0]+mp.v[1]<9999 && base_mam[0]+mp.v[2]<9999);
            assert(!dw4_combat_cast_support(s.c,0,0,80080,&s.view,&res));
            assert(rec_up(s.p[0])[4]==mp.v[1] && rec_up(s.p[0])[5]==mp.v[2] && rec_up(s.p[0])[6]==mp.v[3] && rec_num(s.p[0],"TSUYOSA")==base_tsu[0]+mp.v[1] && rec_num(s.p[0],"MAMORI")==base_mam[0]+mp.v[2]);
            assert(rec_num(s.p[0],"MHP")==base_mhp[0]+mp.v[3] && rec_num(s.p[0],"HP")==hp0[0]);   /* MAXHP: the maximum rises, the HP stays */
            dw4_buffs ref;dw4_buffs_init(&ref,1);assert(dw4_buff_apply(&ref,&mp)==1 && ref.time[DW4_BUFF_POWER]==TIMER(0,DW4_STATUS_POWERUP) && ref.up[4]==rec_up(s.p[0])[4] && ref.up[6]==rec_up(s.p[0])[6]);
            sup_advance(&s,600);
            dw4_magic ms=sup_magic(&s,0,80065);
            assert(!dw4_combat_cast_support(s.c,0,0,80065,&s.view,&res));
            assert(TIMER(0,DW4_STATUS_REFRACT)>0 && TIMER(0,DW4_STATUS_POWERUP)>0 && TIMER(0,DW4_STATUS_SPEEDUP)>0);
            unsigned n;RUN_TO_EXPIRY(DW4_STATUS_REFRACT,3000,n);   /* Resist (armed first) ends first; the others keep their slots */
            assert(1200+n+1>=(unsigned)rtime && 1200+n<=(unsigned)rtime+2);   /* armed 1200 frames before this cast's first tick */
            for(int k=7;k<11;k++)assert(rec_up(s.p[0])[k]==0);
            assert(TIMER(0,DW4_STATUS_POWERUP)>0 && TIMER(0,DW4_STATUS_SPEEDUP)>0 && rec_up(s.p[0])[4]==mp.v[1] && rec_up(s.p[0])[0]==ms.v[1]);
            RUN_TO_EXPIRY(DW4_STATUS_POWERUP,3000,n);
            for(int k=4;k<7;k++)assert(rec_up(s.p[0])[k]==0);
            assert(TIMER(0,DW4_STATUS_SPEEDUP)>0 && rec_up(s.p[0])[0]==ms.v[1]);
            RUN_TO_EXPIRY(DW4_STATUS_SPEEDUP,3000,n);
            for(int k=0;k<11;k++)assert(rec_up(s.p[0])[k]==0);
            assert(rec_num(s.p[0],"MHP")==base_mhp[0] && rec_num(s.p[0],"TSUYOSA")==base_tsu[0] && rec_num(s.p[0],"SUBAYASA")==base_sub[0] && rec_num(s.p[0],rk[0])==base_res[0][0]);
            s.view.pos[1][0]=10;
        }
        /* ---- KO: a downed player's timers are zeroed by the tick, its UPDATA stays, and nothing recalculates (a recalculation would refill HP 0) ---- */
        {
            assert(!dw4_combat_cast_support(s.c,0,0,80065,&s.view,&res) && TIMER(1,DW4_STATUS_SPEEDUP)>0);
            sup_advance(&s,1);
            unsigned recalcs0=st->recalcs;int32_t up0=rec_up(s.p[1])[0];assert(up0!=0);
            assert(!dw4_property_set_number(s.p[1],"HP",0));
            sup_advance(&s,5);
            assert(!TIMER(1,DW4_STATUS_SPEEDUP) && rec_up(s.p[1])[0]==up0 && st->recalcs==recalcs0 && rec_num(s.p[1],"HP")==0 && TIMER(0,DW4_STATUS_SPEEDUP)>0);
            sup_sd(s.m[0],0,"ALLCLEARSTATUS",NULL);
        }
        /* ---- target list order: the area first, the caster last; out of range or dead members are not on it ---- */
        {
            dw4_magic_group g;int32_t out[4];const int joined[2+2]={1,1,0,0};float pos[4][3]={{0,0,0},{10,0,0},{0,0,0},{0,0,0}};
            assert(!dw4_property_set_number(s.p[1],"HP",50));
            assert(!dw4_magic_player_group(s.rec,joined,(const float (*)[3])pos,&g) && dw4_magic_buff_targets(&g,0,out)==2 && out[0]==1 && out[1]==0);
            assert(dw4_magic_buff_targets(&g,1,out)==2 && out[0]==0 && out[1]==1);
            pos[1][0]=30;assert(!dw4_magic_player_group(s.rec,joined,(const float (*)[3])pos,&g) && dw4_magic_buff_targets(&g,0,out)==1 && out[0]==0);
            pos[1][0]=10;assert(!dw4_property_set_number(s.p[1],"HP",0));
            assert(!dw4_magic_player_group(s.rec,joined,(const float (*)[3])pos,&g) && dw4_magic_buff_targets(&g,0,out)==1 && out[0]==0);
        }
        assert(rng_draws(&rng0,&dw4_hubruntime_state(s.h)->random)==0);   /* a buff draws nothing */
        dw4_hubruntime_close(s.h);
        printf("supportbuff: Speed / Power / Resist apply to the area and the caster, record UPDATA + recalculation, 1/60 s timer in 2^18 ns steps, independent timers, refresh, control-off hold, KO (port, not retail-measured)\n");
        return 0;
    }
    if(!strcmp(mode,"supportcure")) {
        /* Cure Lt / Cure on the players' poison status (the status wiring's dw4_status): one rand%10 draw per POISONED target, the caster first, then (Cure) the area in slot order;
         * cured when (row - base + 5) - endurance >= draw; a cure clears the POISON timer. The replay of the engine stream predicts every outcome. Port output; NOT retail-measured. */
        struct sup s;sup_open(&mount,&s,&frame,30,1);
        const dw4_combat_stats *st=dw4_combat_get_stats(s.c);
        const int32_t sk[9]={1,1,1,1,1,1,1,1234,300};
        sup_record(&s,0,sk,567,0,-1);sup_record(&s,1,sk,0,0,-1);
        const int r55=wazalist_row(s.p[0],55);assert(r55>=55 && r55<=59);
        const int32_t items[2][2]={{r55,55},{60+(r55-55),60}};
        waza_set(s.p[0],items,2);   /* Cure (60) is fabricated after the last recalculation (species 15 has Cure Lt only) */
        const int32_t num=r55-55+5;
        assert(sup_magic(&s,0,80055).v[0]==num && sup_magic(&s,0,80060).v[0]==num);
        sup_place(&s,1,10,0,0);sup_advance(&s,2);   /* binds the status hosts */
        dw4_random *rng=(dw4_random *)&dw4_hubruntime_state(s.h)->random;
        int32_t res=0;
        #define POISON(slot,end) do{char a_[48];snprintf(a_,sizeof a_,"I<600>/I<5>/I<%d>",(int)(end));sup_sd(s.m[slot],slot,"SETPOISON",a_);}while(0)
        #define POISONED(slot) dw4_status_is_set(dw4_modelctrl_status(s.m[slot]),DW4_STATUS_POISON)
        #define SAME_STREAM(pr) (!memcmp(&(pr),rng,sizeof *rng))
        const int32_t E_CURE=num-9,E_FAIL=num+1;   /* numerators 9 (beats every draw 0..9) and -1 (beats none) */
        POISON(0,E_CURE);POISON(1,E_FAIL);assert(POISONED(0) && POISONED(1));
        /* Cure Lt: the caster only, one draw. */
        {
            dw4_random pr=*rng;unsigned d=dw4_random_next(&pr)%10;(void)d;unsigned cures0=st->cures;
            assert(!dw4_combat_cast_support(s.c,0,0,80055,&s.view,&res) && res==1);
            assert(!POISONED(0) && POISONED(1) && SAME_STREAM(pr) && st->cures==cures0+1);
        }
        /* Cure Lt with an unpoisoned caster: no draw at all, the poisoned mate is not reached. */
        {
            dw4_random before=*rng;
            assert(!dw4_combat_cast_support(s.c,0,0,80055,&s.view,&res) && POISONED(1) && !memcmp(&before,rng,sizeof before));
        }
        /* Cure: the caster first, then the mate: two draws; the caster (numerator 9) is cured, the mate (-1) is not. */
        {
            POISON(0,E_CURE);dw4_random pr=*rng;dw4_random_next(&pr);dw4_random_next(&pr);
            assert(!dw4_combat_cast_support(s.c,0,0,80060,&s.view,&res) && !POISONED(0) && POISONED(1) && SAME_STREAM(pr));
            /* an unpoisoned caster: only the mate draws */
            POISON(1,E_CURE);pr=*rng;dw4_random_next(&pr);
            assert(!dw4_combat_cast_support(s.c,0,0,80060,&s.view,&res) && !POISONED(0) && !POISONED(1) && SAME_STREAM(pr));
            /* nobody poisoned: no draw */
            dw4_random before=*rng;
            assert(!dw4_combat_cast_support(s.c,0,0,80060,&s.view,&res) && !memcmp(&before,rng,sizeof before));
            /* the mate outside 30 units is not reached */
            POISON(1,E_CURE);s.view.pos[1][0]=31;before=*rng;
            assert(!dw4_combat_cast_support(s.c,0,0,80060,&s.view,&res) && POISONED(1) && !memcmp(&before,rng,sizeof before));
            s.view.pos[1][0]=10;sup_sd(s.m[1],1,"ALLCLEARSTATUS",NULL);
        }
        /* The rate over 2000 casts at endurance 3, each outcome predicted by replaying the stream. */
        {
            dw4_random pr=*rng;int hits=0;
            for(int i=0;i<2000;i++){
                POISON(0,3);unsigned d=dw4_random_next(&pr)%10;int expect=num-3>=(int)d;
                assert(!dw4_combat_cast_support(s.c,0,0,80055,&s.view,&res) && POISONED(0)==!expect && SAME_STREAM(pr));
                hits+=expect;
            }
            double rate=hits/2000.0;fprintf(stderr,"supportcure: Cure Lt rate at endurance 3 (numerator %d): %.3f\n",num,rate);
            assert(fabs(rate-(num-3+1)/10.0)<0.04);
        }
        /* Through the real hit chunk: the cure draw comes first, then the skill-growth draw of BLTcalcSkillUp (SKILL[7] is below the level cap), and the support volume is not an enemy hit. */
        {
            sup_sd(s.m[0],0,"ALLCLEARSTATUS",NULL);
            assert(!dw4_property_set_array(s.p[0],"SKILL",(const int32_t[9]){1,1,1,1,1,1,1,300,300},9) && !dw4_property_set_number(s.p[0],"KASHIKOSA",567));
            waza_set(s.p[0],items,2);POISON(0,E_CURE);
            dw4_random pr=*rng;dw4_random_next(&pr);dw4_random_next(&pr);
            dw4_modelctrl_actor a;float world[16];dw4_modelctrl_actor_state(s.m[0],&a);dw4_modelctrl_actor_matrix(&a,world);
            const float off[3]={0,6,0},size[3]={4,4,4};char error[256];
            unsigned hits0=st->hits,ph0=st->player_hits,sh0=st->support_hits;
            int rc=dw4_combat_fire(s.c,(int64_t)frame*1000000000LL/60,0,s.m[0],80055,world,off,size,error,sizeof error);
            if(rc<0)fprintf(stderr,"fire: %s\n",error);
            assert(rc==1 && !POISONED(0) && SAME_STREAM(pr) && st->hits==hits0 && st->player_hits==ph0 && st->support_hits==sh0+1);
        }
        dw4_hubruntime_close(s.h);
        printf("supportcure: Cure Lt / Cure draw order, cure rule and rate, poison cleared, replayed stream, real hit chunk draw order (port, not retail-measured)\n");
        return 0;
    }
    if(!strcmp(mode,"supportcast")) {
        /* End to end through the real hub: R1 opens the technique panel, the cursor selects the support technique, Cross casts it (MP, SQ_WAZA, the volume on the caster), the ORIGINAL
         * hit_p chunk runs its 80000..89999 branch, BLPcalcKoukaMagic applies the heal / buff, BLTcalcSkillUp draws. Species 15 at level 30 learns Heal Lt (level 1), Cure Lt (12), Speed (22)
         * from the recalculation, so nothing is fabricated for them; Raise (a family species 15 does not learn) is fabricated into WAZALIST after the last recalculation. One player is
         * joined (the runtime admits no more), so the area is empty: a Heal Lt / Speed cast affects the caster alone. Port output; NOT retail-measured, except the Heal Lt gain. */
        const int revisit[]={2,355,503};
        h=enter(&mount,revisit,3);run(h,&frame,600,0,0);assert(control(h));
        dw4_combat *c=dw4_hubruntime_combat_owner(h);dw4_playerrecords *rec=dw4_hubruntime_records(h);const dw4_databases *dbs=dw4_hubruntime_databases(h);const dw4_database *tdb=dw4_databases_get(dbs,"pcTech");
        dw4_property_folder *p0=dw4_playerrecords_get(rec,"GETPLAYER",0);dw4_modelctrl *player=dw4_lobby_player_model(dw4_hubruntime_world(h));
        const dw4_technique *tech=dw4_hubruntime_technique(h);const dw4_hubruntime_hud *hud=dw4_hubruntime_hud_state(h);const dw4_combat_stats *st=dw4_hubruntime_combat(h);
        assert(c && tdb && p0 && player && tech);
        struct sup s;memset(&s,0,sizeof s);s.h=h;s.c=c;s.rec=rec;s.dbs=dbs;s.tdb=tdb;s.p[0]=p0;s.m[0]=player;
        #define RNG() (&dw4_hubruntime_state(h)->random)
        assert(!dw4_property_set_number(p0,"DIGIMONNO",15) && !dw4_property_set_number(p0,"LEVEL",30));
        const int32_t sk[9]={1,1,1,1,1,1,1,1234,1000};
        sup_record(&s,0,sk,567,50000,1000);
        assert(!dw4_property_set_number(p0,"MP",9999));
        /* The generated goblin stands on the caster's origin with its AI off: no support volume may reach it (the old routing offered 8xxxx volumes to the enemies). */
        dw4_modelctrl_actor pa;dw4_modelctrl_actor_state(player,&pa);
        char where[96],error[512];dw4_script_value r;
        snprintf(where,sizeof where,"V<%g,%g,%g>/V<0,0,0>/SQ_WAIT",pa.position[0],pa.position[1],pa.position[2]);
        dw4_script_value gen[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"e_goburi",8},{DW4_SCRIPT_NUMBER,5,NULL,0},{DW4_SCRIPT_STRING,0,"GENERATE",8},{DW4_SCRIPT_STRING,0,where,strlen(where)}};
        assert(!dw4_hubruntime_sd(h,gen,5,&r,error,sizeof error));
        dw4_script_model *goblin=dw4_hubruntime_enemy_state(h,"e_goburi",5);assert(goblin);
        goblin->rec_no=0;goblin->hp=goblin->max_hp=1000;assert(!dw4_hubruntime_enemy_ai_off(h,"e_goburi",5));
        const char *goblin_sequence=goblin_seq(h);
        tech_frames(h,&frame,5);
        /* The world draws on its own (model rhythm), so the cast's draws are counted by the combat owner (skill_draws: BLTcalcSkillUp calls that drew the growth chance). */
        dw4_random b0=*RNG();tech_frames(h,&frame,30);fprintf(stderr,"supportcast: engine draws by the world itself over 30 ticks: %d\n",rng_draws(&b0,RNG()));
        /* Select a technique by its family base in the open panel (R1 opens it when closed), then Cross. Returns the pcTech row. */
        #define PANEL_CAST(base_,row_out) do{\
            tech_frames(h,&frame,1);   /* the panel copies WAZALIST on its tick */\
            dw4_technique_panel pv_=tech_panel(tech,0);\
            if(!pv_.open){tech_step(h,&frame,0x800,0);tech_frames(h,&frame,3);pv_=tech_panel(tech,0);}\
            assert(pv_.open);int target_=-1;for(int i_=0;i_<pv_.count;i_++)if(pv_.base[i_]==(base_))target_=i_;assert(target_>=0);row_out=pv_.row[target_];\
            while(pv_.cursor+pv_.offset<target_){tech_step(h,&frame,0x40,0);tech_step(h,&frame,0,0);pv_=tech_panel(tech,0);}\
            while(pv_.cursor+pv_.offset>target_){tech_step(h,&frame,0x10,0);tech_step(h,&frame,0,0);pv_=tech_panel(tech,0);}\
            tech_step(h,&frame,0,0x4000);}while(0)
        /* ---- Heal Lt, SKILL[7] above the level cap (no skill-growth draw) ---- */
        int row=-1;
        {
            const int32_t delta=tdb_num(tdb,wazalist_row(p0,40),"HP")+1234+567;
            const int32_t mp0=rec_num(p0,"MP");unsigned hits0=st->hits,sh0=st->support_hits,heals0=st->heals,u0=hud->updates,ph0=st->player_hits,sd0=st->skill_draws;
            PANEL_CAST(40,row);
            fprintf(stderr,"supportcast: cast tick: sequence %s MP %d, heals %u, support hits %u missed %u, flying %d\n",dw4_modelctrl_sequence(player),rec_num(p0,"MP"),st->heals,st->support_hits,st->support_missed,dw4_technique_flying(tech,0));
            assert(row==wazalist_row(p0,40) && st->heals==heals0+1);   /* applied in the very tick of the cast */
            const int32_t cost=tdb_num(tdb,row,"MP");
            tech_frames(h,&frame,40);
            fprintf(stderr,"supportcast: Heal Lt row %d: HP 1000 -> %d (delta %d), MP %d -> %d (cost %d), HUD %d / %g\n",row,rec_num(p0,"HP"),delta,mp0,rec_num(p0,"MP"),cost,hud->hp_value[0],hud->hp_percent[0]);
            assert(rec_num(p0,"HP")==1000+delta && rec_num(p0,"MP")==mp0-cost);
            assert(st->support_hits==sh0+1 && st->hits==hits0 && st->player_hits==ph0 && st->skill_draws==sd0);   /* above the cap: the cast draws nothing at all */
            assert(hud->hp_value[0]==1000+delta && hud->updates==u0+2 && hud->hp_percent[0]==100.0f*(float)(1000+delta)/50000.0f);
            assert(goblin->hp==1000 && !strcmp(goblin_seq(h),goblin_sequence));   /* the enemy on the caster's origin never saw the support volume */
            assert(!strcmp(dw4_modelctrl_sequence(player),"SQ_WAIT"));
        }
        /* ---- Heal Lt again, SKILL[7] below the cap: the same gain, plus exactly one skill-growth draw (the cast itself draws nothing) ---- */
        {
            tech_frames(h,&frame,60);
            const int32_t s7[9]={1,1,1,1,1,1,1,500,1000};
            assert(!dw4_property_set_array(p0,"SKILL",s7,9) && !dw4_property_set_number(p0,"HP",1000));
            const int32_t delta=tdb_num(tdb,wazalist_row(p0,40),"HP")+500+rec_num(p0,"KASHIKOSA");
            unsigned sh0=st->support_hits,sd0=st->skill_draws;
            PANEL_CAST(40,row);tech_frames(h,&frame,40);
            assert(st->support_hits==sh0+1 && st->skill_draws==sd0+1);
            size_t n=0;const int32_t *after=dw4_property_array(p0,"SKILL",&n);
            if(after[7]!=500){fprintf(stderr,"supportcast: the skill-growth draw raised SKILL[7] to %d (the record was recalculated)\n",after[7]);assert(rec_num(p0,"HP")==rec_num(p0,"MHP"));}
            else assert(rec_num(p0,"HP")==1000+delta);
        }
        /* ---- Speed: applied to the caster alone (the area is empty), UPDATA + recalculation, the 1/60 s timer runs on the hub tick and expires ---- */
        {
            tech_frames(h,&frame,60);
            assert(!dw4_property_set_array(p0,"SKILL",sk,9) && !dw4_playerstats_recalculate((void *)dbs,p0));   /* the natural stats: MHP, KASHIKOSA */
            assert(!dw4_property_set_number(p0,"HP",rec_num(p0,"MHP")/2) && !dw4_property_set_number(p0,"MP",9999));
            const unsigned sd0=st->skill_draws;
            const int32_t hp0=rec_num(p0,"HP"),sub0=rec_num(p0,"SUBAYASA"),chi0=rec_num(p0,"CHIMEIRITSU");
            dw4_magic m=sup_magic(&s,0,80065);
            const unsigned rc0=st->recalcs,ba0=st->buff_applies,u0=hud->updates,ph0=st->player_hits,ex0=st->buff_expiries;
            assert(m.kind==DW4_MAGIC_SPEEDUP && sub0+m.v[1]<9999);
            PANEL_CAST(65,row);
            assert(st->buff_applies==ba0+1 && st->recalcs==rc0+1);
            const dw4_status *ps=dw4_modelctrl_status(player);assert(ps);
            const int32_t *up=rec_up(p0);
            fprintf(stderr,"supportcast: Speed row %d: time %d, UPDATA %d %d %d %d, SUBAYASA %d -> %d\n",row,m.v[0],up[0],up[1],up[2],up[3],sub0,rec_num(p0,"SUBAYASA"));
            assert(ps->timer[DW4_STATUS_SPEEDUP]==m.v[0] && up[0]==m.v[1] && up[1]==m.v[2] && up[2]==m.v[3] && up[3]==m.v[4]);
            assert(rec_num(p0,"SUBAYASA")==sub0+m.v[1] && floored_sum(chi0,m.v[2],rec_num(p0,"CHIMEIRITSU")) && rec_num(p0,"HP")==hp0);
            assert(hud->updates==u0+2 && hud->hp_value[0]==hp0 && st->skill_draws==sd0);   /* the gauge is republished after the recalculation; SKILL[8] is above the cap: no growth draw */
            unsigned ticks=0;
            while(ps->timer[DW4_STATUS_SPEEDUP] && ticks<(unsigned)m.v[0]+200){tech_step(h,&frame,0,0);ticks++;}
            fprintf(stderr,"supportcast: Speed (%d frames) ended %u ticks after the cast tick\n",m.v[0],ticks);
            assert(!ps->timer[DW4_STATUS_SPEEDUP] && ticks+1>=(unsigned)m.v[0] && ticks<=(unsigned)m.v[0]+5);
            for(int k=0;k<11;k++)assert(rec_up(p0)[k]==0);
            assert(rec_num(p0,"SUBAYASA")==sub0 && rec_num(p0,"HP")==hp0 && st->buff_expiries==ex0+1 && st->recalcs==rc0+2 && st->player_hits==ph0);
            assert(hud->updates==u0+4 && hud->hp_value[0]==hp0);
        }
        /* ---- Raise (fabricated): the SQ_WAZA `reanimation` section's own 80050 HITBOX is the volume (no stand-in bullet): one self hit, one growth draw, no PLAYER2 to revive, and the enemy
         *      standing on the caster still sees nothing ---- */
        {
            tech_frames(h,&frame,60);
            const int32_t s7[9]={1,1,1,1,1,1,1,500,1000};
            assert(!dw4_property_set_array(p0,"SKILL",s7,9) && !dw4_property_set_number(p0,"MP",9999));
            const int32_t items[1][2]={{52,50}};waza_set(p0,items,1);
            unsigned sh0=st->support_hits,hits0=st->hits,rz0=st->raises,sm0=st->support_missed,sd0=st->skill_draws;int32_t mp0=rec_num(p0,"MP");
            PANEL_CAST(50,row);assert(row==52);
            tech_frames(h,&frame,40);
            fprintf(stderr,"supportcast: Raise (reanimation section): support hits %u -> %u, missed %u -> %u, growth draws %u -> %u\n",sh0,st->support_hits,sm0,st->support_missed,sd0,st->skill_draws);
            assert(st->support_hits==sh0+1 && st->hits==hits0 && st->raises==rz0 && st->skill_draws==sd0+1 && rec_num(p0,"MP")==mp0-tdb_num(tdb,52,"MP"));
            assert(goblin->hp==1000 && !strcmp(goblin_seq(h),goblin_sequence) && dw4_technique_flying(tech,0)==0);
        }
        dw4_hubruntime_close(h);
        printf("supportcast: R1 panel -> SQ_WAZA -> support volume on the caster -> original hit_p chunk -> BLPcalcKoukaMagic: Heal Lt gain, Speed UPDATA/timer/expiry, Raise self hit, no enemy hit (port, Heal Lt gain retail-anchored)\n");
        return 0;
    }
    if(!strcmp(mode,"supportraise")) {
        /* Raise as an API: the PLAYER2 (downed) group, the unclamped HP write for a model that is not running, the bank-chip refund. This exercises the combat seam with set_downed capsules;
         * the KO flow end to end (capsule, stash, game over) is `deathcoop` (docs/combat.md "KO, the capsule and game over"). */
        struct sup s;sup_open(&mount,&s,&frame,30,1);
        const dw4_combat_stats *st=dw4_combat_get_stats(s.c);
        const int32_t sk[9]={1,1,1,1,1,1,1,1234,300};
        sup_record(&s,0,sk,567,0,-1);sup_record(&s,1,sk,0,0,-1);
        const int32_t items[1][2]={{52,50}};waza_set(s.p[0],items,1);   /* Raise tier 2 is fabricated */
        dw4_magic m=sup_magic(&s,0,80050);
        assert(m.kind==DW4_MAGIC_RAISE && m.v[0]==77 && m.v[1]==1600 && tdb_num(s.tdb,52,"HP")==1600);
        dw4_property_folder *common=dw4_playerrecords_get(s.rec,"GETCOMMON",0);
        const char *mine=dw4_property_string(s.p[1],"DIGIMONNAME");assert(mine);
        #define ARM_CHIPS(name) do{const int32_t d_[8]={0,0,700,1000,0,0,0,0};const char *n_[4]={NULL,(name),NULL,NULL},*g_[4]={NULL,"stag0101",NULL,NULL};\
            assert(!dw4_property_set_array(common,"BKCHIPDATA",d_,8) && !dw4_property_set_strings(common,"BKCHIPNAME",n_,4) && !dw4_property_set_strings(common,"BKCHIPSTAGE",g_,4) &&\
                !dw4_property_set_number(s.p[1],"BIT",100) && !dw4_property_set_number(s.p[1],"EXP",200) && !dw4_property_set_number(s.p[1],"HP",0));}while(0)
        int32_t res=0;
        s.view.joined[1]=0;s.view.running[1]=0;s.view.downed[1]=1;s.view.pos[1][0]=10;
        const int32_t hp0=rec_num(s.p[0],"HP");
        /* In range, model not running: HP = 1600 (no clamp to MHP), BIT += 700, EXP += 1000 * 77 / 100, the stash and the stage entry cleared. */
        ARM_CHIPS(mine);
        assert(1600>rec_num(s.p[1],"MHP"));
        assert(!dw4_combat_cast_support(s.c,0,0,80050,&s.view,&res) && res==1);
        assert(rec_num(s.p[1],"HP")==1600 && rec_num(s.p[1],"BIT")==800 && rec_num(s.p[1],"EXP")==200+770 && rec_num(s.p[0],"HP")==hp0 && st->raises==1);
        {size_t n=0;const int32_t *d=dw4_property_array(common,"BKCHIPDATA",&n);assert(n==8 && !d[2] && !d[3] && !dw4_property_string_at(common,"BKCHIPSTAGE",1));}
        /* Out of range (30 exactly): nothing happens, no refund. */
        ARM_CHIPS(mine);s.view.pos[1][0]=30;
        assert(!dw4_combat_cast_support(s.c,0,0,80050,&s.view,&res) && rec_num(s.p[1],"HP")==0 && rec_num(s.p[1],"BIT")==100 && rec_num(s.p[1],"EXP")==200 && st->raises==1);
        /* A running model: the HP write is skipped, the refund still happens. */
        ARM_CHIPS(mine);s.view.pos[1][0]=10;s.view.running[1]=1;
        assert(!dw4_combat_cast_support(s.c,0,0,80050,&s.view,&res) && rec_num(s.p[1],"HP")==0 && rec_num(s.p[1],"BIT")==800 && rec_num(s.p[1],"EXP")==970 && st->raises==2);
        /* The stashed EXP returns only to the digimon that dropped it. */
        ARM_CHIPS("p_other");s.view.running[1]=0;
        assert(!dw4_combat_cast_support(s.c,0,0,80050,&s.view,&res) && rec_num(s.p[1],"HP")==1600 && rec_num(s.p[1],"BIT")==800 && rec_num(s.p[1],"EXP")==200);
        /* The item version (attack -50, the Revive disc): the first table pair (59, 100) and no learned technique needed. */
        waza_set(s.p[0],items,0);
        ARM_CHIPS(mine);
        assert(!dw4_combat_cast_support(s.c,0,0,-50,&s.view,&res) && res==1 && rec_num(s.p[1],"HP")==100 && rec_num(s.p[1],"BIT")==800 && rec_num(s.p[1],"EXP")==200+590);
        /* An unlearned Raise is a loud error. */
        assert(dw4_combat_cast_support(s.c,0,0,80050,&s.view,&res)==-1);
        /* Membership from the models and set_downed: the capsule is found at its position, and a revived slot is no longer downed. */
        {
            waza_set(s.p[0],items,1);ARM_CHIPS(mine);
            dw4_modelctrl *only0[4]={s.m[0],NULL,NULL,NULL};dw4_combat_players(s.c,only0);
            const float where[3]={5,0,5};dw4_combat_set_downed(s.c,1,1,where);
            dw4_combat_view v;dw4_combat_view_current(s.c,&v);
            assert(v.joined[0] && !v.joined[1] && v.downed[1] && !v.running[1] && v.pos[1][0]==5 && v.pos[1][2]==5);
            assert(!dw4_combat_cast_support(s.c,0,0,80050,NULL,&res) && rec_num(s.p[1],"HP")==1600);
            assert(!dw4_property_set_number(s.p[1],"HP",0));
            assert(!dw4_combat_cast_support(s.c,0,0,80050,NULL,&res) && rec_num(s.p[1],"HP")==0);   /* the capsule was consumed */
        }
        dw4_hubruntime_close(s.h);
        printf("supportraise: PLAYER2 group, unclamped HP write for a model that is not running, bank-chip refund (BIT, EXP * a / 100 for the same digimon), item pair (59, 100) (seam test; the KO flow is deathcoop)\n");
        return 0;
    }
    if(!strcmp(mode,"droptables")) {
        /* The drop lists decoded from the generator packs against the live-measured sums of findings #263/#264 (stagGF01): the Goburimon generators'
         * lists sum to 3502/3170/4050 (35.02 / 31.70 / 40.50 % chance of any drop) on Normal/Hard/Very Hard, the Guard Room box list nZ1obje1 to 4330, and GENE-19's list is empty. */
        static const int enemy_sum[3]={3502,3170,4050};
        for(int diff=0;diff<3;diff++){
            dw4_fieldgen *g=dw4_fieldgen_open(&mount,"stagGF01",diff);assert(g);
            int checked=0;
            for(size_t i=0;i<dw4_fieldgen_count(g);i++){
                const dw4_gene *e=dw4_fieldgen_at(g,i);int sum=0;for(unsigned k=0;k<e->ndrops[0];k++)sum+=e->drops[0][k].rate;
                if(!strcmp(e->name,"GENE-00")){fprintf(stderr,"diff %d GENE-00: %u entries, sum %d (expect %d)\n",diff,e->ndrops[0],sum,enemy_sum[diff]);assert(sum==enemy_sum[diff]);checked++;}
                if(!strcmp(e->name,"GENE-19")){assert(!e->ndrops[0]);checked++;}
                if(diff==0 && !strcmp(e->name,"GWCS-05")){fprintf(stderr,"GWCS-05: %u entries, sum %d\n",e->ndrops[0],sum);assert(sum==4330);checked++;}
            }
            assert(checked>=2);dw4_fieldgen_close(g);
        }
        /* The roll itself: draw 0 takes the first row, draw 9999 nothing (the sums are below 10000). */
        dw4_fieldgen *g=dw4_fieldgen_open(&mount,"stagGF01",0);const dw4_gene *e=dw4_fieldgen_find(g,"GENE-00");dw4_drop_entry d;
        assert(e && dw4_fieldgen_roll_drop(e,0,0,&d) && d.rate>0 && !dw4_fieldgen_roll_drop(e,0,9999,&d));
        {   /* every draw 0..9999 exactly once: the original selects while the remainder is <= 0 (FUN_00384800, finding 3006), so a list drops on rate-sum + 1 draws */
            int drops=0,sum=0;for(unsigned k=0;k<e->ndrops[0];k++)sum+=e->drops[0][k].rate;
            for(uint32_t r=0;r<10000;r++)if(dw4_fieldgen_roll_drop(e,0,r,&d))drops++;
            assert(drops==sum+1);
        }
        dw4_fieldgen_close(g);
        printf("drop tables: stagGF01 enemy/box lists decode to the live-measured sums on all three difficulties\n");
        return 0;
    }
    if(!strcmp(mode,"fightstatus")) {
        /* P2E status times (cases 15-19 of the FIGHTCALC switch). Internal consistency only (NOT compared with retail): -1 when the chance draw fails,
         * duration = pcTech.TIME + KASHIKOSA/2 otherwise, the success rate grows with the skill and shrinks with the target's SEISHIN, determinism for a
         * fixed stream, and the no-draw strength/flat replies match their formulas. Enemy row 60, the Susanomon WAZALIST. */
        const int revisit[]={2,355,503};h=enter(&mount,revisit,3);
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
        const dw4_database *enemy=dw4_databases_get(dw4_hubruntime_databases(h),"enemy");
        dw4_database *tech=(dw4_database *)dw4_databases_get(dw4_hubruntime_databases(h),"pcTech");assert(p0 && enemy && tech);
        int32_t sk[9];for(int i=0;i<9;i++)sk[i]=9999;
        assert(!dw4_property_set_number(p0,"DIGIMONNO",15) && !dw4_property_set_number(p0,"LEVEL",999) &&
               !dw4_property_set_array(p0,"SKILL",sk,9) && !dw4_playerstats_recalculate((void *)dw4_hubruntime_databases(h),p0) && !dw4_property_set_number(p0,"KASHIKOSA",100));
        size_t nw=0;const dw4_item_record *wz=dw4_property_items(p0,"WAZALIST",&nw);assert(wz && nw);
        dw4_item_record list[64];if(nw>64)nw=64;memcpy(list,wz,nw*sizeof *list);
        dw4_random base=dw4_hubruntime_state(h)->random;
        int32_t sei,res,mamori,tsu,subs;
        assert(!dw4_database_number(enemy,60,"SEISHIN",&sei) && !dw4_database_number(enemy,60,"RES_POISON",&res) && !dw4_database_number(enemy,60,"MAMORI",&mamori) &&
               !dw4_database_number(enemy,60,"TSUYOSA",&tsu) && !dw4_database_number(enemy,60,"SUBAYASA",&subs) && sei>0);
        int timed_techs=0,seen_fail=0,seen_ok=0;
        for(size_t i=0;i<nw;i++){
            int32_t attack=40000+list[i].revision,ttime,thp,tskill;
            if(dw4_database_number(tech,list[i].record,"TIME",&ttime) || dw4_database_number(tech,list[i].record,"HP",&thp) || dw4_database_number(tech,list[i].record,"SKILL",&tskill) || tskill<0 || tskill>=9)continue;
            for(int kind=0;kind<4;kind++){   /* 0 poison, 1 sleep, 2 bind, 3 atkdwn, 4 powdwn */
                int32_t lowhits=0,highhits=0,v,first[16];
                for(int pass=0;pass<2;pass++){   /* skill 0, then skill 9999 */
                    sk[tskill]=pass?9999:0;assert(!dw4_property_set_array(p0,"SKILL",sk,9));
                    dw4_random rng=base,rng2=base;dw4_fight_ctx c={p0,dw4_database_typed(enemy),&rng,dw4_database_typed(tech)},c2={p0,dw4_database_typed(enemy),&rng2,dw4_database_typed(tech)};
                    for(unsigned n=0;n<3000;n++){
                        int32_t v2;int rc,rc2;
                        switch(kind){
                            case 0:rc=dw4_fight_p2e_poison_time(&c,60,attack,"TIME",&v);rc2=dw4_fight_p2e_poison_time(&c2,60,attack,"TIME",&v2);break;
                            case 1:rc=dw4_fight_p2e_sleep_time(&c,60,attack,&v);rc2=dw4_fight_p2e_sleep_time(&c2,60,attack,&v2);break;
                            case 2:rc=dw4_fight_p2e_bind_time(&c,60,attack,&v);rc2=dw4_fight_p2e_bind_time(&c2,60,attack,&v2);break;
                            default:rc=dw4_fight_p2e_atkdwn_time(&c,60,attack,"TIME",&v);rc2=dw4_fight_p2e_atkdwn_time(&c2,60,attack,"TIME",&v2);break;
                        }
                        assert(rc==0 && rc2==0 && v==v2);   /* deterministic for a fixed stream */
                        if(v==-1){seen_fail=1;}else{assert(v==(ttime+50?ttime+50:-1));seen_ok=1;if(pass)highhits++;else lowhits++;}
                        if(n<16)first[n]=v;
                    }
                }
                assert(highhits>=lowhits);   /* a higher skill never lowers the success count over the same stream */
                (void)first;
            }
            timed_techs++;
            /* no-draw replies */
            sk[tskill]=400;assert(!dw4_property_set_array(p0,"SKILL",sk,9));
            dw4_random rng=base;dw4_fight_ctx c={p0,dw4_database_typed(enemy),&rng,dw4_database_typed(tech)};int32_t v,t;
            assert(!dw4_fight_p2e_poison_time(&c,60,attack,"HP",&v) && v==-(thp/5));
            assert(!dw4_fight_p2e_atkdwn_time(&c,60,attack,"SUBAYASA",&v) && !dw4_database_number(tech,list[i].record,"SUBAYASA",&t));
            { int32_t want=t-400/20,floor_=-subs*80/100;if(want<floor_)want=floor_;assert(v==-want);}
            assert(!dw4_fight_p2e_powdwn_time(&c,60,attack,"TSUYOSA",&v) && !dw4_database_number(tech,list[i].record,"TSUYOSA",&t));
            { int32_t want=t-20,floor_=-tsu*80/100;if(want<floor_)want=floor_;assert(v==-want);}
            assert(!dw4_fight_p2e_powdwn_time(&c,60,attack,"MAMORI",&v) && !dw4_database_number(tech,list[i].record,"MAMORI",&t));
            { int32_t want=t-20,floor_=-mamori*80/100;if(want<floor_)want=floor_;assert(v==-want);}
            assert(!dw4_fight_p2e_atkdwn_time(&c,60,attack,"CHIMEIRITSU",&v) && !dw4_database_number(tech,list[i].record,"CHIMEIRITSU",&t) && v==-t);
            assert(!dw4_fight_p2e_atkdwn_time(&c,60,attack,"KAIHIRITSU",&v) && !dw4_database_number(tech,list[i].record,"KAIHIRITSU",&t) && v==-t);
            assert(!dw4_fight_p2e_atkdwn_time(&c,60,attack,"MAHIRITSU",&v) && !dw4_database_number(tech,list[i].record,"MHIRITSU",&t) && v==-t);
            v=12345;assert(dw4_fight_p2e_atkdwn_time(&c,60,attack,"NOPE",&v)==1 && dw4_fight_p2e_powdwn_time(&c,60,attack,"NOPE",&v)==1 && v==12345);
            assert(!memcmp(&rng,&base,sizeof rng));   /* none of these consumed a draw */
        }
        assert(timed_techs>0 && seen_fail && seen_ok);
        printf("P2E status times: %d techniques, formulas internally consistent (not retail-compared)\n",timed_techs);
        return 0;
    }
    if(!strcmp(mode,"retail")) {
        /* Retail oracle (measured live in PCSX2, stagGF03 boss row 60: HPMAX 3194, MAMORI 150; attacker with SKILL[WEAPONSKILLNO]=9999). Every
         * non-critical single-hit swing delta observed per TSUYOSA must lie inside the port's own distribution for the same record. Two-hit
         * swings (about 2x) and the critical one (about 2.7x) are excluded; they were counted, not matched. */
        static const struct {int32_t tsuyosa;int n;int32_t v[12];} retail[]={
            {9999,6,{695,664,653,647,682,658}},{5000,3,{453,454,443}},{2500,4,{380,350,358,369}},{1000,5,{301,303,307,320,305}},{400,5,{285,280,280,279,282}}};
        const int revisit[]={2,355,503};h=enter(&mount,revisit,3);
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
        const dw4_database *enemy=dw4_databases_get(dw4_hubruntime_databases(h),"enemy");assert(p0 && enemy);
        int32_t mamori,hp,skill_no;assert(!dw4_database_number(enemy,60,"MAMORI",&mamori) && !dw4_database_number(enemy,60,"HPMAX",&hp) && mamori==150 && hp==3194);
        assert(!dw4_property_number(p0,"WEAPONSKILLNO",&skill_no));
        size_t nskill=0;const int32_t *orig=dw4_property_array(p0,"SKILL",&nskill);assert(orig && nskill==9);int32_t saved[9];memcpy(saved,orig,sizeof saved);
        int32_t skill[9];for(int i=0;i<9;i++)skill[i]=9999;assert(!dw4_property_set_array(p0,"SKILL",skill,9));
        dw4_random rng=dw4_hubruntime_state(h)->random;dw4_fight_ctx ctx={p0,dw4_database_typed(enemy),&rng};
        for(unsigned k=0;k<sizeof retail/sizeof *retail;k++){
            assert(!dw4_property_set_number(p0,"TSUYOSA",retail[k].tsuyosa));
            int32_t lo=1<<30,hi=0;
            for(int i=0;i<4000;i++){dw4_fight_damage d;assert(!dw4_fight_p2e_damage(&ctx,60,0,0,(dw4_fight_down){0,0},&d));if(d.damage<lo)lo=d.damage;if(d.damage>hi)hi=d.damage;}
            fprintf(stderr,"TSUYOSA %d: port %d..%d, retail",retail[k].tsuyosa,lo,hi);
            for(int i=0;i<retail[k].n;i++){fprintf(stderr," %d",retail[k].v[i]);assert(retail[k].v[i]>=lo-6 && retail[k].v[i]<=hi+6);}
            fputc('\n',stderr);
        }
        /* Enemy to player (same boss, attack row TSUYOSA 160; the player's record DEFENCE written live): single-hit HP losses. The 1918 sample is a
         * critical (2x, attack CHIMEIRITSU 8 adds +94 %) and is checked against the doubled range. */
        {
            static const struct {int32_t mamori;int n;int32_t v[6];} hurt[]={{150,5,{3946,3618,3650,3704,3825}},{600,2,{949,951}}};
            const dw4_database *eneatk=dw4_databases_get(dw4_hubruntime_databases(h),"eneatk");assert(eneatk);
            dw4_fight_e2p_ctx ectx={p0,dw4_database_typed(enemy),dw4_database_typed(eneatk),&rng};
            for(unsigned k=0;k<sizeof hurt/sizeof *hurt;k++){
                int ok=0;
                for(int attack=0;attack<64 && !ok;attack++){
                    int32_t tsu=0,type=1;if(dw4_database_number(eneatk,attack,"TSUYOSA",&tsu) || dw4_database_number(eneatk,attack,"TYPE",&type) || type || tsu!=160)continue;
                    dw4_property_set_number(p0,"MAMORI",hurt[k].mamori);
                    int32_t lo=1<<30,hi=0;
                    for(int i=0;i<4000;i++){dw4_fight_damage d;if(dw4_fight_e2p_damage(&ectx,60,attack,(dw4_fight_e2p_down){0,0},&d))break;if(d.damage<lo)lo=d.damage;if(d.damage>hi && d.damage<lo*12/10)hi=d.damage;}
                    ok=1;for(int i=0;i<hurt[k].n;i++)if(hurt[k].v[i]<lo-6 || hurt[k].v[i]>hi+6)ok=0;
                    fprintf(stderr,"MAMORI %d attack %d: port %d..%d, retail",hurt[k].mamori,attack,lo,hi);for(int i=0;i<hurt[k].n;i++)fprintf(stderr," %d",hurt[k].v[i]);fprintf(stderr,"%s\n",ok?"  OK":"");
                }
                assert(ok);
            }
        }
        {   /* Hit chance (retail, boss row 60 SUBAYASA 388, SKILL 0): the boss's AI is gated to the swing (its _isOnCtrl byte at InfoWork+0x44 is 0 between swings;
             * while 0 the boss also ignores hits) and the player's MEICHURITSU m and SUBAYASA s are written live. A swing connects with two volumes of which the second rolls again after a miss
             * (a first hit leaves the boss briefly hit-protected), so P(swing damages) = control * (1 - (1 - q)^2) with q = m*(30*s + 6000)/388/10000 clamped to 1 and control the connect
             * rate with a guaranteed hit (125 of 150 swings at m=700 or s=3000). Each row must lie within 2.5 sigma of that expectation. */
            static const struct {int32_t m,s,n,hits;} meas[]={
                {700,1,110,88},{60,3000,40,37},{130,1,110,40},{257,1,110,61},{500,1,40,28},{60,1,80,14},{60,300,40,17},{1,1,40,0}};
            int32_t zero[9]={0};assert(!dw4_property_set_array(p0,"SKILL",zero,9));
            const double control=125.0/150.0;
            for(unsigned k=0;k<sizeof meas/sizeof *meas;k++){
                assert(!dw4_property_set_number(p0,"MEICHURITSU",meas[k].m) && !dw4_property_set_number(p0,"SUBAYASA",meas[k].s));
                unsigned hit_n=0,total=20000;for(unsigned i=0;i<total;i++){int hit=0;assert(!dw4_fight_p2e_is_hit(&ctx,60,0,(dw4_fight_down){0,0},&hit));hit_n+=hit;}
                double q=(double)hit_n/total,two=1-(1-q)*(1-q),p=control*two,exp=meas[k].n*p,sd=sqrt(meas[k].n*p*(1-p));
                fprintf(stderr,"hit chance m=%d sub=%d: port q %.3f, two rolls %.3f, expected %.1f +/- %.1f of %d, retail %d\n",meas[k].m,meas[k].s,q,two,exp,sd,meas[k].n,meas[k].hits);
                if(k>0)assert(fabs(meas[k].hits-exp)<=2.5*sd+0.5);
            }
        }
        {   /* Critical rate (retail, same gated-AI setup, MEICHURITSU 700 and SUBAYASA 3000 so every swing connects, SKILL 0): per hit, classified from the HP lost (one hit 400,
             * critical 494..528 = +30 % at SKILL 0, two hits about 800, critical plus normal about 900). CHIMEIRITSU c gives P(critical) = c/200. */
            static const struct {int32_t chi,hits,crits;} crit[]={{20,60,6},{60,52,17},{120,47,32}};
            int32_t zero[9]={0};assert(!dw4_property_set_array(p0,"SKILL",zero,9));
            for(unsigned k=0;k<3;k++){
                assert(!dw4_property_set_number(p0,"CHIMEIRITSU",crit[k].chi));
                unsigned n=0,total=20000;for(unsigned i=0;i<total;i++){int c2=0;assert(!dw4_fight_p2e_is_critical(&ctx,60,0,&c2));n+=c2;}
                double rate=(double)n/total,exp=crit[k].hits*rate,sd=sqrt(crit[k].hits*rate*(1-rate));
                fprintf(stderr,"critical rate chimeiritsu %d: port %.3f, expected %.1f +/- %.1f of %d hits, retail %d\n",crit[k].chi,rate,exp,sd,crit[k].hits,crit[k].crits);
                assert(fabs(crit[k].crits-exp)<=2.5*sd);
            }
            assert(!dw4_property_set_number(p0,"CHIMEIRITSU",2));
        }
        {   /* Critical multiplier at mid skill values (retail: every swing critical, boss row 60, TSUYOSA 9999): mean critical / base damage over single-hit swings
             * (38, 40, 40 and 38 swings; min..max 1.62..1.78, 1.80..1.98, 2.00..2.20, 2.28..2.51) against the port's mean critical / mean normal damage. */
            static const struct {int32_t skill;double ratio;} cm[]={{800,1.709},{1500,1.883},{3000,2.096},{6000,2.385}};
            int32_t arr[9]={0};assert(!dw4_property_set_number(p0,"WEAPONSKILLNO",1) && !dw4_property_set_number(p0,"TSUYOSA",9999));
            for(unsigned k=0;k<4;k++){
                arr[1]=cm[k].skill;assert(!dw4_property_set_array(p0,"SKILL",arr,9));
                double a=0,b=0;unsigned n=4000;
                for(unsigned i=0;i<n;i++){dw4_fight_damage d0,d1;assert(!dw4_fight_p2e_damage(&ctx,60,0,0,(dw4_fight_down){0,0},&d0) && !dw4_fight_p2e_damage(&ctx,60,0,1,(dw4_fight_down){0,0},&d1));a+=d0.damage;b+=d1.damage;}
                fprintf(stderr,"critical multiplier skill %d: port %.3f, retail %.3f\n",cm[k].skill,b/a,cm[k].ratio);
                assert(fabs(b/a-cm[k].ratio)<0.02*cm[k].ratio);
            }
        }
        {   /* Technique damage (retail, boss row 60: SEISHIN 241, RES_FIRE 650; the Susanomon's WAZALIST with SKILL 9999 and KASHIKOSA 9999; casts from the R1 technique list):
             * single-hit casts of Fire (pcTech row 4, element fire: (5*S + 20*800 + 10*K)/SEISHIN scaled by (1000 - 650)/1000, 228..251 in 15 casts) and of Impact (row 29, no element:
             * 696..740 in 7 casts) must lie inside the port's distribution (+-4). */
            static const int32_t fire[]={228,238,239,233,244,237,228,251,251,233,240,231,235,247,250,230},impact[]={722,696,722,740,737,733,731};
            dw4_database *tech=(dw4_database *)dw4_databases_get(dw4_hubruntime_databases(h),"pcTech");
            int32_t sk9[9];for(int i=0;i<9;i++)sk9[i]=9999;
            assert(tech && !dw4_property_set_number(p0,"DIGIMONNO",15) && !dw4_property_set_number(p0,"LEVEL",999) && !dw4_property_set_array(p0,"SKILL",sk9,9) && !dw4_playerstats_recalculate((void *)dw4_hubruntime_databases(h),p0) && !dw4_property_set_number(p0,"KASHIKOSA",9999));
            size_t nw=0;const dw4_item_record *wz=dw4_property_items(p0,"WAZALIST",&nw);int fb=-1,ib=-1;
            for(size_t i=0;i<nw;i++){if(wz[i].record==4)fb=wz[i].revision;if(wz[i].record==29)ib=wz[i].revision;}
            assert(fb>=0 && ib>=0);
            dw4_fight_ctx tctx={p0,dw4_database_typed(enemy),&rng,dw4_database_typed(tech)};
            for(int which=0;which<2;which++){
                int lo=1<<30,hi=0;for(unsigned i=0;i<4000;i++){dw4_fight_damage d;assert(!dw4_fight_p2e_damage(&tctx,60,40000+(which?ib:fb),0,(dw4_fight_down){0,0},&d));if(d.damage<lo)lo=d.damage;if(d.damage>hi)hi=d.damage;}
                const int32_t *v=which?impact:fire;size_t nv=which?sizeof impact/sizeof *impact:sizeof fire/sizeof *fire;
                fprintf(stderr,"technique %s: port %d..%d, retail",which?"Impact":"Fire",lo,hi);
                for(size_t i=0;i<nv;i++){fprintf(stderr," %d",v[i]);assert(v[i]>=lo-4 && v[i]<=hi+4);}fputc(10,stderr);
            }
            {   /* Heal Lt (retail: casts from the R1 list on the player, HP set to 1000 first; the HP gained was the same in all 8 casts at SKILL[7] 9999 / KASHIKOSA 9999): row 44 HP 19200 + SKILL[7] + KASHIKOSA. */
                static const struct {int32_t skill,kash,gain;} heal[]={{9999,9999,39198},{1234,567,21001},{0,100,19300},{5000,9999,34199}};
                for(unsigned k=0;k<4;k++){
                    int32_t arr[9];for(int q=0;q<9;q++)arr[q]=9999;arr[7]=heal[k].skill;dw4_magic mg;
                    assert(!dw4_property_set_array(p0,"SKILL",arr,9) && !dw4_property_set_number(p0,"KASHIKOSA",heal[k].kash) && !dw4_fight_p2p_magic(&tctx,0,0,40040,&mg) && mg.kind==DW4_MAGIC_HEAL);
                    fprintf(stderr,"Heal Lt skill %d kashikosa %d: port %d, retail %d\n",heal[k].skill,heal[k].kash,mg.v[0],heal[k].gain);assert(mg.v[0]==heal[k].gain);
                }
                int32_t sk9b[9];for(int q=0;q<9;q++)sk9b[q]=9999;assert(!dw4_property_set_array(p0,"SKILL",sk9b,9) && !dw4_property_set_number(p0,"KASHIKOSA",9999));
            }
            {   /* Technique skill growth (retail, Fire casts at LEVEL 999: raises of SKILL[6] per hit; chance = table[level group][band][normal] * 100 per 100000). */
                static const struct {int32_t skill,hits,ups;} tg[]={{5000,77,5},{9000,77,10}};
                dw4_random sr2=dw4_hubruntime_state(h)->random;
                for(unsigned k=0;k<2;k++){
                    unsigned n=0,total=4000;
                    for(unsigned i=0;i<total;i++){
                        int32_t arr[9];for(int q=0;q<9;q++)arr[q]=9999;arr[6]=tg[k].skill;
                        assert(!dw4_property_set_number(p0,"LEVEL",999) && !dw4_property_set_array(p0,"SKILL",arr,9) && !dw4_property_set_number(p0,"DIGIMONNO",15));
                        int32_t raised;int rc=dw4_fight_p2e_skillup(dw4_hubruntime_records(h),dw4_hubruntime_databases(h),&sr2,0,40000+fb,0,&raised);assert(rc>=0);n+=rc>0 && raised==6;
                    }
                    double rate=(double)n/total,exp=tg[k].hits*rate,sd=sqrt(tg[k].hits*rate*(1-rate));
                    fprintf(stderr,"technique skill growth skill %d: port %.3f per hit, expected %.1f +/- %.1f of %d hits, retail %d\n",tg[k].skill,rate,exp,sd,tg[k].hits,tg[k].ups);
                    assert(fabs(tg[k].ups-exp)<=2.5*sd+0.5);
                }
            }
            assert(!dw4_property_set_number(p0,"DIGIMONNO",3) && !dw4_property_set_number(p0,"LEVEL",1));
        }
        {   /* Skill growth (retail, same gated-boss setup: LEVEL and SKILL[1] written, every swing connects; P2ESKILLUP per hit). Weapon skill 1 = SLASH, growth column 100 for
             * Susanomon and for the port's Dorumon. hits counted from the HP lost (one hit ~ (6T+4S)/150, two ~ double, critical +S/20+30 %), skill-ups from the skill read back after the swing. */
            static const struct {int32_t idx,level,skill,crit,hits,ups;} su[]={{1,36,500,0,75,13},{1,36,500,1,56,7},{1,999,5000,0,77,5},{1,36,1100,0,76,0},
                {0,36,500,0,77,19},{3,36,500,0,74,11},{5,36,500,0,74,17}};   /* the retail player is a Susanomon: shinka row 15, growth 130 for BLUNT (idx 0) and 100 for the others */
            int32_t zero[9]={0};assert(!dw4_property_set_array(p0,"SKILL",zero,9) && !dw4_property_set_number(p0,"DIGIMONNO",15));
            dw4_random sr=dw4_hubruntime_state(h)->random;
            for(unsigned k=0;k<sizeof su/sizeof *su;k++){
                unsigned n=0,total=4000;
                for(unsigned i=0;i<total;i++){
                    int32_t arr[9]={0};arr[su[k].idx]=su[k].skill;assert(!dw4_property_set_number(p0,"LEVEL",su[k].level) && !dw4_property_set_array(p0,"SKILL",arr,9) && !dw4_property_set_number(p0,"WEAPONSKILLNO",su[k].idx) && !dw4_property_set_number(p0,"DIGIMONNO",15));   /* a skill-up recalculates WEAPONSKILLNO from the equipped weapon */
                    int32_t raised;int rc=dw4_fight_p2e_skillup(dw4_hubruntime_records(h),dw4_hubruntime_databases(h),&sr,0,0,su[k].crit,&raised);assert(rc>=0);n+=rc>0;
                }
                double rate=(double)n/total,exp=su[k].hits*rate,sd=sqrt(su[k].hits*rate*(1-rate));
                fprintf(stderr,"skill growth skill %d level %d value %d %s: port %.3f per hit, expected %.1f +/- %.1f of %d hits, retail %d\n",su[k].idx,su[k].level,su[k].skill,su[k].crit?"critical":"normal",rate,exp,sd,su[k].hits,su[k].ups);
                assert(fabs(su[k].ups-exp)<=2.5*sd+0.5);
            }
            assert(!dw4_property_set_number(p0,"DIGIMONNO",3));
            assert(dw4_fight_skillup_cap(36)==1080 && dw4_fight_skillup_cap(37)==1100 && dw4_fight_skillup_cap(999)==9876);
            assert(!dw4_property_set_number(p0,"LEVEL",1) && !dw4_property_set_number(p0,"WEAPONSKILLNO",3));
        }
        assert(!dw4_property_set_array(p0,"SKILL",saved,9) && !dw4_playerstats_recalculate((void *)dw4_hubruntime_databases(h),p0));   /* back to the created level-1 record */
        assert(!dw4_property_set_array(p0,"SKILL",saved,9) && !dw4_property_set_number(p0,"TSUYOSA",94) && !dw4_property_set_number(p0,"MAMORI",110) && !dw4_property_set_number(p0,"SUBAYASA",60) && !dw4_property_set_number(p0,"MEICHURITSU",80));
        {   /* Level-1 created starters against retail records (PCSX2, fresh-save state before finishing the practice stage: Girumon; the Goblin Pass level-1 state: Dorumon). */
            char err[256];
            assert(!dw4_playerrecords_create(dw4_hubruntime_records(h),dw4_hubruntime_databases(h),1,"p_girumon","Retail",err,sizeof err));
            static const struct {int slot;const char *k;int32_t v;} want[]={
                {1,"MHP",150},{1,"MMP",80},{1,"TSUYOSA",77},{1,"MAMORI",120},{1,"KASHIKOSA",75},{1,"SEISHIN",70},{1,"SUBAYASA",65},{1,"MEICHURITSU",88},{1,"CHIMEIRITSU",2},
                {1,"WEAPONSKILLNO",2},{1,"WEAPONRECNO",268},{1,"ATTACKDELAY",22},{1,"MAHIRITSU",2},{1,"KAIHIRITSU",1},{1,"BOUGYORITSU",0},
                {0,"MHP",170},{0,"MMP",60},{0,"TSUYOSA",94},{0,"MAMORI",110},{0,"KASHIKOSA",65},{0,"SEISHIN",75},{0,"SUBAYASA",60},{0,"MEICHURITSU",80},{0,"CHIMEIRITSU",2},{0,"WEAPONSKILLNO",3},{0,"ATTACKDELAY",26}};
            for(unsigned i=0;i<sizeof want/sizeof *want;i++){int32_t v=-99;dw4_property_number(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",want[i].slot),want[i].k,&v);
                if(v!=want[i].v)fprintf(stderr,"starter slot %d %s: port %d retail %d\n",want[i].slot,want[i].k,v,want[i].v);assert(v==want[i].v);}
            fprintf(stderr,"level-1 Girumon and Dorumon starter records match the retail records field for field\n");
            assert(!dw4_property_set_number(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0),"NINZU",1));   /* the extra record raised the player count: back to one player */
            assert(!dw4_property_set_number(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",1),"ISUSE",0));
        }
        /* EXP: a level-1 Dorumon (1 player) killing the Goblin Pass crown goblin (row 388, table EXP 133) gained 170 -> 303 = +133 in retail. */
        {
            dw4_property_folder *c0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0);
            int32_t level=0,hp0=0,players=0;
            assert(!dw4_property_set_number(p0,"LEVEL",1) && !dw4_property_number(p0,"HP",&hp0) && hp0>0);
            assert(!dw4_property_number(c0,"NINZU",&players) && players==1);
            int32_t share=0;int rc=dw4_fight_p2e_expup(dw4_hubruntime_records(h),dw4_hubruntime_databases(h),388,0,&share);
            (void)level;fprintf(stderr,"EXP row 388: port share %d (rc %d), retail +133\n",share,rc);
            assert(share==133);
            /* Level-up, measured on the same retail kill with EXP set to NEXTEXP-1 (340): LEVEL 2, NEXTEXP 968, MHP 170->181, MMP 60->70, TSUYOSA 94->105,
             * MAMORI 110->119, SUBAYASA 60->69, KASHIKOSA 65->75, SEISHIN 75->87; HP/MP refilled. */
            int32_t v;assert(!dw4_property_number(p0,"NEXTEXP",&v) && v==341 && !dw4_property_set_number(p0,"EXP",340) && !dw4_property_set_number(p0,"HP",5));
            {int rc2=dw4_fight_p2e_expup(dw4_hubruntime_records(h),dw4_hubruntime_databases(h),388,0,&share);fprintf(stderr,"levelup rc %d share %d\n",rc2,share);assert(!rc2 && share==133);}
            static const struct {const char *k;int32_t want;} lv[]={{"LEVEL",2},{"NEXTEXP",968},{"MHP",181},{"HP",181},{"MMP",70},{"MP",70},{"TSUYOSA",105},{"MAMORI",119},{"SUBAYASA",69},{"KASHIKOSA",75},{"SEISHIN",87},{"EXP",473}};
            for(unsigned i=0;i<sizeof lv/sizeof *lv;i++){assert(!dw4_property_number(p0,lv[i].k,&v));if(v!=lv[i].want)fprintf(stderr,"level-up %s: port %d retail %d\n",lv[i].k,v,lv[i].want);assert(v==lv[i].want);}
            fprintf(stderr,"level-up 1 -> 2 matches the retail record\n");
        }
        printf("P2E and E2P damage: retail swings and boss hits (row 60) fall inside the port's distributions\n");
        return 0;
    }
    if(!strcmp(mode,"fightstatus_e2p")) {
        /* Internal consistency of the E2P status rules (cases 7-12): bounds, -1/0 for resisted, determinism, stat monotonicity. No retail oracle. */
        const int revisit[]={2,355,503};h=enter(&mount,revisit,3);
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
        const dw4_database *enemy=dw4_databases_get(dw4_hubruntime_databases(h),"enemy");
        const dw4_database *eneatk=dw4_databases_get(dw4_hubruntime_databases(h),"eneatk");assert(p0 && enemy && eneatk);
        static const char *const kinds[]={"doku","sleep","ashidome","freeze","powerdown"};
        int found[5]={-1,-1,-1,-1,-1},type_of[5]={0};
        for(int a=0;a<2000;a++){const char *k=dw4_database_string(eneatk,a,"KOUKA");if(!k)continue;
            for(int i=0;i<5;i++)if(!strcmp(k,kinds[i]) && found[i]<0){found[i]=a;dw4_database_number(eneatk,a,"TYPE",&type_of[i]);}}
        fprintf(stderr,"eneatk rows by KOUKA: doku %d sleep %d ashidome %d freeze %d powerdown %d\n",found[0],found[1],found[2],found[3],found[4]);
        for(int i=0;i<5;i++)assert(found[i]>=0);
        dw4_random rng=dw4_hubruntime_state(h)->random;
        dw4_fight_e2p_ctx c={p0,dw4_database_typed(enemy),dw4_database_typed(eneatk),&rng};
        const int row=60,none=0;   /* an attack row without KOUKA: every TIME rule answers 0 and draws nothing */
        int noeffect=-1;for(int a=0;a<2000;a++){const char *k=dw4_database_string(eneatk,a,"KOUKA");if(k && (!*k || !strcmp(k,"none"))){noeffect=a;break;}}
        assert(noeffect>=0);(void)none;
        int32_t v;dw4_random before=rng;
        assert(!dw4_fight_e2p_status_poison(&c,"TIME",noeffect,&v) && v==0);
        assert(!dw4_fight_e2p_status_sleep(&c,row,noeffect,&v) && v==0);
        assert(!dw4_fight_e2p_status_bind(&c,row,noeffect,&v) && v==0);
        assert(memcmp(&before,&rng,sizeof rng)==0);
        assert(dw4_fight_e2p_status_poison(&c,"BOGUS",found[0],&v)==1);
        /* Poison: three message paths. */
        int32_t mhp,rank,gedoku;assert(!dw4_property_number(p0,"MHP",&mhp) && !dw4_database_number(eneatk,found[0],"KOUKARANK",&rank));
        assert(!dw4_fight_e2p_status_poison(&c,"DAMAGE",found[0],&v) && v==mhp*rank/100);
        assert(!dw4_database_number(eneatk,found[0],"GEDOKU",&gedoku) && !dw4_fight_e2p_status_poison(&c,"GEDOKU",found[0],&v) && v==gedoku);
        /* Monotonicity: with identical draw streams a higher resistance can only add successes. */
        int32_t base_res,time=0;assert(!dw4_property_number(p0,"DOKUTEIKOU",&base_res) && !dw4_database_number(eneatk,found[0],"KOUKATIME",&time));
        int prev=-1;
        for(int res=0;res<=300;res+=50){
            assert(!dw4_property_set_number(p0,"DOKUTEIKOU",res));rng=before;int n=0;
            for(int i=0;i<2000;i++){assert(!dw4_fight_e2p_status_poison(&c,"TIME",found[0],&v));assert(v==0 || v==-1 || v>=res/2+time-0);
                if(v>0){n++;assert(v==res/2+time);}}
            assert(n>=prev);prev=n;
            dw4_random again=before;rng=again;int32_t a1,a2;
            assert(!dw4_fight_e2p_status_poison(&c,"TIME",found[0],&a1));rng=again;assert(!dw4_fight_e2p_status_poison(&c,"TIME",found[0],&a2) && a1==a2);
        }
        assert(prev>0);dw4_property_set_number(p0,"DOKUTEIKOU",base_res);
        /* Sleep / bind / freeze / powerdown: duration = KOUKATIME * s0 / 100, rising SEISHIN (the resisting stat) never adds successes. */
        for(int which=1;which<5;which++){
            int a=found[which];int32_t base_seishin,ktime;assert(!dw4_property_number(p0,"SEISHIN",&base_seishin) && !dw4_database_number(eneatk,a,"KOUKATIME",&ktime));
            int last=1<<30;
            for(int seishin=20;seishin<=800;seishin*=2){
                assert(!dw4_property_set_number(p0,"SEISHIN",seishin));rng=before;int n=0;
                for(int i=0;i<3000;i++){
                    dw4_fight_status_ctx s={&c,NULL,NULL};
                    int rc=which==1?dw4_fight_e2p_status_sleep(&c,row,a,&v):which==2?dw4_fight_e2p_status_bind(&c,row,a,&v):
                           which==3?dw4_fight_e2p_status_atkdown(&s,"TIME",row,a,&v):dw4_fight_e2p_status_powdown(&s,"TIME",row,a,&v);
                    assert(rc==0 && v>=-1);if(v>0)n++;
                }
                if(which!=2 || type_of[2]!=2)assert(n<=last);   /* a TYPE 2 bind has no roll */
                last=n;
            }
            assert(!dw4_property_set_number(p0,"SEISHIN",base_seishin));
        }
        /* Stun: the resist stat only raises the chance and length; a TYPE 0 hit needs damage rank 1 or 2. */
        {
            int a0=-1;for(int a=0;a<2000;a++){int32_t t;if(!dw4_database_number(eneatk,a,"TYPE",&t) && t==0){a0=a;break;}}
            assert(a0>=0);
            rng=before;assert(!dw4_fight_e2p_status_stun(&c,row,a0,100,0,0,&v) && v==0 && memcmp(&before,&rng,sizeof rng)==0);
            int32_t save;assert(!dw4_property_number(p0,"MAHITEIKOU",&save));int last=-1;
            for(int res=0;res<=200;res+=40){
                assert(!dw4_property_set_number(p0,"MAHITEIKOU",res));rng=before;int n=0;
                for(int i=0;i<3000;i++){assert(!dw4_fight_e2p_status_stun(&c,row,a0,mhp/3,1,0,&v) && v>=-1);if(v>0)n++;}
                assert(n>=last);last=n;
            }
            assert(!dw4_property_set_number(p0,"MAHITEIKOU",save));
        }
        /* Attack/power-down property modes: the stat is scaled to 20..80 % and DOWNDATA is written before the property is read. */
        {
            struct downlog log={0,-1,0};
            dw4_fight_status_ctx s={&c,down_apply,&log};
            static const char *const m11[]={"SUBAYASA","MEICHURITSU"},*const m12[]={"TSUYOSA","MAMORI"};
            for(int k=0;k<2;k++){
                int32_t prop;
                assert(!dw4_property_number(p0,m11[k],&prop) && !dw4_fight_e2p_status_atkdown(&s,m11[k],row,found[3],&v) && v>=prop*20/100 && v<=prop*80/100);
                assert(log.slot==k && log.value==0);
                assert(!dw4_property_number(p0,m12[k],&prop) && !dw4_fight_e2p_status_powdown(&s,m12[k],row,found[4],&v) && v>=prop*20/100 && v<=prop*80/100);
                assert(log.slot==4+k && log.value==0);
            }
            assert(log.calls==4);
            assert(dw4_fight_e2p_status_atkdown(&s,"BOGUS",row,found[3],&v)==1 && log.calls==4);
        }
        dw4_hubruntime_close(h);
        printf("fightstatus_e2p: stun/poison/sleep/bind/attack-down/power-down rules consistent (bounds, determinism, monotonic in the resisting stat)\n");
        return 0;
    }
    if(!strcmp(mode,"damage")) {
        /* P2E rules over the starter's real record and the Goblin Pass e_goburi row (0). Bounds from the formulas: the spread keeps a
         * hit within 0.95..1.025 x base (+ crit bonus), the Goblin dies to a handful of Dorumon hits (HP 50). */
        const int revisit[]={2,355,503};
        h=enter(&mount,revisit,3);
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
        const dw4_database *enemy=dw4_databases_get(dw4_hubruntime_databases(h),"enemy");assert(p0 && enemy);
        int32_t tsuyosa,skill_no,mamori,hp;size_t ns;
        assert(!dw4_property_number(p0,"TSUYOSA",&tsuyosa) && !dw4_property_number(p0,"WEAPONSKILLNO",&skill_no));
        const int32_t *skill=dw4_property_array(p0,"SKILL",&ns);assert(skill && (size_t)skill_no<ns);
        assert(!dw4_database_number(enemy,0,"MAMORI",&mamori) && !dw4_database_number(enemy,0,"HPMAX",&hp) && hp==50 && mamori>0);
        dw4_random rng=dw4_hubruntime_state(h)->random;
        dw4_fight_ctx ctx={p0,dw4_database_typed(enemy),&rng};dw4_fight_down none={0,0};
        int32_t base=(tsuyosa*6+skill[skill_no]*4)/mamori;
        int hits=0,crits=0,highs=0;int32_t lo=1<<30,hi=0;
        for(int i=0;i<2000;i++){
            int hit,crit;dw4_fight_damage d;
            assert(!dw4_fight_p2e_is_hit(&ctx,0,0,none,&hit) && !dw4_fight_p2e_is_critical(&ctx,0,0,&crit));
            assert(!dw4_fight_p2e_damage(&ctx,0,0,crit,none,&d));
            hits+=hit;crits+=crit;highs+=d.high_roll;
            if(!crit){if(d.damage<lo)lo=d.damage;if(d.damage>hi)hi=d.damage;}
        }
        fprintf(stderr,"tsuyosa %d skill %d mamori %d base %d: hits %d/2000 crits %d highs %d noncrit damage %d..%d\n",tsuyosa,skill[skill_no],mamori,base,hits,crits,highs,lo,hi);
        assert(base>0 && lo>=base*95/100-1 && hi<=base*1025/1000+2);   /* spread bounds of the matched formula */
        assert(highs>300 && highs<700);                                 /* one roll in four */
        dw4_hubruntime_close(h);
        printf("field stage stag0101 damage: P2E hit/critical/damage rules run on the starter record and the Goblin row\n");
        return 0;
    }
    if(!strcmp(mode,"e2pboss")) {
        /* Enemy-to-player damage of Mammothmon (enemy row 97) against the retail reads of 2026-11-01 (docs/dungeon-floors.md "Second retail pass", #2984):
         * a player with MAMORI 100, SUBAYASA 1, KAIHIRITSU 0, BOUGYORITSU 0 took body contact (hit boxes 70000 = eneatk row 0) 177-196 with criticals 339-386, the charge
         * (70016 = eneatk row 16) 284-309 with a first critical of 568, and SQ_FIRE (70015 = eneatk row 15) as 0 damage with guard flinches; with SUBAYASA 9999 no hit
         * landed in the sample. The expectation is derived below from the recovered formula (beNDMWGameRam::vfunc_34 FIGHTCALC cases 0 and 3) and the tables, then the
         * port's rules, reached through combat.c's dw4_model_fight table (the hit script's BLPisHitCheck / BLPgetDamageValue seam), are sampled against it and against retail. */
        const int revisit[]={2,355,503};h=enter(&mount,revisit,3);
        dw4_property_folder *p0=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
        const dw4_database *enemy=dw4_databases_get(dw4_hubruntime_databases(h),"enemy"),*eneatk=dw4_databases_get(dw4_hubruntime_databases(h),"eneatk");assert(p0 && enemy && eneatk);
        dw4_model_fight f;dw4_combat_fight(dw4_hubruntime_combat_owner(h),&f);assert(f.e2p_is_hit && f.e2p_damage && f.e2p_rank);
        const int32_t boss=97;
        int32_t e_tsu,e_sub,e_crit;
        assert(!dw4_database_number(enemy,boss,"TSUYOSA",&e_tsu) && !dw4_database_number(enemy,boss,"SUBAYASA",&e_sub) && !dw4_database_number(enemy,boss,"CHIMEIRITSU",&e_crit));
        assert(e_tsu==187);   /* the retail read of the boss's TSUYOSA */
        assert(!dw4_property_set_number(p0,"MAMORI",100) && !dw4_property_set_number(p0,"SUBAYASA",1) && !dw4_property_set_number(p0,"KAIHIRITSU",0) &&
               !dw4_property_set_number(p0,"BOUGYORITSU",0) && !dw4_property_set_number(p0,"HP",99999) && !dw4_property_set_number(p0,"MHP",99999));
        /* The retail ranges (the lowest and highest of 58 contact hits, the charge samples and the critical samples). */
        static const struct {int32_t kind,row;int32_t plain_lo,plain_hi,crit_lo,crit_hi;} retail[]={
            {70000,0,177,196,339,386},   /* body contact; one further 542/543 sample is two merged hits */
            {70016,16,284,309,568,568},  /* the charge; the first hit of the intro (568) was a critical */
        };
        for(unsigned k=0;k<sizeof retail/sizeof *retail;k++){
            const int32_t kind=retail[k].kind,row=retail[k].row;
            int32_t type,a_tsu,a_crit,a_hit;
            assert(!dw4_database_number(eneatk,row,"TYPE",&type) && !dw4_database_number(eneatk,row,"TSUYOSA",&a_tsu) &&
                   !dw4_database_number(eneatk,row,"CHIMEIRITSU",&a_crit) && !dw4_database_number(eneatk,row,"MEICHURITSU",&a_hit));
            const char *z=dw4_database_string(eneatk,row,"ZOKUSEI");assert(type==0 && z && !strcmp(z,"none"));   /* physical, no element: no resistance draw */
            /* Expectation from the recovered formula: base = enemy.TSUYOSA * eneatk.TSUYOSA / MAMORI; a critical adds base*(eneatk.CHIMEIRITSU/2+90)/100 before the spread; the spread
             * keeps (r + base*scale)/1000 with scale 950/975/1000/1025 and r in [0, 25*base). */
            const int32_t base=e_tsu*a_tsu/100,cbase=base+base*(a_crit/2+90)/100;
            const int32_t plo=base*950/1000,phi=(base*25-1+base*1025)/1000,clo=cbase*950/1000,chi=(cbase*25-1+cbase*1025)/1000;
            const int crit_permille=(10000-(100-e_crit)*(100-a_crit))/10;   /* P(critical) = (10000 - (100-c)(100-a)) / 10000 */
            int32_t nlo=1<<30,nhi=0,clo_seen=1<<30,chi_seen=0;int ncrit=0,hits=0;const int N=200000;
            for(int i=0;i<N;i++){
                int hit=0;int32_t out[3];
                assert(!f.e2p_is_hit(f.user,0,boss,kind,&hit));hits+=hit;
                assert(!f.e2p_damage(f.user,0,boss,kind,NULL,out) && out[1]==-1);
                if(out[0]>=clo && out[0]<=chi){ncrit++;if(out[0]<clo_seen)clo_seen=out[0];if(out[0]>chi_seen)chi_seen=out[0];}
                else{assert(out[0]>=plo && out[0]<=phi);if(out[0]<nlo)nlo=out[0];if(out[0]>nhi)nhi=out[0];}
            }
            const int32_t p_hit=a_hit*e_sub/(1*(0+100)/100);   /* hit iff r2 < eneatk.MEICHURITSU * enemy.SUBAYASA / (SUBAYASA * (KAIHIRITSU + 100) / 100) */
            fprintf(stderr,"e2pboss kind %d (eneatk %d TSUYOSA %d CHIMEIRITSU %d): base %d; formula plain %d..%d crit %d..%d; port plain %d..%d crit %d..%d (%d of %d crits, formula %d/1000); retail plain %d..%d crit %d..%d; hits %d/%d\n",
                    kind,row,a_tsu,a_crit,base,plo,phi,clo,chi,nlo,nhi,clo_seen,chi_seen,ncrit,N,crit_permille,retail[k].plain_lo,retail[k].plain_hi,retail[k].crit_lo,retail[k].crit_hi,hits,N);
            assert(p_hit>=100 && hits==N);   /* SUBAYASA 1: the hit chance is at least 100 %, every contact lands */
            /* the port's extremes are the formula's (the draws reach both ends of each range) */
            assert(nlo>=plo && nlo<=plo+1 && nhi<=phi && nhi>=phi-1 && clo_seen>=clo && clo_seen<=clo+2 && chi_seen<=chi && chi_seen>=chi-3);
            /* critical frequency within 5 sigma of the formula */
            {double p=crit_permille/1000.0,sd=sqrt(N*p*(1-p));assert(fabs(ncrit-N*p)<5*sd);}
            /* The plain samples: every retail one lies inside the port's range and the retail extremes sit at its ends (58 contact hits; the charge's top 309 is 4 below the 313 the
             * rounding can reach, a sample of a few hits). */
            assert(retail[k].plain_lo>=plo && retail[k].plain_hi<=phi && retail[k].plain_lo-plo<=1);
            assert(kind==70000?phi-retail[k].plain_hi<=1:phi-retail[k].plain_hi<=6);
            /* The critical samples: the low ones fit the formula; the contact row's retail maximum 386 is ABOVE the formula's 372 (a x1.9 critical of the largest plain hit, 355 x 1.05), and
             * the retail critical rate was about 1 in 5 against the formula's 8 % (58 hits only). Open (#3020): reported, bounded by "about 2x" (<= 2 x base x 1.05), not asserted equal. */
            assert(retail[k].crit_lo>=clo && retail[k].crit_hi<=base*2*105/100);
            if(retail[k].crit_hi>chi)fprintf(stderr,"  OPEN #3020: retail critical maximum %d exceeds the formula's %d (critical factor %d%%)\n",retail[k].crit_hi,chi,100+(a_crit/2+90));
        }
        /* The critical factor 1 + (eneatk.CHIMEIRITSU/2+90)/100: 1.90 for the contact row 0 and 1.92 for the charge row 16 (the task's "about 2x"). */
        {int32_t c0,c16;assert(!dw4_database_number(eneatk,0,"CHIMEIRITSU",&c0) && !dw4_database_number(eneatk,16,"CHIMEIRITSU",&c16));
         assert(c0/2+90==90 && c16/2+90==92);}
        /* SQ_FIRE (kind 70015, eneatk row 15): a TYPE 1 magic attack (always hits, damage = enemy.KASHIKOSA * eneatk.TSUYOSA / SEISHIN, element ice scaled by the player's KOORITEIKO).
         * A hit script that finds damage 0 plays SQ_GUARDR; retail showed 0 damage twice per FIRE. With the maximum SEISHIN the base is 1, which any ice resistance scales to 0. */
        {   int32_t type,a_tsu,e_kas;
            assert(!dw4_database_number(eneatk,15,"TYPE",&type) && type==1 && !dw4_database_number(eneatk,15,"TSUYOSA",&a_tsu) && !dw4_database_number(enemy,boss,"KASHIKOSA",&e_kas));
            const char *z=dw4_database_string(eneatk,15,"ZOKUSEI");assert(z && !strcmp(z,"ice"));
            fprintf(stderr,"e2pboss kind 70015 (eneatk 15 TYPE 1 TSUYOSA %d, enemy KASHIKOSA %d): base %d / SEISHIN\n",a_tsu,e_kas,e_kas*a_tsu);
            for(int pass=0;pass<2;pass++){
                const int32_t seishin=pass?9999:2000,resist=pass?100:0;
                assert(!dw4_property_set_number(p0,"SEISHIN",seishin) && !dw4_property_set_number(p0,"KOORITEIKO",resist));
                int zero=0,nonzero=0;int32_t top=0;const int N=20000;
                for(int i=0;i<N;i++){int hit=0;int32_t out[3];
                    assert(!f.e2p_is_hit(f.user,0,boss,70015,&hit) && hit);
                    assert(!f.e2p_damage(f.user,0,boss,70015,NULL,out) && out[1]==1);
                    if(out[0]==0)zero++;else{nonzero++;if(out[0]>top)top=out[0];}}
                fprintf(stderr,"  SEISHIN %d KOORITEIKO %d: zero-damage %d, damaging %d (max %d)\n",seishin,resist,zero,nonzero,top);
                if(pass)assert(nonzero==0 && zero==N);   /* base 1 x ice factor < 1: no damage, only the guard flinch */
                else assert(nonzero>0 && top<=(e_kas*a_tsu/seishin)*105/100+1);
            }
        }
        /* The hit check against the player's SUBAYASA (retail: with the fixture's 9999 no boss attack landed; with 1 all did). Recovered rule (vfunc_34 case 0): a TYPE 0 attack misses when
         * BOUGYORITSU > r1 (r1 = rand % 100), else hits when r2 < eneatk.MEICHURITSU * enemy.SUBAYASA / (SUBAYASA * (KAIHIRITSU + 100) / 100) (r2 = rand % 100). */
        assert(!dw4_property_set_number(p0,"SUBAYASA",9999));
        for(unsigned k=0;k<sizeof retail/sizeof *retail;k++){
            int32_t a_hit;assert(!dw4_database_number(eneatk,retail[k].row,"MEICHURITSU",&a_hit));
            const int32_t chance=a_hit*e_sub/(9999*(0+100)/100);   /* percent: 100*156/9999 = 1 and 80*156/9999 = 1 */
            int hits=0;const int N=200000;
            for(int i=0;i<N;i++){int hit=0;assert(!f.e2p_is_hit(f.user,0,boss,retail[k].kind,&hit));hits+=hit;}
            fprintf(stderr,"e2pboss SUBAYASA 9999 kind %d: hit chance %d%%, port %d/%d\n",retail[k].kind,chance,hits,N);
            const double p=chance/100.0,sd=sqrt(N*p*(1-p));assert(chance>=1 && chance<100 && fabs(hits-N*p)<5*sd);
        }
        dw4_hubruntime_close(h);
        printf("field stage e2pboss: Mammothmon contact 177-196 and charge 284-309 equal the formula and the retail ranges (criticals about 2x, maximum 386 open #3020), SQ_FIRE 0 and the SUBAYASA hit check follow the recovered rule\n");
        return 0;
    }
    if(!strcmp(mode,"first")) {
    /* First visit (flag 355 clear): GENE-21 spawns the e_goburi of the scripted introduction (Sdc0101a demo camera, Digimon-info window,
     * ENEMY OFCTRL, then ENEMY SQ_ERAS); the arrival script restores control once the enemy is gone. Spawn, enemy HP from the
     * enemy database (row 0 -> 50, the Goblin Pass value in docs/systems/enemy-data.md) and the erase are measured here. */
    const int first[]={2,503};
    h=enter(&mount,first,2);
    unsigned until=0;
    for(;until<4000 && !control(h);until++)run(h,&frame,1,0,0);
    fprintf(stderr,"control after %u ticks\n",until);
    assert(until>300 && until<1200);
    const dw4_gene *g21=dw4_fieldgen_find(dw4_hubruntime_fieldgen(h),"GENE-21");
    assert(g21->state==DW4_GENE_STARTED && g21->spawned_total==1 && g21->nlive==0);
    printf("field stage stag0101 first visit: introduction spawned and erased e_goburi, control after %u ticks\n",until);
    dw4_hubruntime_close(h);
    return 0;
    }
    /* Revisit: the intro demo (flag 355) is already done; the arrival script restores control. */
    const int revisit[]={2,355,503};
    h=enter(&mount,revisit,3);
    const dw4_fieldgen *gen=dw4_hubruntime_fieldgen(h);assert(gen && dw4_fieldgen_count(gen)>=60);size_t generators=dw4_fieldgen_count(gen);
    const dw4_gene *g30=dw4_fieldgen_find(gen,"GENE-30");
    assert(g30 && g30->enemy_row==33 && !strcmp(g30->start_mode,"radar") && g30->state==DW4_GENE_STARTED && g30->starts==1);
    assert(dw4_fieldgen_find(gen,"GENE-e09") && dw4_fieldgen_find(gen,"GENE-e09")->state==DW4_GENE_IDLE);
    assert(!control(h));
    run(h,&frame,600,0,0);
    assert(control(h));
    dw4_lobby_walk_state before,after;assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&before));
    fprintf(stderr,"arrival %.9g %.9g %.9g\n",before.position[0],before.position[1],before.position[2]);
    assert(fabsf(before.position[0]-460)<.01f && fabsf(before.position[1]-50)<.01f && fabsf(before.position[2]-230)<.01f);   /* authored point 0 */
    run(h,&frame,60,0,0);
    assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&after) && !memcmp(before.position,after.position,sizeof before.position));
    run(h,&frame,30,0,-1);
    assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&after) && memcmp(before.position,after.position,sizeof before.position));
    if(getenv("DESCRIBE")){const dw4_database *d=dw4_databases_get(dw4_hubruntime_databases(h),getenv("DESCRIBE"));if(d)dw4_database_describe(d,stderr);else fprintf(stderr,"no database\n");}
    dw4_fb fb;assert(!dw4_fb_init(&fb,320,224));assert(dw4_hubruntime_draw(h,&fb,NULL)>1000);
    dw4_hubruntime_close(h);

    printf("field stage stag0101 revisit: generators %zu, arrival control restored, walking and draw\n",generators);
    return 0;
}
