/* 0x00388ff0 — FUN_00388ff0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
void FUN_00388ff0(beHitLandModelOrder *arg0) {
    arg0->_kind = 0;
    arg0->_rayCount = 0;
    arg0->_hitdataCount = 0;
}
