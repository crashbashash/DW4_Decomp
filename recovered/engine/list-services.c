#include "list-services.h"
#define P(x) ((uint32_t)a->read(a->user,(x),4))
#define W(x,v) a->write(a->user,(x),4,(uint32_t)(v))
#define CALL(x,...) a->call(a->user,(x),(const uint64_t[8]){__VA_ARGS__})
#define CORE(x,...) dw4_list_service(a,(x),(const uint64_t[8]){__VA_ARGS__},scratch)
static void release_string(const Dw4MessengerResultsApi *a,uint32_t token)
{
    if(token) { W(token-4,P(token-4)-1u);if(!P(token-4)) CALL(0x30c940,P(token-8),token-8); }
}
static uint32_t null_string(const Dw4MessengerResultsApi *a)
{
    uint32_t pool=P(0x586f20);
    if(!pool) {
        uint32_t memory=(uint32_t)CALL(0x2eb010,16);
        pool=memory?(uint32_t)CALL(0x2eadf0,memory):0;W(0x586f20,pool);
    }
    return (uint32_t)CALL(0x2eaf60,P(0x586f20),0);
}
uint64_t dw4_list_service(const Dw4MessengerResultsApi *a,uint32_t entry,
                          const uint64_t v[8],uint32_t scratch)
{
    uint32_t self=(uint32_t)v[0],value,old,buffer,meta,capacity,stride;
    int32_t index=(int32_t)v[1],number=(int32_t)v[2],count,i;
    switch(entry) {
    case 0x2d6670:return UINT64_MAX;
    case 0x2d6680:
        capacity=(uint32_t)v[1];stride=(uint32_t)v[2];old=P(self+16);
        if(!capacity) { CALL(0x300f50,self,old);W(self+16,0); }
        else {
            uint32_t kind=(uint32_t)CALL(P(P(self)+88),self);
            int16_t tag=(int16_t)a->read(a->user,P(0x5867a0)+18,2);
            meta=(uint32_t)CALL(0x2fdf00,kind,(uint64_t)(int64_t)tag);
            value=P(meta+60);
            uint32_t unit=(uint32_t)CALL(P(P(value)+100),value)&65535u;
            uint32_t bytes=capacity*stride;
            uint32_t elements=unit?bytes/unit:0xffffffffu;
            uint32_t allocator=(uint32_t)CALL(0x301000,self);
            CALL(0x2fb190,scratch,meta,self,elements,allocator);
            if(old) {
                uint32_t n=(int32_t)capacity<=(int32_t)P(self+12)?capacity:P(self+12);
                CALL(0x127098,P(self+16),old,n*stride);CALL(0x300f50,self,old);
            }
        }
        W(self+12,capacity);return 0;
    case 0x2d6790:
        capacity=P(self+12);if((int32_t)capacity<5)capacity=4;
        while((int32_t)capacity<index) capacity=(int32_t)capacity<1024?capacity*2:capacity+1024;
        CORE(0x2d6680,self,capacity,v[2]);W(self+8,(uint32_t)index);return 0;
    case 0x2d6810:case 0x2d6b80:
        stride=entry==0x2d6810?(uint32_t)v[4]:4;
        count=(int32_t)P(self+8);
        if(index<0 || index>count || number<=0)return 0;
        value=(uint32_t)count+(uint32_t)number;
        if((int32_t)P(self+12)<(int32_t)value) CORE(0x2d6790,self,(uint64_t)(int64_t)(int32_t)value,stride);
        else W(self+8,value);
        buffer=P(self+16)+(uint32_t)index*stride;
        if(count!=index)CALL(0x127148,buffer+(uint32_t)number*stride,buffer,((uint32_t)count-(uint32_t)index)*stride);
        CALL(0x127098,buffer,v[3],(uint32_t)number*stride);return 0;
    case 0x2d6900:case 0x2d6c60:
        number=(int32_t)v[1];stride=entry==0x2d6900?(uint32_t)v[3]:4;
        if(number<=0)return 0;
        old=P(self+8);value=old+(uint32_t)number;
        if((int32_t)P(self+12)<(int32_t)value)CORE(0x2d6790,self,(uint64_t)(int64_t)(int32_t)value,stride);
        else W(self+8,value);
        CALL(0x127098,P(self+16)+old*stride,v[2],(uint32_t)number*stride);return 0;
    case 0x2d69a0:case 0x2d6cf0:
        stride=entry==0x2d69a0?(uint32_t)v[2]:4;count=(int32_t)P(self+8);
        if(count<=0 || index<0 || index>=count)return 0;
        if(index!=count-1) {
            buffer=P(self+16)+(uint32_t)index*stride;
            CALL(0x127148,buffer,buffer+stride,((uint32_t)count-(uint32_t)index-1)*stride);
        }
        W(self+8,P(self+8)-1u);return 0;
    case 0x2d6a20:case 0x2d6d70: {
        int32_t low=0,high=(int32_t)(P(self+8)-1u),middle,result;
        stride=entry==0x2d6a20?(uint32_t)v[3]:4;
        while(low<high) {
            middle=(int32_t)((uint32_t)low+(uint32_t)high)>>1;
            result=(int32_t)CALL((uint32_t)v[2],P(self+16)+(uint32_t)middle*stride,v[1]);
            if(result<0)low=middle+1;
            else if(result>0)high=middle-1;
            else return (uint64_t)(int64_t)middle;
        }
        if(!P(self+8))return UINT64_MAX;
        result=(int32_t)CALL((uint32_t)v[2],P(self+16)+(uint32_t)low*stride,v[1]);
        return result?UINT64_MAX:(uint64_t)(int64_t)low;
    }
    case 0x2d6b20:
        old=P(self+8);CORE(0x2d6790,self,(uint64_t)(int64_t)(int32_t)(old+1u),4);
        W(P(self+16)+old*4,(uint32_t)v[1]);return 0;
    case 0x1c64e0:
        value=P(P((uint32_t)v[1]+16)+(uint32_t)v[2]*4);W(self,value);
        value=P(self);if(value)W(value-4,P(value-4)+1u);return 0;
    case 0x1ca620:
        old=P(self+8);CORE(0x30cdf0,self,(uint64_t)(int64_t)(int32_t)(old+1u));
        buffer=P(self+16)+old*4;value=P((uint32_t)v[1]);
        if(value)W(value-4,P(value-4)+1u);
        release_string(a,P(buffer));W(buffer,P((uint32_t)v[1]));return 0;
    case 0x301e30:
        value=(uint32_t)v[1];if(value)W(value+4,P(value+4)+1u);
        old=P(self+8);
        if((int32_t)old<(int32_t)P(self+12)) {W(self+8,old+1u);W(P(self+16)+old*4,value);}
        else CORE(0x2d6b20,self,v[1]);
        return 0;
    case 0x30cdf0:
        count=(int32_t)P(self+8);
        if(count>=index) {
            for(i=index;i<count;i++) {
                buffer=P(self+16)+(uint32_t)i*4;value=null_string(a);
                release_string(a,P(buffer));W(buffer,value);
            }
            W(self+8,(uint32_t)index);
        } else {
            if(index>=0) {
                if((int32_t)P(self+12)<index)CORE(0x2d6790,self,(uint64_t)(int64_t)index,4);
                else W(self+8,(uint32_t)index);
            }
            CALL(0x12724c,P(self+16)+(uint32_t)count*4,0,((uint32_t)index-(uint32_t)count)*4);
        }
        return 0;
    }
    return 0; /* Only documented entries are valid for this reference adapter. */
}
