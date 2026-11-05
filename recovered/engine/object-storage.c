/* Complete 300d30..301008 helper run, plus encoded-selector dependency.
 * Guest-address behavioral recovery; allocator virtual services remain external. */
#include "object-storage.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define CORE(e,...) dw4_object_storage(a,(e),(const uint64_t[8]){__VA_ARGS__})
uint64_t dw4_object_storage(const Dw4MessengerResultsApi *a,uint32_t entry,const uint64_t v[8]) {
    uint32_t self=(uint32_t)v[0],allocator,slot,count;
    switch(entry) {
    case 0x2f0700: {
        int32_t encoded=(int32_t)v[0];
        return (uint64_t)(int64_t)(int32_t)P(P(P((encoded&1)?0x586f60:0x586f58))+(uint32_t)(encoded>>1)*4);
    }
    case 0x301000: return CORE(0x2f0700,a->read(a->user,self+7,1));
    case 0x300d30: {
        uint32_t meta=(uint32_t)CALL(P(P(self)+88),v[0]);
        return (uint64_t)(int64_t)(int32_t)(self-P(meta+32));
    }
    case 0x300fa0: {
        count=(uint32_t)CALL(0x12a78c,v[1])+1;
        uint64_t result=CORE(0x300d70,v[0],count);
        CALL(0x12a5fc,result,v[1]);return result;
    }
    case 0x300f00: case 0x300f50:
        if(v[1]) {allocator=(uint32_t)CORE(0x301000,v[0]);CALL(P(P(allocator)+264),allocator,v[1]);}
        return 0; /* physical return register is undefined */
    default:
        switch(entry) {
        case 0x300d70:slot=216;count=1;break;
        case 0x300db0:slot=220;count=2;break;
        case 0x300e00:slot=224;count=2;break;
        case 0x300e50:slot=232;count=2;break;
        case 0x300ea0:slot=236;count=3;break;
        default:return 0;
        }
        allocator=(uint32_t)CORE(0x301000,v[0]);
        return CALL(P(P(allocator)+slot),allocator,v[1],count>1?v[2]:0,count>2?v[3]:0);
    }
}
