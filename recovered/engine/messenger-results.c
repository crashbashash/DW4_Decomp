/* Complete contiguous messenger result/accessor block; nonmatching reference. */
#include "messenger-results.h"
#define P(x) ((uint32_t)a->read(a->user,(x),4))
#define W(x,v) a->write(a->user,(x),4,(uint32_t)(v))
#define CALL(x,...) a->call(a->user,(x),(const uint64_t[8]){__VA_ARGS__})
static uint32_t list(const Dw4MessengerResultsApi *a,uint32_t self,unsigned slot)
{
    return P(P(self+16)+slot);
}
static uint32_t append(const Dw4MessengerResultsApi *a,uint32_t items,unsigned width)
{
    uint32_t index=P(items+8);
    if ((int32_t)index<(int32_t)P(items+12)) W(items+8,index+1u);
    else CALL(0x2d6790,items,index+1u,width);
    return P(items+16)+index*width;
}
static void string_release(const Dw4MessengerResultsApi *a,uint32_t value)
{
    if (value) {
        uint32_t refs=P(value-4)-1u;
        W(value-4,refs);
        if (!refs) CALL(0x30c940,P(value-8),value-8);
    }
}
static uint64_t signed_word(uint32_t v) { return (uint64_t)(int64_t)(int32_t)v; }

uint64_t dw4_messenger_result(const Dw4MessengerResultsApi *a,uint32_t entry,
                              uint64_t a0,uint64_t a1,uint64_t a2,
                              uint32_t f12,uint32_t scratch)
{
    uint32_t self=(uint32_t)a0,items,index=(uint32_t)a1,address,value;
    int32_t count,i;
    switch(entry) {
    case 0x38f0e0: a->write(a->user,P(self+16)+8,1,a1); return 0;
    case 0x38f0f0: return signed_word(P(list(a,self,16)+8));
    case 0x38f100:
        items=list(a,self,16);
        if ((int32_t)index>=0) {
            if ((int32_t)P(items+12)<(int32_t)index) CALL(0x2d6790,items,index,1);
            else W(items+8,index);
        }
        return 0;
    case 0x38f150:
        address=append(a,list(a,self,16),1);a->write(a->user,address,1,a1);return 0;
    case 0x38f1d0: W(list(a,self,16)+8,0);return 0;
    case 0x38f1e0:
        items=list(a,self,16);count=(int32_t)P(items+8);
        if (count && (int32_t)index>=0 && (int32_t)index<count)
            a->write(a->user,P(items+16)+index,1,a2);
        return 0;
    case 0x38f220: return a->read(a->user,P(list(a,self,16)+16)+index,1);
    case 0x38f240: return signed_word(P(list(a,self,20)+8));
    case 0x38f250: W(append(a,list(a,self,20),4),a1);return 0;
    case 0x38f2d0: W(list(a,self,20)+8,0);return 0;
    case 0x38f2e0:
        items=list(a,self,20);count=(int32_t)P(items+8);
        if (count && (int32_t)index>=0 && (int32_t)index<count) W(P(items+16)+index*4u,a2);
        return 0;
    case 0x38f320: return signed_word(P(P(list(a,self,20)+16)+index*4u));
    case 0x38f340: return signed_word(P(list(a,self,24)+8));
    case 0x38f350: W(append(a,list(a,self,24),4),f12);return 0;
    case 0x38f3d0: return P(P(list(a,self,24)+16)+index*4u);
    case 0x38f3f0: return signed_word(P(list(a,self,28)+8));
    case 0x38f400: a->write(a->user,append(a,list(a,self,28),8),8,a1);return 0;
    case 0x38f480: return a->read(a->user,P(list(a,self,28)+16)+index*8u,8);
    case 0x38f4a0: return signed_word(P(list(a,self,32)+8));
    case 0x38f4b0:
        address=append(a,list(a,self,32),12);
        for(i=0;i<3;i++) W(address+(uint32_t)i*4,P((uint32_t)a1+(uint32_t)i*4));
        return 0;
    case 0x38f550: W(list(a,self,32)+8,0);return 0;
    case 0x38f560:
        address=P(list(a,(uint32_t)a1,32)+16)+(uint32_t)a2*12u;
        for(i=0;i<3;i++) W(self+(uint32_t)i*4,P(address+(uint32_t)i*4));
        return 0;
    case 0x38f5a0: return signed_word(P(list(a,self,36)+8));
    case 0x38f5b0: CALL(0x1908f0,append(a,list(a,self,36),64),a1);return 0;
    case 0x38f630: CALL(0x1908f0,a0,P(list(a,(uint32_t)a1,36)+16)+(uint32_t)a2*64u);return 0;
    case 0x38f660: return signed_word(P(list(a,self,40)+8));
    case 0x38f670: CALL(0x301e30,list(a,self,40),a1);return 0;
    case 0x38f690:
        items=list(a,self,40);count=(int32_t)P(items+8);
        for(i=0;i<count;i++) {
            value=P(P(items+16)+(uint32_t)i*4);
            if (value) {
                W(value+4,P(value+4)-1u);
                if (!(P(value+4)&0x7fffffu)) CALL(0x2ff820,value);
            }
        }
        count=(int32_t)P(items+8);
        for(i=0;i<count;i++) W(P(items+16)+(uint32_t)i*4,0);
        W(items+8,0);return 0;
    case 0x38f800: return signed_word(P(P(list(a,self,40)+16)+index*4u));
    case 0x38f820: return signed_word(P(list(a,self,44)+8));
    case 0x38f830:
        value=0;
        if (a1) {
            uint32_t pool=P(0x586f20);
            if (!pool) {
                uint32_t allocation=(uint32_t)CALL(0x2eb010,16);
                pool=allocation?(uint32_t)CALL(0x2eadf0,allocation):0;
                W(0x586f20,pool);
            }
            value=(uint32_t)CALL(0x2eaf60,pool,a1);
        }
        W(scratch,value);CALL(0x1ca620,list(a,self,44),scratch);
        string_release(a,P(scratch));return 0;
    case 0x38f8f0:
        CALL(0x1c64e0,scratch,list(a,self,44),a1);
        value=P(scratch);string_release(a,value);return signed_word(value);
    }
    return 0; /* Unknown entry is a harness error, not a recovered engine API. */
}
