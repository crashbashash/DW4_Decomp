/* 0x00325810 — FUN_00325810. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int igMemoryPool_CopyConstruct();
extern int DAT_005311f0[4];
void *FUN_00325810(igPageMemoryPool *arg0) {
    igMemoryPool_CopyConstruct();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_005311f0[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}
