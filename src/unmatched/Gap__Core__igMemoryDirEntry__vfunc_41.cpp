#include "dw4/reflected.h"
#define V1(p) virtual void p();
#define V4(p) V1(p##0) V1(p##1) V1(p##2) V1(p##3)
#define V16(p) V4(p##a) V4(p##b) V4(p##c) V4(p##d)
struct Dev { V16(a) V4(b) V4(c) V1(d) V1(e) V1(f) virtual int v27(int, int, int); };
struct Cod {
    V16(a) V16(b) V16(c)
    virtual void v48(int, int, igIGBFile *, unsigned char);
    virtual void v49();
    virtual void v50(int, int);
};
extern "C" {
int igObject_IsKindOf(...);
int memcpy(...);
extern int DAT_00585a60[4];
void Gap__Core__igMemoryDirEntry__vfunc_41(igMemoryDirEntry *arg0, igIGBFile *arg1);
}
void Gap__Core__igMemoryDirEntry__vfunc_41(igMemoryDirEntry *arg0, igIGBFile *arg1) {
    int s4 = arg1->_chunkSize;
    int s3 = arg1->_memoryBufferPlace;
    int s6 = arg1->_memoryBytesCopied;
    int s2 = arg1->_bytesRemainingInChunk;
    int s8 = arg1->_chunk;
    int cnt = arg0->_memSize;
    Cod *s1 = (Cod *)arg0->_memType;
    int esz = ((igMetaField *)s1)->_size;
    int per = cnt / esz;
    int s0, s7, i, src, j, dst, t0, t1, t2;
    if (((igObject_IsKindOf(s1, DAT_00585a60[0]) != 0) ^ 1) && arg1->_endianSwap != 0) {
        s1->v50(arg0->_ref, per);
    }
    s7 = 0;
    i = 0;
    src = arg0->_ref;
    while (i < cnt) {
        t0 = cnt - i;
        s0 = (t0 < s2) ? t0 : s2;
        if (igObject_IsKindOf(s1, DAT_00585a60[0]) != 0) {
            int q = s0 / esz;
            t1 = per - s7;
            s7 = (t1 < q) ? t1 : q;
            dst = s8 + s3;
            for (j = 0; j < s7; j++) {
                s1->v48(src + j * esz, dst + j * esz, arg1, arg1->_endianSwap);
            }
        } else {
            memcpy(s8 + s3, src, s0);
        }
        src += s0;
        s3 = (s3 + s0) % s4;
        s2 -= s0;
        i += s0;
        if (s2 == 0) {
            s6 += s4 * ((Dev *)arg1->_file)->v27(s8, s4, 1);
            t2 = arg1->_memoryRefBufferSize - s6;
            s2 = (t2 < s4) ? t2 : s4;
            s4 = s2;
        }
    }
    if (s4 != 0) {
        s0 = ((s3 + 3) & ~3) % s4;
        s2 = s2 - (s0 - s3);
        if (s0 < s3) {
            s6 += s4 * ((Dev *)arg1->_file)->v27(s8, s4, 1);
            t2 = arg1->_memoryRefBufferSize - s6;
            s2 = (t2 < s4) ? t2 : s4;
            s4 = s2;
        }
        if (((igObject_IsKindOf(s1, DAT_00585a60[0]) != 0) ^ 1) && arg1->_endianSwap != 0) {
            s1->v50(arg0->_ref, per);
        }
        arg1->_memoryBytesCopied = s6;
        arg1->_bytesRemainingInChunk = s2;
        arg1->_memoryBufferPlace = s0;
        arg1->_chunkSize = s4;
    }
}
