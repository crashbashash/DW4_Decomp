/* 0x003d9e90 — FUN_003d9e90. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * Receiver: beNDMWLoadIntf2DegiState (offsets 32/36/52..64 match _isEnd,
 * _closeKind, _st0.._st3; callers pass an ObjectList_GetAt result). */
#include "dw4/reflected.h"
void FUN_003d9e90(beNDMWLoadIntf2DegiState *arg0) {
    arg0->_isEnd = 0;
    arg0->_closeKind = 1;
    arg0->_st0 = 2;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}
