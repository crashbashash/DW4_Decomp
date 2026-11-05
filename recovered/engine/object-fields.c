/* Generic field cleanup/serialization and concrete object-reference operations.
 * Behavioral recovery; compiler matching is validated independently. */
#include "object-fields.h"
typedef const Dw4MessengerResultsApi *Api;
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define B(p) ((unsigned)a->read(a->user,(p),1))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define CORE(e,...) dw4_object_field(a,(e),(const uint64_t[8]){__VA_ARGS__})
static uint64_t word(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint32_t method(Api a,uint32_t object,unsigned slot){return P(P(object)+slot);}
static void retain(Api a,uint32_t p){if(p)W(p+4,P(p+4)+1);}
static void release(Api a,uint32_t p){if(p){W(p+4,P(p+4)-1);if(!(P(p+4)&0x7fffff))CALL(0x2ff820,p);}}
uint64_t dw4_object_field(Api a,uint32_t entry,const uint64_t v[8]){
    uint32_t self=(uint32_t)v[0],object=(uint32_t)v[1],meta,fields,field,value;
    int32_t count,begin;
    switch(entry){
    case 0x300b00:
        if(CALL((uint32_t)v[1],v[0],0,v[2])==1)return 0;
        CALL(method(a,self,72),v[0]);
        meta=(uint32_t)CALL(method(a,self,88),v[0]);fields=P(meta+40);
        count=(int32_t)P(fields+12);begin=(int32_t)CORE(0x2fe470,P(0x587198));
        for(int32_t i=begin;i<count;i++){
            field=P(P(fields+8)+(uint32_t)i*4);
            if(CALL((uint32_t)v[1],v[0],field,v[2])!=1)
                CALL(method(a,field,168),field,v[0],v[1],v[2]);
        }
        break;
    case 0x2fe470:return word(P(P(self+40)+12));
    case 0x2fdf00:return word(P(P(P(self+40)+8)+(uint32_t)v[1]*4));
    case 0x2ffc10:case 0x2ffcb0:
        if(entry==0x2ffc10)CALL(method(a,self,16),v[0]);
        meta=(uint32_t)CALL(method(a,self,88),v[0]);fields=P(meta+40);
        count=(int32_t)P(fields+12);begin=(int32_t)P(P(P(0x587198)+40)+12);
        for(int32_t i=begin;i<count;i++){
            field=P(P(fields+8)+(uint32_t)i*4);
            CALL(method(a,field,entry==0x2ffc10?128:136),field,v[0]);
        }break;
    case 0x2ffd40:{
        meta=(uint32_t)CALL(method(a,self,88),v[0]);
        if(P(meta+64))meta=(uint32_t)CALL(P(meta+64));
        if(!B(meta+25))return 0;
        uint32_t size=8;
        begin=(int32_t)CORE(0x2fe470,P(0x587198));count=(int32_t)CORE(0x2fe470,meta);
        for(int32_t i=begin;i<count;i++){
            field=(uint32_t)CORE(0x2fdf00,meta,(uint64_t)(int64_t)i);
            size+=(uint32_t)CALL(method(a,field,196),field,v[0]);
        }return word(size);
    }
    case 0x2ffe10:{
        meta=(uint32_t)CALL(method(a,self,88),v[0]);if(!B(meta+25))return 0;
        CALL(method(a,self,56),v[0]);if(P(meta+64))meta=(uint32_t)CALL(P(meta+64));
        uint32_t id=v[3]?(uint32_t)CALL(0x2fe600,v[3],meta):0;
        count=(int32_t)CORE(0x2fe470,meta);begin=(int32_t)CORE(0x2fe470,P(0x587198));
        W(object,id);W(object+4,(uint32_t)CORE(0x2ffd40,v[0]));
        if(v[4]){uint32_t swap=(uint32_t)CALL(0x2c3090);CALL(method(a,swap,208),swap,v[1],2);}
        uint32_t cursor=object+8;
        for(int32_t i=begin;i<count;i++){
            field=(uint32_t)CORE(0x2fdf00,meta,(uint64_t)(int64_t)i);
            if(B(field+38)==1&&!B(field+37))cursor+=(uint32_t)CALL(0x2fc6f0,field,v[0],cursor,v[2],v[4]);
        }
        return CORE(0x2ffd40,v[0]);
    }
    case 0x303390:
        value=P(object+P(self+8));
        if(B(self+60)||B(self+53)){retain(a,(uint32_t)v[2]);release(a,value);}
        W(object+P(self+8),(uint32_t)v[2]);break;
    case 0x303450:return 4;
    case 0x305cd0:return B(self+52);
    case 0x303540:{
        if(!B(self+52))break;
        uint32_t name=P(self+64);uint64_t allocator=0;
        if(name&&B(name))allocator=CALL(0x2f8920,name);
        if(!allocator)allocator=CALL(0x301000,v[1]);
        uint64_t child=CALL(0x2fda40,P(self+56),allocator);
        CORE(0x303390,v[0],v[1],child);
        if(B(self+60)||B(self+53))release(a,(uint32_t)child);
        break;
    }
    case 0x303620:if(B(self+53))release(a,P(object+P(self+8)));break;
    case 0x303680:
        if(B(self+60))release(a,P(object+P(self+8)));
        CORE(0x305540,v[0],v[1]);break;
    case 0x305500:case 0x305540:{
        uint32_t destination=object+P(self+8);
        uint32_t size=(uint32_t)CALL(method(a,self,100),v[0])&65535;
        CALL(0x12724c,destination,0,size);break;
    }
    default:return UINT64_MAX;
    }
    return 0;
}
