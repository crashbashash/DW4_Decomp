#include "dw4/reflected.h"
extern "C" {
int FUN_003ecad0(beNDMWLoadIntf2MesWin *, int);
int FUN_003ecae0(beNDMWLoadIntf2MesWin *, int, int);
int FUN_003ecb00(beNDMWLoadIntf2MesWin *, int);
int beNDMWLoadIntf2MesWin__RequestMesErase(beNDMWLoadIntf2MesWin *, int);

void beNDMWLoadIntf2MesWin__EndSystemMessage(beNDMWLoadIntf2MesWin *arg0) {
    arg0->_isSystemMes = 0;
    if (arg0->_isDisp == 1) {
        if (arg0->_isCtrl == 1) {
            switch (arg0->_kindCtrl) {
            case 0:
                FUN_003ecae0(arg0, arg0->_mesNo, arg0->_curPoint);
                return;
            case 1:
                FUN_003ecb00(arg0, arg0->_mesNo);
                return;
            }
        } else {
            FUN_003ecad0(arg0, arg0->_mesNo);
        }
    } else {
        beNDMWLoadIntf2MesWin__RequestMesErase(arg0, 1);
    }
}
}
