/* Actual application travel, driven through the SDL dummy input/presentation
 * pump. Fixture relocation selects authored arrival points; bridge movement,
 * Lua4 exits, choices, threaded loading, publication and STATUS remain live. */
#include "dw4/engine.h"
#include "dw4/window.h"
#include "dw4/simulation.h"
#include "dw4/frontend.h"
#include "dw4/frontui.h"
#include "dw4/hubruntime.h"
#include "dw4/statusscene.h"
#include "dw4/png.h"
#include "dw4/loadjob.h"
#include "dw4/playerinit.h"
#include "dw4/gpupolicy.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <pthread.h>
#ifdef DW4_ENABLE_SDL2
static const struct {
    const char *from,*to;int point;float start[3],target[2];
} routes[]={
    {"stagML11","StagML12",0,{0,10,-40},{-80,-40}},
    {"stagML12","StagML13",1,{-110,40,260},{-30,260}},
    {"stagML13","StagML12",1,{-110,40,260},{-170,260}},
    {"stagML12","StagML11",1,{-60,40,-40},{20,-40}},
    {"stagML11","StagML13",0,{60,10,20},{60,100}},
    {"stagML13","StagML11",2,{60,40,80},{60,10}},
};
static dw4_lobby *world;
static dw4_hubruntime *candidate,*active_hub;
static int close_test,worker_waiting,worker_release;
static pthread_mutex_t worker_mutex=PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t worker_cond=PTHREAD_COND_INITIALIZER;
static unsigned tick_batch=1;
static unsigned max_legs=6;static int gpu_test;static uint64_t cpu_before[DW4_CPU_KIND_COUNT];
static unsigned polls,leg,phase,age,mode,visited,opens,closes,loading_draws,loading_presents;
static unsigned prepare_calls,injected_failures,failures,retried,backed,source_ticks,loading_ticks;
static int loading,pending_sample,inject,fail_test,fail_leg,status_done,done;
static uint64_t last_ns,held_ns;static int clock_hold;
static const char *capture_dir;
/* DW4_HUB_GATE: the Terminal's Gate to Outside World (mate00) with flag 2 set and 503 clear requests the practice stage stag0001: the
 * application must load it (loading card, worker, publication) and give control back after the stage's introduction. */
