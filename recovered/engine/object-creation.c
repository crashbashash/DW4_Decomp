/* Original reflection allocation/construction and messenger factory path.
 * Behavioral recovery; no compiler match is implied by this adapter. */
#include "object-creation.h"
typedef const Dw4MessengerResultsApi *Api;
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define B(p) ((unsigned)a->read(a->user,(p),1))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define SB(p,v) a->write(a->user,(p),1,(uint8_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define CORE(e,...) dw4_object_creation(a,(e),(const uint64_t[8]){__VA_ARGS__})
static uint64_t virtual_call(Api a,uint32_t self,unsigned slot,uint64_t x){return CALL(P(P(self)+slot),self,x);}
static void count_instance(Api a,uint32_t object){
    uint32_t meta=(uint32_t)virtual_call(a,object,88,0);
    if(meta){W(meta+44,P(meta+44)+1);if(P(meta+48))CALL(0x2eaa60,P(meta+48),object);}
}
static uint64_t create(Api a,uint32_t entry,uint64_t receiver,uint64_t allocator){
    uint32_t meta=(uint32_t)receiver;int pooled=entry==0x2fdb40;
    if(pooled&&!(P(meta+36)&4))return 0;
    uint32_t redirect=P(meta+60);
    if(redirect){uint64_t next=CALL(redirect,receiver,allocator);return CORE(entry,next,allocator);}
    if(B(meta+26)==1)return 0;
    if(!allocator){
        uint32_t name=P(meta+96);
        if(name&&B(name))allocator=CALL(0x2f8920,name);
        if(!allocator)allocator=CALL(0x2f00d0);
    }
    uint32_t offset=P(meta+32),size=P(meta+72);
    uint32_t base=(uint32_t)CALL(P(P((uint32_t)allocator)+216),allocator,offset+size);
    uint32_t object=base+offset;
    if(object)CORE(pooled?0x2ff2f0:0x2ff1d0,object,receiver);
    return (uint64_t)(int64_t)(int32_t)object;
}
static void field_pass(Api a,uint32_t entry,uint64_t receiver){
    uint32_t object=(uint32_t)receiver,meta=(uint32_t)virtual_call(a,object,88,0);
    if(entry==0x2ff930&&!((meta&&(P(meta+36)&4))||!B(P(0x586dc8)+20)||B(P(0x586dc8))))return;
    uint32_t fields=P(meta+40);int32_t count=(int32_t)P(fields+12);
    int32_t begin=(int32_t)P(P(P(0x587198)+40)+12);
    for(int32_t i=begin;i<count;i++){
        uint32_t field=P(P(fields+8)+(uint32_t)i*4);
        if(entry==0x2ff930)CALL(P(P(field)+132),field,receiver);
        else if(entry==0x2ffa00)CALL(P(P(field)+124),field,receiver);
        else if(entry==0x2ffab0)CALL(0x2fc500,field,receiver);
        else if(!virtual_call(a,field,240,0))CALL(0x2fc500,field,receiver);
    }
    if(entry!=0x2ff930)virtual_call(a,object,entry==0x2ffa00?12:52,1);
}
uint64_t dw4_object_creation(Api a,uint32_t entry,const uint64_t v[8]){
    static const uint32_t factories[]={0x358070,0x3584e0,0x358950,0x358d80};
    static const uint32_t guards[]={0x3581d0,0x358620,0x358a90,0x358fa0};
    static const uint32_t registrars[]={0x3581f0,0x358640,0x358ab0,0x358fc0};
    static const uint32_t handles[]={0x588f88,0x588fc8,0x588ff0,0x589038};
    for(unsigned i=0;i<4;i++){
        if(entry==factories[i]){CORE(guards[i]);return CORE(0x2fda40,P(handles[i]),v[0]);}
        if(entry==guards[i]){CORE(0x2fe940,registrars[i]);return 0;}
    }
    uint32_t self=(uint32_t)v[0],meta=(uint32_t)v[1];
    switch(entry){
    case 0x2fda10:{uint64_t allocator=CALL(0x2f00d0,v[0]);return CORE(0x2fda40,v[0],allocator);}
    case 0x2fda40:case 0x2fdb40:return create(a,entry,v[0],v[1]);
    case 0x2fe940:{
        uint32_t callbacks=(uint32_t)CALL(self,v[0]);
        if(callbacks){int32_t n=(int32_t)P(callbacks+4);
            for(int32_t i=0;i<n;i++)CALL(P(P(callbacks)+(uint32_t)i*4),callbacks);
            CALL(0x2d3420,callbacks,1);
        }break;
    }
    case 0x2ff1d0:case 0x2ff2f0:{
        W(self+P(P(0x586dc8)+916),P(meta+92));
        if(entry==0x2ff1d0)W(self+4,0);
        W(self+4,(P(self+4)&0xff800000)|1);SB(self+6,B(self+6)&127);
        uint64_t allocation=CALL(0x300d30,v[0]),owner=CALL(0x2f04f0,allocation);
        SB(self+7,owner?virtual_call(a,(uint32_t)owner,364,0):0);
        CORE(0x2ff930,v[0]);
        if(entry==0x2ff1d0){CORE(0x2ffa00,v[0]);CORE(0x2ffb50,v[0]);virtual_call(a,self,44,0);virtual_call(a,self,36,0);count_instance(a,self);}
        break;
    }
    case 0x2ff3a0:
        if(v[1]&&P(meta+60))virtual_call(a,self,80,v[1]);
        virtual_call(a,self,12,0);virtual_call(a,self,52,0);virtual_call(a,self,36,1);count_instance(a,self);break;
    case 0x2ff930:case 0x2ffa00:case 0x2ffab0:case 0x2ffb50:field_pass(a,entry,v[0]);break;
    case 0x2ff820:{
        uint32_t system=P(0x586dc8);if(!system)break;
        if(!B(system)){
            virtual_call(a,self,40,0);virtual_call(a,self,48,0);virtual_call(a,self,8,0);CALL(0x2ed460,v[0]);
        }else{
            uint32_t type=(uint32_t)virtual_call(a,self,88,0);W(type+44,P(type+44)-1);
            uint32_t list=P(type+48);
            if(list){uint64_t found=CALL(0x2ea820,list,v[0]);CALL(0x2eaa00,list,found);}
            virtual_call(a,self,72,0);virtual_call(a,self,40,0);virtual_call(a,self,48,0);
            CALL(0x2ffc10,v[0]);CALL(0x2ffcb0,v[0]);CALL(0x2ed460,CALL(0x300d30,v[0]));
        }break;
    }
    default:return UINT64_MAX;
    }
    return 0;
}
