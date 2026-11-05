#include "dw4/modelsubcom.h"
#include "arenalist.h"
#include "eefloat.h"
static beModelCtrlSubCom *subcom(dw4_arena *a,dw4_handle h)
{return h.off?DW4_ARENA_OBJ(a,beModelCtrlSubCom,h):NULL;}
int dw4_modelsubcom_type(dw4_arena *a,dw4_handle h)
{
    const char *types[]={"beModelCtrlSCHitBox","beModelCtrlSCEffect","beModelCtrlSCSound"};
    for(int i=0;i<3;i++)if(dw4_arena_object_is(a,h,dw4_metaobject_find(types[i])->vtable))return i+1;
    return 0;
}
static void drop(dw4_arena *a,dw4_handle h)
{
    int type=dw4_modelsubcom_type(a,h);
    /* These aggregate owners release their strings before the object header. */
    if(dw4_arena_object_refcount(a,h)==1 && type==DW4_SC_EFFECT){beModelCtrlSCEffect *e=DW4_ARENA_OBJ(a,beModelCtrlSCEffect,h);
        al_free(a,e->_modelName);al_free(a,e->_seqName);e->_modelName=e->_seqName=0;}
    if(dw4_arena_object_refcount(a,h)==1 && type==DW4_SC_SOUND){beModelCtrlSCSound *s=DW4_ARENA_OBJ(a,beModelCtrlSCSound,h);al_free(a,s->_sndName);s->_sndName=0;}
    dw4_arena_object_release(a,h);
}
static int append(dw4_arena *a,dw4_handle h,dw4_handle child)
{
    beModelCtrlSubCom *s=subcom(a,h);if(!s)return -1;
    igDataList *l=al_list(a,s->_comList);
    if(al_reserve(a,s->_comList,4,l->_count+1))return -1;
    int32_t *v=dw4_arena_at(a,al_handle(l->_data),(uint32_t)l->_capacity*4);
    v[l->_count++]=(int32_t)child.off;return 0;
}
int dw4_modelsubcom_effect(dw4_arena *a,dw4_handle h,const char *model,const char *seq,
    uint32_t start,const float offset[3],const float rotation[3],uint8_t dead,uint8_t follow)
{
    if(!subcom(a,h) || !model || !seq || !offset || !rotation)return -1;
    dw4_handle c=dw4_arena_object_new(a,DW4_REGION_PERSISTENT,dw4_metaobject_find("beModelCtrlSCEffect")->vtable);
    if(!c.off)return -1;
    beModelCtrlSCEffect *e=DW4_ARENA_OBJ(a,beModelCtrlSCEffect,c);
    e->_modelName=al_string(a,model);e->_seqName=al_string(a,seq);e->_geneRamNo=-1;
    memcpy(&e->_startFrame,&start,4);memcpy(e->_offset,offset,12);memcpy(e->_rotation,rotation,12);
    e->_isSeqDead=dead;e->_isPositionLock=follow;
    if(!e->_modelName || !e->_seqName || append(a,h,c)){drop(a,c);return -1;}return 0;
}
int dw4_modelsubcom_sound(dw4_arena *a,dw4_handle h,const char *name,uint32_t start)
{
    if(!subcom(a,h) || !name)return -1;
    dw4_handle c=dw4_arena_object_new(a,DW4_REGION_PERSISTENT,dw4_metaobject_find("beModelCtrlSCSound")->vtable);
    if(!c.off)return -1;
    beModelCtrlSCSound *s=DW4_ARENA_OBJ(a,beModelCtrlSCSound,c);
    s->_sndName=al_string(a,name);memcpy(&s->_startFrame,&start,4);
    if(!s->_sndName || append(a,h,c)){drop(a,c);return -1;}return 0;
}
int dw4_modelsubcom_sound_result(dw4_arena *a,dw4_handle h,int64_t handle,int type)
{
    if(handle==-1 || !handle || type!=4)return 0;
    DW4_ARENA_OBJ(a,beModelCtrlSCSound,h)->_sndHandle=handle;return 1;
}
dw4_handle dw4_modelsubcom_new(dw4_arena *a)
{
    const dw4_metaobject *mo=dw4_metaobject_find("beModelCtrlSubCom");
    dw4_handle h=dw4_arena_object_new(a,DW4_REGION_PERSISTENT,mo->vtable);
    if(h.off){beModelCtrlSubCom *s=subcom(a,h);s->_comList=al_new(a,"igObjectList",4,0,NULL);
        if(!s->_comList){dw4_arena_object_release(a,h);h.off=0;}}
    return h;
}
void dw4_modelsubcom_clear(dw4_arena *a,dw4_handle h)
{
    beModelCtrlSubCom *s=subcom(a,h);if(!s)return;
    igObjectList *l=DW4_ARENA_OBJ(a,igObjectList,al_handle(s->_comList));
    int32_t *v=al_words(a,s->_comList);
    for(int i=0;i<l->_count;i++){if(v[i])drop(a,al_handle(v[i]));v[i]=0;}
    l->_count=0;
}
void dw4_modelsubcom_close(dw4_arena *a,dw4_handle h)
{
    beModelCtrlSubCom *s=subcom(a,h);if(!s)return;
    dw4_modelsubcom_clear(a,h);al_drop(a,&s->_comList);dw4_arena_object_release(a,h);
}
int dw4_modelsubcom_hitbox(dw4_arena *a,dw4_handle h,int32_t kind,
    uint32_t start,uint32_t length,const float offset[3],const float size[3])
{
    beModelCtrlSubCom *s=subcom(a,h);if(!s || !offset || !size)return -1;
    igObjectList *l=DW4_ARENA_OBJ(a,igObjectList,al_handle(s->_comList));
    if(al_reserve(a,s->_comList,4,l->_count+1))return -1;
    const dw4_metaobject *mo=dw4_metaobject_find("beModelCtrlSCHitBox");
    dw4_handle child=dw4_arena_object_new(a,DW4_REGION_PERSISTENT,mo->vtable);if(!child.off)return -1;
    beModelCtrlSCHitBox *b=DW4_ARENA_OBJ(a,beModelCtrlSCHitBox,child);
    memcpy(&b->_startFrame,&start,4);
    uint32_t end=length==0xbf800000?0x4cbebc20:ee_f32_add(start,length);
    memcpy(&b->_endFrame,&end,4);b->_kind=kind;
    /* 39a500 divides the signed kind before the receiver-group switch. */
    switch(kind/10000){case 0:b->_bulletMode=kind<1000?0:2;break;
        case 6:b->_bulletMode=1;break;case 7:case 8:b->_bulletMode=2;break;
        default:b->_bulletMode=0;break;}
    memcpy(b->_offset,offset,12);memcpy(b->_boxSize,size,12);
    int32_t *v=dw4_arena_at(a,al_handle(l->_data),(uint32_t)l->_capacity*4);
    v[l->_count++]=(int32_t)child.off;return 0;
}

