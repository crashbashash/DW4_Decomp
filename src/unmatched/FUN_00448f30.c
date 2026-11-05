/* 0x00448f30 — FUN_00448f30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
void FUN_00448f30(beNDMWItemWaza *arg0, int arg1, int arg2) {
    arg0->_recNo = arg1;
    arg0->_baseNo = arg2;
    arg0->_kindNo = 9;
    arg0->_isEquip = 0;
}
