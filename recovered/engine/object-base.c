/* Native igObject bootstrap, including the two manually registered header fields.
 * The field constructor and shared registration algorithms remain original paths. */
#include "object-base.h"
#include "reflection-registration.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define SB(p,v) a->write(a->user,(p),1,(uint8_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
static uint64_t word(uint32_t p){return (uint64_t)(int64_t)(int32_t)p;}
static void unstring(const Dw4MessengerResultsApi *a,uint32_t token){
    if(token){W(token-4,P(token-4)-1);if(!P(token-4))CALL(0x30c940,P(token-8),token-8);}
}
uint64_t dw4_object_base(const Dw4MessengerResultsApi *a,uint32_t entry,const uint64_t v[8],uint32_t scratch){
    switch(entry){
    case 0x2ff460:{
        uint64_t allocator=CALL(0x2f88e0,P(0x587040));uint64_t callbacks=CALL(0x2ed240,12,allocator);
        return callbacks?CALL(0x2d3400,callbacks):0;
    }
    case 0x2ff4a0:return 0;
    case 0x135530:case 0x155b80:case 0x2ff560:return word(P(0x587198));
    case 0x2ff4b0:
        CALL(0x2fef20,scratch+16);return word(P(scratch+16+P(P(0x586dc8)+916)));
    case 0x2ff4e0:CALL(0x2fe940,0x2ff4f0);return 0;
    case 0x2ff4f0:
        return dw4_reflection_registration(a,0x2fe9c0,(const uint64_t[12]){
            0,0x587198,0x2ff460,0x2ff4a0,0x2ff560,0x4faf30,8,0x2ff4b0,0x2ff570,0,0},scratch);
    case 0x2fde60:
        CALL(0x2fc630,v[1]);CALL(0x2fde50,v[0],v[1]);return 0;
    case 0x2ff570:
        for(unsigned i=0;i<2;i++){
            uint32_t allocator=(uint32_t)CALL(0x2f88e0,P(0x587040));
            uint32_t field=(uint32_t)CALL(0x2b6d20,allocator);
            W(field+8,4);W(field+28,0x5871a0+i*8);
            uint32_t pool=P(0x586f20);
            if(!pool){pool=(uint32_t)CALL(0x2eb010,16);if(pool)pool=(uint32_t)CALL(0x2eadf0,pool);W(0x586f20,pool);}
            W(scratch,(uint32_t)CALL(0x2eaf60,P(0x586f20),0x4faf40+i*16));
            CALL(0x2fc490,field,scratch);unstring(a,P(scratch));
            SB(field+38,0);SB(field+36,3);
            CALL(0x2fde60,P(0x587198),field);
            W(field+4,P(field+4)-1);if(!(P(field+4)&0x7fffff))CALL(0x2ff820,field);
        }return 0;
    default:return UINT64_MAX;
    }
}
