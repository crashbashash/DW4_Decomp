/* Original generic service-root metadata. This constructs metadata and extracts
 * a vtable; actual controller behavior and shared registration remain services. */
#include "shop-root-metadata.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[11]){__VA_ARGS__})
static uint64_t word(uint32_t p){return (uint64_t)(int64_t)(int32_t)p;}
uint64_t dw4_shop_root_metadata(const Dw4MessengerResultsApi*a,uint32_t entry,const uint64_t v[8],uint32_t scratch){
    switch(entry){
    case 0x3b65b0:return word(P(0x58b010));
    case 0x3b8d90:
        CALL(0x3b8ea0);return CALL(0x2fda40,word(P(0x58ae30)),v[0]);
    case 0x3b8dd0:{
        uint32_t meta=P(0x58ae30);
        if(!meta||!(P(meta+36)&4))CALL(0x3b8ea0);
        return word(P(0x58ae30));
    }
    case 0x3b8e20:{
        CALL(0x2fef20,scratch+32);
        uint32_t system=P(0x586dc8);
        for(unsigned offset=84;offset<=108;offset+=4)W(scratch+offset,0);
        W(scratch+32,0x53feb0);
        uint32_t value=P(scratch+32+P(system+916));
        W(scratch+32,0x53feb0);CALL(0x3b6430,scratch+32,0);
        return word(value);
    }
    case 0x3b8ea0:CALL(0x2fe940,0x3b8ec0);return 0;
    case 0x3b8ec0:
        CALL(0x3b0a10);
        return CALL(0x2fe9c0,0,0x58ae30,0x3bb630,0x3b65b0,0x3b8f30,0x5115a0,84,0x3b8e20,0,0,0);
    case 0x3b8f30:return CALL(0x3b8dd0);
    default:return UINT64_MAX;
    }
}
