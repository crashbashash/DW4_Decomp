/* 0x00303460 — FUN_00303460. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int igObject_Destroy();

void FUN_00303460(igObjectRefMetaField *arg0, igObject *arg1) {
    igObject **temp_s0;
    igObject *temp_a0;

    temp_s0 = (igObject **)(arg0->_default);
    if (arg1 != 0) {
        arg1->_refCount = (int)((int) (arg1->_refCount + 1));
    }
    temp_a0 = (igObject *)(*temp_s0);
    if (temp_a0 != 0) {
        temp_a0->_refCount = (int)((int) (temp_a0->_refCount - 1));
        if (((unsigned long long) ((long long) (int) temp_a0->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    *temp_s0 = arg1;
}
