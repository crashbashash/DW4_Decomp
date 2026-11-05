/* 0x00448660 — FUN_00448660. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
void FUN_00448660(beNDMWItemAbilityChip *arg0, int arg1) {
    arg0->_kindNo = 3;
    arg0->_recNo = arg1;
    arg0->_isEquip = 0;
}
