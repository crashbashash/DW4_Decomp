/* Original string/int/object-reference descriptor factories and constructor chain.
 * Guest-address recovery; registrations, instance creation and allocator leaves
 * remain explicit dependencies. No null-success or allocator policy is added. */
#include "field-factories.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define B(p) ((uint32_t)a->read(a->user,(p),1))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define SB(p,v) a->write(a->user,(p),1,(uint8_t)(v))
#define SH(p,v) a->write(a->user,(p),2,(uint16_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define CORE(e,...) dw4_field_factory(a,(e),(const uint64_t[8]){__VA_ARGS__})
static uint64_t pointer(uint32_t p){return (uint64_t)(int64_t)(int32_t)p;}
static uint64_t method(const Dw4MessengerResultsApi *a,uint32_t self,unsigned slot,uint64_t arg,int supplied){
    return supplied?CALL(P(P(self)+slot),self,arg):CALL(P(P(self)+slot),self);
}
uint64_t dw4_field_factory(const Dw4MessengerResultsApi *a,uint32_t entry,const uint64_t v[8]){
    static const uint32_t factories[]={0x2b9750,0x2c2cf0,0x2bce90,0x2b6d20,0x2bf2e0};
    static const uint32_t guards[]={0x2b9940,0x2c2f30,0x2bd0c0,0x2b6f10,0x2bf680};
    static const uint32_t handles[]={0x585908,0x5860f8,0x585b20,0x585738,0x585d80};
    static const uint32_t ctors[]={0x30b230,0x2ea3e0,0x303bc0,0x30e8e0,0x2fb8e0};
    static const uint32_t sizes[]={60,52,68,52,80};
    for(unsigned i=0;i<5;i++)if(entry==factories[i]){
        if(B(P(0x586dc8))){CALL(guards[i]);return CALL(0x2fda40,P(handles[i]),v[0]);}
        uint32_t result=(uint32_t)CORE(0x2ff790,sizes[i],0,v[0]);
        if(result)result=(uint32_t)CORE(ctors[i],result,1);
        method(a,result,44,0,0);method(a,result,36,0,1);return pointer(result);
    }
    uint32_t self=(uint32_t)v[0],pool,value,old;
    switch(entry){
    case 0x2fef20:
        W(self,0x52f0f0);W(self+4,(P(self+4)&0xff800000)|1);SB(self+6,B(self+6)&127);SB(self+7,0);break;
    case 0x2ff010:
        W(self,0x52f0f0);if(v[0])CORE(0x2fef20,v[0]);
        if(B(P(0x586dc8))){
            uint64_t base=CALL(0x300d30,v[0]);uint32_t owner=(uint32_t)CALL(0x2f04f0,base);
            SB(self+7,owner?method(a,owner,364,0,0):0);
        }else SB(self+7,0);
        break;
    case 0x2ff790:{
        uint32_t size=(uint32_t)v[0]+(uint32_t)v[1],allocator=(uint32_t)v[2];
        if(!v[2])allocator=(uint32_t)CALL(0x2f88e0,P(0x587018));
        if(!allocator)return CALL(0x126308,pointer(size));
        uint32_t allocation=(uint32_t)method(a,allocator,216,pointer(size),1);
        return pointer(allocation+(uint32_t)v[1]);
    }
    case 0x2fb8e0:
        CORE(0x305bf0,v[0],v[1]);W(self,0x532a50);W(self+72,0);W(self+76,0);if(v[0])CORE(0x2fb930,v[0]);break;
    case 0x2fb930:
        CORE(0x305c30,v[0]);W(self,0x532a50);W(self+72,0);W(self+76,0);
        SB(self+66,1);W(self+56,0);W(self+60,0);SB(self+36,3);SB(self+65,1);SB(self+64,1);W(self+68,0xffffffff);SB(self+39,2);break;
    case 0x2fbf90:
        CORE(0x2ff010,v[0],v[1]);W(self,0x52f230);W(self+12,0);if(v[0])CORE(0x2fbfe0,v[0]);break;
    case 0x2fbfe0:
        CORE(0x2fef20,v[0]);W(self,0x52f230);W(self+12,0);W(self+8,0);SB(self+37,0);
        SH(self+16,65535);SH(self+18,0);SH(self+20,0);W(self+32,0);W(self+28,0);
        pool=P(0x586f20);
        if(!pool){pool=(uint32_t)CALL(0x2eb010,16);if(pool)pool=(uint32_t)CALL(0x2eadf0,pool);W(0x586f20,pool);}
        value=(uint32_t)CALL(0x2eaf60,P(0x586f20),0);old=P(self+12);
        if(old){uint32_t count=P(old-4)-1;W(old-4,count);if(!count)CALL(0x30c940,P(old-8),old-8);}
        W(self+12,value);W(self+24,0);W(self+48,0);
        SB(self+36,0);SB(self+39,0);SB(self+40,0);SB(self+41,0);SB(self+42,0);SB(self+43,1);SB(self+44,2);SB(self+38,1);break;
    case 0x305bf0:
        CORE(0x2fbf90,v[0],v[1]);W(self,0x52ec50);if(v[0])CORE(0x305c30,v[0]);break;
    case 0x305c30:CORE(0x2fbfe0,v[0]);W(self,0x52ec50);SB(self+52,0);SB(self+53,0);break;
    case 0x30b230:
        CORE(0x305bf0,v[0],v[1]);W(self,0x533180);if(v[0])CORE(0x30b270,v[0]);break;
    case 0x30b270:CORE(0x305c30,v[0]);W(self,0x533180);SB(self+56,1);SB(self+39,2);SB(self+53,1);break;
    case 0x2ea3e0:
        CORE(0x2fbf90,v[0],v[1]);W(self,0x532670);if(v[0])CORE(0x2ea420,v[0]);break;
    case 0x2ea420:CORE(0x2fbfe0,v[0]);W(self,0x532670);break;
    case 0x30e8e0:
        CORE(0x2fbf90,v[0],v[1]);W(self,0x533430);if(v[0])CORE(0x30e920,v[0]);break;
    case 0x30e920:CORE(0x2fbfe0,v[0]);W(self,0x533430);break;
    case 0x303bc0:
        CORE(0x305bf0,v[0],v[1]);W(self,0x532c80);W(self+64,0);if(v[0])CORE(0x303c10,v[0]);break;
    case 0x30a820:case 0x303350:
        CALL(0x2ff140,v[0]);method(a,self,140,0,1);return 0;
    case 0x303c10:CORE(0x305c30,v[0]);W(self,0x532c80);W(self+64,0);SB(self+60,1);W(self+56,0);break;
    default:return UINT64_MAX;
    }
    return v[0];
}
