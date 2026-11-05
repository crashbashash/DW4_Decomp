/* Metadata registration, field creation/binding and runtime-prefix layout.
 * Behavioral guest-reference recovery, not a compiler-match assertion. */
#include "reflection-registration.h"
typedef const Dw4MessengerResultsApi *Api;
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define H(p) ((uint32_t)a->read(a->user,(p),2))
#define B(p) ((unsigned)a->read(a->user,(p),1))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define SH(p,v) a->write(a->user,(p),2,(uint16_t)(v))
#define SB(p,v) a->write(a->user,(p),1,(uint8_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define CORE(e,...) dw4_reflection_registration(a,(e),(const uint64_t[12]){__VA_ARGS__},scratch)
static void release(Api a,uint32_t p){if(p){W(p+4,P(p+4)-1);if(!(P(p+4)&0x7fffff))CALL(0x2ff820,p);}}
static void unstring(Api a,uint32_t p){if(p){uint32_t n=P(p-4)-1;W(p-4,n);if(!n)CALL(0x30c940,P(p-8),p-8);}}
static uint32_t field_count(Api a,uint32_t p){return P(P(p+40)+12);}
static uint32_t field_at(Api a,uint32_t p,int32_t i){return P(P(P(p+40)+8)+(uint32_t)i*4);}
static uint32_t method(Api a,uint32_t p,unsigned slot){return P(P(p)+slot);}
static uint32_t meta_allocator(Api a){return (uint32_t)CALL(0x2f88e0,P(0x587040));}
uint64_t dw4_reflection_registration(Api a,uint32_t entry,const uint64_t v[12],uint32_t scratch){
    uint32_t self=(uint32_t)v[0],field,value,parent;
    switch(entry){
    case 0x2ead30:
        value=(uint32_t)v[1];if(value)W(value+4,P(value+4)+1);
        CALL(0x2eaa60,v[0],v[1]);break;
    case 0x2fde50:CORE(0x2ead30,P(self+40),v[1]);break;
    case 0x2fdc50:
        parent=(uint32_t)v[1];if(!v[1])break;
        if(!P(parent+52))W(parent+52,(uint32_t)CALL(0x2c29c0,meta_allocator(a)));
        CALL(0x2eaa60,P(parent+52),v[0]);W(self+56,parent);W(self+92,P(parent+92));
        SH(self+88,H(P(self+56)+88));W(self+32,P(P(self+56)+32));W(self+72,P(P(self+56)+72));
        {int32_t n=(int32_t)field_count(a,parent);
        for(int32_t i=0;i<n;i++)CORE(0x2fde50,v[0],field_at(a,parent,i));}break;
    case 0x2fdf40:
        for(int32_t i=0;i<(int32_t)v[2];i++){
            uint32_t allocator=meta_allocator(a);
            field=(uint32_t)CALL(P((uint32_t)v[1]+(uint32_t)i*4),allocator);
            CORE(0x2fde50,v[0],field);
            /* Factory success is assumed: the original does not null-guard. */
            W(field+4,P(field+4)-1);if(!(P(field+4)&0x7fffff))CALL(0x2ff820,field);
        }break;
    case 0x2fc490:
        value=P((uint32_t)v[1]);if(value)W(value-4,P(value-4)+1);
        unstring(a,P(self+12));W(self+12,P((uint32_t)v[1]));break;
    case 0x2fc2c0:
        value=0;
        if(v[1]){
            uint32_t pool=P(0x586f20);
            if(!pool){pool=(uint32_t)CALL(0x2eb010,16);if(pool)pool=(uint32_t)CALL(0x2eadf0,pool);W(0x586f20,pool);}
            value=(uint32_t)CALL(0x2eaf60,P(0x586f20),v[1]);
        }
        W(scratch,value);CORE(0x2fc490,v[0],scratch);unstring(a,P(scratch));
        W(self+28,(uint32_t)v[2]);W(self+8,(uint32_t)v[3]);W(self+24,(uint32_t)v[4]);CORE(0x2fc3b0,v[0]);break;
    case 0x2fc3b0:{
        SH(self+20,(uint32_t)CALL(method(a,self,100),v[0]));value=P(self+32);
        if(!value)W(self+32,(uint32_t)CALL(0x300e00,v[0],H(self+20),1));
        else{
            uint32_t size=H(self+20);uint64_t oldsize=CALL(0x2ed4e0,value);
            if((int64_t)oldsize<(int64_t)size){CALL(0x300f00,v[0],P(self+32));W(self+32,(uint32_t)CALL(0x300e00,v[0],H(self+20),1));}
        }break;
    }
    case 0x2fc440:
        CORE(0x2fc3b0,v[0]);if(v[1])CALL(0x127098,P(self+32),v[1],H(self+20));break;
    case 0x2fc630:
        value=(uint32_t)CALL(method(a,self,92),v[0]);SH(self+16,value?H(value+18):65535);
        SH(self+20,(uint32_t)CALL(method(a,self,100),v[0]));CALL(method(a,self,140),v[0],0);
        value=P(self+28);if(value)W(value,self);break;
    case 0x2fe000:{
        int32_t n=(int32_t)field_count(a,self),index=(int32_t)v[4];uint32_t row=0;
        for(;index<n;index++,row++){
            field=field_at(a,self,index);
            CORE(0x2fc2c0,field,P((uint32_t)v[1]+row*4),P((uint32_t)v[2]+row*4),P((uint32_t)v[3]+row*4),v[0]);
            CORE(0x2fc630,field);
        }break;
    }
    case 0x2fe0d0:{
        int32_t n=(int32_t)field_count(a,self);uint32_t prefix=0,normal_align=4,all_align=4,runtime_count=0;
        for(int32_t i=0;i<n;i++){
            field=field_at(a,self,i);uint32_t alignment=(uint32_t)CALL(method(a,field,108),field)&65535;
            if(all_align<alignment)all_align=alignment;
            if(!B(field+37)){
                parent=P(self+56);
                if(!parent||(int32_t)field_count(a,parent)<=i||field_at(a,parent,i)!=field){SH(field+18,(uint32_t)i-runtime_count);W(field+24,self);}
                if(normal_align<=alignment)normal_align=alignment;
            }else{runtime_count++;prefix=(prefix-H(field+20))&~(alignment-1);W(field+8,prefix);}
        }
        SH(self+88,all_align);if(P(self+72)!=0xffffffff)W(self+32,0u-(prefix&~(normal_align-1)));
        W(self+36,P(self+36)|4);CALL(0x2d3150,P(0x586dc8),v[0]);break;
    }
    case 0x3581f0:
        CALL(0x33c8e0);
        return CORE(0x2fe9c0,0,0x588f88,0x2ff4f0,0x135530,0x358270,0x5043d0,32,0x358100,0x358290,0,0x4c5cc8);
    case 0x358290:{
        uint32_t meta=P(0x588f88);int32_t start=(int32_t)field_count(a,meta);
        CORE(0x2fdf40,meta,0x4c5ce0,6);
        field=field_at(a,meta,start+4);W(field+56,(uint32_t)CALL(0x2caab0));SB(field+52,1);
        field=field_at(a,meta,start+5);W(field+56,(uint32_t)CALL(0x36a0a0));SB(field+52,1);
        CORE(0x2fe000,meta,0x4c5d00,0x4c5d20,0x4c5d40,(uint64_t)(int64_t)start);break;
    }
    case 0x2fe9c0:{
        uint32_t allocator=meta_allocator(a),handle=(uint32_t)v[1];
        if(!P(handle)){
            for(unsigned i=0;i<15;i++)SB(scratch+16+i,B(0x4faf20+i));
            if(v[5])CALL(0x12a1e8,scratch+16,v[5]);
            W(handle,(uint32_t)CALL(0x2be4f0,allocator));
        }
        uint32_t meta=P(handle);uint64_t callbacks=0;
        if(!(P(meta+36)&8)){
            W(meta+36,P(meta+36)|8);
            int configured=0;
            if(!(P(meta+36)&4)){
                if(!(P(meta+36)&2)){
                    configured=1;
                    if(!(P(meta+36)&1)){
                        callbacks=CALL((uint32_t)v[2],meta);
                        parent=(uint32_t)CALL((uint32_t)v[3]);CORE(0x2fdc50,meta,parent);W(meta+36,P(meta+36)|1);
                    }
                    CALL(0x2fddb0,meta,v[5]);W(meta+72,(uint32_t)v[6]);W(meta+84,(uint32_t)v[4]);SB(meta+26,(uint32_t)v[0]);
                    if(!v[0])W(meta+92,(uint32_t)CALL((uint32_t)v[7]));
                    if(v[8])CALL((uint32_t)v[8]);
                    W(meta+36,P(meta+36)|2);CALL(0x2fe7a0,meta);release(a,meta);
                    uint32_t system=P(0x586dc8);
                    if(P(system+100)&&P(system+96)&&P(system+104)){
                        uint64_t found=CALL(0x30d350,P(system+104),v[5]);
                        if(found!=UINT64_MAX)CALL(0x2fe810,scratch,meta,P(P(0x586dc8)+96));
                    }
                }
                CORE(0x2fe0d0,meta);
                value=P(meta+76);if(value)CALL(value,meta);
                if(!callbacks){allocator=meta_allocator(a);callbacks=CALL(0x2ed240,12,allocator);if(callbacks)callbacks=CALL(0x2d3400,callbacks);}
                uint32_t list=(uint32_t)v[10];if(list){while(P(list)){CALL(0x2d3480,callbacks,P(list));list+=4;}}
                if(configured&&v[9])CALL(0x2d3480,callbacks,v[9]);
                W(meta+36,P(meta+36)|4);
            }
            W(meta+36,P(meta+36)&~8u);
        }
        return callbacks;
    }
    default:return UINT64_MAX;
    }
    return 0;
}
