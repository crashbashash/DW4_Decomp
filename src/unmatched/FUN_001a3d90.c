/* 0x001a3d90 — FUN_001a3d90. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int igObject_InitHeader();
extern int DAT_00528250[4];
void *FUN_001a3d90(igTraversal *arg0) {
    igObject_InitHeader();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00528250[0]);
    arg0->_travProcs = 0;
    return arg0;
}