uint32_t dw4_modelsubcom_frame(int64_t previous,int64_t now)
{
    int64_t elapsed=(int64_t)((uint64_t)now-(uint64_t)previous);
    double wide=(double)elapsed;float converted=(float)wide;uint32_t value;memcpy(&value,&converted,4);
    return ee_f32_div(value,0x4b7e502b);
}
/* 399d90 -> SCHitBox slots 21/22 (3993e0/3998f0), then 399e20 removal.
 * The first start crossing emits even beyond end; only later updates test end. */
int dw4_modelsubcom_step_events(dw4_arena *a,dw4_handle h,uint32_t frame,
    dw4_modelsubcom_event emit,void *user)
{
    beModelCtrlSubCom *s=subcom(a,h);if(!s)return -1;
    igObjectList *l=DW4_ARENA_OBJ(a,igObjectList,al_handle(s->_comList));
    int n=l->_count;
    for(int i=0;i<n && i<l->_count;i++){
        int32_t *v=al_words(a,s->_comList);dw4_handle child=al_handle(v[i]);
        int type=dw4_modelsubcom_type(a,child);if(!type)return -1;
        /* All three derive the same 20-byte base; copy the common payload
         * without aliasing a smaller sound object as a HITBOX. */
        unsigned char *base=dw4_arena_at(a,child,20);
        uint32_t run,start;memcpy(&run,base+12,4);memcpy(&start,base+16,4);
        run=ee_f32_add(run,frame);memcpy(base+12,&run,4);
        int pulse=0,keep=1;
        if(!base[8]){if(ee_f32_cmp(run,start)>=0){base[8]=1;pulse=1;}}
        else if(type==DW4_SC_HITBOX){
            beModelCtrlSCHitBox *b=DW4_ARENA_OBJ(a,beModelCtrlSCHitBox,child);uint32_t end;memcpy(&end,&b->_endFrame,4);
            if(ee_f32_cmp(run,end)<0)pulse=1;else keep=0;
        } /* Effect/sound inherit 36f8b0: subsequent update always returns 1. */
        if(pulse && emit){
            if(dw4_arena_object_addref(a,child)<0)return -1;
            int rc=emit(user,child,0,&keep);drop(a,child);
            if(rc)return rc<0?-1:0;
            /* Native callback guard: replacing/clearing this source invalidates
             * the current traversal, never visits freshly appended commands. */
            v=al_words(a,s->_comList);if(i>=l->_count || v[i]!=(int32_t)child.off)return 0;
        }
        if(!keep){
            drop(a,child);
            v=al_words(a,s->_comList);memmove(v+i,v+i+1,(size_t)(l->_count-i-1)*4);
            v[--l->_count]=0;i--;n--;
        }
    }
    return 0;
}
struct hit_adapter {dw4_arena *arena;dw4_modelsubcom_emit emit;void *user;};
static int hit_event(void *u,dw4_handle h,int finish,int *keep)
{struct hit_adapter *v=u;(void)finish;(void)keep;
    if(dw4_modelsubcom_type(v->arena,h)!=DW4_SC_HITBOX)return -1;
    return v->emit?v->emit(v->user,h):0;}
