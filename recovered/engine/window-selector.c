/* Original SELECTCTRL protocol and parent selection publication. */
#include "window-selector.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define B(p) ((uint32_t)a->read(a->user,(p),1))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define MSG word(P(self+12))
static uint64_t word(uint32_t p){return (uint64_t)(int64_t)(int32_t)p;}
static void advance(const Dw4MessengerResultsApi*a,uint32_t self){W(self+28,P(self+28)+1);W(self+40,0);W(self+36,0);W(self+32,0);}
static void select_self(const Dw4MessengerResultsApi*a,uint32_t self){CALL(0x38d860,MSG,0x51a918,word(P(self+80)),word(P(self+20)));}
static void send_self(const Dw4MessengerResultsApi*a,uint32_t self,uint32_t command){CALL(0x38e5f0,MSG,0x51a918,word(P(self+80)),word(P(self+20)),command);}
static void flags(const Dw4MessengerResultsApi*a,uint32_t self){
    if(P(self+108)&&(int32_t)P(P(self+108)+8)>0){
        uint32_t i=0;
        do{CALL(0x38f150,MSG,B(P(P(self+108)+16)+i));i++;}while((int32_t)i<(int32_t)P(P(self+108)+8));
    }
}
static void publish(const Dw4MessengerResultsApi*a,uint32_t self){send_self(a,self,0x51a948);uint64_t result=CALL(0x38f320,MSG,0);W(P(self+56)+48,result);}
uint64_t dw4_window_selector(const Dw4MessengerResultsApi*a,uint32_t entry,const uint64_t v[8],uint32_t scratch){
    uint32_t self=(uint32_t)v[0];
    if(entry==0x423700){send_self(a,self,0x51a968);return CALL(0x38f220,MSG,0)==0;}
    if(entry!=0x4233f0)return UINT64_MAX;
    uint32_t state=P(self+28);
    if(state==4){
        if(CALL(0x423700,v[0])){select_self(a,self);CALL(0x38f250,MSG,word(P(self+84)));flags(a,self);CALL(0x38e060,MSG,0x51a960);publish(a,self);}
        W(self+28,1);W(self+40,0);W(self+36,0);W(self+32,0);return 0;
    }
    if(state==0){
        CALL(P(P(self)+96),v[0]);select_self(a,self);CALL(0x38f250,MSG,word(P(self+84)));CALL(0x38f250,MSG,word(P(self+100)));
        W(scratch+48,P(self+88));W(scratch+52,P(self+92));W(scratch+56,P(self+96));CALL(0x38f4b0,MSG,scratch+48);
        if(B(self+104))CALL(0x38f830,MSG,0x51a928);
        flags(a,self);CALL(0x38e060,MSG,0x51a938);advance(a,self);
    }else if(state!=1&&state!=2&&state!=3)return 0;
    if(state==0||state==1){
        publish(a,self);send_self(a,self,0x51a958);
        if(!(CALL(0x38f220,MSG,0)&255))return 0;
        advance(a,self);
    }
    if(state!=3){CALL(0x3f5f80,v[0]);CALL(0x3f5a40,v[0]);advance(a,self);}
    if(CALL(0x3f6090,v[0]))a->write(a->user,self+24,1,0);
    return 0;
}
