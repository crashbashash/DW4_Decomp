#include "list-controller.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
static uint64_t word(uint32_t n){return (uint64_t)(int64_t)(int32_t)n;}
static void vector(const Dw4MessengerResultsApi*a,uint32_t dest,uint32_t src){for(unsigned i=0;i<3;i++)W(dest+i*4,P(src+i*4));}
static void send(const Dw4MessengerResultsApi*a,uint32_t self,uint32_t name,uint32_t sequence){CALL(0x38e5f0,word(P(self+12)),0x519a90,name,0,sequence);}
uint64_t dw4_list_controller(const Dw4MessengerResultsApi*a,uint32_t entry,const uint64_t v[8],uint32_t scratch){
    uint32_t self=(uint32_t)v[0];
    if(entry==0x40dae0){
        vector(a,scratch+80,(uint32_t)v[1]);CALL(0x3f5c90,v[0],0x519a40,0,0x519a50,0x519a58,scratch+80);
        if((int32_t)P(self+88)>=2){vector(a,scratch+64,(uint32_t)v[2]);CALL(0x3f5c90,v[0],0x519a70,0,0x519a80,0x519a58,scratch+64);}
        else{vector(a,scratch+48,(uint32_t)v[2]);CALL(0x3f5c90,v[0],0x519a70,0,0x519a50,0x519a58,scratch+48);}
        return 0;
    }
    if(entry!=0x40dbf0&&entry!=0x40dd30)return UINT64_MAX;
    uint32_t pad=(uint32_t)CALL(0x39b810,word(P(self+16)),word(P(self+20)));
    uint32_t buttons72=P(pad+72),buttons76=P(pad+76),repeat=P(pad+36),input28=P(pad+28),input32=P(pad+32);
    int previous=entry==0x40dbf0;
    int horizontal=((input28|input32)&(previous?8:2))||((buttons72|buttons76)&(previous?128:32));
    int vertical=(repeat&1)||(repeat&4);
    uint32_t page=P(self+84),last=previous?0:P(self+88)-1;
    if((previous?(int32_t)page>0:(int32_t)page<(int32_t)last)&&horizontal&&!vertical){
        W(self+84,previous?page-1:page+1);
        uint32_t edge=previous?P(self+84)==0:P(self+84)==P(self+88)-1;
        send(a,self,previous?0x519a40:0x519a70,edge?0x519aa0:0x519ab0);
        send(a,self,previous?0x519a70:0x519a40,0x519a80);
        return 1;
    }
    return 0;
}
