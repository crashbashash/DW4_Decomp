/* Original shop selector configuration and XDATA stat/cost display. */
#include "shop-selectors.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define SB(p,v) a->write(a->user,(p),1,(uint8_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define MSG word(P(self+12))
static uint64_t word(uint32_t p){return (uint64_t)(int64_t)(int32_t)p;}
static void unstring(const Dw4MessengerResultsApi*a,uint32_t p){if(p){W(p-4,P(p-4)-1);if(!P(p-4))CALL(0x30c940,word(P(p-8)),word(p-8));}}
static uint32_t intern(const Dw4MessengerResultsApi*a,uint64_t value){
    if(!P(0x586f20)){uint64_t m=CALL(0x2eb010,16);W(0x586f20,m?CALL(0x2eadf0,m):0);}
    return (uint32_t)CALL(0x2eaf60,word(P(0x586f20)),value);
}
static void append(const Dw4MessengerResultsApi*a,uint32_t self,unsigned field,uint32_t temp,uint64_t value){
    W(temp,intern(a,value));CALL(0x1ca620,word(P(self+field)),temp);unstring(a,P(temp));
}
static void set_name(const Dw4MessengerResultsApi*a,uint32_t self,uint64_t text){uint32_t value=intern(a,text);unstring(a,P(self+80));W(self+80,value);}
static int in(const uint32_t*values,unsigned count,uint32_t value){for(unsigned i=0;i<count;i++)if(values[i]==value)return 1;return 0;}
static int32_t cost(uint32_t stat){int32_t n=(int32_t)(stat-45),q=n/5+(n%5!=0);return q>400?400:q<0?1:q;}
static void refresh(const Dw4MessengerResultsApi*a,uint32_t self,uint32_t scratch){
    CALL(0x38e5d0,MSG,0x51c500);CALL(0x38f250,MSG,word(P(self+20)));CALL(0x38e060,MSG,0x51c508);uint64_t folder=CALL(0x38f800,MSG,0);
    for(unsigned i=0;i<7;i++){W(scratch+224+i*4,P(0x4cfad0+i*4));W(scratch+192+i*4,P(0x4cfaf0+i*4));W(scratch+160+i*4,P(0x4cfb10+i*4));}
    for(unsigned i=0;i<7;i++){
        uint32_t property=(uint32_t)CALL(0x3a9220,folder,word(P(scratch+224+i*4))),stat=P(property+12);
        int32_t price=cost(stat);
        CALL(0x129e60,scratch+256,(int32_t)stat<(int32_t)P(scratch+192+i*4)?0x51c6e0:0x51c6d8,word((uint32_t)price));
        CALL(0x38e5d0,MSG,0x51c6e8);CALL(0x38f830,MSG,0x51c650);CALL(0x38f830,MSG,word(P(scratch+160+i*4)));CALL(0x38f830,MSG,scratch+256);CALL(0x38e060,MSG,0x51c6f0);
        CALL(0x38e5d0,MSG,0x51c6e8);CALL(0x38f830,MSG,0x51c620);CALL(0x38f830,MSG,word(P(scratch+160+i*4)));
        if((int32_t)stat<(int32_t)P(scratch+192+i*4))CALL(0x38e060,MSG,0x51c700);
        else{W(scratch+272,0x3f666666);W(scratch+276,0x3ecccccd);W(scratch+280,0x3e4ccccd);CALL(0x38f4b0,MSG,scratch+272);CALL(0x38e060,MSG,0x51c6f8);}
    }
}
uint64_t dw4_shop_selectors(const Dw4MessengerResultsApi*a,uint32_t entry,const uint64_t v[8],uint32_t scratch){
    uint32_t self=(uint32_t)v[0];
    if(entry==0x43fb70){refresh(a,self,scratch);return 0;}
    if(entry==0x43d1d0){
        if((int32_t)P(self+44)>0){
            append(a,self,60,scratch+60,0x51c488);
            uint32_t text=P(self+112);
            if(!text)append(a,self,64,scratch+56,0x51c498);
            else{if(text)W(text-4,P(text-4)+1);W(scratch+52,text);CALL(0x1ca620,word(P(self+64)),scratch+52);unstring(a,P(scratch+52));}
            CALL(0x3f5920,v[0],0x51c4a0,word(P(self+44)));
        }
        set_name(a,self,0x51c4b0);W(self+84,1);W(self+88,0);W(self+92,0);W(self+96,0);W(self+100,0);SB(self+104,0);return 0;
    }
    if(entry==0x43d450){
        static const uint32_t triples[]={0x79e,0x73a,0x6d6,0x672,0x60e,0x546,0x47e};
        static const uint32_t pairs[]={0x7aa,0x5ad,0x61a,0x740,0x6dc,0x678,0x614,0x54b,0x4f8,0x4ea,0x4e7,0x493,0x48e,0x48b};
        uint32_t code=P(self+44);unsigned count=in(triples,7,code)?3:in(pairs,14,code)?2:0;
        if(count){
            for(unsigned i=0;i<count;i++){
                uint32_t type=scratch+(count==3?76:92)-i*8;
                static const uint32_t fonts[]={0x51c498,0x51c4c0,0x51c4c8};
                append(a,self,60,type,0x51c488);append(a,self,64,type-4,fonts[i]);
            }
            CALL(0x3f5920,v[0],0x51c4a0,word(P(self+44)));W(self+84,count);
        }
        set_name(a,self,0x51c4d0);W(self+88,0);W(self+92,0);W(self+96,0);SB(self+104,0);SB(self+104,0);return 0;
    }
    if(entry==0x43ecc0){
        CALL(0x3f5f00,v[0],0x51c5c0,0,0x51c5d0,0x51c5e8);
        static const uint32_t types[]={0x51c488,0x51c600,0x51c610,0x51c620,0x51c620,0x51c620,0x51c620,0x51c620,0x51c620,0x51c620};
        static const uint32_t fonts[]={0x51c5f8,0x51c498,0x51c4c0,0x51c498,0x51c4c0,0x51c4c8,0x51c630,0x51c638,0x51c640,0x51c648};
        for(unsigned i=0;i<10;i++){
            append(a,self,60,scratch+124-i*8,types[i]);append(a,self,64,scratch+120-i*8,fonts[i]);
            if(i==0)CALL(0x3f5920,v[0],0x51c4a0,0x481);
            if(i==2)CALL(0x3f5920,v[0],0x51c4a0,0x44d);
        }
        CALL(0x3f5920,v[0],0x51c4a0,0x44f);
        for(unsigned i=3;i<10;i++)CALL(0x3f5410,v[0],0x51c650,fonts[i],0x51c660,0x51c668);
        CALL(0x3f5410,v[0],0x51c488,0x51c498,0x51c660,0x51c540);
        CALL(0x38e5d0,MSG,0x51c500);CALL(0x38f250,MSG,word(P(self+20)));CALL(0x38f150,MSG,0);CALL(0x38e060,MSG,0x51c670);
        CALL(0x43fb70,v[0]);CALL(0x3f5920,v[0],0x51c4a0,word(P(self+44)+0x482));
        set_name(a,self,0x51c680);W(self+84,7);W(self+88,0xc2f20000);W(self+92,0x43000000);W(self+96,0);W(self+100,P(self+44));SB(self+104,0);return 0;
    }
    return UINT64_MAX;
}
