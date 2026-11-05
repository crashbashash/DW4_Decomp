/* 0x001423d0 — FUN_001423d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
void FUN_001423d0(igTextureAttr *arg0, int arg1) {
    arg0->_minFilter = arg1;
}
