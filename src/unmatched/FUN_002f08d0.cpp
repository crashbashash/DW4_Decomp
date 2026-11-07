#include "dw4/reflected.h"
class VT { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual int v168(); };
extern "C" {
int FUN_00304680();
extern int DAT_004f90b0[4];
extern int DAT_004f9d60[4];
int FUN_00304430(void *, ...);
void FUN_002f08d0(igMemoryPool *arg0, char *arg1);
}
struct F { VT v; };
void FUN_002f08d0(igMemoryPool *arg0, char *arg1) {
    long long s4, s3, s2, s1, s0, s6, s7, s8;
    long long sp120, sp110, sp100, spF0;
    __int128 spE0;
    VT *o = (VT *)arg0;

    if (arg1 != 0 && *arg1 != 0) {
        FUN_00304430(&DAT_004f90b0[0]);
        FUN_00304680();
    }
    s4 = arg0->_localNetAllocationCountHigh;
    s3 = arg0->_localNetAllocationCount;
    s2 = arg0->_localFreeCount;
    s1 = arg0->_localAllocationCount;
    s0 = arg0->_localNetAllocatedWithOverheadHigh;
    s6 = arg0->_localNetAllocatedWithOverhead;
    s7 = arg0->_localFreedWithOverhead;
    s8 = arg0->_localAllocatedWithOverhead;
    sp120 = arg0->_localNetAllocatedHigh;
    sp110 = arg0->_localNetAllocated;
    sp100 = arg0->_localFreed;
    spF0 = arg0->_localAllocated;
    spE0 = o->v144();
    FUN_00304430(&DAT_004f9d60[0], (int)spF0, (int)sp100, (int)sp110, (int)sp120, (long long)(int)s8, (long long)(int)s7, (long long)(int)s6, (long long)(int)s0, (long long)(int)s1, (long long)(int)s2, (long long)(int)s3, (long long)(int)s4, (long long)spE0, (long long)o->v168());
    FUN_00304680();
}
