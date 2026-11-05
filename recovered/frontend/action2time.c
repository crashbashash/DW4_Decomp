#include "action2time.h"
#define P(a)      api->base.peek(api->base.user,(a),4)
#define PB(a)     ((uint8_t)api->base.peek(api->base.user,(a),1))
#define W(a,v)    api->base.poke(api->base.user,(a),4,(v))
#define WB(a,v)   api->base.poke(api->base.user,(a),1,(v))
#define CALL(a,...) api->base.call(api->base.user,(a),(const int32_t[8]){__VA_ARGS__})
#define CALL64(a,...) api->call64(api->base.user,(a),(const int64_t[8]){__VA_ARGS__})
#define RELEASE_MASK 0x7fffffu          /* object reference count: low 23 bits */

static int64_t rd64(const Dw4Action2Api *api,int32_t a)
{
    return (int64_t)((uint64_t)(uint32_t)P(a)|(uint64_t)(uint32_t)P(a+4)<<32);
}
static void wr64(const Dw4Action2Api *api,int32_t a,int64_t v)
{
    W(a,(int32_t)(uint32_t)(uint64_t)v);
    W(a+4,(int32_t)(uint32_t)((uint64_t)v>>32));
}
/* ref->refs -= 1, destroy at zero (0x002ff820); null is ignored. */
static void drop(const Dw4Action2Api *api,int32_t obj)
{
    if(!obj)return;
    W(obj+4,(int32_t)((uint32_t)P(obj+4)-1u));
    if(!((uint32_t)P(obj+4)&RELEASE_MASK))CALL(0x2ff820,obj);
}
static int64_t system_clock(const Dw4Action2Api *api,int32_t sys){return rd64(api,sys+0x50);}

int64_t a2_f32_to_s64(ee_f32 f){return ee_f32_to_s64(f);}

/* 0x00398e80: nanoseconds, evaluated at 2^18 ns granularity. */
int64_t a2_node_time(const Dw4Action2Api *api,int32_t node,int64_t clock)
{
    ee_f32 f=ee_f32_mul(ee_f32_from_clock_ticks(clock),(ee_f32)P(node+A2_N_SCALE));
    return (int64_t)(((uint64_t)ee_f32_to_s64(f)<<18)+(uint64_t)rd64(api,node+A2_N_BIAS));
}

/* Lazily create act+0x28 (the property list): 0x003a7e90's prologue and the
 * identical blocks in 0x003a7a20/0x003a7d80/0x003a7fd0. */
static void ensure_list(const Dw4Action2Api *api,int32_t act)
{
    int32_t pool,list,old;
    if(P(act+0x28))return;
    pool=CALL(0x301000,act);
    if(!(uint8_t)api->base.peek(api->base.user,A2_GP_FLAG,1))
        pool=CALL(0x2f88e0,P(A2_POOL_ROOT));
    list=CALL(0x36ae80,pool);
    if(list)W(list+4,(int32_t)((uint32_t)P(list+4)+1u));
    old=P(act+0x28);
    drop(api,old);
    W(act+0x28,list);
    drop(api,list);
}
static int32_t find_timer(const Dw4Action2Api *api,int32_t act,int32_t name)
{
    return CALL(0x3022c0,P(act+0x28),P(A2_PROP_TYPE),name);
}

void a2_timer_start(const Dw4Action2Api *api,int32_t act,int32_t name,int64_t duration)
{
    int32_t t,pool,clk_owner;
    int64_t clock;
    ensure_list(api,act);
    t=find_timer(api,act,name);
    if(!t){
        pool=CALL(0x301000,act);
        if(!(uint8_t)api->base.peek(api->base.user,A2_GP_FLAG,1))
            pool=CALL(0x2f88e0,P(A2_POOL_ROOT));
        t=CALL(0x36a510,pool);
        CALL(0x2fecb0,t,name);
        ensure_list(api,act);
        CALL(0x301e30,P(act+0x28),t);
        drop(api,t);
    }
    clk_owner=P(P(act+0x10)+0xc);
    clock=system_clock(api,clk_owner);
    {
        ee_f32 f=ee_f32_mul(ee_f32_from_clock_ticks(clock),(ee_f32)P(t+A2_T_SCALE));
        int64_t ticks=(int64_t)((uint64_t)ee_f32_to_s64(f)<<18);
        wr64(api,t+A2_T_BASE,(int64_t)((uint64_t)0-(uint64_t)ticks));
    }
    wr64(api,t+A2_T_START,clock);
    W(t+A2_T_ONE,0x3f800000);
    wr64(api,t+A2_T_DURATION,duration);
}

