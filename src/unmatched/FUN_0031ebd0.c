/* 0x0031ebd0 — FUN_0031ebd0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_002effb0();
int FUN_0031eb90();
extern int DAT_00531030[4];
void *FUN_0031ebd0(igArenaMemoryPool *arg0) {
    FUN_002effb0();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00531030[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    if (arg0 != 0) {
        FUN_0031eb90(arg0);
    }
    return arg0;
}
