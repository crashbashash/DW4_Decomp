/* 0x003ad700 — Gap__Bec__beSvEndApi__vfunc_21. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
extern "C" {
int sceMtapPortClose(int);
void Gap__Bec__beSvEndApi__vfunc_21(beSvEndApi *arg0);
}

void Gap__Bec__beSvEndApi__vfunc_21(beSvEndApi *arg0) {
    arg0->_isEnd = 0;
    arg0->_result = 1;
    sceMtapPortClose(2);
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}
