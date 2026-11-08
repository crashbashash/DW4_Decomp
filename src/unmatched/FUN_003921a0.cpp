#include "dw4/reflected.h"
extern "C" {
int strcmp(int, int);
int FUN_003921a0(beModelCtrlInfoRideOn *arg0, int arg1, int arg2);
}
int FUN_003921a0(beModelCtrlInfoRideOn *arg0, int arg1, int arg2) {
    if (strcmp(arg0->_modelName, arg1) != 0) return 0;
    if (arg2 == arg0->_modelRamNo) return 1;
    return 0;
}