static int gate_test,gate_field;static unsigned gate_phase,gate_mark;static dw4_playerrecords *gate_records;
static void place(const float p[3]);
static int gate_pump(dw4_input_state *in,const dw4_lobby_control_state *c)
{
    static const float label[3]={5,100,-70},pad[3]={5,100,-95}; /* matf00 beside the pad, then the pad mate00 */
    if(gate_phase==0 && c->player_control) {
        dw4_script_value a[2]={{DW4_SCRIPT_NUMBER,2,NULL,0},{DW4_SCRIPT_NUMBER,1,NULL,0}},r;char e[256];
        assert(!dw4_playerrecords_call(gate_records,"FLGset",a,2,&r,e,sizeof e));
        place(label);gate_phase=1;age=0;
    }else if(gate_phase==1 && age>60){place(pad);gate_phase=2;age=0;}
    else if(gate_phase==2 && !c->player_control){gate_phase=3;age=0;}
    else if(gate_phase==3 && age>=80){in->cross=1;gate_phase=4;gate_mark=loading_draws;age=0;}
    else if(gate_phase==5 && c->player_control && age>120)done=1;
    if(gate_phase<5)assert(age<1500);
    return 1;
}
/* The title opening (about 270 frames) ignores input in windowed play, so the pad script starts after it. */
static const char *base="285:start,350:start,410:cross,580:cross,625:cross,675:cross,690:right,700:right,712:cross,728:start,780:cross,810:cross,860:start,880:cross";
static void place(const float p[3])
{
    char value[128],error[256];snprintf(value,sizeof value,"V<%.9g,%.9g,%.9g>/V<0,0,0>",p[0],p[1],p[2]);
    dw4_script_value a[]={{DW4_SCRIPT_STRING,0,"PLAYER",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},
        {DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,value,strlen(value)}},r;
    assert(!dw4_lobby_player_service(world,"sd",a,5,&r,error,sizeof error));
}
int __wrap_dw4_window_pump(dw4_window *w,dw4_input_state *in);
/* The engine pumps through dw4_window_pump_mates (the co-op pads of players 2-4); the scripted pad is the first player's. */
int __wrap_dw4_window_pump_mates(dw4_window *w,dw4_input_state *in,dw4_input_state mates[3]){(void)mates;return __wrap_dw4_window_pump(w,in);}
int __wrap_dw4_window_pump(dw4_window *w,dw4_input_state *in)
{
    (void)w;pending_sample=0;dw4_input_script(in,base,(int)polls++);
    if(done || polls>200000){in->quit=1;return 1;}
    if(failures==1 && !retried){in->cross=1;retried=1;return 1;}
    if(failures==2 && !backed){in->circle=1;backed=1;return 1;}
    if(close_test && loading && loading_draws>200) {
        pthread_mutex_lock(&worker_mutex);
        if(worker_waiting){worker_release=1;pthread_cond_signal(&worker_cond);in->quit=1;done=1;}
        pthread_mutex_unlock(&worker_mutex);
        if(done)return 1;
    }
    if(loading || !world)return 1;
    dw4_lobby_control_state c;assert(!dw4_lobby_control(world,&c));
    if(gate_field){if(c.player_control && age>200)done=1;else if(polls%90<4)in->cross=1;return 1;}   /* the practice stage: Cross through its introduction until control returns */
    if(!dw4_lobby_intro_done(world)){if(polls%10==0)in->cross=1;return 1;}
    if(gate_test)return gate_pump(in,&c);
    if(leg==max_legs){if(c.player_control && age>180)done=1;return 1;}
    if(phase==0 && c.player_control && (!active_hub || !dw4_hubruntime_input_state(active_hub)->disabled)) {
        if(!status_done){in->start=1;phase=5;age=0;return 1;}
        place(routes[leg].start);phase=1;age=0;
    }
    if(phase==1) {
        dw4_lobby_walk_state player;assert(!dw4_lobby_walk(world,&player));
        float yaw=atan2f(routes[leg].target[0]-player.position[0],routes[leg].target[1]-player.position[2])-atan2f(c.camera_world[8],c.camera_world[10]);
        in->lx=sinf(yaw);in->ly=-cosf(yaw);
    }else if(phase==2) {
        if(mode==1 && age==65)in->down=1;
        if(age>=80){if(mode==0)in->circle=1;else in->cross=1;phase=mode<2?3:4;age=0;}
    }else if(phase==5 && age>=180){in->circle=1;phase=6;age=0;}
    return 1;
}
uint64_t __wrap_dw4_simulation_due(dw4_simulation *s,uint64_t host)
{
    (void)host;if(s->holds || s->failed)return 0;
    if(!s->due)s->due=world?tick_batch:1;
    if(inject==1){s->due+=10;inject=2;}
    return s->due;
}
int __real_dw4_simulation_step(dw4_simulation *);
int __wrap_dw4_simulation_step(dw4_simulation *s)
{
    int rc=__real_dw4_simulation_step(s);uint64_t ns=dw4_clock_host_world(&s->clock);
    if(clock_hold){assert(ns>held_ns && ns-held_ns<=16666668);clock_hold=0;loading_ticks++;}
    last_ns=ns;return rc;
}
void __real_dw4_lobby_tick(dw4_lobby *,int);
void __wrap_dw4_lobby_tick(dw4_lobby *l,int edge)
{
    if(l!=world) {
        dw4_lobby_world_state info;assert(!dw4_lobby_world_info(l,&info));
        if(visited && gate_test){assert(!strcasecmp(info.stage,"stag0001") && info.arrival_point==0 && gate_phase==4);gate_field=1;}   /* the gate published the practice stage through the loading path */
        else if(visited){assert(leg<6 && !strcasecmp(info.stage,routes[leg].to) && info.arrival_point==routes[leg].point);leg++;}
        else {assert(!strcmp(info.stage,"stagML11"));for(unsigned k=0;k<DW4_CPU_KIND_COUNT;k++)cpu_before[k]=dw4_gpu_policy_cpu_count(k);}
        active_hub=candidate && dw4_hubruntime_world(candidate)==l?candidate:NULL;
        world=l;visited++;phase=0;age=0;mode=0;status_done=0;
        fprintf(stderr,"APP AREA %u %s group %d; route %u\n",visited,info.stage,info.arrival_point,leg);
    }
    loading=0;__real_dw4_lobby_tick(l,edge);age++;source_ticks++;
    if(leg<6) {
        dw4_lobby_control_state c;assert(!dw4_lobby_control(l,&c));
        if(phase==1 && !c.player_control){phase=2;age=0;}
        if(phase==3 && age>100 && c.player_control){mode++;phase=0;age=0;}
        if(phase==6 && age>100 && c.player_control){phase=0;age=0;status_done=1;}
        if(backed && failures==2 && phase==4 && age>30 && c.player_control){phase=0;age=0;mode=2;}
        assert(age<3000);
    }
}
void __real_dw4_frontui_loading_sample(dw4_frontui *,uint64_t);
void __wrap_dw4_frontui_loading_sample(dw4_frontui *ui,uint64_t ns)
{
    if(world && !loading){held_ns=last_ns;clock_hold=1;}
    if(world){loading=1;if(!inject && ns>=20*1000000000ULL/60)inject=1;}
    loading_draws++;pending_sample=1;__real_dw4_frontui_loading_sample(ui,ns);
}
int __real_dw4_window_present(dw4_window *,const dw4_fb *);
int __wrap_dw4_window_present(dw4_window *w,const dw4_fb *fb)
{
    if(pending_sample)loading_presents++;
    if(capture_dir && !loading && world && phase==2 && age==70 && mode==2) {
        char path[512];snprintf(path,sizeof path,"%s/app-choice-%u.png",capture_dir,leg);assert(!dw4_png_write(path,fb->rgba,fb->w,fb->h));
    }
    if(capture_dir && gate_test && !loading && gate_field && age>0 && age%45==0 && age<=900) {   /* the practice stage's introduction, one frame every 0.75 s */
        char path[512];snprintf(path,sizeof path,"%s/gate-practice-%04u.png",capture_dir,age);assert(!dw4_png_write(path,fb->rgba,fb->w,fb->h));
    }
    return __real_dw4_window_present(w,fb);
}
dw4_hubruntime *__real_dw4_hubruntime_prepare(dw4_mount *,const dw4_hubruntime_source *,const char *,int32_t,int,char *,size_t);
dw4_hubruntime *__wrap_dw4_hubruntime_prepare(dw4_mount *m,const dw4_hubruntime_source *s,const char *stage,int32_t point,int light,char *error,size_t cap)
{
    prepare_calls++;dw4_be_state before=*s->state;
    if(close_test) {
        pthread_mutex_lock(&worker_mutex);worker_waiting=1;
        while(!worker_release)pthread_cond_wait(&worker_cond,&worker_mutex);
        pthread_mutex_unlock(&worker_mutex);
    }
    int32_t values[5];const char *keys[]={"BIT","XDATA","LEVEL","HP","MP"};
    for(unsigned i=0;i<5;i++)assert(!dw4_property_number(dw4_playerrecords_get((dw4_playerrecords *)s->records,"GETPLAYER",0),keys[i],values+i));
    assert(values[0]==12345 && values[1]==789);
    if(fail_test && leg==(unsigned)fail_leg && injected_failures<2){snprintf(error,cap,"injected destination failure after retaining source");injected_failures++;return NULL;}
    dw4_hubruntime *h=__real_dw4_hubruntime_prepare(m,s,stage,point,light,error,cap);
    assert(!memcmp(&before,s->state,sizeof before));
    if(h)for(unsigned i=0;i<5;i++){int32_t after;assert(!dw4_property_number(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0),keys[i],&after) && after==values[i]);}
    if(h)candidate=h;
    return h;
}
int __real_dw4_playerrecords_create(dw4_playerrecords *,const dw4_databases *,int32_t,const char *,const char *,char *,size_t);
int __wrap_dw4_playerrecords_create(dw4_playerrecords *players,const dw4_databases *db,int32_t slot,const char *model,const char *name,char *error,size_t cap)
{
    int rc=__real_dw4_playerrecords_create(players,db,slot,model,name,error,cap);
    if(!rc)gate_records=players;
    if(!rc){dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",slot);
        assert(!dw4_property_set_number(f,"BIT",12345) && !dw4_property_set_number(f,"XDATA",789));}
    return rc;
}
int __real_dw4_loadjob_poll(dw4_loadjob *,void **);
int __wrap_dw4_loadjob_poll(dw4_loadjob *job,void **result)
{
    int ready=__real_dw4_loadjob_poll(job,result);
    if(ready && !*result && injected_failures>failures)failures=injected_failures;
    return ready;
}
int __real_dw4_statusscene_freeze(dw4_statusscene *,char *,size_t);
int __wrap_dw4_statusscene_freeze(dw4_statusscene *s,char *e,size_t n)
{int rc=__real_dw4_statusscene_freeze(s,e,n);if(!rc)opens++;return rc;}
int __real_dw4_statusscene_restore(dw4_statusscene *,char *,size_t);
int __wrap_dw4_statusscene_restore(dw4_statusscene *s,char *e,size_t n)
{int rc=__real_dw4_statusscene_restore(s,e,n);if(!rc)closes++;return rc;}
int __real_dw4_frontend_boot(const char *,dw4_title_menu *,char *,size_t,int,int,struct dw4_window *,struct dw4_vk *,const char *,int);
int __wrap_dw4_frontend_boot(const char *r,dw4_title_menu *m,char *s,size_t n,int p,int f,struct dw4_window *w,struct dw4_vk *v,const char *input,int skip)
{(void)p;(void)w;(void)v;(void)input;(void)skip;return __real_dw4_frontend_boot(r,m,s,n,0,f,NULL,NULL,NULL,1);}
int main(int argc,char **argv)
{
    assert(argc>=2);close_test=getenv("DW4_HUB_CLOSE_LOAD")!=NULL;fail_test=getenv("DW4_HUB_FAIL")!=NULL;capture_dir=argc>2?argv[2]:NULL;max_legs=getenv("DW4_HUB_LEGS")?(unsigned)atoi(getenv("DW4_HUB_LEGS")):6;assert(max_legs>0 && max_legs<=6);fail_leg=getenv("DW4_HUB_FAIL_LEG")?atoi(getenv("DW4_HUB_FAIL_LEG")):0;
    if(!dw4_window_built()){puts("hub application: SDL unavailable, skipped");return 0;}
    tick_batch=getenv("DW4_HUB_TICK_BATCH")?(unsigned)atoi(getenv("DW4_HUB_TICK_BATCH")):1;assert(tick_batch>0 && tick_batch<=16);
    gpu_test=getenv("DW4_HUB_GPU")!=NULL;gate_test=getenv("DW4_HUB_GATE")!=NULL;
    dw4_engine_opts o={.roms=argv[1],.frames=200000,.w=160,.h=112,.window=1,.software=!gpu_test,.gl=gpu_test,.fps=0};char stage[128];
    int rc=dw4_engine_boot(&o,NULL,stage,sizeof stage);
    fprintf(stderr,"APP HUB rc%d routes%u visits%u status%u/%u loads%u/%u clock-holds%u calls%u failures%u polls%u\n",rc,leg,visited,opens,closes,loading_draws,loading_presents,loading_ticks,prepare_calls,failures,polls);
    if(close_test){assert(rc>=0 && done && worker_waiting && worker_release && prepare_calls==1 && visited==1 && !leg && loading_draws==loading_presents);
        puts("hub application: window close joins a confirmed in-flight worker before source teardown; no candidate publication");return 0;}
    if(gate_test){fprintf(stderr,"APP GATE phase %u done %d mark %u stage %s\n",gate_phase,done,gate_mark,stage);assert(rc>=0 && done && gate_field && prepare_calls==1 && visited==2 && !leg && loading_draws>gate_mark+30 && loading_draws==loading_presents && !strncasecmp(stage,"stag0001",8));
        puts("hub application: the Terminal gate of a fresh save loads the practice stage stag0001 through the loading card and worker, publishes it, and control returns after its introduction");return 0;}
    assert(rc>=0 && done && leg==max_legs && visited==max_legs+1 && opens==max_legs && closes==max_legs && !strcasecmp(stage,routes[max_legs-1].to));
    if(gpu_test)for(unsigned k=0;k<DW4_CPU_KIND_COUNT;k++)assert(dw4_gpu_policy_cpu_count(k)==cpu_before[k]);
    assert(loading_draws==loading_presents && loading_ticks>=max_legs && inject==2);
    assert(!fail_test || (failures==2 && retried && backed && prepare_calls==max_legs+2));
    printf("hub application: %u original exits, bridge input, choices, threaded loading/presentation, held session clocks, source records and STATUS restore pass\n",max_legs);return 0;
}

#else
int main(void){puts("hub application: SDL unavailable, skipped");return 0;}
#endif
