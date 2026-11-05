/* 0x003ad6e0 — Gap__Bec__beSvStartApi__vfunc_23. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
void Gap__Bec__beSvStartApi__vfunc_23(beSvStartApi *arg0, void *arg1) {
    *(int *)((char *)(arg1) + 24) = (int)((int) arg0->_result);
    *(char *)((char *)(arg1) + 44) = 1;
}
