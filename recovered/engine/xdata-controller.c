/* Original XDATA stat/menu controller. Factories, record recalculation, text,
 * chip subcontroller and receiver services remain explicit dependencies. */
#include "xdata-controller.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define B(p) ((uint32_t)a->read(a->user,(p),1))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define MSG word(P(self+12))
static uint64_t word(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void release(const Dw4MessengerResultsApi*a,uint32_t p){if(p){W(p+4,P(p+4)-1);if(!(P(p+4)&0x7fffff))CALL(0x2ff820,word(p));}}
static void unstring(const Dw4MessengerResultsApi*a,uint32_t p){if(p){W(p-4,P(p-4)-1);if(!P(p-4))CALL(0x30c940,word(P(p-8)),word(p-8));}}
static void advance(const Dw4MessengerResultsApi*a,uint32_t self){W(self+28,P(self+28)+1);W(self+40,0);W(self+36,0);W(self+32,0);}
static void phase(const Dw4MessengerResultsApi*a,uint32_t self,uint32_t n){W(self+32,n);W(self+40,0);W(self+36,0);}
static void next_subphase(const Dw4MessengerResultsApi*a,uint32_t self){W(self+36,P(self+36)+1);W(self+40,0);}
static void snapshot(const Dw4MessengerResultsApi*a,uint32_t self){W(self+80,P(P(self+52)+8));}
static int changed(const Dw4MessengerResultsApi*a,uint32_t self){return P(P(self+52)+8)!=P(self+80);}
static uint64_t allocator(const Dw4MessengerResultsApi*a,uint64_t owner){uint64_t p=CALL(0x301000,owner);if(!B(0x554c14))p=CALL(0x2f88e0,word(P(0x587110)));return p;}
static void child(const Dw4MessengerResultsApi*a,uint32_t self,uint64_t owner,uint32_t temp,uint32_t factory,uint64_t code){
    W(temp,CALL(factory,allocator(a,owner)));
    CALL(0x3f63c0,word(P(temp)),owner,word(P(self+8)),word(P(self+20)),code);
    CALL(0x301e30,word(P(self+52)),word(P(temp)));
}
static void recalc(const Dw4MessengerResultsApi*a,uint32_t self,int bool_arg){
    CALL(0x38e5d0,MSG,0x51b398);CALL(0x38f250,MSG,word(P(self+20)));
    if(bool_arg)CALL(0x38f150,MSG,0);
    CALL(0x38e060,MSG,0x51b3a0);
}
static uint64_t player(const Dw4MessengerResultsApi*a,uint32_t self){
    CALL(0x38e5d0,MSG,0x51b398);CALL(0x38f250,MSG,word(P(self+20)));CALL(0x38e060,MSG,0x51b3e8);return CALL(0x38f800,MSG,0);
}
static uint32_t property(const Dw4MessengerResultsApi*a,uint64_t folder,uint64_t key){uint32_t p=(uint32_t)CALL(0x3a9220,folder,key);return P(p+12);}
static void restore_hp_mp(const Dw4MessengerResultsApi*a,uint64_t folder){
    uint32_t hp=property(a,folder,0x51b430),target=(uint32_t)CALL(0x3a9220,folder,0x51b488);W(target+12,hp);
    uint32_t mp=property(a,folder,0x51b438);target=(uint32_t)CALL(0x3a9220,folder,0x51b490);W(target+12,mp);
}
static int32_t cost(uint32_t stat){int32_t n=(int32_t)(stat-45),q=n/5+(n%5!=0);return q>400?400:q<0?1:q;}
static const uint32_t keys[]={0x51b3f8,0x51b400,0x51b408,0x51b418,0x51b420,0x51b430,0x51b438};
static uint32_t intern(const Dw4MessengerResultsApi*a,uint64_t value){
    if(!P(0x586f20)){uint64_t m=CALL(0x2eb010,16);W(0x586f20,m?CALL(0x2eadf0,m):0);}
    return (uint32_t)CALL(0x2eaf60,word(P(0x586f20)),value);
}
static void append_string(const Dw4MessengerResultsApi*a,uint32_t owner_cell,unsigned field,uint32_t temp,uint64_t text,int nullable){
    W(temp,nullable&&!text?0:intern(a,text));CALL(0x1ca620,word(P(P(owner_cell)+field)),temp);unstring(a,P(temp));
}
uint64_t dw4_xdata_controller(const Dw4MessengerResultsApi*a,const uint64_t v[8],uint32_t scratch,uint64_t incoming_s0){
    uint32_t self=(uint32_t)v[0],state=P(self+28);
    if(state==3){if(CALL(0x3f6090,v[0]))a->write(a->user,self+24,1,0);return 0;}
    if(state==2){recalc(a,self,0);restore_hp_mp(a,player(a,self));CALL(0x3f5f80,v[0]);CALL(0x3f5a40,v[0]);CALL(0x3f6350,v[0]);advance(a,self);return 0;}
    if(state!=1){if(state!=0)return 0;advance(a,self);phase(a,self,0);}
    uint32_t main=P(self+32);
    if(main==0){
        uint32_t sub=P(self+36);
        if(sub!=1){
            if(sub)return 0;
            child(a,self,v[0],scratch+364,0x3b4d90,0x47e);W(P(scratch+364)+100,P(self+84));release(a,P(scratch+364));snapshot(a,self);next_subphase(a,self);
        }
        if(changed(a,self)){
            W(self+88,0);uint32_t selected=P(self+48);
            if(selected==1){W(self+84,1);phase(a,self,2);return 0;}
            if(!selected){W(self+84,0);phase(a,self,1);return 0;}
            advance(a,self);
        }
        return 0;
    }
    if(main==2){
        uint32_t sub=P(self+36);
        if(sub!=1){if(sub)return 0;recalc(a,self,0);child(a,self,v[0],scratch+340,0x3b6940,0);release(a,P(scratch+340));snapshot(a,self);next_subphase(a,self);}
        if(changed(a,self)){phase(a,self,0);W(self+40,1);}return 0;
    }
    if(main!=1)return 0;
    switch(P(self+36)){
    case 0:
        recalc(a,self,1);child(a,self,v[0],scratch+360,0x3b4790,word(P(self+88)));release(a,P(scratch+360));snapshot(a,self);next_subphase(a,self);W(self+40,P(self+88));break;
    case 1:
        if(!changed(a,self)){
            uint32_t selected=P(self+48);if(selected!=UINT32_MAX&&selected!=P(self+40)){CALL(0x3f5920,v[0],0x51b3b0,word(selected+0x482));W(self+40,P(self+48));}
        }else{
            for(unsigned i=0;i<7;i++)W(scratch+272+i*4,P(0x4cf950+i*4));
            for(unsigned i=0;i<7;i++){
                CALL(0x38e5d0,MSG,0x51b3c0);CALL(0x38f830,MSG,0x51b3c8);CALL(0x38f830,MSG,word(P(scratch+272+i*4)));CALL(0x38e060,MSG,0x51b3d8);
            }
            uint64_t folder=player(a,self);uint32_t selected=P(self+48);
            if(selected>=7){phase(a,self,0);return 0;}
            uint32_t stat=property(a,folder,keys[selected]),limit=selected<5?9999:99999;int32_t price=cost(stat);
            W(self+88,P(self+48));child(a,self,v[0],scratch+356,0x3b4f50,0);next_subphase(a,self);
            uint32_t balance=property(a,folder,0x51b440);
            if((int32_t)stat>=(int32_t)limit){W(P(scratch+356)+44,0x48a);W(self+40,0);}
            else if((int32_t)balance<price){W(P(scratch+356)+44,0x489);W(self+40,0);}
            else{
                CALL(0x3f5410,word(P(scratch+356)),0x51b448,0x51b220,0x51b458,0x51b460);
                CALL(0x129e60,scratch+144,0x51b468,word(balance-(uint32_t)price));
                CALL(0x3f5410,word(P(scratch+356)),0x51b448,0x51b248,scratch+144,0x51b460);
                for(unsigned i=0;i<4;i++){
                    append_string(a,scratch+356,60,scratch+336,0x51b448,0);
                    append_string(a,scratch+356,64,scratch+332,word(P(scratch+272+i*4)),1);
                }
                append_string(a,scratch+356,60,scratch+328,0x51b448,0);
                append_string(a,scratch+356,64,scratch+324,0x51b220,0);
                append_string(a,scratch+356,60,scratch+320,0x51b448,0);
                append_string(a,scratch+356,64,scratch+316,0x51b248,0);
                append_string(a,scratch+356,60,scratch+312,0x51b470,0);
                append_string(a,scratch+356,64,scratch+308,word(P(scratch+280)),1);
                for(unsigned i=0;i<7;i++)W(scratch+112+i*4,P(0x4cf970+i*4));
                W(P(scratch+356)+44,P(scratch+112+P(self+48)*4));W(self+40,1);
            }
            release(a,P(scratch+356));snapshot(a,self);
        }
        break;
    case 2:
        if(changed(a,self)){
            if(P(self+40)==1){child(a,self,v[0],scratch+352,0x3b4d90,0x48b);release(a,P(scratch+352));snapshot(a,self);next_subphase(a,self);}
            else phase(a,self,1);
        }
        break;
    case 3:
        if(changed(a,self)){
            if(P(self+48)){phase(a,self,1);break;}
            uint64_t folder=player(a,self),key=incoming_s0;uint32_t parameter=P(self+88);if(parameter<7)key=keys[parameter];
            int32_t price=cost(property(a,folder,key));uint32_t balance=property(a,folder,0x51b440);
            uint32_t target=(uint32_t)CALL(0x3a9220,folder,0x51b440);W(target+12,balance-(uint32_t)price);
            uint32_t p=(uint32_t)CALL(0x3a9250,folder,0x51b480),counts=P(p+12);parameter=P(self+88);
            if(parameter<7){
                static const unsigned indices[]={2,3,4,5,6,0,1};unsigned index=indices[parameter];
                uint32_t cell=P(counts+16)+index*4,n,value;
                if(index==0){value=P(cell);n=P(counts+8);}else{n=P(counts+8);value=P(cell);}
                if(n&&(int32_t)n>(int32_t)index)W(cell,value+1);
            }
            recalc(a,self,0);restore_hp_mp(a,player(a,self));
            CALL(0x38e5d0,MSG,0x51b498);CALL(0x38f250,MSG,word(P(self+20)));CALL(0x38e060,MSG,0x51b4a0);
            child(a,self,v[0],scratch+348,0x3b4f50,0x48d);release(a,P(scratch+348));snapshot(a,self);next_subphase(a,self);
        }
        break;
    case 4:
        if(changed(a,self)){child(a,self,v[0],scratch+344,0x3b4d90,0x48e);release(a,P(scratch+344));snapshot(a,self);next_subphase(a,self);}break;
    case 5:
        if(changed(a,self))phase(a,self,P(self+48)?0:1);
        break;
    }
    return 0;
}
uint64_t dw4_xdata_reference_cleanup(const Dw4MessengerResultsApi*a,const uint64_t v[8]){
    if(v[0]){release(a,P((uint32_t)v[0]));if((int16_t)v[1]>0)CALL(0x100610,v[0]);}return v[0];
}
