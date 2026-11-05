/* 0x003e0b80 — FUN_003e0b80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * Receiver is the beNDMWLoadIntf2SelSlot record (ss_clear). */
#include "dw4/reflected.h"

void FUN_003e0b80(beNDMWLoadIntf2SelSlot *arg0) {
    arg0->_isOpen = 0;
    arg0->_isCansel = 0;
    arg0->_isEnd = 0;
    arg0->_isSelect = 0;
    arg0->_isEnd = 0;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}
