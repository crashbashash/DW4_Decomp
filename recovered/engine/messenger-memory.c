/* Complete initialization/reset group, temporary owners and reset forwarding.
 * Behavioral guest-reference recovery, excluded from the matching build. */
#include "messenger-memory.h"
typedef const Dw4MessengerResultsApi *Api;
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
static void retain(Api a,uint32_t p){if(p)W(p+4,P(p+4)+1);}
static void release(Api a,uint32_t p){if(p){W(p+4,P(p+4)-1);if(!(P(p+4)&0x7fffff))CALL(0x2ff820,p);}}
static uint32_t allocator(Api a,uint64_t self){
    uint32_t result=(uint32_t)CALL(0x301000,self);
    if(!a->read(a->user,0x554c14,1))result=(uint32_t)CALL(0x2f88e0,P(0x587110));
    return result;
}
static void initialize(Api a,uint64_t receiver){
    uint32_t self=(uint32_t)receiver;
    uint32_t value=(uint32_t)CALL(0x358d80,allocator(a,receiver));
    retain(a,value);release(a,P(self+16));W(self+16,value);release(a,value);
    static const unsigned offsets[]={24,28,32},counts[]={64,32,4};
    static const uint32_t factories[]={0x358070,0x358950,0x358d80};
    for(unsigned group=0;group<3;group++){
        unsigned offset=offsets[group],count=counts[group];
        if((int32_t)P(P(self+offset)+8)<(int32_t)count+1)CALL(0x2d6680,P(self+offset),count,4);
        CALL(0x301ee0,P(self+offset),count);
        for(unsigned i=0;i<count;i++){
            value=(uint32_t)CALL(factories[group],allocator(a,receiver));
            uint32_t list=P(self+offset);retain(a,value);
            release(a,P(P(list+16)+i*4));
            int32_t n=(int32_t)P(list+8);
            if(n&&i<(uint32_t)n&&(int32_t)i<n)W(P(list+16)+i*4,value);
            release(a,value);
        }
    }
    W(self+36,0);a->write(a->user,self+48,1,1);
}
static void reset(Api a,uint32_t self){
    release(a,P(self+16));W(self+16,0);
    for(unsigned offset=20;offset<=32;offset+=4){
        uint32_t list=P(self+offset);int32_t n=(int32_t)P(list+8);
        for(int32_t i=0;i<n;i++)release(a,P(P(list+16)+(uint32_t)i*4));
        /* Destructors can change count and storage before this pass. */
        n=(int32_t)P(list+8);
        for(int32_t i=0;i<n;i++)W(P(list+16)+(uint32_t)i*4,0);
        W(list+8,0);
        /* This condition is on the cleared count, not on capacity. */
        if((int32_t)P(P(self+offset)+8)<5)CALL(0x2d6680,P(self+offset),4,4);
    }
    W(self+36,0);a->write(a->user,self+40,8,0);a->write(a->user,self+48,1,0);
}
uint64_t dw4_messenger_memory(Api a,uint32_t entry,const uint64_t v[8]){
    uint32_t self=(uint32_t)v[0];
    switch(entry){
    case 0x38bee0:initialize(a,v[0]);break;
    case 0x38c390:case 0x38c410:
        if(v[0]){release(a,P(self));if((int16_t)v[1]>0)CALL(0x100610,v[0]);}return v[0];
    case 0x38c490:case 0x38d080:reset(a,self);break;
    default:return UINT64_MAX;
    }
    return 0;
}
