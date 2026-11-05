/* 0x00330cf0 - Gap__Core__igPsx2LongTimer__vfunc_31. Virtual call returning long long (sd store). */
#include "dw4/reflected.h"
extern "C" {

void Gap__Core__igPsx2LongTimer__vfunc_31(igPsx2LongTimer *arg0);
}
class DW4VC_148_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual long long vX(); };
void Gap__Core__igPsx2LongTimer__vfunc_31(igPsx2LongTimer *arg0) {
    arg0->_isStopped = 0;
    arg0->_additionalTime = (long long) arg0->_resetTime;
    arg0->_startTime = ((DW4VC_148_0 *)(((char *)(arg0) + 0)))->vX();
}
