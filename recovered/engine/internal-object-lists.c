/* Complete raw/retaining pointer-list run and internal-list factory. The
 * 16-byte ABI is buffer+8/count+12; allocator byte capacity is queried externally. */
#include "internal-object-lists.h"
#include "metadata-bootstrap.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define B(p) ((uint32_t)a->read(a->user,(p),1))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define CORE(e,...) dw4_internal_object_list(a,(e),(const uint64_t[8]){__VA_ARGS__})
static uint64_t ptr(uint32_t p){return (uint64_t)(int64_t)(int32_t)p;}
static uint32_t capacity(const Dw4MessengerResultsApi *a,uint32_t list){
    uint32_t buffer=P(list+8);return buffer?((uint32_t)CALL(0x2ed4e0,buffer)>>2):0;
}
static void retain(const Dw4MessengerResultsApi *a,uint32_t p){if(p)W(p+4,P(p+4)+1);}
static void release(const Dw4MessengerResultsApi *a,uint32_t p){if(p){W(p+4,P(p+4)-1);if(!(P(p+4)&0x7fffff))CALL(0x2ff820,p);}}
uint64_t dw4_internal_object_list(const Dw4MessengerResultsApi *a,uint32_t entry,const uint64_t v[8]){
    uint32_t self=(uint32_t)v[0],other=(uint32_t)v[1],allocator,bytes;
    int32_t index=(int32_t)v[1],count,i;
    switch(entry){
    case 0x2c2670:
        if(B(P(0x586dc8))){CALL(0x2c2860);return CALL(0x2fda40,P(0x5860d0),v[0]);}
        other=(uint32_t)CALL(0x2ff790,16,0,v[0]);if(other)other=(uint32_t)CORE(0x2eab70,other,1);
        CALL(P(P(other)+44),other);CALL(P(P(other)+36),other,0);return ptr(other);
    case 0x2ea4f0:
        CALL(0x2ff010,v[0],v[1]);W(self,0x532770);if(v[0])CORE(0x2ea550,v[0]);
        allocator=(uint32_t)CALL(0x301000,v[0]);W(self+8,(uint32_t)CALL(P(P(allocator)+216),allocator,16));return v[0];
    case 0x2ea550:
        CALL(0x2fef20,v[0]);W(self,0x532770);W(self+8,0);W(self+12,0);return v[0];
    case 0x2ea590:
        CALL(0x2fef70,v[0],v[1]);W(self,0x532770);W(self+12,P(other+12));
        if(P(other+8)){
            bytes=P(self+12)*4;allocator=(uint32_t)CALL(0x301000,v[0]);
            W(self+8,(uint32_t)CALL(P(P(allocator)+216),allocator,ptr(bytes)));
            CALL(0x127098,P(self+8),P(other+8),ptr(bytes));
        }else W(self+8,0);
        return v[0];
    case 0x2ea630:
        other=P(self+8);if(other){allocator=(uint32_t)CALL(0x301000,v[0]);CALL(P(P(allocator)+264),allocator,other);}
        CALL(0x2ff0a0,v[0]);return 0;
    case 0x2ea690:{
        if(index<(int32_t)capacity(a,self))return 0;
        uint32_t old=capacity(a,self),size=old;if(!size)size=4;
        while(index>=(int32_t)size)size=(int32_t)size<512?size*2:size+512;
        W(self+8,(uint32_t)CALL(0x300e50,v[0],P(self+8),ptr(size*4)));
        CALL(0x12724c,P(self+8)+old*4,0,ptr((size-old)*4));return 0;
    }
    case 0x2ea780:
        for(i=0;i<(int32_t)P(self+12);i++){
            uint32_t offset=(uint32_t)i*4;
            uint32_t buffer=P(self+8),field_offset=P(other+8);
            uint32_t element=P(buffer+offset),name=P(element+field_offset);
            if(!CALL(0x12a4a4,name,v[2]))return ptr(P(P(self+8)+offset));
        }return 0;
    case 0x2ea820:return dw4_metadata_bootstrap(a,entry,v); /* shared recovered lookup */
    case 0x2ea870:
        i=(int32_t)P(self+12);while(i<(int32_t)capacity(a,self)){W(P(self+8)+(uint32_t)i*4,0);i++;}return 0;
    case 0x2ea8e0:
        count=(int32_t)P(self+12);if(count>=(int32_t)capacity(a,self))CORE(0x2ea690,v[0],(uint64_t)(int64_t)count);
        for(i=(int32_t)P(self+12);i>index;i--)W(P(self+8)+(uint32_t)i*4,P(P(self+8)+(uint32_t)(i-1)*4));
        W(P(self+8)+(uint32_t)index*4,(uint32_t)v[2]);W(self+12,P(self+12)+1);return 0;
    case 0x2ea9a0:
        if(index>=(int32_t)capacity(a,self)){CORE(0x2ea690,v[0],v[1]);}
        W(self+12,other);return 0;
    case 0x2eaa00:
        if(index>=(int32_t)P(self+12))return UINT64_MAX;
        for(i=index;i<(int32_t)(P(self+12)-1);i++)W(P(self+8)+(uint32_t)i*4,P(P(self+8)+(uint32_t)(i+1)*4));
        W(self+12,P(self+12)-1);return (uint64_t)(int64_t)index;
    case 0x2eaa60:
        count=(int32_t)P(self+12);if(count>=(int32_t)capacity(a,self))CORE(0x2ea690,v[0],(uint64_t)(int64_t)count);
        W(P(self+8)+P(self+12)*4,other);W(self+12,P(self+12)+1);return 0;
    case 0x2eaaf0:
        if(index>=(int32_t)capacity(a,self)){CORE(0x2ea690,v[0],v[1]);}
        W(P(self+8)+other*4,(uint32_t)v[2]);return 0;
    case 0x2eab70:CORE(0x2ea4f0,v[0],v[1]);W(self,0x5327d0);return v[0];
    case 0x2eabb0:CORE(0x2ea550,v[0]);W(self,0x5327d0);return v[0];
    case 0x2eabf0:CORE(0x2ea590,v[0],v[1]);W(self,0x5327d0);return v[0];
    case 0x2eac30:CORE(0x2eac80,v[0],0);CORE(0x2ea630,v[0]);return 0;
    case 0x2eac60:retain(a,(uint32_t)v[2]);CORE(0x2ea8e0,v[0],v[1],v[2]);return 0;
    case 0x2eac80:
        count=(int32_t)P(self+12);if(index<count){i=count-1;while(i>=index){release(a,P(P(self+8)+(uint32_t)i*4));i--;}}
        CORE(0x2ea9a0,v[0],v[1]);return 0;
    case 0x2ead50:
        retain(a,(uint32_t)v[2]);release(a,P(P(self+8)+other*4));CORE(0x2eaaf0,v[0],v[1],v[2]);return 0;
    case 0x2ead30:retain(a,other);CORE(0x2eaa60,v[0],v[1]);return 0;
    default:return UINT64_MAX;
    }
}
