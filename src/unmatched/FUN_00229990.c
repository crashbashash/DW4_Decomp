/* 0x00229990 — FUN_00229990. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int Gap__Core__igObject__vfunc_11();

void FUN_00229990(igInterface *arg0) {
    Gap__Core__igObject__vfunc_11();
    arg0->_itemInterface = (int)(arg0);
}
