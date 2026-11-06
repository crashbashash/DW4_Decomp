/* Receiver: beNDMWLoadIntf2MesWin (fields +33/+34 bool, +36/+40/+48/+52 int; the caller
 * beNDMWLoadIntf2MesWin__EndSystemMessage reads the same fields). */
#include "dw4/reflected.h"
void FUN_003ecae0(beNDMWLoadIntf2MesWin *arg0, int arg1, int arg2) {
    arg0->_isMesCom = 1;
    arg0->_isCtrl = 1;
    arg0->_mesNo = arg1;
    arg0->_curPoint = arg2;
    arg0->_statCtrl = 0;
    arg0->_kindCtrl = 0;
}
