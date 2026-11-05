/* Original window parent/context binding and recursive update/removal. */
#include "window-tree.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define B(p) ((uint32_t)a->read(a->user,(p),1))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
static uint64_t word(uint32_t p){return (uint64_t)(int64_t)(int32_t)p;}
static void release(const Dw4MessengerResultsApi*a,uint32_t p){
    if(p){W(p+4,P(p+4)-1);if(!(P(p+4)&0x7fffff))CALL(0x2ff820,word(p));}
}
static void close_children(const Dw4MessengerResultsApi*a,uint32_t self){
    int32_t count=(int32_t)P(P(self+52)+8);
    for(int32_t i=0;i<count;i++){
        uint32_t child=P(P(P(self+52)+16)+(uint32_t)i*4);
        if((int32_t)P(child+28)<2){W(child+28,2);W(child+40,0);W(child+36,0);W(child+32,0);}
    }
}
uint64_t dw4_window_tree(const Dw4MessengerResultsApi*a,uint32_t entry,const uint64_t v[8]){
    uint32_t self=(uint32_t)v[0];
    if(entry==0x3f6350){close_children(a,self);return 0;}
    if(entry==0x3f63c0){
        uint32_t parent=(uint32_t)v[1];if(v[1])W(parent+4,P(parent+4)+1);
        release(a,P(self+56));W(self+56,parent);W(self+8,v[2]);
        W(self+12,CALL(0x236f80,v[2],word(P(0x588f38))));
        W(self+16,CALL(0x236f80,v[2],word(P(0x588518))));
        W(self+20,v[3]);W(self+44,v[4]);return 0;
    }
    if(entry!=0x3f6490)return UINT64_MAX;
    if(B(self+24))CALL(P(P(self)+92),v[0]);
    if(!B(self+24)||(int32_t)P(self+28)>=2)close_children(a,self);
    int32_t count=(int32_t)P(P(self+52)+8);
    for(int32_t i=0;i<count;i++){
        uint32_t child=P(P(P(self+52)+16)+(uint32_t)i*4);
        CALL(0x3f6490,word(child));
        uint32_t list=P(self+52);child=P(P(list+16)+(uint32_t)i*4);
        if(!B(child+24)){
            release(a,child);CALL(0x2d6cf0,word(list),word((uint32_t)i));
            i--;count--;W(P(list+16)+P(list+8)*4,0);
        }
    }
    return 0;
}
