/* Descriptor construction/copy and actual inherited _data specialization. */
#include "list-descriptor-copy.h"
#include "field-factories.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define B(p) ((uint32_t)a->read(a->user,(p),1))
#define H(p) ((uint32_t)a->read(a->user,(p),2))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define SB(p,v) a->write(a->user,(p),1,(uint8_t)(v))
#define SH(p,v) a->write(a->user,(p),2,(uint16_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define CORE(e,...) dw4_list_descriptor_copy(a,(e),(const uint64_t[8]){__VA_ARGS__})
static void release(const Dw4MessengerResultsApi *a,uint32_t p){if(p){W(p+4,P(p+4)-1);if(!(P(p+4)&0x7fffff))CALL(0x2ff820,p);}}
uint64_t dw4_list_descriptor_copy(const Dw4MessengerResultsApi *a,uint32_t entry,const uint64_t v[8]){
    uint32_t self=(uint32_t)v[0],source=(uint32_t)v[1],value;
    switch(entry){
    case 0x2bf2e0:case 0x2fb8e0:case 0x2fb930:return dw4_field_factory(a,entry,v);
    case 0x2fc0e0:
        CALL(0x2fef70,v[0],v[1]);W(self,0x52f230);W(self+12,0);
        W(self+8,P(source+8));SB(self+37,B(source+37));SH(self+16,H(source+16));SH(self+20,H(source+20));SH(self+18,H(source+18));W(self+28,P(source+28));
        value=P(source+12);if(value)W(value-4,P(value-4)+1);
        value=P(self+12);if(value){W(value-4,P(value-4)-1);if(!P(value-4))CALL(0x30c940,P(value-8),value-8);}
        W(self+12,P(source+12));W(self+24,P(source+24));W(self+48,P(source+48));
        SB(self+36,B(source+36));SB(self+39,B(source+39));SB(self+40,B(source+40));SB(self+41,B(source+41));SB(self+42,B(source+42));SB(self+43,B(source+43));SB(self+44,B(source+44));SB(self+38,B(source+38));
        W(self+32,(uint32_t)CALL(0x300d70,v[0],H(self+20)));CALL(0x127098,P(self+32),P(source+32),H(self+20));return v[0];
    case 0x305c70:
        CORE(0x2fc0e0,v[0],v[1]);W(self,0x52ec50);SB(self+52,B(source+52));SB(self+53,B(source+53));return v[0];
    case 0x2fb9a0:
        CORE(0x305c70,v[0],v[1]);W(self,0x532a50);W(self+72,0);W(self+76,0);
        SB(self+66,B(source+66));W(self+60,P(source+60));W(self+56,P(source+56));SB(self+36,B(source+36));SB(self+65,B(source+65));SB(self+64,B(source+64));W(self+68,P(source+68));return v[0];
    case 0x2ff800:return CALL(0x2ff790,v[0],v[1],0);
    case 0x2bf380:
        if(B(P(0x586dc8))){CALL(0x2bf680);return CORE(0x300c60,v[0],v[1]);}
        value=(uint32_t)CORE(0x2ff800,80,0);return value?CORE(0x2fb9a0,value,v[0]):0;
    case 0x300c60:{
        uint32_t meta=(uint32_t)CALL(P(P(self)+88),v[0]);uint64_t allocator=CALL(0x301000,v[0]);
        uint64_t result=CALL(0x2fda40,meta,allocator);CALL(0x300c00,result,v[0],v[1]);return result;
    }
    case 0x2bd830:case 0x2cac20:{
        uint32_t meta=P(entry==0x2bd830?0x585b60:0x586880);
        uint32_t old=(uint32_t)CALL(0x2fdf20,meta,0x4f5eb0);
        uint64_t index=CALL(0x2ea820,P(meta+40),old);
        uint32_t field=(uint32_t)CALL(P(P(old)+84),old,1);
        W(field+60,(uint32_t)CALL(entry==0x2bd830?0x2bd2e0:0x2c3090));W(field+56,0);W(field+28,entry==0x2bd830?0x585b68:0x586888);
        CALL(0x2fdea0,meta,index,field);release(a,field);return 0;
    }
    default:return UINT64_MAX;
    }
}
