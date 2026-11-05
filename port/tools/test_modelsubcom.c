#include "dw4/modelctrl.h"
#include "dw4/modelsubcom.h"
#include "dw4/modelai.h"
#include "dw4/mount.h"
#include "../src/arenalist.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
struct sink {int pulses,releases,replace;float world[16];dw4_script_model *transport;};
static void release(void *u){((struct sink *)u)->releases++;}
static int emit(void *u,dw4_modelctrl *m,const dw4_modelctrl_hitbox *event,const float world[16],int64_t ns)
{
    struct sink *s=u;(void)ns;s->pulses++;assert(event->object.off);
    assert(s->transport && s->transport->hp==9 && s->transport->rec_no==42);memcpy(s->world,world,64);
    if(s->replace){s->replace=0;assert(!dw4_modelctrl_start(m,"SQ_WAIT02"));}
    return 0;
}
static beModelCtrlInfoWork *work(dw4_modelctrl *m,dw4_modelctrl_record *r)
{*r=dw4_modelctrl_records(m);return DW4_ARENA_OBJ(r->arena,beModelCtrlInfoWork,r->work);}
static void add(dw4_modelctrl *m,unsigned start,unsigned length)
{
    dw4_modelctrl_record r;beModelCtrlInfoWork *w=work(m,&r);const float offset[3]={0},size[3]={1,1,1};
    assert(!dw4_modelsubcom_hitbox(r.arena,al_handle(w->_subCommand),1,start,length,offset,size));
}
struct dependencies {
    dw4_arena *arena;dw4_handle track;
    int starts,finishes,plays,downs,type,replace,missing,releases,fail_down,reject_rebind,finish_order;
    dw4_modelctrl *model;
    int64_t handle;float matrix[16];
};
static int effect(void *u,dw4_modelctrl *m,dw4_handle h,int finish,int *keep)
{
    struct dependencies *d=u;beModelCtrlSCEffect *e=DW4_ARENA_OBJ(d->arena,beModelCtrlSCEffect,h);
    if(d->reject_rebind)assert(dw4_modelctrl_dependencies_bind(m,NULL)==-1);
    assert(!strcmp(al_text(d->arena,e->_modelName),"effect"));
    assert(e->_offset[0]==0x3f800000 && e->_rotation[2]==0x40400000);
    if(finish){d->finishes++;d->finish_order=d->finish_order*10+1;return 0;}
    d->starts++;e->_geneRamNo=7;*keep=e->_isSeqDead!=0;
    if(d->replace){d->replace=0;assert(!dw4_modelctrl_start(m,"SQ_WAIT02"));
        /* The callback's retain includes its owned strings until return. */
        assert(!strcmp(al_text(d->arena,e->_seqName),"SQ_WAIT"));}
    return 0;
}
static int play(void *u,const char *name,int64_t *handle,int *kind)
{struct dependencies *d=u;assert(!strcmp(name,"sound"));d->plays++;*handle=d->handle;*kind=d->type;return 0;}
static int down(void *u,int64_t handle)
{struct dependencies *d=u;assert(handle==d->handle);d->downs++;d->finish_order=d->finish_order*10+2;return d->fail_down?-1:0;}
static int track(void *u,dw4_modelctrl *m,const char *name,dw4_handle *out)
{struct dependencies *d=u;(void)m;assert(!strcmp(name,"parent"));*out=d->track;return d->missing?0:1;}
static int bone(void *u,dw4_modelctrl *m,const char *name,const char *joint,float out[16])
{struct dependencies *d=u;(void)m;assert(!strcmp(name,"parent") && !strcmp(joint,"joint"));if(d->missing)return 0;memcpy(out,d->matrix,64);return 1;}
static void message(dw4_modelctrl *m,const char *key,const char *text)
{
    char error[256];dw4_script_value result,args[]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{0},
        {DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,key,strlen(key)},{DW4_SCRIPT_STRING,0,text,strlen(text)}};
    int rc=dw4_modelctrl_service(m,"sd",args,5,&result,error,sizeof error);
    if(rc)fprintf(stderr,"%s: %s\n",key,error);
    assert(!rc);
}
static int list_count(dw4_modelctrl *m)
{dw4_modelctrl_record r;beModelCtrlInfoWork *w=work(m,&r);beModelCtrlSubCom *s=DW4_ARENA_OBJ(r.arena,beModelCtrlSubCom,al_handle(w->_subCommand));return al_count(r.arena,s->_comList);}
static void dependency_release(void *u)
{
    struct dependencies *d=u;d->releases++;d->finish_order=d->finish_order*10+3;
    dw4_modelctrl_record r;beModelCtrlInfoWork *w=work(d->model,&r);
    assert(!w->_posLockModelName && !w->_posLockTrc);
    assert(dw4_modelctrl_dependencies_bind(d->model,NULL)==-1);
}
static void dependency_replacement(dw4_modelctrl *m)
{
    dw4_modelctrl_record r;beModelCtrlInfoWork *w=work(m,&r);
    struct dependencies a={.arena=r.arena,.model=m,.handle=27,.type=4,.reject_rebind=1},b={.arena=r.arena,.model=m,.handle=39,.type=4};
    dw4_modelctrl_dependencies da={&a,effect,play,down,bone,track,dependency_release},db={&b,effect,play,down,bone,track,dependency_release};
    assert(!dw4_modelctrl_dependencies_bind(m,&da));
    message(m,"SETSOUND","sound/F<0>");
    message(m,"SETEFFECT","effect/SQ_WAIT/F<0>/V<1,2,3>/V<1,2,3>/TRUE/FALSE");
    assert(!dw4_modelctrl_tick_frame(m,20,0));
    assert(a.starts==1 && a.plays==1);
    message(m,"SETEFFECT","effect/SQ_WAIT/F<100>/V<1,2,3>/V<1,2,3>/TRUE/FALSE");
    message(m,"SETSOUND","sound/F<100>");add(m,0,0x41200000);
    assert(!dw4_modelctrl_relative(m,"BONE","parent","joint"));
    assert(!dw4_modelctrl_dependencies_bind(m,&db));
    assert(a.finishes==1 && a.downs==1 && a.releases==1 && a.finish_order==213 && list_count(m)==1 && !w->_isPosLock);
    assert(dw4_modelctrl_active(m) && !b.finishes && !b.downs);
    assert(!dw4_modelctrl_dependencies_bind(m,&db) && !b.releases);
    assert(!dw4_modelctrl_start(m,"SQ_WAIT02"));
    message(m,"SETSOUND","sound/F<0>");assert(!dw4_modelctrl_tick_frame(m,21,0));
    b.fail_down=1;assert(dw4_modelctrl_dependencies_bind(m,&da)==-1);
    assert(b.downs==1 && b.releases==1 && !list_count(m));
    assert(!dw4_modelctrl_dependencies_bind(m,NULL) && a.releases==1);
    /* Closing a model invokes its service release while records remain valid. */
    dw4_modelctrl *child=dw4_modelctrl_instance(m);assert(child);
    a.model=child;a.reject_rebind=0;assert(!dw4_modelctrl_dependencies_bind(child,&da));
    assert(!dw4_modelctrl_start(child,"SQ_WAIT02"));message(child,"SETSOUND","sound/F<0>");
    assert(!dw4_modelctrl_tick_frame(child,0,0));dw4_modelctrl_close(child);
    assert(a.downs==2 && a.releases==2);
}
static void dependencies_test(dw4_modelctrl *m)
{
    dw4_modelctrl_record r;beModelCtrlInfoWork *w=work(m,&r);
    struct dependencies d={.arena=r.arena,.handle=INT64_C(0x123456789abcdef),.type=4};
    dw4_modelctrl_dependencies dep={&d,effect,play,down,bone,track,NULL};assert(!dw4_modelctrl_dependencies_bind(m,&dep));
    /* First activation can drop a fire-and-forget effect/sound without finish. */
    message(m,"SETEFFECT","effect/SQ_WAIT/F<2>/V<1,2,3>/V<1,2,3>/FALSE/TRUE");
    message(m,"SETSOUND","sound/F<2>");add(m,0,0x41200000);
    assert(!dw4_modelctrl_tick_frame(m,1,0x3f800000));assert(d.starts==0 && d.plays==0);
    unsigned n;dw4_modelctrl_hitboxes(m,&n);assert(n==1 && list_count(m)==3);
    assert(!dw4_modelctrl_tick_frame(m,2,0x3f800000));assert(d.starts==1 && d.plays==1 && list_count(m)==2);
    assert(!dw4_modelsubcom_clear_events(r.arena,al_handle(w->_subCommand),DW4_SC_HITBOX,NULL,NULL));
    assert(list_count(m)==1 && !d.downs);dw4_modelctrl_hitboxes(m,&n);assert(n==0);
    assert(!dw4_modelctrl_tick_frame(m,3,0x41200000));assert(d.plays==1);
    assert(!dw4_modelctrl_start(m,"SQ_WAIT02"));assert(d.downs==1 && d.finishes==0 && !list_count(m));
    /* Ordinary one-shots and failure sentinels never retain a stop handle. */
    for(int i=0;i<3;i++){
        d.type=i?4:3;d.handle=i==1?0:i==2?-1:7;
        message(m,"SETSOUND","sound/F<0>");assert(!dw4_modelctrl_tick_frame(m,4+i,0));assert(!list_count(m));
    }
    /* Sequence-dependent finish, cancellation before start, and callback reentry. */
    message(m,"SETEFFECT","effect/SQ_WAIT/F<100>/V<1,2,3>/V<1,2,3>/TRUE/FALSE");
    assert(!dw4_modelctrl_start(m,"SQ_WAIT02") && d.finishes==0);
    message(m,"SETEFFECT","effect/SQ_WAIT/F<0>/V<1,2,3>/V<1,2,3>/TRUE/FALSE");
    assert(!dw4_modelctrl_tick_frame(m,8,0));assert(list_count(m)==1);
    assert(!dw4_modelctrl_start(m,"SQ_WAIT02") && d.finishes==1);
    message(m,"SETEFFECT","effect/SQ_WAIT/F<0>/V<1,2,3>/V<1,2,3>/FALSE/FALSE");
    d.replace=1;assert(!dw4_modelctrl_tick_frame(m,9,0) && !list_count(m));
    /* JOINT copies recorder._mvm (+96), not its unrelated +32 matrix. */
    d.track=dw4_arena_object_new(r.arena,DW4_REGION_PERSISTENT,dw4_metaobject_find("beModelCtrlInfoDataTrc")->vtable);
    dw4_handle recorder=dw4_arena_object_new(r.arena,DW4_REGION_PERSISTENT,dw4_metaobject_find("igTransformRecorder")->vtable);
    beModelCtrlInfoDataTrc *t=DW4_ARENA_OBJ(r.arena,beModelCtrlInfoDataTrc,d.track);t->_recorderNode=(int32_t)recorder.off;
    for(unsigned i=0;i<16;i++)d.matrix[i]=(float)i;
    memcpy((char *)dw4_arena_at(r.arena,recorder,160)+96,d.matrix,64);
    assert(!dw4_modelctrl_relative(m,"JOINT","parent",NULL));assert(dw4_arena_object_refcount(r.arena,d.track)==2);
    assert(!dw4_modelctrl_tick_frame(m,10,0));float actual[16];dw4_modelctrl_matrix(m,actual);assert(!memcmp(actual,d.matrix,64));
    assert(!dw4_modelctrl_position_lock(m,NULL,NULL));assert(dw4_arena_object_refcount(r.arena,d.track)==1);
    assert(!dw4_modelctrl_relative(m,"BONE","parent","joint"));
    d.matrix[12]=50;assert(!dw4_modelctrl_tick_frame(m,11,0));dw4_modelctrl_matrix(m,actual);assert(!memcmp(actual,d.matrix,64));
    d.missing=1;d.matrix[12]=80;assert(!dw4_modelctrl_tick_frame(m,12,0));dw4_modelctrl_matrix(m,actual);assert(actual[12]==50);
    dw4_modelctrl_remove(m);assert(!w->_isPosLock && !w->_posLockModelName && !w->_posLockTrc);
    dw4_arena_object_release(r.arena,d.track);dw4_arena_object_release(r.arena,recorder);
    dw4_modelctrl_dependencies_bind(m,NULL);assert(!dw4_modelctrl_start(m,"SQ_WAIT02"));
}
int main(int argc,char **argv)
{
    dw4_mount mount={0};assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../local/extracted"));
    uint32_t size;const uint8_t *blob=dw4_mount_entry(&mount,0,820,&size,NULL);assert(blob);
    dw4_arena *a=dw4_session_arena();unsigned baseline=dw4_arena_live(a,DW4_REGION_PERSISTENT);
    for(int repeat=0;repeat<32;repeat++){
        dw4_modelctrl *m=dw4_modelctrl_open(blob,size,"n_digilff");assert(m);
        dw4_modelctrl_sample(m,0);assert(!dw4_modelctrl_start(m,"SQ_WAIT02"));
        dw4_script_model transport={.ram_no=0,.rec_no=4,.hp=5,.max_hp=20,.info_name="n_digilff"};
        dw4_modelctrl_script(m,NULL,0,&transport);
        dw4_modelctrl_record initial;beModelCtrlInfoWork *initial_work=work(m,&initial);
        DW4_ARENA_OBJ(a,beDataObjInt,al_handle(initial_work->_hp))->_data=9;initial_work->_recNo=42;
        dependencies_test(m);
        dependency_replacement(m);
        struct sink sink={.transport=&transport};dw4_modelctrl_hit_sink(m,emit,&sink,release);
        /* First start crossing is unconditional, even when end was crossed. */
        add(m,0x3f800000,0);assert(!dw4_modelctrl_tick_frame(m,1,0x40a00000));assert(sink.pulses==1);
        unsigned n;dw4_modelctrl_hitboxes(m,&n);assert(n==1);
        assert(!dw4_modelctrl_tick_frame(m,2,0));dw4_modelctrl_hitboxes(m,&n);assert(!n && sink.pulses==1);
        add(m,0,0x40000000);
        dw4_modelctrl_record r;beModelCtrlInfoWork *w=work(m,&r);w->_isOnFreeze=1;
        assert(!dw4_modelctrl_tick_frame(m,3,0x41200000) && sink.pulses==1);
        w->_isOnFreeze=0;assert(!dw4_modelctrl_tick_frame(m,4,0x3f800000) && sink.pulses==2);
        for(int i=0;i<8;i++){dw4_modelctrl_hitboxes(m,&n);float matrix[16];dw4_modelctrl_matrix(m,matrix);}
        assert(sink.pulses==2);assert(!dw4_modelctrl_tick_frame(m,4,0) && sink.pulses==3);
        assert(!dw4_modelctrl_tick_frame(m,5,0x3f800000));dw4_modelctrl_hitboxes(m,&n);assert(!n && sink.pulses==3);
        /* A source-sequence change releases the old entry while it is emitted. */
        add(m,0,0x41200000);add(m,0,0x41200000);sink.replace=1;
        assert(!dw4_modelctrl_tick_frame(m,6,0) && sink.pulses==4);
        dw4_modelctrl_hitboxes(m,&n);assert(!n);
        /* Lock follows the retained parent node, including scale/shear and W. */
        dw4_modelctrl *parent=dw4_modelctrl_instance(m);assert(parent);
        dw4_modelctrl_record pr=dw4_modelctrl_records(parent);
        beModelCtrlNode2 *node=DW4_ARENA_OBJ(a,beModelCtrlNode2,pr.node);
        const float matrix[16]={2,0,0,.25f,0,3,0,.5f,1,0,4,.75f,10,20,30,1},offset[3]={1,2,3};
        memcpy(node->_m,matrix,64);assert(!dw4_modelctrl_position_lock(m,parent,offset));
        beModelCtrlMoveObject *move=DW4_ARENA_OBJ(a,beModelCtrlMoveObject,al_handle(al_words(a,w->_moveObjectList)[2]));
        move->_speed=3;move->_isRun=1;
        const char *text="V<7,8,9>/V<0,0,0>";char error[256];dw4_script_value result;
        dw4_script_value args[]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,"n_digilff",9},
            {DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"MOVETRANS",9},{DW4_SCRIPT_STRING,0,text,strlen(text)}};
        assert(!dw4_modelctrl_service(m,"sd",args,5,&result,error,sizeof error));
        float immediate[16];dw4_modelctrl_matrix(m,immediate);assert(immediate[0]==1 && immediate[12]==7 && immediate[13]==8);
        add(m,0,0x40000000);assert(!dw4_modelctrl_tick_frame(m,16666667,0x3f800000));
        float expected[16],actual[16];dw4_model_lock_matrix(expected,matrix,offset);dw4_modelctrl_matrix(m,actual);
        assert(!memcmp(actual,expected,64) && !memcmp(sink.world,expected,64) && move->_speed==3);
        ((float *)(void *)node->_m)[12]=11;
        dw4_modelctrl_close(parent);assert(dw4_arena_object_refcount(a,pr.node)==1);
        assert(!dw4_modelctrl_tick_frame(m,33333334,0x3f800000));dw4_modelctrl_matrix(m,actual);assert(actual[12]==16);
        assert(!dw4_modelctrl_position_lock(m,NULL,NULL));
        assert(dw4_arena_object_refcount(a,pr.node)==-1);
        dw4_modelctrl_remove(m);dw4_modelctrl_hitboxes(m,&n);assert(!n);
        dw4_modelctrl_close(m);assert(sink.releases==1);
        assert(dw4_arena_live(a,DW4_REGION_PERSISTENT)==baseline);
    }
    dw4_mount_close(&mount);
    puts("Model subcommands: synchronous start/end pulses, no query delivery, freeze, replacement, node-lock matrices and retained-parent teardown pass");
    return 0;
}
