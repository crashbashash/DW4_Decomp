/* 0x003d9e70 — FUN_003d9e70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * Receiver: beNDMWLoadIntf2DegiState (element of DegiStateCtrl._statDataList). */
#include "dw4/reflected.h"
void FUN_003d9e70(beNDMWLoadIntf2DegiState *arg0, int arg1) {
    arg0->_isEnd = 0;
    arg0->_closeKind = arg1;
    arg0->_st0 = 2;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}