int32_t a2_ref_release(const Dw4Action2Api *api,int32_t ref,int32_t flags)
{
    if(ref){
        drop(api,P(ref));
        if((int16_t)flags>0)CALL(0x100610,ref);
    }
    return ref;
}

int32_t a2_timer_exists(const Dw4Action2Api *api,int32_t act,int32_t name)
{
    ensure_list(api,act);
    return find_timer(api,act,name)!=0;
}

int64_t a2_timer_elapsed(const Dw4Action2Api *api,int32_t act,int32_t name)
{
    int32_t t;
    int64_t clock;
    ee_f32 f;
    ensure_list(api,act);
    t=find_timer(api,act,name);
    clock=system_clock(api,P(P(act+0x10)+0xc));
    f=ee_f32_mul(ee_f32_from_clock_ticks(clock),(ee_f32)P(t+A2_T_SCALE));
    return (int64_t)(((uint64_t)ee_f32_to_s64(f)<<18)+(uint64_t)rd64(api,t+A2_T_BASE));
}

/* Strict: a timer of duration D is complete once D < elapsed.  A missing
 * timer reads as complete. */
int32_t a2_timer_complete(const Dw4Action2Api *api,int32_t act,int32_t name)
{
    int32_t t;
    int64_t duration;
    ensure_list(api,act);
    t=find_timer(api,act,name);
    if(!t)return 1;
    duration=rd64(api,t+A2_T_DURATION);
    return duration<a2_timer_elapsed(api,act,name);
}

void a2_waitcheck_update(const Dw4Action2Api *api,int32_t mgr,int32_t act)
{
    int32_t work=P(act+0x38);
    switch(P(work+A2_W_WAIT)){
    case A2_WAIT_JOINT:
        if(PB(work+A2_W_JISEND)){
            W(work+A2_W_WAIT,0);
            a2_start_components(api,mgr,act);
        }
        break;
    case A2_WAIT_FRAME:
        if(a2_timer_complete(api,act,A2_TIMER_NAME)){
            W(work+A2_W_WAIT,0);
            a2_start_components(api,mgr,act);
        }
        break;
    case A2_WAIT_MOTION: {
        int32_t data=P(act+0xc),list=P(P(data+0x20)+0x24);
        int32_t elem=P(P(list+0x10)+(int32_t)((uint32_t)P(act+8)*4u)),w2=P(elem+0x38),m,q;
        int64_t cur,end;
        if(P(w2+8)!=1)break;
        m=P(P(w2+0x10));
        q=P(m+8);
        end=rd64(api,q+0x30);
        if(end){
            int64_t a0=(int64_t)((uint64_t)rd64(api,m+0x28)-(uint64_t)rd64(api,q+0x20)-(uint64_t)rd64(api,q+0x28));
            CALL64(0x1dd4b0,a0,end,A2_SCRATCH);
        }
        CALL64(0x1af510,m,a2_node_time(api,P(act+0x2c),system_clock(api,P(mgr+0xc))));
        cur=rd64(api,m+0x28);
        if((uint64_t)cur<(uint64_t)end)break;
        W(work+A2_W_WAIT,0);
        a2_start_components(api,mgr,act);
        break;
    }
    default:
        break;
    }
}