int dw4_modelsubcom_step(dw4_arena *a,dw4_handle h,uint32_t frame,dw4_modelsubcom_emit emit,void *u)
{struct hit_adapter v={a,emit,u};return dw4_modelsubcom_step_events(a,h,frame,hit_event,&v);}
int dw4_modelsubcom_clear_events(dw4_arena *a,dw4_handle h,int type,dw4_modelsubcom_event event,void *u)
{
    beModelCtrlSubCom *s=subcom(a,h);if(!s)return -1;
    igDataList *l=al_list(a,s->_comList);int rc=0;
    /* Callbacks may operate on other models; clearing this list recursively
     * or destroying its owner during finish is outside the service contract. */
    for(int i=0;i<l->_count;i++){
        dw4_handle c=al_handle(al_words(a,s->_comList)[i]);int kind=dw4_modelsubcom_type(a,c);
        if(type==DW4_SC_DEPENDENCIES){if(kind!=DW4_SC_EFFECT && kind!=DW4_SC_SOUND)continue;}
        else if(type && type!=kind)continue;
        int finish=1,keep=1;
        if(!type && kind==DW4_SC_EFFECT)finish=DW4_ARENA_OBJ(a,beModelCtrlSCEffect,c)->_isSeqDead!=0;
        if(finish && event){dw4_arena_object_addref(a,c);int result=event(u,c,1,&keep);drop(a,c);if(result<0)rc=-1;}
        if(type){
            drop(a,c);int32_t *v=al_words(a,s->_comList);
            memmove(v+i,v+i+1,(size_t)(l->_count-i-1)*4);v[--l->_count]=0;i--;
        }
    }
    if(type)return rc;
    for(int i=0;i<l->_count;i++){
        int32_t *v=al_words(a,s->_comList);dw4_handle c=al_handle(v[i]);
        if(type && dw4_modelsubcom_type(a,c)!=type)continue;
        drop(a,c);v=al_words(a,s->_comList);memmove(v+i,v+i+1,(size_t)(l->_count-i-1)*4);v[--l->_count]=0;i--;
    }
    return rc;
}
