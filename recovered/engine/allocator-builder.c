/* Complete original context slot204 builder (2f5cd0). */
#include "allocator-builder.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define B(p) ((uint32_t)a->read(a->user,(p),1))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
static uint64_t word(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint32_t method(const Dw4MessengerResultsApi *a,uint32_t object,unsigned slot){return P(P(object)+slot);}
static void release(const Dw4MessengerResultsApi *a,uint32_t object){
    if(object){W(object+4,P(object+4)-1);if(!(P(object+4)&0x7fffff))CALL(0x2ff820,object);}
}
static void enable(const Dw4MessengerResultsApi *a,uint32_t object){
    if(!CALL(method(a,object,132),object))CALL(method(a,object,120),object);
}
static int contains(const Dw4MessengerResultsApi *a,uint32_t text,uint32_t token){
    return CALL(0x12aff0,text,token)!=0;
}
static int equals(const Dw4MessengerResultsApi *a,uint32_t text,uint32_t token){
    return CALL(0x12a4a4,text,token)==0;
}
static void status(const Dw4MessengerResultsApi *a,uint32_t out,int success){W(out,P(success?0x4fb410:0x4fb418));}
uint64_t dw4_allocator_builder(const Dw4MessengerResultsApi *a,uint32_t entry,const uint64_t v[8],uint32_t scratch){
    if(entry==0x2fe460)return CALL(0x2d3070,P(0x586dc8),v[0]);
    if(entry==0x2d3070){
        uint32_t system=(uint32_t)v[0];
        return B(system)?CALL(0x2ea780,P(system+24),P(0x585c28),v[1]):0;
    }
    if(entry!=0x2f5cd0)return UINT64_MAX;
    uint32_t out=(uint32_t)v[0],context=(uint32_t)v[1],index=(uint32_t)v[2],mode=(uint32_t)v[3];
    uint32_t meta=P(0x586a88),primary=P(context+20),current=P(context+164),nontracked=P(context+452);
    uint32_t row=context+index*144,cell=row+20,config=P(row+152),target=P(cell);
    if(!primary)primary=(uint32_t)CALL(0x2f88e0,P(0x587018));
    if(!current){current=(uint32_t)CALL(0x2f88e0,P(0x587020));if(!current)current=primary;}
    if(!nontracked)CALL(0x2f88e0,P(0x587030)); /* Original side-effect lookup; result is discarded. */
    if(index==2){W(cell,current);W(current+4,P(current+4)+1);}
    if(!config){status(a,out,(int32_t)index>=30);return 0;}
    uint32_t options=P(config+52);
    if(options){
        W(cell+140,0);
        if(!contains(a,P(config+52),0x4fa620)){
            if(contains(a,P(config+52),0x4fa2a8))W(cell+140,P(cell+140)|1);
            else if(contains(a,P(config+52),0x4fa2b0))W(cell+140,P(cell+140)|2);
        }
        if(contains(a,P(config+52),0x4fa630))W(cell+140,P(cell+140)|0x01000000);
        if(contains(a,P(config+52),0x4fa638))W(cell+140,P(cell+140)|0x02000000);
        if(contains(a,P(config+52),0x4fa600))W(cell+140,P(cell+140)|0x04000000);
        uint32_t flags=P(cell+140);
        if(!mode&&(flags&0xffffff)&&(flags&0x05000000)){status(a,out,1);return 0;}
    }
    if(target){
        uint32_t length=P(config+28);
        if(length){
            uint32_t kind=P(config+44);
            if(!kind||equals(a,kind,0x4fa640))CALL(method(a,target,172),scratch,target,word(length));
        }
        enable(a,target);status(a,out,1);return 0;
    }
    uint32_t alias_name=P(config+24);
    if(alias_name&&B(alias_name)){
        uint32_t alias_index=(uint32_t)CALL(method(a,context,116),context,alias_name);
        if(alias_index!=0xffffffff){
            uint32_t alias_cell=context+alias_index*144+20;
            target=P(alias_cell);
            if(!target){
                CALL(method(a,context,204),scratch,context,word(alias_index),v[3]);
                if(P(scratch)!=P(0x4fb410)){status(a,out,0);return 0;}
                target=P(alias_cell);
            }
        }
        if(target){
            int owned=(P(context+12)&4)!=0;
            if(owned){
                options=P(config+52);
                if(options&&(contains(a,options,0x4fa600)||contains(a,P(config+52),0x4fa648)||contains(a,P(config+52),0x4fa658))&&!mode){
                    status(a,out,1);return 0;
                }
                if(index==5){if(!CALL(0x2f88e0,P(0x587040)))W(context+740,primary);}
                uint32_t borrowed=target;
                target=(uint32_t)CALL(0x2cd170,primary);
                CALL(method(a,target,400),target,borrowed);
                if(index==5&&P(context+740)==primary)W(context+740,0);
            }
            CALL(method(a,context,100),context,v[2],target);
            if(owned)release(a,target);
            enable(a,target);status(a,out,1);return 0;
        }
    }
    uint32_t class_name=P(config+40);
    if(class_name&&B(class_name)){
        meta=(uint32_t)CALL(0x2fe460,class_name);
        if(!meta)meta=P(0x586a88);
    }
    target=(uint32_t)CALL(0x2fda40,meta,primary);
    uint32_t length=P(config+28),tracker=P(0x587218);
    uint32_t alignment=(uint32_t)CALL(method(a,tracker,84),tracker);
    uint32_t rounded=length+alignment-1;
    tracker=P(0x587218);alignment=(uint32_t)CALL(method(a,tracker,84),tracker);
    rounded&=~(alignment-1);
    if(length){
        uint32_t kind=P(config+44);
        if(!kind||equals(a,kind,0x4fa640))CALL(method(a,target,172),scratch,target,word(length));
        else if(equals(a,P(config+44),0x4fa5e8)){
            uint32_t backing=P(config+48);
            if(backing&&B(backing)){
                if(equals(a,backing,0x4fa668)||equals(a,backing,0x4fa678)||equals(a,backing,0x4fa680)||equals(a,backing,0x4fa688)){
                    tracker=P(0x587218);
                    uint64_t buffer=CALL(method(a,tracker,68),tracker,0,word(rounded));
                    CALL(method(a,target,96),scratch,target,buffer,word(rounded),0);
                    W(cell+136,P(cell+136)|2);backing=0;
                }else if(equals(a,backing,0x4fa5f0)){
                    uint32_t base=P(config+36);if(!base)base=0x70000000;
                    CALL(method(a,target,96),scratch,target,base,word(length),0);backing=0;
                }else if(equals(a,backing,0x4fa690)||equals(a,backing,0x4fa698)){
                    backing=0;
                }else{
                    backing=(uint32_t)CALL(method(a,context,96),context,backing);
                    if(!backing)backing=current;
                }
            }else backing=current;
            if(backing){
                enable(a,backing);
                uint64_t buffer=CALL(method(a,backing,216),backing,word(length));
                CALL(method(a,target,96),scratch,target,buffer,word(length),1);
                W(backing+4,P(backing+4)+1);W(cell+136,P(cell+136)|1);
            }
        }
    }
    CALL(method(a,target,180),scratch,target,config);
    CALL(method(a,context,100),context,v[2],target);
    release(a,target);enable(a,target);status(a,out,1);return 0;
}