int32_t a2_waitcheck_start(const Dw4Action2Api *api,int32_t mgr,int32_t act,int32_t comp)
{
    int32_t work=P(act+0x38),name=P(comp+8),text=name?name:A2_STR_EMPTY;
    ee_f32 secs=(ee_f32)P(comp+0xc);
    int c=(int8_t)api->base.peek(api->base.user,text,1);
    if(c=='J'){W(work+A2_W_WAIT,A2_WAIT_JOINT);return 0;}
    if(c=='M'){W(work+A2_W_WAIT,A2_WAIT_MOTION);return 0;}
    if(c=='R'){
        int32_t obj,rem,divisor;
        ee_f32 g,acc,span;
        if((int8_t)api->base.peek(api->base.user,text+3,1)=='S'){
            W(A2_RHYTHM_GLOBAL,(int32_t)secs);
            return 1;
        }
        g=(ee_f32)P(A2_RHYTHM_GLOBAL);
        acc=ee_f32_mul(0x42c80000u,secs);
        span=ee_f32_sub(acc,ee_f32_mul(0x42c80000u,g));
        obj=P(P(mgr+0x10)+0x30);
        divisor=ee_f32_trunc_s32(span);
        rem=CALL(P(P(obj)+0x60),obj);
        /* divu: remainder, or the dividend when the divisor is zero. */
        rem=divisor?(int32_t)((uint32_t)rem%(uint32_t)divisor):rem;
        secs=ee_f32_add((ee_f32)P(A2_RHYTHM_GLOBAL),
                        ee_f32_div(ee_f32_from_u32((uint32_t)rem),0x42c80000u));
        c='F';
    }
    if(c=='F'){
        int64_t ns=ee_f32_to_s64(ee_f32_div(ee_f32_mul(0x4e6e6b28u,secs),0x42700000u));
        a2_timer_start(api,act,A2_TIMER_NAME,ns);
        W(work+A2_W_WAIT,A2_WAIT_FRAME);
    }
    return 0;
}

void a2_jointset_update(const Dw4Action2Api *api,int32_t mgr,int32_t act)
{
    int32_t work=P(act+0x38),node;
    int64_t now,end,clock;
    int changed=0,state=P(work+A2_W_JOINT);
    if(state!=1&&state!=2)return;
    now=a2_node_time(api,P(act+0x2c),system_clock(api,P(mgr+0xc)));
    end=rd64(api,work+A2_W_JEND);
    /* Strict: nothing happens until end < now. */
    while(end<now){
        state=P(work+A2_W_JOINT);
        if(state==2){now=end;changed=1;}
        else if(state==1){
            now=(int64_t)((uint64_t)now+(uint64_t)rd64(api,work+A2_W_JSTART)-(uint64_t)end);
            changed=1;
        }else break;
    }
    if(!changed)return;
    clock=system_clock(api,P(mgr+0xc));
    node=P(act+0x2c);
    {
        ee_f32 f=ee_f32_mul(ee_f32_from_clock_ticks(clock),(ee_f32)P(node+A2_N_SCALE));
        int64_t ticks=(int64_t)((uint64_t)ee_f32_to_s64(f)<<18);
        wr64(api,node+A2_N_BIAS,(int64_t)((uint64_t)now-(uint64_t)ticks));
    }
    WB(work+A2_W_JISEND,1);
}

int32_t a2_jointset_start(const Dw4Action2Api *api,int32_t mgr,int32_t act,int32_t comp)
{
    int32_t work=P(act+0x38),node;
    int64_t clock,start;
    W(work+A2_W_JOINT,(int8_t)api->base.peek(api->base.user,P(comp+0x14),1)=='L'?1:2);
    wr64(api,work+A2_W_JSTART,ee_f32_to_s64(ee_f32_div(ee_f32_mul(0x4e6e6b28u,(ee_f32)P(comp+0xc)),0x42700000u)));
    wr64(api,work+A2_W_JEND,ee_f32_to_s64(ee_f32_div(ee_f32_mul(0x4e6e6b28u,(ee_f32)P(comp+0x10)),0x42700000u)));
    clock=system_clock(api,P(mgr+0xc));
    node=P(act+0x2c);
    start=rd64(api,work+A2_W_JSTART);
    {
        ee_f32 f=ee_f32_mul(ee_f32_from_clock_ticks(clock),(ee_f32)P(node+A2_N_SCALE));
        int64_t ticks=(int64_t)((uint64_t)ee_f32_to_s64(f)<<18);
        wr64(api,node+A2_N_BIAS,(int64_t)((uint64_t)start-(uint64_t)ticks));
    }
    WB(work+A2_W_JISEND,0);
    return 1;
}

