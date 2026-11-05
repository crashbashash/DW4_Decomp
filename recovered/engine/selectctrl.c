/* beSelectCtrl manager: original input, command and animation state machines. */
#include "selectctrl.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define B(p) ((uint32_t)a->read(a->user,(p),1))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define MSG word(P(self+20))
static uint64_t word(uint32_t n){return (uint64_t)(int64_t)(int32_t)n;}
static void retain(const Dw4MessengerResultsApi*a,uint32_t p){if(p)W(p+4,P(p+4)+1);}
static void release(const Dw4MessengerResultsApi*a,uint32_t p){if(p){W(p+4,P(p+4)-1);if(!(P(p+4)&0x7fffff))CALL(0x2ff820,word(p));}}
static uint64_t allocator(const Dw4MessengerResultsApi*a,uint64_t owner){uint64_t p=CALL(0x301000,owner);if(!B(0x554c14))p=CALL(0x2f88e0,word(P(0x587110)));return p;}
static uint32_t data(const Dw4MessengerResultsApi*a,uint64_t context,uint32_t temp){
    uint32_t ctx=(uint32_t)context;
    if(!P(ctx+40)){
        W(temp,CALL(0x36ae80,allocator(a,context)));uint32_t fresh=P(temp);retain(a,fresh);
        release(a,P(ctx+40));W(ctx+40,fresh);release(a,P(temp));
    }
    return (uint32_t)CALL(0x3022c0,word(P(ctx+40)),word(P(0x585be0)),0x50f800);
}
static void reset(const Dw4MessengerResultsApi*a,uint32_t ctx,uint32_t state){W(ctx+24,state);W(ctx+36,0);W(ctx+32,0);W(ctx+28,0);}
static void next(const Dw4MessengerResultsApi*a,uint32_t ctx){W(ctx+28,P(ctx+28)+1);W(ctx+36,0);W(ctx+32,0);}
static uint32_t name(const Dw4MessengerResultsApi*a,uint32_t info){uint32_t p=P(info+8);return p?p:0x4e0858;}
static void select_model(const Dw4MessengerResultsApi*a,uint32_t self,uint32_t ctx,uint32_t info){CALL(0x38d860,MSG,0x50f808,word(name(a,info)),word(P(ctx+8)));}
static void send_sequence(const Dw4MessengerResultsApi*a,uint32_t self,uint32_t ctx,uint32_t info,uint64_t seq){CALL(0x38e5f0,MSG,0x50f808,word(name(a,info)),word(P(ctx+8)),seq);}
static uint64_t wait_sequence(const Dw4MessengerResultsApi*a,uint32_t self,uint32_t ctx,uint32_t info,uint64_t seq){select_model(a,self,ctx,info);CALL(0x38f830,MSG,seq);CALL(0x38e060,MSG,0x50f830);return CALL(0x38f220,MSG,0);}
/* The work-owned sequence is loaded after selecting the receiver: that call
 * can replace the retained string. Constants in the opening/top paths are fixed. */
