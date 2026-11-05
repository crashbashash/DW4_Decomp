/* Original list metadata access, registrar tuples and inherited data schema. */
#include "list-registration.h"
#include "reflection-registration.h"
#include "list-descriptor-copy.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define SB(p,v) a->write(a->user,(p),1,(uint8_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
static uint64_t word(uint32_t p){return (uint64_t)(int64_t)(int32_t)p;}
uint64_t dw4_list_registration(const Dw4MessengerResultsApi *a,uint32_t entry,const uint64_t v[8],uint32_t scratch){
    static const uint32_t handles[]={0x586788,0x585b60,0x586880,0x589d20};
    static const uint32_t allocate[]={0x2c8490,0x2bd6c0,0x2caab0,0x36a0a0};
    static const uint32_t ready[]={0x2c84e0,0x2bd710,0x2cab00,0x36a0f0};
    static const uint32_t tables[]={0x2c8530,0x2bd760,0x2cab50,0x36a140};
    static const uint32_t guards[]={0x2c8570,0x2bd7a0,0x2cab90,0x36a180};
    static const uint32_t registrars[]={0x2c8580,0x2bd7b0,0x2caba0,0x36a1a0};
    static const uint32_t accessors[]={0x2c85f0,0x2bd820,0x2cac10,0x36a210};
    static const uint32_t names[]={0x4f8448,0x4f6480,0x4f8628,0x505dc0};
    static const uint32_t vtables[]={0x5309b0,0x5249b0,0x531b70,0x534890};
    static const uint32_t parents[]={0x2ff4f0,0x2c8580,0x2c8580,0x2bd7b0};
    static const uint32_t parent_getters[]={0x135530,0x143720,0x143720,0x130c00};
    static const uint32_t adders[]={0x2c8600,0x2bd830,0x2cac20,0};
    for(unsigned i=0;i<4;i++){
        if(entry==allocate[i]){
            if(!P(handles[i])){uint64_t allocator=CALL(0x2f88e0,P(0x587040));W(handles[i],(uint32_t)CALL(0x2be4f0,allocator));}
            return word(P(handles[i]));
        }
        if(entry==ready[i]){uint32_t meta=P(handles[i]);if(!meta||!(P(meta+36)&4))CALL(guards[i]);return word(P(handles[i]));}
        if(entry==tables[i]){CALL(0x2fef20,scratch+16);W(scratch+16,vtables[i]);return word(P(scratch+16+P(P(0x586dc8)+916)));}
        if(entry==guards[i]){CALL(0x2fe940,registrars[i]);return 0;}
        if(entry==accessors[i])return CALL(ready[i]);
        if(entry==registrars[i]){
            CALL(i==3?0x33c8e0:0x2b5d50);
            return dw4_reflection_registration(a,0x2fe9c0,(const uint64_t[12]){0,handles[i],parents[i],parent_getters[i],accessors[i],names[i],20,tables[i],adders[i],0,i==3?0x4c7b98:0},scratch);
        }
    }
    switch(entry){
    case 0x143720:return word(P(0x586788));
    case 0x130c00:return word(P(0x585b60));
    case 0x2b7660:if(!P(0x585768))CALL(0x2b7500);return word(P(0x585768));
    case 0x2bd2e0:if(!P(0x585b28))CALL(0x2bd0c0);return word(P(0x585b28));
    case 0x2c3090:if(!P(0x586100))CALL(0x2c2f30);return word(P(0x586100));
    case 0x2bd830:case 0x2cac20:return dw4_list_descriptor_copy(a,entry,v);
    case 0x2c8600:{
        uint32_t meta=P(0x586788);uint32_t start=P(P(meta+40)+12);
        CALL(0x2fdf40,meta,0x4c1380,3);
        uint32_t field=P(P(P(meta+40)+8)+(start+2)*4);
        W(field+60,(uint32_t)CALL(0x2b7660));SB(field+53,1);SB(field+64,1);SB(field+65,1);
        CALL(0x2fe000,meta,0x4c1390,0x4c13a0,0x4c13b0,start);return 0;
    }
    default:return UINT64_MAX;
    }
}
