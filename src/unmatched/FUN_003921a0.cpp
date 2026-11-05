#include "dw4/reflected.h"
extern "C" {
int igStrCmp(int, int);
int FUN_003921a0(beModelCtrlInfoRideOn *arg0, int arg1, int arg2);
}
int FUN_003921a0(beModelCtrlInfoRideOn *arg0, int arg1, int arg2) {
    int r;
    if (igStrCmp(arg0->_modelName, arg1) != 0) {
        r = 0;
    } else {
        r = arg2 == arg0->_modelRamNo;
        asm { nop }
    }
    return r;
}
