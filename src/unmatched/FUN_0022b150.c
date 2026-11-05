/* 0x0022b150 — FUN_0022b150. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int Gap__Core__igObject__vfunc_11();

void FUN_0022b150(igInterface *arg0) {
    Gap__Core__igObject__vfunc_11();
    arg0->_listenerInterface = (int)(arg0);
}
