#include "dw4/reflected.h"
extern "C" {
int strcmp(int, int);
int FUN_003921a0(beModelCtrlInfoRideOn *arg0, int arg1, int arg2);
}
int FUN_003921a0(beModelCtrlInfoRideOn *arg0, int arg1, int arg2) {
    int r;
    if (strcmp(arg0->_modelName, arg1) != 0) return 0;
    r = arg2 == arg0->_modelRamNo;
    /* matching construct: hand search — the branch folds away, leaving its delay slot */
    if (r) return r;
    return r;
}
