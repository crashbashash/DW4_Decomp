/* 0x003ad240 — Gap__Bec__beSvGetFreeSizeApi__vfunc_21. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
extern int DAT_0058a600[4];
extern char GPR_00554e60;

void Gap__Bec__beSvGetFreeSizeApi__vfunc_21(beSvGetFreeSizeApi *arg0, void *arg1) {
    arg0->_connect = (int)((int) *(int *)((char *)(arg1) + 16));
    arg0->_isEnd = 0;
    arg0->_result = 1;
    DAT_0058a600[0] = *(int *)((char *)(arg1) + 64);
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
    GPR_00554e60 = 1;
    *(int *)((char *)(arg0) + 60) = 0;
}
