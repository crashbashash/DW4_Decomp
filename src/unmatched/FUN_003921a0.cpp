#include "dw4/reflected.h"
extern "C" {
int strcmp(int, int);
int FUN_003921a0(beModelCtrlInfoRideOn *arg0, int arg1, int arg2);
}
int FUN_003921a0(beModelCtrlInfoRideOn *arg0, int arg1, int arg2) {
    int r;
    if (strcmp(arg0->_modelName, arg1) != 0) {
        r = 0;
    } else {
        r = arg2 == arg0->_modelRamNo;
        asm { nop }
    }
    return r;
}
