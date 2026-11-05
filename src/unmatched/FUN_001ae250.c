/* 0x001ae250 — FUN_001ae250. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int igObject_Destroy(void *);

void **FUN_001ae250(void **arg0, igObject *arg1) {
    igObject *temp_a0;

    if (arg1 != 0) {
        arg1->_refCount = (int) (arg1->_refCount + 1);
    }
    temp_a0 = (igObject *)*arg0;
    if (temp_a0 != 0) {
        temp_a0->_refCount = (int) (temp_a0->_refCount - 1);
        if (((unsigned long long) ((long long) (int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    *arg0 = arg1;
    return arg0;
}
