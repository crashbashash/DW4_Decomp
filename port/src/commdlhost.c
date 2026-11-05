#include "dw4/commdlhost.h"
#include <string.h>
static int valid(dw4_commdl_host *h,int32_t addr,int width)
{
    if(width!=4 || addr<DW4_CM_BASE || addr>DW4_CM_BASE+DW4_CM_BYTES-width) {
        h->error=addr ? addr : -5; return 0;
    }
    return 1;
}
static int32_t peek(void *p,int32_t addr,int width)
{
    dw4_commdl_host *h=p; unsigned v=0;int i;
    /* Native allocator and immutable token table: no generic engine recovery. */
    if(addr==0x554c14 && width==1)return 1;
    if(addr==0x586f20 && width==4)return 1;
    if(!valid(h,addr,width))return 0;
    for(i=0;i<width;++i)v|=(unsigned)h->memory[addr-DW4_CM_BASE+i]<<(8*i);
    return (int32_t)v;
}
static void poke(void *p,int32_t addr,int width,int32_t v)
{
    dw4_commdl_host *h=p;int i;
    if(!valid(h,addr,width))return;
    for(i=0;i<width;++i)h->memory[addr-DW4_CM_BASE+i]=(uint32_t)v>>(8*i);
}
static int32_t call(void *p,int32_t addr,const int32_t a[8])
{
    dw4_commdl_host *h=p;int i,count,data,item;
    switch(addr) {
    case 0x301000:return 1;
    case 0x3c7450:
        for(i=0;i<DW4_CM_CAPACITY;++i)if(!h->used[i]) {
            h->used[i]=1;item=DW4_CM_BASE+0x1000+i*32;
            memset(h->memory+item-DW4_CM_BASE,0,32);
            poke(h,item+4,4,1);return item;
        }
        /* Reserved overflow record keeps the reference code memory-safe; the
         * screen stops on error, never reporting a successful completion. */
        h->error=-6;item=DW4_CM_BASE+0x2fe0;
        memset(h->memory+0x2fe0,0,32);poke(h,item+4,4,1);return item;
    case 0x2eaf60:return a[1]; /* fresh records, stable immutable title tokens */
    case 0x301e30:
        count=peek(h,a[0]+8,4);data=peek(h,a[0]+16,4);
        if(count<0 || count>=DW4_CM_CAPACITY || h->error){h->error=-6;return 0;}
        poke(h,data+count*4,4,a[1]);poke(h,a[0]+8,4,count+1);
        poke(h,a[1]+4,4,peek(h,a[1]+4,4)+1);return 0;
    case 0x2d6cf0:
        count=peek(h,a[0]+8,4);data=peek(h,a[0]+16,4);
        if(a[1]<0 || a[1]>=count){h->error=-7;return 0;}
        for(i=a[1];i<count-1;++i)poke(h,data+i*4,4,peek(h,data+(i+1)*4,4));
        poke(h,a[0]+8,4,count-1);return 0;
    case 0x2ff820:
        i=(a[0]-DW4_CM_BASE-0x1000)/32;
        if(i>=0 && i<DW4_CM_CAPACITY)h->used[i]=0;
        else if(a[0]!=DW4_CM_BASE+0x2fe0)h->error=-8;
        return 0;
    case 0x38d860:case 0x38f830:case 0x38e060:case 0x38e5f0:case 0x38f220:
        return h->message(h->user,addr,a);
    default:h->error=addr;return 0;
    }
}
void dw4_commdl_host_init(dw4_commdl_host *h,void *user,int32_t (*message)(void *,int32_t,const int32_t[8]))
{
    memset(h,0,sizeof(*h));h->user=user;h->message=message;
    h->api=(Dw4LoadIntf2Api){h,peek,poke,call};
    poke(h,DW4_CM_BASE+16,4,DW4_CM_BASE+0x200);
    poke(h,DW4_CM_BASE+20,4,DW4_CM_BASE+0x100);
    poke(h,DW4_CM_BASE+24,4,DW4_CM_BASE+0x120);
    poke(h,DW4_CM_BASE+0x110,4,DW4_CM_BASE+0x400);
    poke(h,DW4_CM_BASE+0x130,4,DW4_CM_BASE+0x800);
}
