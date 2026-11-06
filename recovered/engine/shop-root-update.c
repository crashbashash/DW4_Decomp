/* Original generic service-root state machine. */
#include "shop-root-update.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define B(p) ((uint32_t)a->read(a->user,(p),1))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define MSG word(P(self+12))
static uint64_t word(uint32_t p){return (uint64_t)(int64_t)(int32_t)p;}
static void release(const Dw4MessengerResultsApi*a,uint32_t p){
    if(p){W(p+4,P(p+4)-1);if(!(P(p+4)&0x7fffff))CALL(0x2ff820,word(p));}
}
static uint64_t allocator(const Dw4MessengerResultsApi*a,uint64_t self){
    uint64_t result=CALL(0x301000,self);
    if(!B(0x554c14))result=CALL(0x2f88e0,word(P(0x587110)));
    return result;
}
static void append(const Dw4MessengerResultsApi*a,uint32_t self,uint64_t owner,uint32_t temp,unsigned mode){
    uint64_t which=mode?word(P(self+44)):0;
    CALL(0x3f63c0,word(P(temp)),owner,word(P(self+8)),word(P(self+20)),which);
    CALL(0x301e30,word(P(self+52)),word(P(temp)));release(a,P(temp));
}
static void advance(const Dw4MessengerResultsApi*a,uint32_t self){
    W(self+28,P(self+28)+1);W(self+40,0);W(self+36,0);W(self+32,0);
}
uint64_t dw4_shop_root_update(const Dw4MessengerResultsApi*a,const uint64_t v[8],uint32_t scratch){
    uint32_t self=(uint32_t)v[0],state=P(self+28);
    if(state==0){
        static const uint32_t factories[]={0x3b3370,0x3b3ac0,0x3b3900,0x3b36f0,0x3b31b0};
        for(unsigned i=0;i<5;i++){
            uint32_t temp=scratch+76-i*4;
            W(temp,CALL(factories[i],allocator(a,v[0])));append(a,self,v[0],temp,i==4);
        }
        advance(a,self);
    }else if(state==1){
        uint32_t phase=P(self+32);
        if(phase!=1){
            if(phase!=0)return 0;
            CALL(0x38d860,MSG,0x51b308,0x51b318,0);
            CALL(0x38f830,MSG,0x51b328);CALL(0x38e060,MSG,0x51b338);
            if((CALL(0x38f220,MSG,0)&255)==1)return 0;
            W(scratch+56,0);uint32_t factory,mode=P(self+44);
            switch(mode){
            case 1:factory=0x3b8b60;break;
            case 3:factory=0x3b8630;break;
            case 4:factory=0x3b8400;break;
            case 5:factory=0x3b81d0;break;
            case 6:case 7:case 8:factory=0x3b6650;break;
            case 9:factory=0x3b6310;break;
            default:factory=0x3b8b60;break;
            }
            uint64_t pool=allocator(a,v[0]);release(a,P(scratch+56));
            W(scratch+56,CALL(factory,pool));append(a,self,v[0],scratch+56,1);
            W(self+80,P(P(self+52)+8));W(self+32,P(self+32)+1);W(self+40,0);W(self+36,0);
        }
        if(P(P(self+52)+8)!=P(self+80))advance(a,self);
    }else if(state==2){
        CALL(0x38e5f0,MSG,0x51b308,0x51b348,0,0x51b358);
        CALL(0x3f5f80,v[0]);CALL(0x3f5a40,v[0]);CALL(0x3f6350,v[0]);advance(a,self);
    }else if(state==3){
        if(CALL(0x3f6090,v[0]))a->write(a->user,self+24,1,0);
    }
    return 0;
}

uint64_t dw4_shop_root_reference_cleanup(const Dw4MessengerResultsApi*a,const uint64_t v[8]){
    if(v[0]){release(a,P((uint32_t)v[0]));if((int16_t)v[1]>0)CALL(0x100610,v[0]);}
    return v[0];
}
