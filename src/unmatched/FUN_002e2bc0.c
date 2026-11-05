/* 0x002e2bc0 — FUN_002e2bc0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int FUN_002d7aa0();

void FUN_002e2bc0(igDirEntry *arg0) {
    FUN_002d7aa0();
    arg0->_resolveMethod = 2;
    arg0->_refType = 0;
}
