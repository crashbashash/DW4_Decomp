/* 0x003d9de0 — FUN_003d9de0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * Receiver is the beNDMWLoadIntf2DegiState record: the two callers
 * (0x003ea2a0, 0x003ea5f0 in LoadIntf2 vfunc_34) wire its messenger/model
 * controller/text order/common interface/player number/display position. */
#include "dw4/reflected.h"
void FUN_003d9de0(beNDMWLoadIntf2DegiState *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    arg0->_comMdlCtrl = arg4;
    arg0->_commonIntf = arg2;
    arg0->_textOrder = arg3;
    arg0->_plNo = arg1;
    arg0->_messenger = arg5;
    arg0->_dispPos = arg6;
    arg0->_isEnd = 0;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}
