#include "loadingnode.h"
#include "eefloat.h"
#define R(a,n) api->read(api->user,(uint32_t)(a),(n))
#define W(a,n,v) api->write(api->user,(uint32_t)(a),(n),(v))
static uint64_t leaf(const Dw4SystemClockApi *api,uint32_t f,uint64_t a,uint64_t b,uint64_t c)
{ uint64_t args[8]={a,b,c,0,0,0,0,0};return api->call(api->user,f,args); }
static uint64_t scaled(const Dw4SystemClockApi *api,uint32_t node,uint64_t now)
{ return (uint64_t)ee_f32_to_s64(ee_f32_mul(ee_f32_from_clock_ticks((int64_t)now),(uint32_t)R(node+0x50,4)))<<18; }
static void rebase(const Dw4SystemClockApi *api,uint32_t node,uint64_t local,uint64_t now)
{ W(node+0x58,8,local-scaled(api,node,now)); }
static uint64_t tick(const Dw4SystemClockApi *api,uint32_t node,uint64_t now)
{
    uint64_t t=R(node+0x38,8);
    if(t)return t;
    uint64_t delta=now-R(node+0x60,8);
    W(node+0x68,8,R(node+0x68,8)+delta);
    if((int64_t)delta>33333333)W(node+0x58,8,R(node+0x58,8)-(delta-33333333));
    W(node+0x60,8,now);
    t=scaled(api,node,now)+R(node+0x58,8);
    uint64_t end=R(node+0x30,8);
    if((int64_t)end<=(int64_t)t){
        /* Preserve the retail strict subtraction and equality boundary. The
         * authored interval must be positive if this branch is entered. */
        while((int64_t)end<(int64_t)t)t-=end;
        t+=R(node+0x28,8);rebase(api,node,t,now);
    }
    return t;
}
static uint32_t bucket(const Dw4SystemClockApi *api,uint32_t ctx,uint32_t value,uint32_t *index)
{
    uint32_t resolver=(uint32_t)R(ctx+0x34,4);
    *index=(uint32_t)((int16_t)R(value+10,2)+(uint32_t)R(R(resolver+0x44,4)+R(value+8,2)*4,4));
    return (uint32_t)R(R(R(resolver+0x10,4)+0x10,4)+*index*4,4);
}
static uint64_t traverse(const Dw4SystemClockApi *api,uint32_t node,uint32_t ctx)
{
    uint32_t vt=(uint32_t)R(ctx,4),resolver=(uint32_t)R(ctx+0x34,4);
    uint64_t now=leaf(api,(uint32_t)R(vt+0x68,4),ctx,0,0);
    if(R(node+0x40,1)){
        rebase(api,node,R(node+0x20,8),now);W(node+0x60,8,now);W(node+0x40,1,0);
    }
    uint64_t t=tick(api,node,now);
    uint32_t list=(uint32_t)R(ctx+0x4c,4);
    if((int32_t)R(list+8,4)<=(int32_t)R(list+0x14,4))leaf(api,0x1dca40,list,0x130f20,0);
    uint32_t cursor=(uint32_t)R(list+0x14,4);
    W(list+0x14,4,cursor+1);
    uint32_t value=(uint32_t)R(R(list+0x10,4)+cursor*4,4);
    W(value+0x10,8,t);
    leaf(api,(uint32_t)R(vt+0x80,4),ctx,t,0);
    uint32_t index,group=bucket(api,ctx,value,&index),count=(uint32_t)R(group+8,4);
    if((int32_t)count<(int32_t)R(group+0xc,4))W(group+8,4,count+1);
    else leaf(api,0x2d6790,group,count+1,4);
    W(R(group+0x10,4)+count*4,4,value);
    leaf(api,0x1b1490,resolver,group,index);
    uint64_t result=leaf(api,0x1e07a0,ctx,node,0);
    group=bucket(api,ctx,value,&index);
    uint32_t callback=(uint32_t)R(group+0x1c,4);
    if(callback)leaf(api,callback,R(R(group+0x10,4)+(R(group+8,4)-1)*4,4),R(resolver+0x30,4),0);
    W(group+8,4,R(group+8,4)-1);
    leaf(api,0x1b1490,resolver,group,index);
    leaf(api,(uint32_t)R(vt+0x84,4),ctx,0,0);
    return result==2?2:0;
}
uint64_t dw4_loadingnode_call(const Dw4SystemClockApi *api,uint32_t entry,uint64_t a,uint64_t b,uint64_t c)
{
    uint32_t node=(uint32_t)a;
    switch(entry){
    case 0x39a930:case 0x39adc0:return traverse(api,(uint32_t)b,node);
    case 0x39a960:rebase(api,node,b,c);return 0;
    case 0x39a9e0:return tick(api,node,b);
    case 0x39ab20:return traverse(api,node,(uint32_t)b);
    case 0x39ad80:case 0x39ae10:{
        uint32_t get=entry==0x39ad80?0x34e870:0x34e5d0;
        uint64_t meta=leaf(api,get,0,0,0);
        leaf(api,0x1e06c0,R(0x562640,4),meta,entry==0x39ad80?0x39a930:0x39adc0);return 0;
    }
    case 0x39adf0:W(node+0x38,8,R(node+0x70,8));return 0;
    case 0x39ae00:return (int64_t)R(node+0x78,8)<(int64_t)R(node+0x68,8);
    default:return leaf(api,entry,a,b,c);
    }
}
