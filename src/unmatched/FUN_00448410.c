/* 0x00448410 — FUN_00448410. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
void FUN_00448410(beNDMWItemBlueArmor *arg0, int arg1, int arg2, int arg3) {
    arg0->_kindNo = 1;
    arg0->_recNo = arg1;
    arg0->_isEquip = 0;
    arg0->_pocket = arg2;
    arg0->_revision = arg3;
}
