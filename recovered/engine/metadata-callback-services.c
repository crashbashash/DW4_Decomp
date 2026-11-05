/* Name-selector metadata lookup, replacement and deferred callback-array lifetime. */
#include "metadata-callback-services.h"
#include "internal-object-lists.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
static uint64_t word(uint32_t value){return (uint64_t)(int64_t)(int32_t)value;}
uint64_t dw4_metadata_callback_service(const Dw4MessengerResultsApi *a,uint32_t entry,const uint64_t v[8]){
    uint32_t self=(uint32_t)v[0];
    switch(entry){
    case 0x2d3400:W(self,0);W(self+8,0);W(self+4,0);return v[0];
    case 0x2d3420:
        if(self){uint32_t buffer=P(self);if(buffer)CALL(0x2ed460,buffer);if((int16_t)v[1]>0)CALL(0x2ed5c0,v[0]);}
        return v[0];
    case 0x2d3480:{
        int32_t capacity=(int32_t)P(self+8);
        if(P(self+4)==(uint32_t)capacity){
            uint32_t next;
            if(!capacity)next=4;
            else{int32_t triple=(int32_t)((uint32_t)capacity*3);next=(uint32_t)capacity*(uint32_t)(triple/2);}
            W(self+8,next);
            uint64_t buffer=P(self)?CALL(0x2ed330,P(self),word(P(self+8)*4)):
                CALL(0x2ed240,word(P(self+8)*4),P(P(0x586dc8)+52));
            W(self,(uint32_t)buffer);
        }
        uint32_t count=P(self+4);W(self+4,count+1);W(P(self)+count*4,(uint32_t)v[1]);return 0;
    }
    case 0x2ea780:return dw4_internal_object_list(a,entry,v);
    case 0x2fdf20:return CALL(0x2ea780,P(self+40),P(0x585cd8),v[1]);
    case 0x2fdea0:CALL(0x2fc630,v[2]);CALL(0x2ead50,P(self+40),v[1],v[2]);return 0;
    default:return UINT64_MAX;
    }
}
