/* Complete scalar-string value method run and retained field-slot helper.
 * Shared methods also appear in the derived string-array field vtable. */
#include "string-fields.h"
typedef const Dw4MessengerResultsApi *Api;
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define B(p) ((unsigned)a->read(a->user,(p),1))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define CORE(e,...) dw4_string_field(a,(e),(const uint64_t[8]){__VA_ARGS__},scratch)
static void retain(Api a,uint32_t token){if(token)W(token-4,P(token-4)+1);}
static void release(Api a,uint32_t token){if(token){uint32_t n=P(token-4)-1;W(token-4,n);if(!n)CALL(0x30c940,P(token-8),token-8);}}
static uint32_t intern(Api a,uint64_t text){
    uint32_t pool=P(0x586f20);
    if(!pool){pool=(uint32_t)CALL(0x2eb010,16);if(pool)pool=(uint32_t)CALL(0x2eadf0,pool);W(0x586f20,pool);}
    return (uint32_t)CALL(0x2eaf60,P(0x586f20),text);
}
static void assign_interned(Api a,uint32_t destination,uint64_t text){uint32_t value=intern(a,text);release(a,P(destination));W(destination,value);}
static uint32_t allocator(Api a,uint64_t field){
    uint32_t value=(uint32_t)CALL(0x301000,field);
    if(!B(0x554c14))value=(uint32_t)CALL(0x2f88e0,P(0x587060));
    return value;
}
static void swap_word(Api a,uint32_t p){uint32_t swap=(uint32_t)CALL(0x2c3090);CALL(P(P(swap)+208),swap,p,1);}
static uint64_t word(uint32_t value){return (uint64_t)(int64_t)(int32_t)value;}
uint64_t dw4_string_field(Api a,uint32_t entry,const uint64_t v[8],uint32_t scratch){
    uint32_t self=(uint32_t)v[0],object=(uint32_t)v[1],source=(uint32_t)v[2],value,old,slot;
    switch(entry){
    case 0x2fc500:
        value=B(self+36);
        if(value==0||value==2||value==3)CALL(P(P(self)+(value==0?112:value==2?120:116)),v[0],v[1]);
        break;
    case 0x2fc6f0:
        if(!B(self+38))return 0;
        value=(uint32_t)CALL(P(P(self)+200),v[0],object+P(self+8),v[2],v[3],v[4]);
        return word((value+3)&~3u);
    case 0x1c8c00:
        value=P(source);slot=object+P(self+8);retain(a,value);release(a,P(slot));W(slot,P(source));break;
    case 0x30a910:case 0x30aeb0:
        value=entry==0x30a910?P(source):P(P(self+32));
        W(scratch,value?intern(a,value):0);CORE(0x1c8c00,v[0],v[1],scratch);release(a,P(scratch));break;
    case 0x30a9d0:W(self,P(source));retain(a,P(self));break;
    case 0x30aa00:return 4;
    case 0x30aa10:
        slot=P(self+32);assign_interned(a,slot,v[1]);break;
    case 0x30aab0:
        if(!B(self+38))return 0;
        value=P(object+P(self+8));return value?word((((uint32_t)CALL(0x12a78c,value)+4)&~3u)+4):4;
    case 0x30ab20:{
        W(scratch,P(source));if(v[4])swap_word(a,scratch);
        int32_t length=(int32_t)P(scratch);
        if(length<1){assign_interned(a,object,0);return 4;}
        uint32_t remaining=(uint32_t)length,cursor=source+4;
        while(remaining&&B(cursor)){remaining--;cursor++;}
        if(!remaining){
            uint32_t alloc=allocator(a,v[0]);value=(uint32_t)CALL(P(P(alloc)+216),alloc,(uint32_t)length+1);
            CALL(0x127098,value,source+4,(uint32_t)length);a->write(a->user,value+(uint32_t)length,1,0);
            assign_interned(a,object,value);
            alloc=allocator(a,v[0]);CALL(P(P(alloc)+264),alloc,value);
        }else assign_interned(a,object,source+4);
        return word((uint32_t)length+4);
    }
    case 0x30add0:
        value=P(object);
        if(!value){W(source,0);return 4;}
        old=((uint32_t)CALL(0x12a78c,value)+4)&~3u;W(source,old);
        if(v[4])swap_word(a,source);
        CALL(0x12a5fc,source+4,P(object));return word(old+4);
    case 0x30ae90:case 0x30aea0:case 0x30b0b0:break;
    case 0x30af80:case 0x30aff0:
        value=P(source+P(self+8));W(scratch,value);retain(a,value);
        CORE(0x1c8c00,v[0],v[1],scratch);release(a,P(scratch));break;
    case 0x30b060:
        value=P(object+P(self+8));old=P(source+P(self+8));
        if(!value)return old?UINT64_MAX:0;
        return old?CALL(0x12a4a4,value,old):1;
    case 0x30b0c0:
        if(B(self+53)){W(scratch,0);CORE(0x1c8c00,v[0],v[1],scratch);release(a,P(scratch));}break;
    case 0x30b110:case 0x30b170:case 0x30b1d0:
        value=P(object+P(self+8));old=P(source+P(self+8));
        return value==old?1:(!value||!old)?0:!CALL(0x12a4a4,value,old);
    default:return UINT64_MAX;
    }
    return 0;
}
