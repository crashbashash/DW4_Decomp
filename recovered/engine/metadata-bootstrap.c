/* Original metadata construction, base copy header, ownership and indexing.
 * Guest references; object/allocator/interner/list/system services are external. */
#include "metadata-bootstrap.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define B(p) ((uint32_t)a->read(a->user,(p),1))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define SB(p,v) a->write(a->user,(p),1,(uint8_t)(v))
#define SH(p,v) a->write(a->user,(p),2,(uint16_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define CORE(e,...) dw4_metadata_bootstrap(a,(e),(const uint64_t[8]){__VA_ARGS__})
static uint32_t pool(const Dw4MessengerResultsApi *a){
    uint32_t p=P(0x586f20);
    if(!p){p=(uint32_t)CALL(0x2eb010,16);if(p)p=(uint32_t)CALL(0x2eadf0,p);W(0x586f20,p);}
    return P(0x586f20);
}
static void unstring(const Dw4MessengerResultsApi *a,uint32_t p){
    if(p){uint32_t n=P(p-4)-1;W(p-4,n);if(!n)CALL(0x30c940,P(p-8),p-8);}
}
static void release(const Dw4MessengerResultsApi *a,uint32_t p){
    if(p){W(p+4,P(p+4)-1);if(!(P(p+4)&0x7fffff))CALL(0x2ff820,p);}
}
uint64_t dw4_metadata_bootstrap(const Dw4MessengerResultsApi *a,uint32_t entry,const uint64_t v[8]){
    uint32_t self=(uint32_t)v[0],value;
    switch(entry){
    case 0x2be4f0:
        if(B(P(0x586dc8))){CALL(0x2be760);return CALL(0x2fda40,P(0x585be8),v[0]);}
        value=(uint32_t)CALL(0x2ff790,100,0,v[0]);
        if(value)value=(uint32_t)CORE(0x2fd7c0,value,1);
        CALL(P(P(value)+44),value);CALL(P(P(value)+36),value,0);
        return (uint64_t)(int64_t)(int32_t)value;
    case 0x2fd7c0:
        CALL(0x2ff010,v[0],v[1]);W(self,0x532bb0);W(self+28,0);W(self+96,0);
        if(v[0])CORE(0x2fd820,v[0]);
        W(self+40,(uint32_t)CALL(0x2c2670,0));break;
    case 0x2fd820:
        CALL(0x2fef20,v[0]);W(self,0x532bb0);
        W(self+28,0);W(self+96,0);W(self+40,0);W(self+48,0);W(self+52,0);
        W(self+56,0);W(self+60,0);W(self+64,0);W(self+68,0);
        SB(self+24,0);SB(self+25,1);SB(self+26,0);
        W(self+16,1);W(self+20,0);W(self+12,0);W(self+8,0);W(self+40,0);
        W(self+32,0);W(self+44,0);W(self+36,0);W(self+72,0xffffffff);
        W(self+76,0);W(self+80,0);W(self+84,0);SH(self+88,4);W(self+92,0);
        value=(uint32_t)CALL(0x2eaf60,pool(a),0);
        unstring(a,P(self+96));W(self+96,value);break;
    case 0x2fef70:
        W(self,0x52f0f0);if(v[0])CALL(0x2fef20,v[0]);
        SB(self+6,(B(self+6)&127)|(B((uint32_t)v[1]+6)&128));
        if(B(P(0x586dc8))){uint64_t base=CALL(0x300d30,v[0]);uint64_t owner=CALL(0x2f04f0,base);SB(self+7,CALL(0x2f0670,owner));}
        break;
    case 0x2fd940:
        CORE(0x2fef70,v[0],v[1]);W(self,0x532bb0);W(self+28,0);W(self+96,0);break;
    case 0x2fd980:
        release(a,P(self+40));release(a,P(self+52));return 0;
    case 0x2fddb0:
        value=(uint32_t)CALL(0x2eaf60,pool(a),v[1]);unstring(a,P(self+28));W(self+28,value);return 0;
    case 0x2ea820:{
        uint32_t buffer=P(self+8);int32_t count=(int32_t)P(self+12);
        for(int32_t i=0;i<count;i++)if(P(buffer+(uint32_t)i*4)==(uint32_t)v[1])return (uint64_t)(int64_t)i;
        return UINT64_MAX;
    }
    case 0x2d3060:CALL(0x2ead30,P(self+24),v[1]);return 0;
    case 0x2fe7a0:
        W(self+12,(uint32_t)CALL(0x2ea820,P(P(0x586dc8)+24),v[0]));
        if(P(self+12)==0xffffffff){
            CALL(0x2d3060,P(0x586dc8),v[0]);
            W(self+12,(uint32_t)CALL(0x2ea820,P(P(0x586dc8)+24),v[0]));
        }return 0;
    default:return UINT64_MAX;
    }
    return v[0];
}
