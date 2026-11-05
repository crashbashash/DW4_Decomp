#include "context-lifecycle.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
static uint64_t word(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint32_t method(const Dw4MessengerResultsApi *a,uint32_t object,unsigned slot){return P(P(object)+slot);}
static void release(const Dw4MessengerResultsApi *a,uint32_t object){
    if(object){W(object+4,P(object+4)-1);if(!(P(object+4)&0x7fffff))CALL(0x2ff820,object);}
}
static void attach_tracker(const Dw4MessengerResultsApi *a,uint32_t context,uint32_t pool,uint32_t config_cell){
    uint32_t allocator=(uint32_t)CALL(method(a,context,92),context,3);
    uint32_t tracker=(uint32_t)CALL(0x2c5780,allocator);
    uint32_t config=P(config_cell),limit=P(config+80),fallback=P(P(0x586dc8)+124);
    CALL(0x2dcc40,tracker,limit?limit:fallback);
    CALL(method(a,tracker,92),tracker);
    CALL(method(a,pool,360),pool,tracker);
    release(a,tracker);
}
uint64_t dw4_context_lifecycle(const Dw4MessengerResultsApi *a,uint32_t entry,const uint64_t v[8],uint32_t scratch){
    uint32_t self=(uint32_t)v[0];
    switch(entry){
    case 0x2f25d0:{
        CALL(0x2fef20,v[0]);W(self,0x52f510);W(self+8,30);W(self+12,0);W(self+16,0);
        uint32_t parent=P(self+16);if(parent)W(parent+4,P(parent+4)+1);
        W(self+4,0);W(self+4,(P(self+4)&0xff800000)|1);
        CALL(0x12724c,self+20,0,6624);CALL(method(a,self,180),v[0]);return v[0];
    }
    case 0x2f2670:
        if(self){W(self,0x52f510);W(self+4,0);CALL(0x12724c,self+20,0,6624);CALL(method(a,self,180),v[0]);
            if(self+16)release(a,P(self+16));
            if((int16_t)v[1]>0)CALL(0x2f8830,v[0]);
        }
        return v[0];
    case 0x2f49e0:
        for(uint32_t i=0;i<46;++i){CALL(0x12ad58,self+i*144+24,P(0x4c2170+i*4),127);a->write(a->user,self+i*144+151,1,0);}
        return 0;
    case 0x2f8830:
        CALL(a->read(a->user,P(0x586dc8),1)?0x2ff810:0x126360,v[0]);return 0;
    case 0x2f28d0:{
        int32_t index=(int32_t)v[1];uint32_t value=(uint32_t)v[2];if(index<0||index>=46)return 0;
        uint32_t cell=self+(uint32_t)index*144+20,old=P(cell);
        if(old&&old==value)return 0;
        if(old)CALL(method(a,self,212),v[0],v[1]);
        W(cell,value);
        if(value){W(value+4,P(value+4)+1);uint32_t high=P(self+8);if(index>=(int32_t)high)W(self+8,(uint32_t)index+1);}
        return 0;
    }
    case 0x2f64e0:{
        uint32_t out=self,context=(uint32_t)v[1],index=(uint32_t)v[2];
        CALL(method(a,context,204),scratch,v[1],v[2],1);
        uint32_t row=context+index*144,pool=P(row+20),status=P(scratch),config_cell=row+152;
        if(P(context+12)&1){
            uint32_t config=P(config_cell),name=config?P(config+60):0;
            if(name&&CALL(0x12aff0,name,0x4fa530)){W(out,status);return 0;}
            if((P(context+12)&2)&&index!=1)attach_tracker(a,context,pool,config_cell);
            else if(name&&CALL(0x12aff0,name,0x4fa550))attach_tracker(a,context,pool,config_cell);
            else{
                uint32_t parent=(uint32_t)CALL(method(a,context,92),context,1);
                uint32_t tracker=(uint32_t)CALL(method(a,parent,356),parent);
                if(tracker)CALL(method(a,pool,360),pool,tracker);
            }
        }else{
            uint32_t config=P(config_cell),name=config?P(config+60):0;
            if(name&&CALL(0x12aff0,name,0x4fa550))attach_tracker(a,context,pool,config_cell);
        }
        W(out,status);return 0;
    }
    case 0x2f6780:{
        int32_t index=(int32_t)v[1];if(index<0||index>=46)return 0;
        uint32_t cell=self+(uint32_t)index*144+20,pool=P(cell);if(!pool)return 0;
        W(cell,0);
        if((P(pool+4)&0x7fffff)==1){
            if(CALL(method(a,pool,188),pool))CALL(method(a,pool,348),pool,0);
            CALL(method(a,pool,128),pool);
            uint32_t flags=P(cell+136);
            if(flags&1){
                W(cell+136,flags&~1u);
                uint32_t buffer=(uint32_t)CALL(method(a,pool,104),pool);
                if(buffer){CALL(method(a,pool,96),scratch+12,pool,0,0,0);
                    uint32_t owner=(uint32_t)CALL(0x2f04f0,buffer);
                    if(owner){release(a,owner);CALL(0x2ed460,buffer);}}
            }else if(flags&2){
                W(cell+136,flags&~2u);
                uint32_t buffer=(uint32_t)CALL(method(a,pool,104),pool);
                if(buffer){uint64_t size=word((uint32_t)CALL(method(a,pool,144),pool));
                    CALL(method(a,pool,96),scratch+8,pool,0,0,0);
                    uint32_t tracker=P(0x587218);CALL(method(a,tracker,72),scratch+4,tracker,buffer,size);}
            }
        }
        release(a,pool);if((uint32_t)index==P(self+8)+1)W(self+8,(uint32_t)index);return 0;
    }
    default:return UINT64_MAX;
    }
}
