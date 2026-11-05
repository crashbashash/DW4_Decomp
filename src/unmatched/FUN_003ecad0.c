/* 0x003ecad0 — FUN_003ecad0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * Receiver is the load-menu message window (beNDMWLoadIntf2MesWin): +33 _isMesCom, +52 _mesNo. */
#include "dw4/reflected.h"
void FUN_003ecad0(beNDMWLoadIntf2MesWin *arg0, int arg1) {
    arg0->_isMesCom = 1;
    arg0->_mesNo = arg1;
}
