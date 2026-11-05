#include "string-pool.h"
#define P(x) ((uint32_t)a->read(a->user,(x),4))
#define W(x,v) a->write(a->user,(x),4,(uint32_t)(v))
#define B(x) ((uint32_t)a->read(a->user,(x),1))
#define CALL(x,...) a->call(a->user,(x),(const uint64_t[8]){__VA_ARGS__})
#define CORE(x,...) dw4_string_pool(a,(x),(const uint64_t[8]){__VA_ARGS__},scratch)
static void lock(const Dw4MessengerResultsApi *a,uint32_t scratch,int acquire)
{
    uint32_t object=P(0x5871c8);
    if(object) {
        if(acquire)CALL(P(P(object)+132),scratch+16,object,1);
        else CALL(P(P(object)+124),scratch+20,object);
    }
}
uint64_t dw4_string_pool(const Dw4MessengerResultsApi *a,uint32_t entry,
                         const uint64_t v[8],uint32_t scratch)
{
    uint32_t self=(uint32_t)v[0],value,object,header,token,index,count;
    switch(entry) {
    case 0x2eadf0:
        W(self,0);W(self+4,0);W(self+8,16384);W(self+12,0);
        if(!B(0x554c14))W(self+12,(uint32_t)CALL(0x2f88e0,P(0x587048)));
        if(!P(self+12))W(self+12,(uint32_t)CALL(0x2f00d0));
        object=(uint32_t)CALL(0x30c740,24,P(self+12));
        value=object?(uint32_t)CORE(0x30c0c0,object,self,1024):0;W(self,value);
        object=(uint32_t)CALL(0x30cce0,36,P(self+12));
        value=object?(uint32_t)CALL(0x30c770,object,0,P(self),P(self+8)):0;W(self+4,value);
        return self;
    case 0x2eaec0:
        if(self) {
            CORE(0x2eaf20,self);CORE(0x30c120,P(self),1);
            if((int16_t)v[1]>0)CALL(0x2eb050,self);
        }
        return self;
    case 0x2eaf20:
        object=P(self+4);
        while(object) {uint32_t next=P(object+4);CALL(0x30c7d0,object,1);object=next;}
        return 0;
    case 0x2eaf60:
        token=(uint32_t)v[1];if(!token)return 0;
        W(scratch+12,0);
        value=(uint32_t)CORE(0x30c240,P(self),token);
        if(!value) {
            W(scratch+8,0);count=(uint32_t)CALL(0x12a78c,token)+1u;
            value=(uint32_t)CALL(0x30c830,P(self+4),count,scratch+8,scratch+12);
            CALL(0x127098,value,token,count);
            CORE(0x30c2d0,P(self),P(scratch+12),P(scratch+8),value);
        }
        return value;
    case 0x30c0c0:
        W(self,(uint32_t)v[1]);W(self+4,0);W(self+8,0);W(self+12,(uint32_t)v[2]);
        object=P((uint32_t)v[1]+12);
        value=(uint32_t)CALL(P(P(object)+216),object,(uint32_t)v[2]*4u);
        W(self+16,value);W(self+20,0);return self;
    case 0x30c120:
        if(self) {
            CALL(0x2ed460,P(self+16));
            if((int16_t)v[1]>0)CALL(0x30c760,self);
        }
        return self;
    case 0x30c180:
        object=P(0x5871c8);
        if(!v[0]) {
            if(object) {
                W(0x5871c8,0);W(object+4,P(object+4)-1u);
                if(!(P(object+4)&0x7fffffu))CALL(0x2ff820,object);
            }
        } else if(!object) {
            value=(uint32_t)CALL(0x2f8a20);
            if(!B(0x554c14))value=(uint32_t)CALL(0x2f88e0,P(0x587038));
            object=(uint32_t)CALL(0x2ba650,value);
            CALL(P(P(object)+92),scratch+16,object);W(0x5871c8,object);
        }
        return 0;
    case 0x30c240:
        W(scratch,0);W(scratch+4,0);lock(a,scratch,1);
        CORE(0x30c500,self,v[1],scratch,scratch+4);lock(a,scratch,0);return P(scratch);
    case 0x30c2d0:
        lock(a,scratch,1);header=(uint32_t)v[1];W(header,(uint32_t)v[2]);W(header+4,1);
        W(scratch,0);W(scratch+4,0);
        CORE(0x30c500,self,v[3],scratch,scratch+4);
        CORE(0x30c670,self,header,P(scratch+4));lock(a,scratch,0);return header;
    case 0x30c390:
        lock(a,scratch,1);W(scratch,0);W(scratch+4,0);
        CORE(0x30c500,self,(uint32_t)v[1]+8,scratch,scratch+4);
        CORE(0x30c600,self,P(scratch+4));lock(a,scratch,0);return 0;
    case 0x30c430:
        lock(a,scratch,1);object=(uint32_t)v[1];
        if((int32_t)P(self+20)>0) {
            uint32_t owner=P(self),first=P(owner+4);
            if(object==first)W(owner+4,P(first+4));
            else {
                uint32_t previous=P(object+8);W(previous+4,P(object+4));
                uint32_t next=P(previous+4);if(next)W(next+8,previous);
            }
            CALL(0x30c7d0,object,1);
        } else W(self+20,P(self+20)+1u);
        lock(a,scratch,0);return 0;
    case 0x30c500: {
        uint32_t step=P(self+8),lower=0;
        while(step) {
            uint32_t candidate=lower+step;
            if(candidate<=P(self+4)) {
                header=P(P(self+16)+candidate*4u-4u);token=header+8;
                int32_t comparison=(int32_t)CALL(0x12a4a4,v[1],token);
                if(!comparison) {
                    W(header+4,P(header+4)+1u);W((uint32_t)v[2],token);W((uint32_t)v[3],candidate-1u);return 1;
                }
                if(comparison>0)lower=candidate;
            }
            step>>=1;
        }
        W((uint32_t)v[3],lower);return 0;
    }
    case 0x30c600:
        index=(uint32_t)v[1];value=P(self+16)+index*4u;W(self+4,P(self+4)-1u);
        CALL(0x127148,value,value+4,(P(self+4)-index)*4u);
        if(P(self+4)<P(self+8))W(self+8,P(self+8)>>1);
        return 0;
    case 0x30c670:
        count=P(self+12);index=(uint32_t)v[2];
        if(P(self+4)==count) {
            value=(uint32_t)CALL(0x2ed330,P(self+16),count*8u);
            W(self+16,value);W(self+12,count*2u);
        }
        value=P(self+16)+index*4u;
        CALL(0x127148,value+4,value,(P(self+4)-index)*4u);
        W(P(self+16)+index*4u,(uint32_t)v[1]);W(self+4,P(self+4)+1u);
        value=P(self+8)*2u;
        if(value<=P(self+4))W(self+8,P(self+8)?value:1);
        return 0;
    case 0x30c940:
        header=(uint32_t)v[1];CORE(0x30c390,P(self),header);
        count=(uint32_t)CALL(0x12a78c,header+8)+9u;CALL(0x30cb80,self,header,count);
        if(B(self+32))CORE(0x30c430,P(self),self);
        return 0;
    }
    return 0;
}
