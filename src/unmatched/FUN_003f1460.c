/* Receiver: beNDMWMcUtilCtrl (reflected offsets 14/16/20/28/32/36/48..60 all match; callers pass
 * beNDMWLoadCtrl2CommonIntf::_mcUtilCtrl, +52). */
#include "dw4/reflected.h"
void FUN_003f1460(beNDMWMcUtilCtrl *arg0, int arg1, int arg2) {
    arg0->_tgCon = arg2;
    arg0->_kind = arg1;
    arg0->_result = 0;
    arg0->_isResult = 0;
    arg0->_isRun = 1;
    arg0->_isFormatRun = 0;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}