static uint64_t wait_work(const Dw4MessengerResultsApi*a,uint32_t self,uint32_t ctx,uint32_t info,uint32_t work){
    select_model(a,self,ctx,info);CALL(0x38f830,MSG,word(P(work+28)));
    CALL(0x38e060,MSG,0x50f830);return CALL(0x38f220,MSG,0);
}
static void sequence(const Dw4MessengerResultsApi*a,uint32_t work,uint64_t text){
    uint32_t pool=P(0x586f20);
    if(!pool){uint64_t raw=CALL(0x2eb010,16);pool=raw?(uint32_t)CALL(0x2eadf0,raw):0;}
    W(0x586f20,pool);uint32_t token=(uint32_t)CALL(0x2eaf60,word(P(0x586f20)),text),old=P(work+28);
    if(old){W(old-4,P(old-4)-1);if(!P(old-4))CALL(0x30c940,word(P(old-8)),word(old-8));}
    W(work+28,token);
}
static void reject(const Dw4MessengerResultsApi*a,uint32_t self,uint32_t ctx){CALL(0x38e5d0,MSG,0x50f870);CALL(0x38f830,MSG,0x50f878);CALL(0x38e060,MSG,0x50f888);W(ctx+28,2);W(ctx+36,0);W(ctx+32,0);}
static void decision_flags(const Dw4MessengerResultsApi*a,uint32_t self,uint64_t owner,uint32_t work,uint32_t temp,uint64_t count){
    W(temp,CALL(0x2cb0d0,allocator(a,owner)));uint32_t fresh=P(temp);retain(a,fresh);
    release(a,P(work+32));W(work+32,fresh);
    if((int64_t)count>0){
        uint32_t i=0;
        do{
            uint32_t flag=(uint32_t)CALL(0x38f220,MSG,word(i)),list=P(temp),n=P(list+8);
            if((int32_t)n<(int32_t)P(list+12))W(list+8,n+1);
            else CALL(0x2d6790,word(list),word(n+1),1);
            a->write(a->user,P(list+16)+n,1,flag);i++;
        }while((int64_t)(int32_t)i<(int64_t)count);
    }
    release(a,P(temp));
}
uint64_t dw4_selectctrl_manager(const Dw4MessengerResultsApi*a,uint32_t entry,const uint64_t v[8],uint32_t scratch){
    uint32_t self=(uint32_t)v[0],ctx=(uint32_t)v[1];
    if(entry==0x39d720){
        uint32_t record=data(a,v[1],scratch+144),work=P(record+28);
        uint64_t type=CALL(0x3459a0),command=CALL(0x38d4a0,MSG,type,v[2]);
        switch(command){
        case 0:{
            a->write(a->user,ctx+20,1,1);reset(a,ctx,0);
            W(scratch+156,CALL(0x345680,allocator(a,v[0])));uint32_t fresh=P(scratch+156);retain(a,fresh);
            release(a,P(record+28));W(record+28,fresh);work=P(scratch+156);release(a,work);
            W(record+24,0);
            if(!CALL(0x38f240,MSG))W(work+20,P(record+20));
            else{W(work+20,CALL(0x38f320,MSG,0));if(CALL(0x38f240,MSG)==2)W(record+24,CALL(0x38f320,MSG,1));}
            if(!CALL(0x38f4a0,MSG)){for(unsigned i=0;i<3;i++)W(work+8+i*4,P(0x4e1058+i*4));}
            else{CALL(0x38f560,scratch+128,MSG,0);for(unsigned i=0;i<3;i++)W(work+8+i*4,P(scratch+128+i*4));}
            if(CALL(0x38f820,MSG)){uint64_t s=CALL(0x38f8f0,MSG,0);if(!CALL(0x12a4a4,s,0x50f8d0))a->write(a->user,work+24,1,0);}
            uint64_t count=CALL(0x38f0f0,MSG);
            if(count&&count==word(P(work+20)))decision_flags(a,self,v[0],work,scratch+152,count);
            return 1;
        }
        case 1:CALL(0x38f150,MSG,!B(ctx+20));return 1;
        case 2:CALL(0x38f250,MSG,word(P(record+24)));return 1;
        case 3:CALL(0x38f150,MSG,B(ctx+20)&&P(ctx+24)!=2&&P(ctx+24)!=3);return 1;
        case 4:
            if(P(ctx+24)==1&&!P(ctx+28)){
                W(record+24,0);
                if((int64_t)CALL(0x38f240,MSG)>0){
                    W(work+20,CALL(0x38f320,MSG,0));uint64_t count=CALL(0x38f0f0,MSG);
                    if(count&&count==word(P(work+20)))decision_flags(a,self,v[0],work,scratch+148,count);
                }
                reset(a,ctx,10);CALL(0x38f150,MSG,1);
            }else CALL(0x38f150,MSG,0);
            return 1;
        case 5:CALL(0x38f150,MSG,!(P(ctx+24)==1&&!P(ctx+28)));return 1;
        case 6:W(record+24,UINT32_MAX);reset(a,ctx,2);return 0;
        default:return 0;
        }
    }
    if(entry!=0x39cbf0)return UINT64_MAX;
    if(!B(ctx+20))return 0;
    uint32_t info=P(ctx+12),record=data(a,v[1],scratch+236),work=P(record+28);
    uint32_t pad=(uint32_t)CALL(0x39b810,word(P(self+32)),word(P(ctx+8)));
    uint32_t directions=P(pad+68)&0xf0,state=P(ctx+24),buttons=P(pad+72),repeat=P(pad+36),sub=P(ctx+28);
    if(state==10){
        if(!sub){send_sequence(a,self,ctx,info,0x50f8c0);next(a,ctx);}
        else if(sub==1&&!wait_sequence(a,self,ctx,info,0x50f8c0))reset(a,ctx,1);
        return 0;
    }
    if(state==2){
        if(!sub){sequence(a,work,P(record+24)==UINT32_MAX?0x50f8b0:0x50f8a0);send_sequence(a,self,ctx,info,word(P(work+28)));next(a,ctx);}
        else if(sub==1&&!wait_work(a,self,ctx,info,work))reset(a,ctx,P(ctx+24)+1);
        return 0;
    }
    if(state==0){
        if(!sub){
            select_model(a,self,ctx,info);for(unsigned i=0;i<3;i++)W(scratch+224+i*4,P(work+8+i*4));
            CALL(0x38f4b0,MSG,scratch+224);CALL(0x38f830,MSG,0x50f818);CALL(0x38e060,MSG,0x50f820);next(a,ctx);
        }else if(sub==1&&((wait_sequence(a,self,ctx,info,0x50f818)&255)!=1)){
            CALL(0x129e60,scratch+208,0x50f840,word(P(record+24)));send_sequence(a,self,ctx,info,scratch+208);reset(a,ctx,P(ctx+24)+1);
        }
        return 0;
    }
    if(state!=1){a->write(a->user,ctx+20,1,0);release(a,P(record+28));W(record+28,0);return 0;}
    if(sub==2){if((int32_t)P(ctx+32)<16){W(ctx+32,P(ctx+32)+1);W(ctx+36,0);}else{W(ctx+28,0);W(ctx+36,0);W(ctx+32,0);}return 0;}
    if(sub==1){if(!wait_work(a,self,ctx,info,work))reset(a,ctx,P(ctx+24)+1);return 0;}
    if(sub)return 0;
    if(repeat||directions){
        if(!P(ctx+36)){
            uint32_t selected=P(record+24),changed=0;
            int left=(repeat&8)||(directions&0x80),right=(repeat&2)||(directions&0x20),up=(repeat&1)||(directions&0x10),down=(repeat&4)||(directions&0x40);
            int vertical=B(record+16)!=0;
            if(vertical?up:left){if(selected){selected--;changed=1;CALL(0x129e60,scratch+192,0x50f850,word(selected));sequence(a,work,scratch+192);}}
            else if((vertical?down:right)&&selected!=P(work+20)-1){selected++;changed=1;CALL(0x129e60,scratch+176,0x50f860,word(selected));sequence(a,work,scratch+176);}
            if(changed){W(record+24,selected);send_sequence(a,self,ctx,info,word(P(work+28)));W(ctx+36,P(ctx+36)+1);}
        }else if(!wait_work(a,self,ctx,info,work))W(ctx+36,0);
    }
    if(buttons&0x2000){if(!B(work+24))reject(a,self,ctx);else{W(record+24,UINT32_MAX);reset(a,ctx,P(ctx+24)+1);}}
    else if(buttons&0x4000){
        if(!P(work+32)||B(P(P(work+32)+16)+P(record+24))){
            CALL(0x129e60,scratch+160,0x50f890,word(P(record+24)));sequence(a,work,scratch+160);
            send_sequence(a,self,ctx,info,word(P(work+28)));next(a,ctx);
        }else reject(a,self,ctx);
    }
    return 0;
}
