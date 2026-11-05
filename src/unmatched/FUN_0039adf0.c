/* 0x0039adf0 — FUN_0039adf0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
void FUN_0039adf0(beLoadingNode *arg0) {
    arg0->_stopTime = arg0->_lockTime;
}
