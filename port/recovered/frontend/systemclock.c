#include "systemclock.h"
#define R(a,n) api->read(api->user,(uint32_t)(a),(n))
#define W(a,n,v) api->write(api->user,(uint32_t)(a),(n),(uint64_t)(v))
#define CALL(a,x,y) dw4_clock_call(api,(a),(x),(y))
static uint64_t virt(const Dw4SystemClockApi *api, uint32_t object,
                     unsigned slot, uint64_t value)
{
    return CALL((uint32_t)R(R(object,4)+slot,4), object, value);
}
/* Portable arithmetic shift, after multiplication has wrapped to 64 bits. */
static uint64_t sar18(uint64_t v)
{
    return (v >> 18) | ((v >> 63) ? (UINT64_MAX << 46) : 0);
}
static uint64_t sx32(uint64_t v)
{
    v &= UINT64_C(0xffffffff);
    return v & UINT64_C(0x80000000) ? v | UINT64_C(0xffffffff00000000) : v;
}
/* Three seconds-accessor wrappers share this exact software arithmetic chain.
 * These leaves carry double bit patterns in integer registers; do not replace
 * them with host float operations without a separate arithmetic verification. */
static uint64_t seconds(const Dw4SystemClockApi *api, uint64_t ticks)
{
    uint64_t rem = CALL(0x22eb50,ticks,1000000000);
    uint64_t low = CALL(0x22fcc8,rem,0);
    uint64_t billion = CALL(0x230cc8,1000000000,0);
    low = CALL(0x230a18,low,billion);
    rem = CALL(0x22e4b8,ticks,1000000000);
    rem = CALL(0x22fcc8,rem,0);
    return CALL(0x2306d0,rem,low);
}
uint64_t dw4_clock_call(const Dw4SystemClockApi *api, uint32_t entry,
                        uint64_t arg0, uint64_t arg1)
{
    uint32_t self = (uint32_t)arg0, obj, list, count, i;
    uint64_t now, first, second, last, value;
    switch (entry) {
    /* Complete contiguous timer runtime group 0x330a50..0x330e58. */
    case 0x330a50: return seconds(api,virt(api,self,0x60,0));
    case 0x330af0:
        if (R(self+0x20,1)) return R(self+0x10,8);
        now=virt(api,self,0x94,0);
        return R(self+0x10,8)+now-R(self+8,8);
    case 0x330b40: return seconds(api,virt(api,self,0x68,0));
    case 0x330be0: /* resume: only sample on paused -> running */
        if (R(self+0x20,1)) {
            W(self+0x20,1,0);
            now=virt(api,self,0x94,0);
            W(self+8,8,now);
        }
        return 0;
    case 0x330c20: /* pause: capture elapsed before setting flag */
        if (!R(self+0x20,1)) {
            now=virt(api,self,0x94,0);
            W(self+0x10,8,R(self+0x10,8)+now-R(self+8,8));
            W(self+0x20,1,1);
        }
        return 0;
    case 0x330c80: /* reset to preset, preserving paused/running status */
        W(self+0x10,8,R(self+0x18,8));
        if (!R(self+0x20,1)) {
            now=virt(api,self,0x94,0);
            W(self+8,8,now);
        }
        return 0;
    case 0x330cd0: /* stop and reset */
        W(self+0x20,1,1);
        W(self+0x10,8,R(self+0x18,8));
        return 0;
    case 0x330cf0: /* restart, even when already running */
        W(self+0x20,1,0);
        W(self+0x10,8,R(self+0x18,8));
        now=virt(api,self,0x94,0);
        W(self+8,8,now);
        return 0;
    case 0x330d30:
        value=CALL(0x230cc8,1000000000,0);
        value=CALL(0x230790,value,arg1);
        value=CALL(0x22ff70,value,0);
        virt(api,self,0x84,value);
        return 0;
    case 0x330d90: W(self+0x18,8,arg1); return 0;
    case 0x330da0: return R(self+0x18,8);
    case 0x330db0: return seconds(api,virt(api,self,0x8c,0));
    case 0x330e50: return R(self+0x20,1);
    /* Notification dispatcher: snapshot the manager list before calling it.
     * 0x237ec0's body is 336 contiguous bytes, not a split-table entry. */
    case 0x237ec0: {
        uint32_t snapshot, manager, old;
        list=(uint32_t)R(R(self+8,4)+8,4);
        count=(uint32_t)R(list+8,4);
        CALL(0x301ee0,R(self+0xc,4),count);
        for(i=0;i<count;i++) {
            list=(uint32_t)R(R(self+8,4)+8,4);
            manager=(uint32_t)R(R(list+0x10,4)+i*4,4);
            snapshot=(uint32_t)R(self+0xc,4);
            if(manager) W(manager+4,4,R(manager+4,4)+1);
            old=(uint32_t)R(R(snapshot+0x10,4)+i*4,4);
            if(old) {
                W(old+4,4,R(old+4,4)-1);
                if(!(R(old+4,4)&0x7fffff)) CALL(0x2ff820,old,0);
            }
            value=R(snapshot+8,4);
            if(value && (int32_t)i>=0 && (int32_t)i<(int32_t)value)
                W(R(snapshot+0x10,4)+i*4,4,manager);
        }
        for(i=0;i<count;i++) {
            snapshot=(uint32_t)R(self+0xc,4);
            virt(api,(uint32_t)R(R(snapshot+0x10,4)+i*4,4),0x74,0);
        }
        CALL(0x301ee0,R(self+0xc,4),0);
        return 0;
    }
    case 0x3a0540:
        return (R(self+0x2c,1)&(R(self+0x2d,1)==0))!=0;
    /* The shared manager driver used by beAction2: invoke vfunc_31 for
     * every action, after the three gates, retaining group/list order. */
    case 0x378bc0: {
        uint32_t group, actions, n, j;
        if(!CALL(0x3a0540,R(self+0x10,4),0) || !R(self+0x1c,1) ||
           R(R(self+0x10,4)+0x2e,1)) return 0;
        count=(uint32_t)R(R(self+0x18,4)+8,4);
        for(i=0;(int32_t)i<(int32_t)count;i++) {
            group=(uint32_t)R(R(R(self+0x18,4)+0x10,4)+i*4,4);
            actions=(uint32_t)R(group+0x18,4);
            n=(uint32_t)R(actions+8,4);
            for(j=0;(int32_t)j<(int32_t)n;j++)
                virt(api,self,0x84,R(R(actions+0x10,4)+j*4,4));
        }
        return 0;
    }
    /* Adjacent system start/stop pair. List length is re-read each iteration. */
    case 0x2371f0:
        W(self+0x40,8,0);
        W(self+0x38,8,0);
        for(i=0;;i++) {
            list=(uint32_t)R(R(self+8,4)+8,4);
            if(i>=R(list+8,4)) break;
            obj=(uint32_t)R(R(list+0x10,4)+i*4,4);
            virt(api,obj,0x64,0);
        }
        virt(api,(uint32_t)R(self+0x30,4),0x6c,0);
        return 0;
    case 0x237280:
        virt(api,(uint32_t)R(self+0x30,4),0x70,0);
        for(i=0;;i++) {
            list=(uint32_t)R(R(self+8,4)+8,4);
            if(i>=R(list+8,4)) break;
            obj=(uint32_t)R(R(list+0x10,4)+i*4,4);
            virt(api,obj,0x68,0);
        }
        return 0;
    /* Adjacent system sample/update and task-pass pair. */
    case 0x237730:
        now=virt(api,(uint32_t)R(self+0x30,4),0x68,0);
        W(self+0x40,8,now-R(self+0x38,8));
        W(self+0x38,8,now);
        value=R(self+0x40,8)*sx32(R(self+0x48,4));
        W(self+0x50,8,R(self+0x50,8)+sar18(value));
        virt(api,(uint32_t)R(self+0x20,4),0x5c,0);
        virt(api,(uint32_t)R(self+0xc,4),0x5c,0);
        return 0;
    case 0x2377c0:
        if(virt(api,(uint32_t)R(self+0x18,4),0x90,0)) return 0;
        W(self+0x34,4,R(self+0x34,4)+1);
        list=(uint32_t)R(R(self+0x1c,4)+8,4);
        count=(uint32_t)R(list+8,4);
        first=virt(api,(uint32_t)R(self+0x30,4),0x68,0);
        for(i=0; (int32_t)i<(int32_t)count; i++) {
            list=(uint32_t)R(R(self+0x1c,4)+8,4);
            obj=(uint32_t)R(R(list+0x10,4)+i*4,4);
            virt(api,obj,0x64,0);
        }
        if(!virt(api,(uint32_t)R(self+0x18,4),0x2b4,0)) return 0;
        second=virt(api,(uint32_t)R(self+0x30,4),0x68,0);
        for(i=0; (int32_t)i<(int32_t)count; i++) {
            list=(uint32_t)R(R(self+0x1c,4)+8,4);
            obj=(uint32_t)R(R(list+0x10,4)+i*4,4);
            virt(api,obj,0x68,0);
        }
        last=virt(api,(uint32_t)R(self+0x30,4),0x68,0);
        virt(api,(uint32_t)R(self+0x18,4),0x2b8,0);
        W(self+0x58,8,second-first);
        W(self+0x60,8,last-second);
        return 0;
    default:
        return api->call(api->user,entry,(const uint64_t[8]){arg0,arg1});
    }
}
