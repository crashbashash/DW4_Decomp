/* 0x003ecb00 — FUN_003ecb00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * Receiver: beNDMWLoadIntf2MesWin (fields +33/+34/+36/+40/+52 match exactly). */
#include "dw4/reflected.h"
void FUN_003ecb00(beNDMWLoadIntf2MesWin *arg0, int arg1) {
    arg0->_isMesCom = 1;
    arg0->_isCtrl = 1;
    arg0->_mesNo = arg1;
    arg0->_statCtrl = 0;
    arg0->_kindCtrl = 1;
}
