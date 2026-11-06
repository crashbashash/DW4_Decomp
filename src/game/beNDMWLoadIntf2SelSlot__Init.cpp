#include "dw4/reflected.h"
extern "C" {
int FUN_003e0b80();

void beNDMWLoadIntf2SelSlot__Init(beNDMWLoadIntf2SelSlot *arg0) {
    int temp_a1;
    beNDMWLoadCtrl2CommonIntf *temp_s0;

    temp_s0 = (beNDMWLoadCtrl2CommonIntf *)arg0->_commonIntf;
    FUN_003e0b80();
    arg0->_selPoint = 0;
    temp_a1 = temp_s0->_kindHard;
    switch (temp_a1) {
    case 0:
        arg0->_selMax = 5;
        arg0->_kindHard = 0;
        return;
    case 1:
        arg0->_selMax = 2;
        arg0->_kindHard = 1;
        return;
    case 2:
        arg0->_selMax = 9;
        arg0->_kindHard = 2;
        break;
    }
}
}
