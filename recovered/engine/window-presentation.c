/* Original text/model close queues, model presentation and shared title update. */
#include "window-presentation.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define MSG word(P(self+12))
static uint64_t word(uint32_t p){return (uint64_t)(int64_t)(int32_t)p;}
static void unstring(const Dw4MessengerResultsApi*a,uint32_t p){
    if(p){W(p-4,P(p-4)-1);if(!P(p-4))CALL(0x30c940,word(P(p-8)),word(p-8));}
}
static uint32_t token(const Dw4MessengerResultsApi*a,uint32_t list,uint32_t i,uint32_t temp){
    CALL(0x1c64e0,temp,word(list),word(i));uint32_t value=P(temp);unstring(a,value);return value;
}
static uint32_t intern(const Dw4MessengerResultsApi*a,uint64_t value){
    if(!P(0x586f20)){
        uint64_t memory=CALL(0x2eb010,16);uint32_t pool=memory?(uint32_t)CALL(0x2eadf0,memory):0;
        W(0x586f20,pool);
    }
    return (uint32_t)CALL(0x2eaf60,word(P(0x586f20)),value);
}
static void clear_strings(const Dw4MessengerResultsApi*a,uint32_t list){
    int32_t count=(int32_t)P(list+8);
    for(int32_t i=0;i<count;i++){
        uint32_t cell=P(list+16)+(uint32_t)i*4,value=intern(a,0);
        unstring(a,P(cell));W(cell,value);
    }
    W(list+8,0);
}
static void advance(const Dw4MessengerResultsApi*a,uint32_t self){
    W(self+28,P(self+28)+1);W(self+40,0);W(self+36,0);W(self+32,0);
}
uint64_t dw4_window_presentation(const Dw4MessengerResultsApi*a,uint32_t entry,const uint64_t v[8],uint32_t scratch){
    uint32_t self=(uint32_t)v[0];
    switch(entry){
    case 0x3f5920:{
        uint64_t lua=CALL(0x236f80,word(P(self+8)),word(P(0x589208)));
        if(!lua||!CALL(0x300cd0,lua,word(P(0x589208))))lua=0;
        W(0x58a220,v[2]);CALL(0x389ff0,lua,v[1],0);return 0;
    }
    case 0x3f59b0:
        CALL(0x38d860,MSG,0x518700,0,UINT64_MAX);
        CALL(0x38f830,MSG,v[1]);CALL(0x38f830,MSG,v[2]);CALL(0x38f830,MSG,0x518730);
        CALL(0x38e060,MSG,0x518720);return 0;
    case 0x3f5a40:{
        int32_t count=(int32_t)P(P(self+60)+8);
        for(int32_t i=0;i<count;i++){
            uint32_t type=token(a,P(self+60),(uint32_t)i,scratch+140);
            uint32_t name=token(a,P(self+64),(uint32_t)i,scratch+136);
            CALL(0x3f59b0,v[0],word(type),word(name));
        }
        clear_strings(a,P(self+60));clear_strings(a,P(self+64));return 0;
    }
    case 0x3f5c90:
        CALL(0x38e5f0,MSG,0x518738,v[1],v[2],0x518748);
        if(!CALL(0x38f220,MSG,0)){
            CALL(0x38d860,MSG,0x518738,v[1],v[2]);CALL(0x38f830,MSG,v[3]);
            W(scratch+120,P((uint32_t)v[5]));W(scratch+124,P((uint32_t)v[5]+4));W(scratch+128,P((uint32_t)v[5]+8));
            CALL(0x38f4b0,MSG,scratch+120);CALL(0x38e060,MSG,0x518750);
        }else CALL(0x38e5f0,MSG,0x518738,v[1],v[2],v[3]);
        if(v[4]){
            W(scratch+140,v[1]?intern(a,v[1]):0);
            CALL(0x1ca620,word(P(self+68)),scratch+140);unstring(a,P(scratch+140));
            uint32_t ids=P(self+72),count=P(ids+8);
            if((int32_t)count<(int32_t)P(ids+12))W(ids+8,P(ids+8)+1);
            else CALL(0x2d6790,word(ids),word(count+1),4);
            W(P(ids+16)+count*4,v[2]);
            W(scratch+136,v[4]?intern(a,v[4]):0);
            CALL(0x1ca620,word(P(self+76)),scratch+136);unstring(a,P(scratch+136));
        }
        return 0;
    case 0x3f5f00:
        for(unsigned i=0;i<3;i++)W(scratch+16+i*4,P(0x4e1058+i*4));
        CALL(0x3f5c90,v[0],v[1],v[2],v[3],v[4],scratch+16);return 0;
    case 0x3f5f40:CALL(0x38e5f0,MSG,0x518738,v[1],v[2],v[3]);return 0;
    case 0x3f5f80:{
        int32_t count=(int32_t)P(P(self+68)+8);
        for(int32_t i=0;i<count;i++){
            uint32_t name=token(a,P(self+68),(uint32_t)i,scratch+140);
            uint32_t id=P(P(P(self+72)+16)+(uint32_t)i*4);
            uint32_t sequence=token(a,P(self+76),(uint32_t)i,scratch+136);
            CALL(0x3f5f40,v[0],word(name),word(id),word(sequence));
        }
        return 0;
    }
    case 0x3f6090:{
        int32_t count=(int32_t)P(P(self+68)+8);
        for(int32_t i=0;i<count;i++){
            uint32_t name=token(a,P(self+68),(uint32_t)i,scratch+140);
            uint32_t id=P(P(P(self+72)+16)+(uint32_t)i*4);
            token(a,P(self+76),(uint32_t)i,scratch+136);
            CALL(0x38e5f0,MSG,0x518738,word(name),word(id),0x518748);
            if((int64_t)CALL(0x38f0f0,MSG)>0&&CALL(0x38f220,MSG,0))return 0;
        }
        if(P(P(self+52)+8))return 0;
        clear_strings(a,P(self+68));W(P(self+72)+8,0);clear_strings(a,P(self+76));return 1;
    }
    case 0x424160:{
        uint32_t state=P(self+28);
        if(state==0){CALL(P(P(self)+96),v[0]);advance(a,self);}
        else if(state==2){CALL(0x3f5f80,v[0]);CALL(0x3f5a40,v[0]);CALL(0x3f6350,v[0]);advance(a,self);}
        else if(state==3&&CALL(0x3f6090,v[0]))a->write(a->user,self+24,1,0);
        return 0;
    }
    default:return UINT64_MAX;
    }
}
