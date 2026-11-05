/* Original argument clearing, delayed delivery and context push/pop semantics.
 * This behavioral source is not part of the matching build. */
#include "messenger-lifecycle.h"
typedef const Dw4MessengerResultsApi *Api;
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define B(p) ((uint32_t)a->read(a->user,(p),1))
#define Q(p) (a->read(a->user,(p),8))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define SB(p,v) a->write(a->user,(p),1,(uint8_t)(v))
#define SQ(p,v) a->write(a->user,(p),8,(uint64_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define CORE(e,...) dw4_messenger_lifecycle(a,(e),(const uint64_t[8]){__VA_ARGS__},scratch+8)
static void retain(Api a,uint32_t p){if(p)W(p+4,P(p+4)+1);}
static void release(Api a,uint32_t p){if(p){W(p+4,P(p+4)-1);if(!(P(p+4)&0x7fffff))CALL(0x2ff820,p);}}
static uint32_t item(Api a,uint32_t list,int32_t index){return P(P(list+16)+(uint32_t)index*4);}
static uint32_t intern(Api a,uint32_t text){
    uint32_t pool=P(0x586f20);
    if(!pool){pool=(uint32_t)CALL(0x2eb010,16);if(pool)pool=(uint32_t)CALL(0x2eadf0,pool);W(0x586f20,pool);}
    return (uint32_t)CALL(0x2eaf60,P(0x586f20),text);
}
static void assign_string(Api a,uint32_t slot,uint32_t text){
    uint32_t value=intern(a,text),old=P(slot);
    if(old){uint32_t n=P(old-4)-1;W(old-4,n);if(!n)CALL(0x30c940,P(old-8),old-8);}
    W(slot,value);
}
static void shrink(Api a,uint32_t list,unsigned width){
    if((int32_t)P(list+12)>4&&(int32_t)P(list+8)<5)CALL(0x2d6680,list,4,width);
}
static void clear_context(Api a,uint32_t self){
    static const unsigned widths[]={1,4,4,8,12,64};
    SB(self+8,0);assign_string(a,self+12,0);
    for(unsigned i=0;i<6;i++){W(P(self+16+i*4)+8,0);shrink(a,P(self+16+i*4),widths[i]);}
    uint32_t list=P(self+44);int32_t n=(int32_t)P(list+8);
    for(int32_t i=0;i<n;i++)assign_string(a,P(list+16)+(uint32_t)i*4,0);
    W(list+8,0);shrink(a,P(self+44),4);
    list=P(self+40);n=(int32_t)P(list+8);
    for(int32_t i=0;i<n;i++)release(a,item(a,list,i));
    n=(int32_t)P(list+8);
    for(int32_t i=0;i<n;i++)W(P(list+16)+(uint32_t)i*4,0);
    W(list+8,0);shrink(a,P(self+40),4);
}
static void swap_context(Api a,uint32_t self,uint32_t row){
    uint32_t old=P(self+16);retain(a,old);
    uint32_t next=P(row+40);retain(a,next);release(a,P(self+16));W(self+16,next);
    retain(a,old);release(a,P(row+40));W(row+40,old);release(a,old);
}
static void remove_owner(Api a,uint32_t list,int32_t index){
    release(a,item(a,list,index));CALL(0x2d6cf0,list,(uint32_t)index);
    W(P(list+16)+P(list+8)*4,0);
}
uint64_t dw4_messenger_lifecycle(Api a,uint32_t entry,const uint64_t v[8],uint32_t scratch){
    uint32_t self=(uint32_t)v[0];
    switch(entry){
    case 0x38ca40:clear_context(a,self);break;
    case 0x38ce70:
        SB(self+8,0);SQ(self+16,0);assign_string(a,self+24,0);assign_string(a,self+28,0);
        W(self+32,0);assign_string(a,self+36,0);CORE(0x38ca40,P(self+40));break;
    case 0x38d050:if(!B(self+48))CALL(0x38bee0,v[0]);return 0;
    case 0x38d0a0:{
        if(!B(self+48))break;
        int32_t count=(int32_t)P(P(self+28)+8);if(!count)break;
        uint64_t frozen=Q(self+40),now=Q(P(self+12)+80);
        if(!frozen){
            /* Bound is captured before callbacks. Newly queued records may run
             * this tick, but cannot increase this tick's original bound. */
            for(int32_t i=0;i<count;i++){
                uint32_t row=item(a,P(self+28),0);retain(a,row);
                if(!B(row+8)||(int64_t)now<(int64_t)Q(row+16)){release(a,row);break;}
                CALL(0x38d860,v[0],P(row+24),P(row+28),P(row+32));
                swap_context(a,self,row);CALL(0x38e060,v[0],P(row+36));CORE(0x38ce70,row);
                remove_owner(a,P(self+28),0);CALL(0x301e30,P(self+28),row);release(a,row);
            }
        }else{
            for(int32_t i=0;i<count;i++){
                uint32_t row=item(a,P(self+28),i);if(!B(row+8))break;
                SQ(row+16,now-frozen+Q(row+16));
            }
            SQ(self+40,now);
        }
        CORE(0x38ca40,P(self+16));break;
    }
    case 0x38e8f0:{
        uint32_t list=P(self+28),row=item(a,list,(int32_t)P(list+8)-1);retain(a,row);
        SQ(row+16,Q(P(self+12)+80)+v[2]*UINT64_C(0xfe502a));
        swap_context(a,self,row);assign_string(a,row+36,(uint32_t)v[1]);SB(row+8,1);
        list=P(self+28);remove_owner(a,list,(int32_t)P(list+8)-1);
        int32_t count=(int32_t)P(P(self+28)+8),index=0;
        for(;index<count;index++){
            uint32_t other=item(a,P(self+28),index);
            if(!B(other+8)||(int64_t)Q(row+16)<(int64_t)Q(other+16))break;
        }
        W(scratch,row);retain(a,row);CALL(0x2d6b80,P(self+28),(uint32_t)index,1,scratch);release(a,row);break;
    }
    case 0x38eca0:
        CALL(0x38e6b0,v[0],v[1],v[2],v[3]);CORE(0x38e8f0,v[0],v[4],v[5]);break;
    case 0x38ecf0:
        CALL(0x38e6b0,v[0],v[1],0,UINT64_MAX);CORE(0x38e8f0,v[0],v[2],v[3]);break;
    case 0x38ed50:CALL(0x38e6b0,v[0],v[1],0,UINT64_MAX);break;
    case 0x38ed70:{
        uint32_t old=P(self+16);retain(a,old);
        uint32_t list=P(self+32),next=item(a,list,(int32_t)P(list+8)-1);retain(a,next);
        release(a,P(self+16));W(self+16,next);
        list=P(self+32);remove_owner(a,list,(int32_t)P(list+8)-1);
        W(scratch,old);list=P(self+32);retain(a,old);CALL(0x2d6b80,list,0,1,scratch);release(a,old);
        W(self+36,P(self+36)+1);break;
    }
    case 0x38ef50:{
        CORE(0x38ca40,P(self+16));uint32_t old=P(self+16);retain(a,old);
        uint32_t next=item(a,P(self+32),0);retain(a,next);release(a,P(self+16));W(self+16,next);
        remove_owner(a,P(self+32),0);CALL(0x301e30,P(self+32),old);release(a,old);
        W(self+36,P(self+36)-1);break;
    }
    default:return UINT64_MAX;
    }
    return 0;
}
