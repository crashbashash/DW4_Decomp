#include "dw4/reflected.h"
extern "C" {

int beNDMWLoadIntf2MesWin__RequestMesErase();

void beNDMWLoadIntf2MesWin__RequestClose(beNDMWLoadIntf2MesWin *arg0) {
    beNDMWLoadIntf2MesWin__RequestMesErase();
    arg0->_isWinClose = 1;
}
}
