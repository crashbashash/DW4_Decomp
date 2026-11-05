/* 0x001ae1d0 — FUN_001ae1d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int igObject_Destroy(void *);

void **FUN_001ae1d0(void **arg0, void *arg1) {
    void *temp_a0;

    if (arg1 != 0) {
        ((igObject *)arg1)->_refCount = (int) ((int)((igObject *)arg1)->_refCount + 1);
    }
    temp_a0 = *arg0;
    if (temp_a0 != 0) {
        ((igObject *)temp_a0)->_refCount = (int) ((int)((igObject *)temp_a0)->_refCount - 1);
        if (((unsigned long long) ((long long) (int)((igObject *)temp_a0)->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    *arg0 = arg1;
    return arg0;
}
