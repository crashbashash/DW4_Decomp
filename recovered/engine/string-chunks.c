#include "string-chunks.h"
#define P(x) ((uint32_t)a->read(a->user,(x),4))
#define H(x) ((uint32_t)a->read(a->user,(x),2))
#define W(x,v) a->write(a->user,(x),4,(uint32_t)(v))
#define SH(x,v) a->write(a->user,(x),2,(uint16_t)(v))
#define CALL(x,...) a->call(a->user,(x),(const uint64_t[8]){__VA_ARGS__})
#define CORE(x,...) dw4_string_chunk(a,(x),(const uint64_t[8]){__VA_ARGS__})
uint64_t dw4_string_chunk(const Dw4MessengerResultsApi *a,uint32_t entry,const uint64_t v[8])
{
    uint32_t self=(uint32_t)v[0],object,size,value,node,previous,next,amount;
    switch(entry) {
    case 0x30c740:case 0x30cce0:
        object=(uint32_t)v[1];return CALL(P(P(object)+216),object,v[0]);
    case 0x30c760:case 0x30cd00:return CALL(0x2ed4b0,self);
    case 0x30c770:
        W(self,(uint32_t)v[2]);W(self+4,0);W(self+8,(uint32_t)v[1]);W(self+12,(uint32_t)v[3]);
        W(self+16,0);W(self+20,0);W(self+24,0);W(self+28,0xffffffffu);
        a->write(a->user,self+32,1,1);CORE(0x30c9b0,self);return self;
    case 0x30c7d0:
        if(self) {CORE(0x30ca30,self);if((int16_t)v[1]>0)CORE(0x30cd00,self);}
        return self;
    case 0x30c9b0:
        object=P(P(P(self))+12);size=P(self+12);
        value=(uint32_t)CALL(P(P(object)+216),object,size);W(self+16,value);
        W(self+24,P(self+16)+P(self+12));W(self+20,P(self+16)+P(self+12));
        SH(P(self+24)-2,P(self+12)>>2);SH(P(self+24)-4,0);return 0;
    case 0x30ca30:return CALL(0x2ed460,P(self+16));
    case 0x30ca40: {
        uint32_t units=((uint32_t)v[1]>>2)&65535u,largest=0;
        node=P(self+24);previous=0;
        while(node) {
            uint32_t length=H(node-2),delta=H(node-4);
            if((largest&65535u)<length)largest=length;
            if(length>=units) {
                value=node-length*4u;
                if(length==units) {
                    if(previous)SH(previous-4,delta?H(previous-4)+delta:0);
                    if(node==P(self+24))W(self+24,delta?node+delta*4u:0);
                } else SH(node-2,length-units);
                W(self+28,0xffffffffu);return value;
            }
            previous=node;node=delta?node+delta*4u:0;
        }
        W(self+28,(largest&65535u)*4u);return 0;
    }
    case 0x30cb30:
        previous=(uint32_t)v[1];node=(uint32_t)v[2];next=(uint32_t)v[3];
        if(node==P(self+24))W(self+24,next);
        if(previous)SH(previous-4,H(previous-4)+H(node-4));
        SH(next-2,H(node-2)+H(next-2));return H(next-2)*4u;
    case 0x30cb80: {
        amount=(((uint32_t)v[2]+3u)>>2)&65535u;size=amount*4u;
        uint32_t end=(uint32_t)v[1]+size,prevprev=0;
        previous=0;node=P(self+24);
        if(!node || end<node)W(self+24,end);
        else {
            while(node && node<end) {
                uint32_t delta=H(node-4);prevprev=previous;previous=node;
                node=delta?node+delta*4u:0;
            }
        }
        SH(end-2,amount);SH(end-4,node?(uint32_t)((int32_t)(node-end)>>2):0);
        if(previous) {
            SH(previous-4,(uint32_t)((int32_t)(end-previous)>>2));
            if(end-size==previous) {
                size=(uint32_t)CORE(0x30cb30,self,prevprev,previous,end);
                previous=prevprev;
            }
        }
        if(node && node-H(node-2)*4u==end)size=(uint32_t)CORE(0x30cb30,self,previous,end,node);
        value=P(self+28);if((int32_t)value>=0 && (int32_t)value<(int32_t)size)W(self+28,size);
        if(size==P(self+12))a->write(a->user,self+32,1,1);
        return 0;
    }
    case 0x30c830:
        size=(((uint32_t)v[1]+3u)&~3u)+8u;node=self;value=0;
        while(!value) {
            uint32_t cached=P(node+28);
            if((int32_t)cached<0 || cached>=size)value=(uint32_t)CORE(0x30ca40,node,size);
            if(value)break;
            if(!P(node+4)) {
                uint32_t block=P(self+12);if(block<size)block=size;
                object=P(P(P(self))+12);
                uint32_t fresh=(uint32_t)CORE(0x30cce0,36,object);
                if(fresh)fresh=(uint32_t)CORE(0x30c770,fresh,node,P(self),block);
                W(node+4,fresh);
            }
            node=P(node+4);
        }
        W((uint32_t)v[2],node);W((uint32_t)v[3],value);a->write(a->user,node+32,1,0);
        return value+8;
    }
    return 0;
}
