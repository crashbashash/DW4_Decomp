#include "dw4/clockhost.h"
#include <string.h>
enum {
    SYS=DW4_CLOCK_BASE, TIMER=SYS+0x100, TVT=SYS+0x200,
    DISPATCH=SYS+0x300, DVT=SYS+0x400, SCHEDULER=SYS+0x500,
    SVT=SYS+0x600, RAW=0x1610000, NOTIFY=0x1610010, UPDATE=0x1610020
};
static int valid(dw4_clock_host *h,uint32_t a,unsigned n)
{
    if((n!=1 && n!=4 && n!=8) || a<DW4_CLOCK_BASE ||
       a-DW4_CLOCK_BASE>DW4_CLOCK_BYTES-n) { h->error=1;return 0; }
    return 1;
}
static uint64_t read_mem(void *p,uint32_t a,unsigned n)
{
    dw4_clock_host *h=p;uint64_t v=0;unsigned i;
    if(valid(h,a,n))for(i=0;i<n;i++)v|=(uint64_t)h->memory[a-DW4_CLOCK_BASE+i]<<(8*i);
    return v;
}
static void write_mem(void *p,uint32_t a,unsigned n,uint64_t v)
{
    dw4_clock_host *h=p;unsigned i;
    if(valid(h,a,n))for(i=0;i<n;i++)h->memory[a-DW4_CLOCK_BASE+i]=(unsigned char)(v>>(8*i));
}
static uint64_t call(void *p,uint32_t entry,const uint64_t args[8])
{
    dw4_clock_host *h=p;(void)args;
    if(entry==RAW)return h->raw;
    /* External dispatcher receivers and the full manager graph are not yet
     * ported. The bounded scheduler runs title models after the world store. */
    if(entry==NOTIFY)return 0;
    if(entry==UPDATE) { if(h->update && !h->error)h->update(h->user);return 0; }
    h->error=1;return 0;
}
static uint64_t invoke(dw4_clock_host *h,uint32_t entry,uint32_t self)
{
    if(h->invoke)return h->invoke(h->oracle_user,entry,&h->api,self,0);
    return dw4_clock_call(&h->api,entry,self,0);
}
void dw4_clock_host_init(dw4_clock_host *h,void *user,void (*update)(void *))
{
    memset(h,0,sizeof(*h));h->user=user;h->update=update;
    h->api=(Dw4SystemClockApi){h,read_mem,write_mem,call};
    write_mem(h,SYS+0x30,4,TIMER);write_mem(h,TIMER,4,TVT);
    write_mem(h,TVT+0x68,4,0x330af0);write_mem(h,TVT+0x94,4,RAW);
    write_mem(h,SYS+0x20,4,DISPATCH);write_mem(h,DISPATCH,4,DVT);
    write_mem(h,DVT+0x5c,4,NOTIFY);
    write_mem(h,SYS+0xc,4,SCHEDULER);write_mem(h,SCHEDULER,4,SVT);
    write_mem(h,SVT+0x5c,4,UPDATE);
    write_mem(h,SYS+0x48,4,0x40000);
    /* Native initial state: running timer at raw zero, world zero, unit scale.
     * Do not call system start on menu re-entry: it clears the sample baseline. */
}
void dw4_clock_host_set_raw(dw4_clock_host *h,uint64_t raw)
{ h->raw=raw;h->external=1; }
void dw4_clock_host_step(dw4_clock_host *h)
{
    if(h->error)return;
    if(!h->external)h->raw+=16666667;
    invoke(h,0x237730,SYS);
}
void dw4_clock_host_pause(dw4_clock_host *h) { invoke(h,0x330c20,TIMER); }
void dw4_clock_host_resume(dw4_clock_host *h) { invoke(h,0x330be0,TIMER); }
void dw4_clock_host_scale(dw4_clock_host *h,int32_t scale)
{ write_mem(h,SYS+0x48,4,(uint32_t)scale); }
uint64_t dw4_clock_host_world(dw4_clock_host *h) { return read_mem(h,SYS+0x50,8); }
