/* Original igAliasMemoryPool factory, retained binding and accounting controls. */
#include "alias-pool-binding.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
uint64_t dw4_alias_pool_binding(const Dw4MessengerResultsApi *a,uint32_t entry,const uint64_t v[8]){
    uint32_t self=(uint32_t)v[0];
    switch(entry){
    case 0x2cd170:{
        uint32_t pool;
        if(a->read(a->user,P(0x586dc8),1)){
            CALL(0x2cd3f0);
            return CALL(0x2fda40,P(0x5869b0),v[0]);
        }
        pool=(uint32_t)CALL(0x2f0040,184,0,v[0]);
        if(pool)pool=(uint32_t)CALL(0x2d1540,pool,1);
        /* Retail dereferences even a null allocation result; no new guard. */
        CALL(P(P(pool)+44),pool);
        CALL(P(P(pool)+36),pool,0);
        return pool;
    }
    case 0x2d0560:{
        uint32_t alias=(uint32_t)v[1];
        if(alias)W(alias+4,P(alias+4)+1);
        uint32_t old=P(self+180);
        if(old){W(old+4,P(old+4)-1);if(!(P(old+4)&0x7fffff))CALL(0x2ff820,old);}
        W(self+180,alias);
        uint64_t delegated=alias?CALL(P(P(alias)+376),v[1],v[0]):0;
        a->write(a->user,self+113,1,delegated);
        return 0;
    }
    case 0x2d0600:
    case 0x2d0620:
        a->write(a->user,self+128,8,0);
        a->write(a->user,self+160,8,0);
        W(self+136,0);W(self+140,0);W(self+168,0);
        if(entry==0x2d0600)a->write(a->user,self+112,1,1);
        return 0;
    case 0x2d0640:
        CALL(P(P(self)+124),v[0]);
        a->write(a->user,self+112,1,0);
        return 0;
    case 0x2d0670:return a->read(a->user,self+112,1);
    case 0x2d0680:case 0x2d06a0:case 0x2d06b0:return 0;
    case 0x2d0690:W(self,P(0x4fb418));return 0;
    default:return UINT64_MAX;
    }
}
