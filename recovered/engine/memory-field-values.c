/* Memory-reference value lifetime, scalar defaults and exact supporting leaves. */
#include "memory-field-values.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define H(p) ((uint32_t)a->read(a->user,(p),2))
#define B(p) ((uint32_t)a->read(a->user,(p),1))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define CORE(e,...) dw4_memory_field_value(a,(e),(const uint64_t[8]){__VA_ARGS__},scratch)
static uint32_t method(const Dw4MessengerResultsApi *a,uint32_t p,unsigned slot){return P(P(p)+slot);}
static void release(const Dw4MessengerResultsApi *a,uint32_t p){if(p){W(p+4,P(p+4)-1);if(!(P(p+4)&0x7fffff))CALL(0x2ff820,p);}}
uint64_t dw4_memory_field_value(const Dw4MessengerResultsApi *a,uint32_t entry,const uint64_t v[8],uint32_t scratch){
    uint32_t self=(uint32_t)v[0],object=(uint32_t)v[1],buffer,value;
    switch(entry){
    case 0x2fa9d0:return 4;
    case 0x2fa9e0:W(scratch,(uint32_t)v[1]);CALL(method(a,self,140),v[0],scratch);return 0;
    case 0x2faa10:{
        if(!B(self+52))return 0;
        uint32_t type=P(self+60),size=(uint32_t)CALL(method(a,type,100),type)&65535;
        uint32_t numerator=P(self+56)+size-1,count=size?numerator/size:0xffffffff;
        uint32_t name=P(self+76);uint64_t allocator=0;
        if(name&&B(name))allocator=CALL(0x2f8920,name);
        if(!allocator)allocator=CALL(0x301000,v[1]);
        CALL(0x2fb190,scratch,v[0],v[1],count,allocator);return 0;
    }
    case 0x2faae0:
        if(B(self+53)){CORE(0x2fabf0,v[0],v[1]);CALL(0x2ed460,P(object+P(self+8)));W(object+P(self+8),0);}return 0;
    case 0x2fab40:case 0x2fabf0:{
        if(!B(self+66)||!P(self+60))return 0;
        uint64_t reference=CALL(0x300cd0,P(self+60),P(0x585b20));if(!reference)return 0;
        buffer=P(object+P(self+8));if(!buffer)return 0;
        uint32_t count=(uint32_t)CALL(0x2ed4e0,buffer)>>2;
        for(int32_t i=0;i<(int32_t)count;i++){
            value=P(buffer+(uint32_t)i*4);
            if(entry==0x2fab40){if(value)W(value+4,P(value+4)+1);}else release(a,value);
        }return 0;
    }
    case 0x2facc0:
        CORE(0x2fabf0,v[0],v[1]);
        if(B(self+65)){value=P(object+P(self+8));if(value)CALL(0x2ed5d0,value);}
        value=P(P(self+32));value=value?(uint32_t)CALL(0x2ed530,value):0;
        W(object+P(self+8),value);CORE(0x2fab40,v[0],v[1]);return 0;
    case 0x2fc580:case 0x2fc5a0:CALL(0x127098,object+P(self+8),P(self+32),H(self+20));return 0;
    case 0x2fc5c0:case 0x2fd040:case 0x2fd050:case 0x2fd060:case 0x2fd070:case 0x2fd080:case 0x2fd230:return 0;
    case 0x13c180:case 0x331d60:
        if((int32_t)P(self+8)<(int32_t)P(self+12)){CALL(0x2d6680,v[0],P(self+8),4);}
        return 0;
    case 0x142b40:return (uint64_t)(int64_t)(int32_t)P(0x586788);
    case 0x142a70:return (uint64_t)(int64_t)(int32_t)P(0x585b60);
    case 0x331660:return (uint64_t)(int64_t)(int32_t)P(0x586880);
    case 0x36efa0:return (uint64_t)(int64_t)(int32_t)P(0x589d20);
    case 0x36f600:return (uint64_t)(int64_t)(int32_t)P(0x588f88);
    case 0x2ff0a0:case 0x2ff0b0:case 0x2ff0c0:case 0x2ff0e0:case 0x2ff0f0:case 0x2ff140:case 0x2ff150:case 0x2ff130:case 0x2ff1a0:return 0;
    default:return UINT64_MAX;
    }
}