/* Walk the component list from work._comIndex.  A handler's low byte of
 * return value decides whether to continue.  Retail spins forever on a
 * component of unknown class (the index never advances); this reference stops
 * there instead. */
void a2_start_components(const Dw4Action2Api *api,int32_t mgr,int32_t act)
{
    int32_t work=P(act+0x38),data=P(work+A2_W_COMDATA),idx=P(work+A2_W_COMINDEX);
    int32_t cont=1;
    if(idx!=P(P(data+0xc)+8)){
        do{
            int32_t comp=P(P(P(data+0xc)+0x10)+(int32_t)((uint32_t)idx*4u)),r;
            if(CALL(P(P(comp)+0x58),comp)==P(A2_CLASS_MOTIONSET))r=CALL(0x377340,mgr,act,comp);
            else if(CALL(P(P(comp)+0x58),comp)==P(A2_CLASS_JOINTSET))r=a2_jointset_start(api,mgr,act,comp);
            else if(CALL(P(P(comp)+0x58),comp)==P(A2_CLASS_FADESET))r=CALL(0x376930,mgr,act,comp);
            else if(CALL(P(P(comp)+0x58),comp)==P(A2_CLASS_WAITCHECK))r=a2_waitcheck_start(api,mgr,act,comp);
            else if(CALL(P(P(comp)+0x58),comp)==P(A2_CLASS_FLASHSET))r=CALL(0x375ff0,mgr,act,comp);
            else break;
            cont=r&0xff;
            ++idx;
        }while(cont&&idx!=P(P(data+0xc)+8));
    }
    W(work+A2_W_COMINDEX,idx);
}

/* Gap::Bec::beAction2::vfunc_31: one call per frame while the action is
 * active and not frozen.  The component Update handlers run in this order. */
void a2_update(const Dw4Action2Api *api,int32_t mgr,int32_t act)
{
    int32_t work;
    if(!PB(act+0x14))return;
    work=P(act+0x38);
    if(PB(work+A2_W_FREEZE))return;
    if(P(work+A2_W_MOTION))CALL(0x377090,mgr,act);
    if(P(work+A2_W_JOINT))a2_jointset_update(api,mgr,act);
    if(P(work+A2_W_FADE))CALL(0x376680,mgr,act);
    if(P(work+A2_W_WAIT))a2_waitcheck_update(api,mgr,act);
    if(P(work+A2_W_FLASH))CALL(0x375e70,mgr,act);
}

/* vfunc_33 (0x00377990), message case 0: "ISCOMEND" is true when every
 * component has started and no WAITCHECK is pending.  Returns the handler's
 * return value (1), or -1 when the message resolved to a case not recovered
 * here (the other cases are outside this slice). */
int32_t a2_msg_iscomend(const Dw4Action2Api *api,int32_t mgr,int32_t act,int32_t msg)
{
    int32_t work=P(act+0x38),tmp=work,c,v,data,index,wait,count;
    int32_t result=1;
    if(tmp)W(tmp+4,(int32_t)((uint32_t)P(tmp+4)+1u));
    v=CALL(0x36dcd0,mgr);
    c=CALL(0x38d4a0,P(mgr+0x14),v,msg);
    if((uint32_t)c!=0)result=-1;
    else{
        data=P(work+A2_W_COMDATA);
        index=P(work+A2_W_COMINDEX);
        wait=P(work+A2_W_WAIT);
        count=P(P(data+0xc)+8);
        CALL(0x38f150,P(mgr+0x14),!wait&&index==count);
    }
    drop(api,tmp);
    return result;
}
