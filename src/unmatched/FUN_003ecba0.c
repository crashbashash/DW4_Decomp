/* 0x003ecba0 — FUN_003ecba0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
void FUN_003ecba0(beNDMWLoadIntf2MesWin *arg0, int arg1) {
    arg0->_isMesCom = 1;
    arg0->_isSystemMes = 1;
    arg0->_sysMesNo = arg1;
    arg0->_sysStat = 0;
}
