#include "commdl.h"
#define P(a) api->peek(api->user,(a),4)
#define W(a,v) api->poke(api->user,(a),4,(v))
#define CALL(addr,...) api->call(api->user,(addr),(const int32_t[8]){__VA_ARGS__})
static void release(const Dw4LoadIntf2Api *api, int32_t obj)
{
    if (!obj) return;
    W(obj+4,(int32_t)((uint32_t)P(obj+4)-1u));
    if (!(P(obj+4)&0x7fffff)) CALL(0x2ff820,obj);
}
static void assign(const Dw4LoadIntf2Api *api, int32_t field, int32_t token)
{
    int32_t pool=P(0x586f20), fresh, old, refs;
    if (!pool) {
        pool=CALL(0x2eb010,16);
        if (pool) pool=CALL(0x2eadf0,pool);
        W(0x586f20,pool);
    }
    fresh=CALL(0x2eaf60,P(0x586f20),token);
    old=P(field);
    if (old) {
        refs=(int32_t)((uint32_t)P(old-4)-1u);
        W(old-4,refs);
        if (!refs) CALL(0x30c940,P(old-8),old-8);
    }
    W(field,fresh);
}
static void track(const Dw4LoadIntf2Api *api, int32_t cm, int32_t slot,
                  int32_t name, int32_t seq, int32_t wait, int off)
{
    int32_t allocator, item;
    if ((wait&255)!=1) return;
    allocator=CALL(0x301000,cm);
    if (!api->peek(api->user,0x554c14,1)) allocator=CALL(0x2f88e0,P(0x587110));
    item=CALL(0x3c7450,allocator);
    W(item+8,slot);
    assign(api,item+0x10,name);
    assign(api,item+0xc,seq);
    CALL(0x301e30,P(cm+off),item);
    release(api,item);
}
void cm_start(const Dw4LoadIntf2Api *api,int32_t cm,int32_t slot,int32_t name,int32_t seq,int32_t wait)
{
    CALL(0x38e5f0,P(cm+0x10),CM_MODELCTRL,name,slot,CM_GENERATE);
    cm_play(api,cm,slot,name,seq,wait);
}
int32_t cm_ref_destroy(const Dw4LoadIntf2Api *api,int32_t ref,int32_t flags)
{
    if (ref) {
        release(api,P(ref));
        if ((int16_t)flags>0) CALL(0x100610,ref);
    }
    return ref;
}
void cm_start_at(const Dw4LoadIntf2Api *api,int32_t cm,int32_t slot,int32_t name,int32_t seq,int32_t vec,int32_t wait)
{
    int i;
    CALL(0x38d860,P(cm+0x10),CM_MODELCTRL,name,slot);
    for(i=0;i<12;i+=4) W(CM_SCRATCH+i,P(vec+i));
    CALL(0x38f4b0,P(cm+0x10),CM_SCRATCH);
    CALL(0x38e060,P(cm+0x10),CM_GENERATE);
    cm_play(api,cm,slot,name,seq,wait);
}
void cm_play(const Dw4LoadIntf2Api *api,int32_t cm,int32_t slot,int32_t name,int32_t seq,int32_t wait)
{
    CALL(0x38e5f0,P(cm+0x10),CM_MODELCTRL,name,slot,seq);
    track(api,cm,slot,name,seq,wait,0x14);
}
void cm_close(const Dw4LoadIntf2Api *api,int32_t cm,int32_t slot,int32_t name,int32_t seq,int32_t wait)
{
    CALL(0x38e5f0,P(cm+0x10),CM_MODELCTRL,name,slot,seq);
    track(api,cm,slot,name,seq,wait,0x18);
}
int32_t cm_is_sequence(const Dw4LoadIntf2Api *api,int32_t cm,int32_t slot,int32_t name,int32_t seq)
{
    CALL(0x38d860,P(cm+0x10),CM_MODELCTRL,name,slot);
    CALL(0x38f830,P(cm+0x10),seq);
    CALL(0x38e060,P(cm+0x10),CM_ISSEQNAME);
    return CALL(0x38f220,P(cm+0x10),0);
}
int32_t cm_is_running(const Dw4LoadIntf2Api *api,int32_t cm,int32_t slot,int32_t name)
{
    CALL(0x38e5f0,P(cm+0x10),CM_MODELCTRL,name,slot,CM_ISRUN);
    return CALL(0x38f220,P(cm+0x10),0);
}
void cm_poll(const Dw4LoadIntf2Api *api,int32_t cm)
{
    int off;
    for(off=0x14;off<=0x18;off+=4) {
        int32_t count=P(P(cm+off)+8), i;
        if(count<=0) continue;
        i=count-1;
        for(;i>=0;--i) {
            int32_t list=P(cm+off), item=P(P(list+0x10)+i*4), answer;
            if(off==0x14) answer=cm_is_sequence(api,cm,P(item+8),P(item+0x10),P(item+0xc));
            else answer=cm_is_running(api,cm,P(item+8),P(item+0x10));
            if((answer&255)==1) break;
            list=P(cm+off);
            release(api,P(P(list+0x10)+i*4));
            CALL(0x2d6cf0,list,i);
            W(P(list+0x10)+P(list+8)*4,0);
        }
    }
}
