#include "chip-list-view.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define MSG word(P(self+12))
static uint64_t word(uint32_t n){return (uint64_t)(int64_t)(int32_t)n;}
/* Font pointers and messenger are intentionally reloaded around callbacks. */
static void text(const Dw4MessengerResultsApi*a,uint32_t self,uint32_t group,uint32_t font_cell,uint64_t value,uint32_t command){
    CALL(0x38e5d0,MSG,0x51b3c0);CALL(0x38f830,MSG,group);
    CALL(0x38f830,MSG,word(P(font_cell)));CALL(0x38f830,MSG,value);CALL(0x38e060,MSG,command);
}
uint64_t dw4_chip_list_view(const Dw4MessengerResultsApi*a,uint32_t entry,const uint64_t v[8],uint32_t scratch){
    uint32_t self=(uint32_t)v[0];
    if(entry==0x43c720){
        int32_t count=(int32_t)P(P(self+96)+8),pages=count/12+(count%12!=0);
        W(self+88,pages);
        int32_t remaining=(int32_t)(P(P(self+96)+8)-P(self+84)*12),rows=remaining<12?remaining%12:12;
        return word((uint32_t)(rows<1?1:rows));
    }
    if(entry!=0x43c7f0)return UINT64_MAX;
    uint64_t context=CALL(0x236f80,word(P(self+8)),word(P(0x58b028)));
    if(v[1]){
        for(uint32_t i=0;i<12;i++){
            uint32_t index=P(self+84)*12+i,font=0x4cf8a0+i*4;
            if((int32_t)index<(int32_t)P(P(self+96)+8)){
                uint32_t item=P(P(P(self+96)+16)+index*4);
                if(!item)continue; /* An in-range null leaves both old fields. */
                uint64_t name=CALL(0x447cb0,word(item),context,0x51b678);
                uint64_t next_x=CALL(0x447c10,word(item),context,0x51be38);
                text(a,self,0x51b3c8,font,name,0x51b6b0);
                if((int64_t)next_x<1){W(scratch+128,P(0x51bdc0));a->write(a->user,scratch+132,1,a->read(a->user,0x51bdc4,1));}
                else CALL(0x129e60,scratch+128,0x51b468,next_x);
                text(a,self,0x51b680,font,scratch+128,0x51b6b0);
                text(a,self,0x51b3c8,font,0x51b6b8,0x51b558);
                text(a,self,0x51b680,font,0x51b6b8,0x51b558);
            }else{
                text(a,self,0x51b3c8,font,0x51b550,0x51b558);
                text(a,self,0x51b680,font,0x51b550,0x51b558);
            }
        }
        a->write(a->user,scratch+157,1,0);
        a->write(a->user,scratch+156,1,P(self+84)+'1');
        text(a,self,0x51bd60,0x4cf8a0,scratch+156,0x51b6b0);
        a->write(a->user,scratch+156,1,P(self+88)+'0');
        text(a,self,0x51bd60,0x4cf8a4,scratch+156,0x51b6b0);
    }
    if(v[2]){
        uint32_t index=P(self+84)*12+P(self+48);
        if((int32_t)index<(int32_t)P(P(self+96)+8)){
            uint32_t item=P(P(P(self+96)+16)+index*4);
            if(item){
                uint64_t description=CALL(0x447cb0,word(item),context,0x51b6a8);
                text(a,self,0x51b470,0x4cf8a0,description,0x51b6b0);
                text(a,self,0x51b470,0x4cf8a0,0x51b6b8,0x51b558);
            }
        }
    }
    return 0;
}
