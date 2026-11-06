#include "dw4/modelctrl.h"
#include "../src/arenalist.h"
#include <math.h>
#include "dw4/controllers.h"
#include "dw4/filelist.h"
#include "dw4/lobby.h"
#include "dw4/lobbyui.h"
#include "dw4/scriptservices.h"
#include "dw4/stageobjects.h"
#include "dw4/frontaudio.h"
#include "dw4/modelsubcom.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
static void action_sink(void *user,const char *model,const char *action)
{assert(model && *model && action && *action);(*(unsigned *)user)++;}
static dw4_script_value str(const char *s) {return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
static double call_slot(dw4_script_binding service,void *owner,const char *method,const char *category,
    const char *name,int32_t slot,const char *key,const char *value)
{
    dw4_script_value a[]={str(category),name?str(name):(dw4_script_value){0},
        {DW4_SCRIPT_NUMBER,slot,NULL,0},str(key),value?str(value):(dw4_script_value){0}},r={0};char error[256];
    int rc=service(owner,method,a,value?5:4,&r,error,sizeof error);
    if(rc)fprintf(stderr,"%s %s: %s\n",name?name:category,key,error);
    assert(!rc);return r.number;
}
static double call(dw4_script_binding service,void *owner,const char *method,const char *category,
    const char *name,const char *key,const char *value) {
    return call_slot(service,owner,method,category,name,0,key,value);
}
static void model_test(dw4_mount *mount,int archive,int entry,const char *name,const char *open,const char *wait,const char *close)
{
    uint32_t size;const uint8_t *blob=dw4_mount_entry(mount,archive,entry,&size,NULL);assert(blob);
    dw4_modelctrl *m=dw4_modelctrl_open(blob,size,name);
    if(!m)fprintf(stderr,"load failed: %s\n",name);
    assert(m);
    assert(!dw4_modelctrl_active(m));
    assert(!dw4_modelctrl_tick(m,1000000000));
    call(dw4_modelctrl_service,m,"sd","MODELCTRL",name,"GENERATE",open);
    assert(dw4_modelctrl_active(m));
    for(unsigned i=0;i<400;i++) {
        const char *s=dw4_modelctrl_sequence(m);assert(s);
        int64_t time=dw4_modelctrl_time(m);
        for(unsigned q=0;q<4;q++)assert(call(dw4_modelctrl_service,m,"querySD","MODELCTRL",name,"ISRUN",NULL)==1);
        assert(time==dw4_modelctrl_time(m));
        assert(!dw4_modelctrl_tick(m,1000000000LL+(int64_t)(i+1)*1000000000LL/60));
        if(!strcmp(dw4_modelctrl_sequence(m),wait))break;
    }
    assert(!strcmp(dw4_modelctrl_sequence(m),wait));
    /* Failed replacements retain a live sequence and its animation. */
    int64_t time=dw4_modelctrl_time(m);
    assert(dw4_modelctrl_start(m,"SQ_NOT_AUTHORED")==-1);
    assert(!strcmp(dw4_modelctrl_sequence(m),wait) && time==dw4_modelctrl_time(m));
    if(close) {
        assert(!dw4_modelctrl_start(m,close));
        for(unsigned i=0;dw4_modelctrl_active(m) && i<400;i++)
            assert(!dw4_modelctrl_tick(m,8000000000LL+(int64_t)i*1000000000LL/60));
        assert(!dw4_modelctrl_active(m));
    }
    assert(!dw4_modelctrl_start(m,open));dw4_modelctrl_remove(m);
    assert(!dw4_modelctrl_active(m) && !dw4_modelctrl_sequence(m));
    dw4_modelctrl *instance=dw4_modelctrl_instance(m);assert(instance && !dw4_modelctrl_active(instance));
    dw4_modelctrl_close(m);
    assert(!dw4_modelctrl_start(instance,open));
    dw4_modelctrl_close(instance);
}
static int dm_source(void *user,const char *path,const void **bytes,size_t *size)
{
    (void)user;(void)path;
    static const char source[]=
        "be:DMsetSD('MODELCTRL','i_talkwn',0,'GENERATE','SQ_OPENL',3) "
        "be:DMchkSD('MODELCTRL','i_talkwn',0,'ISSEQNAME','SQ_OPENL','==0') "
        "be:DMchkSD('MODELCTRL','i_talkwn',0,'ISSEQNAME','SQ_OPENL','!=0') "
        "be:DMsetSD('MODELCTRL','i_talkwn',0,'SQ_CLOSEL') "
        "be:DMchkSD('MODELCTRL','i_talkwn',0,'ISRUN','!=0') be:DMrun() [EOF]";
    *bytes=source;*size=sizeof(source)-1;return 0;
}
static void window_test(dw4_mount *mount)
{
    uint32_t size;const uint8_t *blob=dw4_mount_entry(mount,0,820,&size,NULL);
    dw4_scene scene;assert(!dw4_scene_load(&scene,blob,size));
    dw4_lobbyui *ui=dw4_lobbyui_open(mount,&scene,blob,size);assert(ui);
    dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));
    dw4_scriptservices *sd=dw4_scriptservices_open();assert(sd);
    const char *names[]={"i_messwn","i_talkwn","n_digilffic","i_messky","i_talkky"};
    for(unsigned i=0;i<5;i++)assert(dw4_scriptservices_register(sd,2,"MODELCTRL",names[i],0,0,dw4_lobbyui_script_service,ui));
    assert(!dw4_lobbyui_services_tick(ui,1000000000));
    call(dw4_scriptservices_call,sd,"sd","MODELCTRL","i_talkwn","GENERATE","SQ_OPENL");
    assert(dw4_lobbyui_draw(ui,&fb)>0);
    unsigned draws=0;const dw4_ui_draw *d=dw4_lobbyui_draws(ui,&draws);
    for(unsigned i=0;i<draws;i++)assert(d[i].tex->w!=64 || d[i].tex->h!=64);
    call(dw4_scriptservices_call,sd,"sd","MODELCTRL","n_digilffic","GENERATE","SQ_OPENL");
    assert(call(dw4_scriptservices_call,sd,"querySD","MODELCTRL","i_talkwn","ISSEQNAME","SQ_OPENL")==1);
    assert(call(dw4_scriptservices_call,sd,"querySD","MODELCTRL","i_messwn","ISRUN",NULL)==0);
    /* Draws/queries/holds cannot complete the controller. */
    for(unsigned i=0;i<20;i++)assert(dw4_lobbyui_draw(ui,&fb)>0);
    assert(call(dw4_scriptservices_call,sd,"querySD","MODELCTRL","i_talkwn","ISSEQNAME","SQ_OPENL")==1);
    unsigned finish=0;
    for(unsigned i=1;i<=40;i++) {
        assert(!dw4_lobbyui_services_tick(ui,1000000000LL+(int64_t)i*1000000000LL/60));
        if(call(dw4_scriptservices_call,sd,"querySD","MODELCTRL","i_talkwn","ISSEQNAME","SQ_WAITL")){finish=i;break;}
    }
    assert(finish && finish<=40);
    call(dw4_scriptservices_call,sd,"sd","MODELCTRL","i_talkwn","SQ_CLOSEL",NULL);
    for(unsigned i=1;i<=40;i++)assert(!dw4_lobbyui_services_tick(ui,2000000000LL+(int64_t)i*1000000000LL/60));
    assert(call(dw4_scriptservices_call,sd,"querySD","MODELCTRL","i_talkwn","ISRUN",NULL)==0);
    assert(call(dw4_scriptservices_call,sd,"querySD","MODELCTRL","n_digilffic","ISRUN",NULL)==1);
    call(dw4_scriptservices_call,sd,"sd","MODELCTRL","n_digilffic","REMOVE",NULL);
    assert(dw4_lobbyui_draw(ui,&fb)==0);
    dw4_be_state state;dw4_be_init(&state);
    dw4_scriptengine *engine=dw4_scriptengine_open(&state,dw4_scriptservices_call,sd);assert(engine);
    dw4_script_source_set(dw4_scriptengine_vm(engine),dm_source,NULL,NULL);
    dw4_scriptservices_scope(sd,2);
    int script_rc=dw4_script_run_named(dw4_scriptengine_vm(engine),"window-dm.lua",NULL);
    if(script_rc)fprintf(stderr,"DM source: %s\n",dw4_script_error(dw4_scriptengine_vm(engine)));
    assert(!script_rc);
    assert(dw4_scriptengine_pending(engine)==1);
    for(unsigned i=1;i<=80;i++) {
        uint64_t now=3000000000ULL+(uint64_t)i*1000000000/60;
        dw4_lobbyui_services_sample(ui,(int64_t)now);
        assert(!dw4_scriptservices_tick(sd,now));
        assert(!dw4_scriptengine_tick(engine));
        assert(!dw4_lobbyui_services_tick(ui,(int64_t)now));
        if(i<=3)assert(call(dw4_scriptservices_call,sd,"querySD","MODELCTRL","i_talkwn","ISRUN",NULL)==0);
    }
    assert(!dw4_scriptengine_pending(engine));
    assert(call(dw4_scriptservices_call,sd,"querySD","MODELCTRL","i_talkwn","ISRUN",NULL)==0);
    /* Queued creation cannot reach a released/re-entered scene. */
    dw4_script_value delayed[]={str("MODELCTRL"),str("i_talkwn"),{DW4_SCRIPT_NUMBER,0,NULL,0},
        str("GENERATE"),str("SQ_OPENL"),{DW4_SCRIPT_NUMBER,100,NULL,0}},unused={0};char diagnostic[256];
    assert(!dw4_scriptservices_call(sd,"sd",delayed,6,&unused,diagnostic,sizeof diagnostic));
    assert(dw4_scriptservices_pending(sd)==1);
    dw4_scriptengine_close(engine);
    dw4_scriptservices_remove_scope(sd,2);
    assert(!dw4_scriptservices_pending(sd));
    dw4_script_value a[]={str("MODELCTRL"),str("i_talkwn"),{DW4_SCRIPT_NUMBER,0,NULL,0},str("ISRUN")},r={0};char error[256];
    assert(!dw4_scriptservices_call(sd,"querySD",a,4,&r,error,sizeof error) && r.type==DW4_SCRIPT_NIL);
    dw4_scriptservices_close(sd);dw4_fb_free(&fb);dw4_lobbyui_close(ui);dw4_scene_close(&scene);
    printf("Window authored OPENL -> WAITL: %u clock samples; independent portrait, close/remove and held rendering passed\n",finish);
}
static void camera_test(dw4_mount *mount)
{
    dw4_lobby *l=dw4_lobby_open(mount,3,"CLOCK");assert(l);
    call(dw4_lobby_camera_service,l,"sd","CAMERA",NULL,"SETDEMOCAMERA","camsp0101");
    assert(call(dw4_lobby_camera_service,l,"querySD","CAMERA",NULL,"ISDEMOCAMERA",NULL)==1);
    for(unsigned i=1;i<=60;i++)assert(!dw4_lobby_services_tick(l,(uint64_t)i*1000000000/60));
    call(dw4_lobby_camera_service,l,"sd","CAMERA",NULL,"ONFREEZE",NULL);
    for(unsigned i=61;i<=600;i++)assert(!dw4_lobby_services_tick(l,(uint64_t)i*1000000000/60));
    assert(call(dw4_lobby_camera_service,l,"querySD","CAMERA",NULL,"ISDEMOCAMERA",NULL)==1);
    call(dw4_lobby_camera_service,l,"sd","CAMERA",NULL,"OFFREEZE",NULL);
    unsigned finish=0;
    for(unsigned i=601;i<=850;i++) {
        assert(!dw4_lobby_services_tick(l,(uint64_t)i*1000000000/60));
        if(!call(dw4_lobby_camera_service,l,"querySD","CAMERA",NULL,"ISDEMOCAMERA",NULL)){finish=i;break;}
    }
    assert(finish==781);
    call(dw4_lobby_camera_service,l,"sd","CAMERA",NULL,"SETBOXCAMERA",NULL);
    dw4_lobby_control_state control;assert(!dw4_lobby_control(l,&control) && control.box_camera && control.material_ticks==0);
    call(dw4_lobby_camera_service,l,"sd","CAMERA",NULL,"SETDEMOCAMERA","camsp0101");
    assert(call(dw4_lobby_camera_service,l,"querySD","CAMERA",NULL,"ISDEMOCAMERA",NULL)==1);
    dw4_lobby_close(l);puts("Lobby camera: authored duration, freeze/resume, inclusive completion, box and restart passed");
}
typedef struct {
    dw4_scriptservices *sd;
    dw4_controllers *controllers;
    dw4_scriptengine *engine;
    size_t index;
    uint64_t scope;
    int cancel;
} prepared_context;
static int prepare_binding(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    prepared_context *c=user;*r=(dw4_script_value){0};
    if(!strcmp(method,"sd") && n>=4 && a[0].type==DW4_SCRIPT_STRING && !strcmp(a[0].string,"TEST")) {
        assert(!dw4_controllers_health(c->controllers,c->index,99,100));
        if(c->cancel) {
            dw4_scriptengine_remove_scope(c->engine,c->scope);
            dw4_scriptservices_remove_scope(c->sd,c->scope);
        }
        return 0;
    }
    if(!strcmp(method,"SYSgetLightMode"))*r=(dw4_script_value){DW4_SCRIPT_NUMBER,1,NULL,0};
    else if(!strcmp(method,"SYSisJoinPlayer"))*r=(dw4_script_value){DW4_SCRIPT_NUMBER,n==1 && a[0].number==0,NULL,0};
    else if(!strcmp(method,"SYSgetPlayerName"))*r=str("m_dorumon");
    else if(!strcmp(method,"SYSgetWeaponName"))*r=str("w_axe01");
    else return c->sd?dw4_scriptservices_call(c->sd,method,a,n,r,error,cap):-1;
    return 0;
}
static int prepared_source(void *user,const char *path,const void **bytes,size_t *size) {
    (void)user;assert(!strcmp(path,"aim_n_digilff.lua"));
    static const char source[]=
        "assert(be:MDLgetRamNo()==2 and be:MDLgetRecNo()==-1) "
        "assert(be:MDLgetHp()==1 and be:MDLgetMHp()==100) "
        "assert(be:MDLgetInfoName()=='n_digilff' and be:MDLisCallName('WPos')==1) "
        "be:MDLaddHp(1) be:MDLsetWorldPosTarget(4,5,6) "
        "be:sd('TEST',nil,0,'MUTATE') be:MDLsetSeq('SQ_WAIT02') [EOF]";
    *bytes=source;*size=sizeof source-1;return 0;
}
static void prepared_actor_test(prepared_context *c,dw4_be_state *state) {
    size_t slots[2]={SIZE_MAX,SIZE_MAX};dw4_script_model value;
    for(size_t i=0;i<dw4_controllers_count(c->controllers);i++) {
        const dw4_stageobject *info;int32_t slot;
        dw4_controllers_model(c->controllers,i,&info,&slot);
        if(!strcmp(dw4_stageobject_name(info),"n_digilff") && (slot==2 || slot==3))slots[slot-2]=i;
    }
    assert(slots[0]!=SIZE_MAX && slots[1]!=SIZE_MAX);
    dw4_random expected=state->random;
    for(unsigned which=0;which<2;which++) {
        size_t i=slots[which];int32_t slot=(int32_t)which+2;
        assert(!dw4_controllers_model_state(c->controllers,i,&value));
        assert(value.ram_no==slot && value.rec_no==-1 && value.hp==0 && value.max_hp==0);
        call_slot(dw4_scriptservices_call,c->sd,"sd","MODELCTRL","n_digilff",slot,"SQ_WALKON",NULL);
        assert(!dw4_controllers_model_state(c->controllers,i,&value) && value.hp==0);
        call_slot(dw4_scriptservices_call,c->sd,"sd","MODELCTRL","n_digilff",slot,"GENERATE","SQ_WAIT02");
        assert(!dw4_controllers_model_state(c->controllers,i,&value) && value.hp==100 && value.max_hp==100);
        int hp=100;
        for(unsigned j=0;j<128;j++) {
            if(!which) {
                hp=hp==100?1:hp;hp=hp==1?2:hp==3?2:hp+(dw4_random_mod(&expected,2)==0?1:-1);
            }
            call_slot(dw4_scriptservices_call,c->sd,"sd","MODELCTRL","n_digilff",slot,"GENERATE","SQ_WALKON");
            assert(!dw4_controllers_model_state(c->controllers,i,&value));
            if(value.hp!=hp)fprintf(stderr,"prepared WPos slot %d sample %u: HP %d expected %d\n",slot,j,value.hp,hp);
            assert(value.hp==hp && value.max_hp==100);
            dw4_modelctrl_aim aim;dw4_modelctrl_aim_state(dw4_controllers_model(c->controllers,i,NULL,NULL),&aim);
            assert(aim.index==1);
            if(!which)assert(aim.target[1]==10 && aim.target[0]==(hp==1?130:hp==2?20:60) && aim.target[2]==(hp==3?-10:-35));
            else assert(!aim.target[0] && !aim.target[1] && !aim.target[2]); /* no WPos row for slot 3 */
            assert(!memcmp(&expected,&state->random,sizeof expected));
        }
        call_slot(dw4_scriptservices_call,c->sd,"sd","MODELCTRL","n_digilff",slot,"REMOVE",NULL);
        call_slot(dw4_scriptservices_call,c->sd,"sd","MODELCTRL","n_digilff",slot,"GENERATE","SQ_WAIT02");
        assert(!dw4_controllers_model_state(c->controllers,i,&value) && value.hp==hp);
        dw4_random held=state->random;
        for(unsigned j=0;j<16;j++)assert(!dw4_controllers_model_state(c->controllers,i,&value));
        assert(!memcmp(&held,&state->random,sizeof held));
    }
    c->index=slots[0];
    assert(!dw4_controllers_health(c->controllers,c->index,1,100));
    /* Replace Lua collection with a controlled fallback, keeping the live
     * prepared owner. This tests native mutation/reentry and scope invalidation. */
    dw4_script_remove_scope(dw4_scriptengine_vm(c->engine),c->scope);
    dw4_script_source_set(dw4_scriptengine_vm(c->engine),prepared_source,NULL,NULL);
    dw4_modelctrl_aim before,after;
    dw4_modelctrl_aim_state(dw4_controllers_model(c->controllers,c->index,NULL,NULL),&before);
    dw4_script_value a[]={str("MODELCTRL"),str("n_digilff"),{DW4_SCRIPT_NUMBER,2,NULL,0},str("SQ_WALKON")},r={0};char error[256];
    int rc=dw4_scriptservices_call(c->sd,"sd",a,4,&r,error,sizeof error);
    assert((rc!=0)==c->cancel);
    assert(!dw4_controllers_model_state(c->controllers,c->index,&value) && value.hp==99);
    assert(!dw4_controllers_model_state(c->controllers,slots[1],&value) && value.hp==100 && value.max_hp==100);
    dw4_modelctrl_aim_state(dw4_controllers_model(c->controllers,c->index,NULL,NULL),&after);
    if(c->cancel)assert(!memcmp(before.target,after.target,sizeof before.target));
    else assert(after.target[0]==4 && after.target[1]==5 && after.target[2]==6);
    if(!c->cancel)assert(!strcmp(dw4_modelctrl_sequence(dw4_controllers_model(c->controllers,c->index,NULL,NULL)),"SQ_WAIT02"));
    puts("Prepared actors: per-slot health/identity, 256 original WPos/RNG states, regeneration, reentry and cancellation passed");
}
static void scene_dependencies(dw4_controllers *c)
{
    dw4_modelctrl *source=NULL,*effect=NULL,*window=NULL;const dw4_stageobject *source_info=NULL;
    for(size_t i=0;i<dw4_controllers_count(c);i++){
        const dw4_stageobject *info;int32_t slot;dw4_controllers_model(c,i,&info,&slot);if(slot)continue;
        const char *name=dw4_stageobject_name(info);
        if(!strcmp(name,"n_digilff")){source=dw4_controllers_owned_model(c,i);source_info=info;}
        if(!strcmp(name,"x_250healhit00"))effect=dw4_controllers_owned_model(c,i);
        if(!strcmp(name,"i_talkwn"))window=dw4_controllers_owned_model(c,i);
    }
    assert(source && effect && window && source_info);
    assert(!dw4_modelctrl_start(source,"SQ_WAIT02"));
    dw4_modelctrl_record sr=dw4_modelctrl_records(source),er=dw4_modelctrl_records(effect);
    beModelCtrlNode2 *sn=DW4_ARENA_OBJ(sr.arena,beModelCtrlNode2,sr.node);
    const float identity[16]={1,0,0,0,0,1,0,0,0,0,1,0,10,20,30,1};memcpy(sn->_m,identity,64);
    call_slot(dw4_modelctrl_service,source,"sd","MODELCTRL","n_digilff",0,"SETEFFECT",
        "x_250healhit00/SQ_HEALEFONLY/F<0>/V<1,2,3>/TRUE/TRUE");
    assert(!dw4_modelctrl_tick_frame(source,0,0) && dw4_modelctrl_active(effect));
    float pose[16];dw4_modelctrl_matrix(effect,pose);assert(pose[12]==11 && pose[13]==22 && pose[14]==33);
    beModelCtrlInfoWork *ew=DW4_ARENA_OBJ(er.arena,beModelCtrlInfoWork,er.work);
    assert(ew->_isPosLock && ew->_posLockNode==(int32_t)sr.node.off && ew->_hitParentRamNo==0);
    assert(!strcmp(al_text(er.arena,ew->_hitParentName),"n_digilff"));
    beModelCtrlInfoWork *frozen=DW4_ARENA_OBJ(er.arena,beModelCtrlInfoWork,er.work);frozen->_isOnFreeze=1;
    assert(!dw4_modelctrl_start(source,"SQ_WAIT02") && dw4_modelctrl_active(effect));
    assert(!strcmp(dw4_modelctrl_sequence(effect),"SQ_ERAS"));
    assert(!dw4_modelctrl_tick_frame(effect,0,0) && dw4_modelctrl_active(effect));
    frozen->_isOnFreeze=0;assert(!dw4_modelctrl_tick_frame(effect,0,0) && !dw4_modelctrl_active(effect));
    ((float *)(void *)sn->_m)[0]=((float *)(void *)sn->_m)[10]=0;
    ((float *)(void *)sn->_m)[2]=-1;((float *)(void *)sn->_m)[8]=1;
    /* A non-sequence-dependent effect survives its producer's sequence change
     * and continues following its retained source node. */
    call_slot(dw4_modelctrl_service,source,"sd","MODELCTRL","n_digilff",0,"SETEFFECT",
        "x_250healhit00/SQ_HEALEFONLY/F<0>/V<1,2,3>/FALSE/TRUE");
    assert(!dw4_modelctrl_tick_frame(source,1,0));assert(!dw4_modelctrl_start(source,"SQ_WAIT02"));
    assert(dw4_modelctrl_active(effect) && ew->_direction[1]==1.57079625f);
    ((float *)(void *)sn->_m)[12]=15;
    assert(!dw4_modelctrl_tick_frame(effect,2,0));dw4_modelctrl_matrix(effect,pose);assert(pose[12]==18);
    dw4_modelctrl_remove(effect);
    call_slot(dw4_modelctrl_service,source,"sd","MODELCTRL","n_digilff",0,"SETEFFECT",
        "missing-effect/SQ_WAIT/F<0>/V<0,0,0>/TRUE/TRUE");
    assert(!dw4_modelctrl_tick_frame(source,3,0));
    /* Use an actual bone from the mounted model's pack. Pose queries preserve
     * clocks and adding translation affects the composed matrix once. */
    const dw4_igb *g=source_info->igb;char joint[128]="";float before[16],after[16];
    for(uint32_t id=0;id<g->table_n && !joint[0];id++){
        if(g->id_kind[id]!=2)continue;
        dw4_igb_record r={0};if(!dw4_igb_decode(g,g->id_off[id],&r))continue;
        if(r.name && !strcmp(r.class_name,"igSkeletonBoneInfo") && dw4_controllers_bone(c,"n_digilff",0,r.name,before)==1)
            snprintf(joint,sizeof joint,"%s",r.name);
        dw4_igb_record_free(&r);
    }
    if(!joint[0])fprintf(stderr,"bone lookup: %s\n",dw4_controllers_error(c));
    assert(joint[0]);
    int64_t clock=dw4_modelctrl_time(source);((float *)(void *)sn->_m)[12]+=5;
    assert(dw4_controllers_bone(c,"n_digilff",0,joint,after)==1 && dw4_modelctrl_time(source)==clock);
    assert(fabsf((after[12]-before[12])-5)<.0001f);
    assert(dw4_controllers_bone(c,"n_digilff",0,"missing-bone",pose)==0);
    assert(dw4_controllers_bone(c,"n_digilff",999,joint,pose)==0);
    assert(!dw4_modelctrl_start(window,"SQ_OPENL"));
    assert(!dw4_modelctrl_relative(window,"JOINT","n_digilff",NULL));
    dw4_modelctrl_record wr=dw4_modelctrl_records(window);
    assert(!DW4_ARENA_OBJ(wr.arena,beModelCtrlInfoWork,wr.work)->_isPosLock);
    assert(!dw4_modelctrl_relative(window,"BONE","n_digilff",joint));
    assert(!dw4_modelctrl_tick_frame(window,4,0));dw4_modelctrl_matrix(window,pose);assert(!memcmp(pose,after,64));
    dw4_modelctrl_remove(window);dw4_modelctrl_remove(source);
    puts("Prepared model dependencies: effect generation/follow/finish, missing slots and asset-backed named bones pass");
}
static void specialized_dependencies(dw4_mount *mount,dw4_stageobjects *objects,dw4_be_state *state)
{
    const char *name="p_dorumon",*exclude[]={"p_dorumon"};
    const dw4_stageobject *info=dw4_stageobjects_find(objects,"beModelCtrlInfo",name,0);assert(info);
    dw4_arena *arena=dw4_session_arena();unsigned baseline=dw4_arena_live(arena,DW4_REGION_PERSISTENT);
    dw4_frontaudio *audio=dw4_frontaudio_prepare_lobby(mount);assert(audio);
#ifdef DW4_ENABLE_SDL2
    assert(!setenv("SDL_AUDIODRIVER","dummy",1));
    assert(!dw4_frontaudio_start_scripted(audio));
#endif
    for(int order=0;order<2;order++){
        dw4_scriptservices *sd=dw4_scriptservices_open();assert(sd);
        dw4_controllers *c=dw4_controllers_open(sd,1,objects,exclude,1,&state->random,&state->action_rhythm,NULL);assert(c);
        dw4_controllers_audio(c,audio);
        dw4_modelctrl *p=dw4_modelctrl_open_info(info->igb,info->id);assert(p);
        size_t roster=dw4_controllers_count(c);
        assert(dw4_controllers_bind_model(c,"not-a-model",0,p)==-1);
        assert(!dw4_controllers_bind_model(c,name,0,p) && dw4_controllers_count(c)==roster);
        assert(dw4_controllers_bind_model(c,name,0,p)==-1);
        dw4_modelctrl_record pr=dw4_modelctrl_records(p);
        beBaseInfoRam *ram=DW4_ARENA_OBJ(arena,beBaseInfoRam,pr.ram);
        assert(ram->_parentInfo==(int32_t)info->object.off && ram->_parentManager);
        assert(!dw4_modelctrl_label(p,"SQ_WAIT","slash") && !dw4_modelctrl_start(p,"SQ_WAIT"));
        int64_t time=dw4_modelctrl_time(p);
        dw4_controllers_sample(c,1000000000);assert(!dw4_controllers_tick(c,1000000000));
        assert(dw4_modelctrl_time(p)==time);
        float matrix[16];int bone=dw4_controllers_bone(c,name,0,"RArm04",matrix);
        if(bone!=1)fprintf(stderr,"specialized bone: %d %s\n",bone,dw4_controllers_error(c));
        assert(bone==1 && dw4_modelctrl_time(p)==time);
        dw4_modelctrl *effect=NULL;
        for(size_t i=0;i<roster;i++){
            const dw4_stageobject *o;int32_t slot;dw4_controllers_model(c,i,&o,&slot);
            if(!slot && !strcmp(dw4_stageobject_name(o),"x_250healhit00"))effect=dw4_controllers_owned_model(c,i);
        }
        assert(effect);
        call_slot(dw4_modelctrl_service,p,"sd","PLAYER",name,0,"SETEFFECT","x_250healhit00/SQ_HEALEFONLY/F<0>/V<1,2,3>/TRUE/TRUE");
        dw4_frontaudio_set_clock(audio,(uint64_t)(order+1)*1000000000);
        call_slot(dw4_modelctrl_service,p,"sd","PLAYER",name,0,"SETSOUND","CURSOR_START/F<0>");
        assert(!dw4_modelctrl_tick_frame(p,0,0) && dw4_modelctrl_active(effect));
        int heard=0;for(unsigned v=0;v<8;v++){
            int clip=dw4_frontaudio_voice_clip(audio,v,NULL);const char *n=dw4_frontaudio_clip_name(audio,clip);
            heard|=n && !strcmp(n,"CURSOR_START");
        }
#ifdef DW4_ENABLE_SDL2
        assert(heard);
#else
        assert(!heard); /* Prepared service without a media device returns no handle. */
#endif
        dw4_modelctrl_record er=dw4_modelctrl_records(effect);
        beModelCtrlInfoWork *ew=DW4_ARENA_OBJ(arena,beModelCtrlInfoWork,er.work);
        assert(ew->_hitParentRamNo==0 && !strcmp(al_text(arena,ew->_hitParentName),name));
        /* A generated model can resolve the specialized player's pose. */
        assert(dw4_controllers_bone(c,name,0,"RArm04",matrix)==1);
        float parent_follow[16];dw4_modelctrl_matrix(effect,parent_follow);
        assert(!dw4_modelctrl_relative(effect,"BONE",name,"RArm04"));
        assert(!dw4_modelctrl_tick_frame(effect,0,0));float followed[16];dw4_modelctrl_matrix(effect,followed);
        /* Retail MOVERL retains an existing direct-node lock, which takes
         * precedence. Explicitly release it before testing named following. */
        assert(ew->_posLockNode==(int32_t)pr.node.off && !memcmp(parent_follow,followed,64));
        assert(!dw4_modelctrl_position_lock(effect,NULL,NULL));
        assert(!dw4_modelctrl_relative(effect,"BONE",name,"RArm04"));
        assert(!dw4_modelctrl_tick_frame(effect,0,0));dw4_modelctrl_matrix(effect,followed);
        assert(!memcmp(matrix,followed,64));
        if(!order){
            dw4_modelctrl_close(p);
            assert(dw4_controllers_bone(c,name,0,"RArm04",matrix)==0);
            assert(dw4_modelctrl_active(effect) && !strcmp(dw4_modelctrl_sequence(effect),"SQ_ERAS"));
            assert(!dw4_controllers_tick(c,1000000001) && !dw4_modelctrl_active(effect));
            dw4_controllers_close(c);
        }else{
            dw4_controllers_close(c);
            assert(dw4_modelctrl_active(p) && !ram->_parentInfo && !ram->_parentManager);
            beModelCtrlInfoWork *pw=DW4_ARENA_OBJ(arena,beModelCtrlInfoWork,pr.work);
            beModelCtrlSubCom *sc=DW4_ARENA_OBJ(arena,beModelCtrlSubCom,al_handle(pw->_subCommand));
            assert(!al_count(arena,sc->_comList));
            assert(dw4_modelctrl_relative(p,"BONE",name,"RArm04")==-1);
            dw4_modelctrl_close(p);
        }
        dw4_scriptservices_close(sd);
    }
    dw4_frontaudio_close(audio);assert(dw4_arena_live(arena,DW4_REGION_PERSISTENT)==baseline);
    puts("Specialized player: one updater/renderer, effect/sound services, private bone graph and both close orders pass");
}
static void prepared_test(dw4_mount *mount)
{
    dw4_be_state state;dw4_be_init(&state);
    prepared_context context={0};
    dw4_scriptengine *engine=dw4_scriptengine_open(&state,prepare_binding,&context);assert(engine);context.engine=engine;
    dw4_filelist *files=dw4_filelist_open(mount);assert(files);dw4_scriptengine_filelist(engine,files);
    const char *stages[]={"stagIS10","stagML11"};
    for(unsigned pass=0;pass<4;pass++) {
        unsigned stage=pass%2;
        dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
        if(pass==1)dw4_stageobjects_actor_skins(objects,1);
        int prep=dw4_filelist_begin(files,engine,stages[stage],pass+1);
        if(!prep)prep=dw4_filelist_shared(files);
        if(prep)fprintf(stderr,"prepare: %s / %s\n",dw4_filelist_error(files),dw4_scriptengine_error(engine));
        assert(!prep);
        assert(!dw4_filelist_route_assets(files,dw4_stageobjects_route,objects));
        assert(!dw4_filelist_bind_layers(files,dw4_stageobjects_bind_layers,objects));
        dw4_scriptservices *sd=dw4_scriptservices_open();assert(sd);
        context.sd=sd;context.scope=pass+1;context.cancel=pass==3;
        dw4_controllers *controllers=dw4_controllers_open(sd,pass+1,objects,NULL,0,&state.random,&state.action_rhythm,engine);
        assert(controllers && dw4_controllers_count(controllers)==(stage?199:190));
        context.controllers=controllers;
        /* Every authored instance has its own inactive state and native identity. */
        const dw4_stageobject *previous=NULL;int32_t expected_slot=0;
        for(size_t i=0;i<dw4_controllers_count(controllers);i++) {
            const dw4_stageobject *info;int32_t slot;
            const dw4_modelctrl *model=dw4_controllers_model(controllers,i,&info,&slot);
            assert(model && info && slot>=0 && !dw4_modelctrl_active(model));
            if(!previous || !dw4_stageobject_same(info,previous)){previous=info;expected_slot=0;}
            assert(slot==expected_slot++);
        }
        assert(!dw4_controllers_model(controllers,dw4_controllers_count(controllers),NULL,NULL));
        if(pass==1)scene_dependencies(controllers);
        if(pass==3)specialized_dependencies(mount,objects,&state);
        unsigned action_count=0;dw4_controllers_actions(controllers,action_sink,&action_count);
        const char *name=stage?"i_talkwn":"j_startback";
        call(dw4_scriptservices_call,sd,"sd","MODELCTRL",name,"GENERATE",stage?"SQ_OPENL":"SQ_OPEN");
        assert(call(dw4_scriptservices_call,sd,"querySD","MODELCTRL",name,"ISRUN",NULL)==1);
        /* Active-selector bookkeeping updates in the command callback. */
        dw4_script_value selector[]={str("MODELCTRL"),str(name),{DW4_SCRIPT_NUMBER,-2,NULL,0},str("ISRUN")},r={0};char error[256];
        assert(!dw4_scriptservices_call(sd,"querySD",selector,4,&r,error,sizeof error) && r.type==DW4_SCRIPT_NIL);
        assert(!dw4_controllers_tick(controllers,1000000000));
        assert(action_count);dw4_controllers_actions(controllers,NULL,NULL);
        call(dw4_scriptservices_call,sd,"sd","MODELCTRL",name,"REMOVE",NULL);
        assert(call(dw4_scriptservices_call,sd,"querySD","MODELCTRL",name,"ISRUN",NULL)==0);
        assert(!dw4_scriptservices_call(sd,"querySD",selector,4,&r,error,sizeof error) && r.type==DW4_SCRIPT_NUMBER && r.number==0);
        printf("Prepared %s: %zu owned model instances, create/remove and inactive selector passed\n",stages[stage],dw4_controllers_count(controllers));
        if(stage){
            const dw4_stageobject *borrowed_info=dw4_stageobjects_find(objects,"beModelCtrlInfo","i_messwn",0);assert(borrowed_info);
            dw4_modelctrl *peer=dw4_modelctrl_open_info((borrowed_info)->igb,borrowed_info->id);assert(peer);
            /* Existing receiver identities reject accidental duplicate peers. */
            assert(dw4_controllers_external(controllers,objects,"i_messwn",0,peer));
            dw4_modelctrl_close(peer);
            dw4_scriptservices *peer_sd=dw4_scriptservices_open();assert(peer_sd);
            const char *excluded[]={"i_messwn"};
            dw4_controllers *peer_owner=dw4_controllers_open(peer_sd,context.scope,objects,excluded,1,&state.random,&state.action_rhythm,NULL);assert(peer_owner);
            peer=dw4_modelctrl_open_info((borrowed_info)->igb,borrowed_info->id);assert(peer);size_t before=dw4_controllers_count(peer_owner);
            assert(!dw4_controllers_external(peer_owner,objects,"i_messwn",0,peer) && dw4_controllers_count(peer_owner)==before+1);
            assert(dw4_controllers_model(peer_owner,before,NULL,NULL)==peer);
            assert(!dw4_modelctrl_start(peer,"SQ_OPEN"));int64_t clock=dw4_modelctrl_time(peer);
            dw4_controllers_sample(peer_owner,9999999999);assert(!dw4_controllers_tick(peer_owner,9999999999));
            assert(dw4_modelctrl_time(peer)==clock);
            dw4_controllers_close(peer_owner);assert(dw4_modelctrl_active(peer));dw4_modelctrl_close(peer);dw4_scriptservices_close(peer_sd);
            prepared_actor_test(&context,&state);
        }
        assert(!dw4_scriptengine_reset_scene(engine,sd));
        dw4_controllers_close(controllers);dw4_stageobjects_close(objects);dw4_scriptservices_close(sd);
        context.sd=NULL;context.controllers=NULL;
    }
    dw4_filelist_close(files);dw4_scriptengine_close(engine);
}
static void health_oracle(dw4_mount *mount) {
    uint32_t size;const uint8_t *blob=dw4_mount_entry(mount,0,820,&size,NULL);assert(blob);
    dw4_modelctrl *model=dw4_modelctrl_open(blob,size,"n_digilff");assert(model);
    dw4_be_state be;dw4_be_init(&be);
    dw4_scriptengine *engine=dw4_scriptengine_open(&be,NULL,NULL);assert(engine);
    dw4_script_model state={.ram_no=2,.rec_no=-1,.info_name="n_digilff"};
    dw4_modelctrl_script(model,engine,1,&state);
    const int values[]={0,1,99,-3};
    for(unsigned active=0;active<2;active++)for(unsigned generate=0;generate<2;generate++)
        for(unsigned max=0;max<4;max++)for(unsigned hp=0;hp<4;hp++) {
            if(active)assert(!dw4_modelctrl_start(model,"SQ_WAIT02"));
            else dw4_modelctrl_remove(model);
            state.hp=values[hp];state.max_hp=values[max];
            call(dw4_modelctrl_service,model,"sd","MODELCTRL","n_digilff",generate?"GENERATE":"SQ_WAIT02",generate?"SQ_WAIT02":NULL);
            printf("HEALTH %u %u %d %d %d %d\n",active,generate,values[hp],values[max],state.hp,state.max_hp);
        }
    /* Preflight rejects unsupported generation before initialization. */
    state.hp=7;state.max_hp=0;
    dw4_script_value a[]={str("MODELCTRL"),str("n_digilff"),{DW4_SCRIPT_NUMBER,2,NULL,0},str("GENERATE"),str("SQ_FALL")},r={0};char error[256];
    assert(dw4_modelctrl_service(model,"sd",a,5,&r,error,sizeof error));
    assert(state.hp==7 && state.max_hp==0);
    dw4_modelctrl_script(model,NULL,0,NULL);dw4_modelctrl_close(model);dw4_scriptengine_close(engine);
}
static void freeze_test(dw4_mount *mount)
{
    uint32_t size;const uint8_t *blob=dw4_mount_entry(mount,0,820,&size,NULL);assert(blob);
    for(int cycle=0;cycle<32;cycle++){
        dw4_modelctrl *world=dw4_modelctrl_open(blob,size,"i_messwn"),*reference=dw4_modelctrl_open(blob,size,"i_messwn"),*menu=dw4_modelctrl_open(blob,size,"i_talkwn");assert(world && reference && menu);
        int64_t start=(int64_t)cycle*20000000000LL;
        dw4_modelctrl_remove(world);dw4_modelctrl_remove(reference);dw4_modelctrl_remove(menu);
        dw4_modelctrl_sample(world,start);dw4_modelctrl_sample(reference,start);
        assert(!dw4_modelctrl_start(world,"SQ_OPEN") && !dw4_modelctrl_start(reference,"SQ_OPEN"));
        int64_t at=start+100000000;assert(!dw4_modelctrl_tick(world,at) && !dw4_modelctrl_tick(reference,at));
        int64_t time=dw4_modelctrl_time(world);const char *sequence=dw4_modelctrl_sequence(world);
        call(dw4_modelctrl_service,world,"sd","MODELCTRL","i_messwn","ONFREEZE",NULL);assert(dw4_modelctrl_frozen(world));
        /* An inactive slot is unaffected and can create a live menu while the
         * already generated world instance is frozen. */
        dw4_modelctrl_sample(menu,at);call(dw4_modelctrl_service,menu,"sd","MODELCTRL","i_talkwn","ONFREEZE",NULL);
        assert(!dw4_modelctrl_frozen(menu));assert(!dw4_modelctrl_start(menu,"SQ_OPENL"));
        for(int frame=1;frame<=120;frame++){
            int64_t now=at+(int64_t)frame*16666667;
            dw4_modelctrl_sample(world,now);assert(!dw4_modelctrl_tick(world,now));
            assert(dw4_modelctrl_time(world)==time && !strcmp(dw4_modelctrl_sequence(world),sequence));
            assert(call(dw4_modelctrl_service,world,"querySD","MODELCTRL","i_messwn","ISRUN",NULL)==1);
            assert(!dw4_modelctrl_tick(menu,now));
        }
        assert(!strcmp(dw4_modelctrl_sequence(menu),"SQ_WAITL"));
        call(dw4_modelctrl_service,world,"sd","MODELCTRL","i_messwn","OFFREEZE",NULL);assert(!dw4_modelctrl_frozen(world));
        for(int frame=1;frame<=120;frame++){
            assert(!dw4_modelctrl_tick(world,at+120LL*16666667+(int64_t)frame*16666667));
            assert(!dw4_modelctrl_tick(reference,at+(int64_t)frame*16666667));
            assert(dw4_modelctrl_time(world)==dw4_modelctrl_time(reference));
            assert(!strcmp(dw4_modelctrl_sequence(world),dw4_modelctrl_sequence(reference)));
        }
        dw4_modelctrl_close(world);dw4_modelctrl_close(reference);dw4_modelctrl_close(menu);
    }
}
static void freeze_oracle(dw4_mount *mount)
{
    uint32_t size;const uint8_t *blob=dw4_mount_entry(mount,0,820,&size,NULL);assert(blob);
    for(int active=0;active<2;active++)for(int initial=0;initial<2;initial++)for(int on=0;on<2;on++){
        dw4_modelctrl *m=dw4_modelctrl_open(blob,size,"i_messwn");assert(m);dw4_modelctrl_sample(m,1000000000);
        if(active)assert(!dw4_modelctrl_start(m,"SQ_OPEN"));
        if(initial)call(dw4_modelctrl_service,m,"sd","MODELCTRL","i_messwn","ONFREEZE",NULL);
        call(dw4_modelctrl_service,m,"sd","MODELCTRL","i_messwn",on?"ONFREEZE":"OFFREEZE",NULL);
        printf("FREEZE %d %d %d %d\n",active,initial,on,dw4_modelctrl_frozen(m));dw4_modelctrl_close(m);
    }
}
static void model_fade_test(dw4_mount *mount)
{
    uint32_t size;const uint8_t *blob=dw4_mount_entry(mount,0,820,&size,NULL);assert(blob);
    dw4_modelctrl *m=dw4_modelctrl_open(blob,size,"i_fadewn01");assert(m);dw4_modelctrl_sample(m,0);
    assert(!dw4_modelctrl_start(m,"SQ_BLOUT30") && dw4_modelctrl_alpha(m)==0);
    for(int i=0;i<15;i++)assert(!dw4_modelctrl_tick(m,(int64_t)i*16666667));
    float alpha=dw4_modelctrl_alpha(m);assert(alpha>.45f && alpha<.55f);
    for(int i=0;i<32;i++)assert(dw4_modelctrl_alpha(m)==alpha);
    call(dw4_modelctrl_service,m,"sd","MODELCTRL","i_fadewn01","ONFREEZE",NULL);
    for(int i=15;i<75;i++){dw4_modelctrl_sample(m,(int64_t)i*16666667);assert(!dw4_modelctrl_tick(m,(int64_t)i*16666667) && dw4_modelctrl_alpha(m)==alpha);}
    call(dw4_modelctrl_service,m,"sd","MODELCTRL","i_fadewn01","OFFREEZE",NULL);
    for(int i=75;i<95;i++)assert(!dw4_modelctrl_tick(m,(int64_t)i*16666667));
    assert(dw4_modelctrl_alpha(m)==1);
    assert(!dw4_modelctrl_start(m,"SQ_BLIN30") && dw4_modelctrl_alpha(m)==1);
    for(int i=95;i<135;i++)assert(!dw4_modelctrl_tick(m,(int64_t)i*16666667));
    assert(dw4_modelctrl_alpha(m)==0);
    dw4_modelctrl_remove(m);assert(!dw4_modelctrl_drawable(m) && dw4_modelctrl_alpha(m)==0);dw4_modelctrl_close(m);
}
int main(int argc,char **argv)
{
    dw4_mount mount;assert((argc==2 || argc==3) && !dw4_mount_open(&mount,argv[1]));
    if(argc==3 && !strcmp(argv[2],"--freeze")){freeze_oracle(&mount);dw4_mount_close(&mount);return 0;}
    if(argc==3) {assert(!strcmp(argv[2],"--health"));health_oracle(&mount);dw4_mount_close(&mount);return 0;}
    model_test(&mount,1,620,"j_startback","SQ_OPEN","SQ_WAIT",NULL);
    model_test(&mount,1,620,"j_startlogo","SQ_OPEN","SQ_WAIT","SQ_CLOSE");
    model_test(&mount,0,820,"i_messwn","SQ_OPEN","SQ_WAIT","SQ_CLOSE");
    model_test(&mount,0,820,"i_talkwn","SQ_OPENL","SQ_WAITL","SQ_CLOSEL");
    model_test(&mount,0,820,"n_digilffic","SQ_OPENL","SQ_WAITL","SQ_CLOSEL");
    model_test(&mount,0,820,"i_talkky","SQ_OPEN","SQ_LINESL00",NULL);
    model_fade_test(&mount);freeze_test(&mount);window_test(&mount);camera_test(&mount);prepared_test(&mount);
    dw4_mount_close(&mount);puts("Controller services: original model programs and live window/camera state passed");return 0;
}
