/* Receiver is a beNDMWLoadIntf2MesWin: the only reflected class with seven bool fields at +28..+34
 * (_isWinOpen.._isCtrl). */
#include "dw4/reflected.h"

void beNDMWLoadIntf2MesWin__RequestOpen(beNDMWLoadIntf2MesWin *arg0) {
    arg0->_isWinOpen = 1;
    arg0->_isWinClose = 0;
    arg0->_isSelect = 0;
    arg0->_isCtrl = 0;
    arg0->_isSystemMes = 0;
    arg0->_isMesErase = 0;
    arg0->_isMesCom = 0;
}
