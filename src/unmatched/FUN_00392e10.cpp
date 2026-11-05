#include "dw4/reflected.h"
extern "C" {
int FUN_00392d90(void *);
float FUN_00392e10(beModelCtrlMoveObject *arg0, float arg1);
}
float FUN_00392e10(beModelCtrlMoveObject *arg0, float arg1) {
    float f1, f2, f0;
    if (arg0->_isRun == 0) { return 0.0f; }
    f1 = arg0->_endTime;
    if (f1 != 0.0f) {
        f1 = f1 - arg1;
        if (f1 < 0.0f) {
            FUN_00392d90(arg0);
            if (arg0->_isRun == 0) { return 0.0f; }
        } else {
            arg0->_endTime = f1;
        }
    }
    if (!(arg1 <= 3.0f)) { arg1 = 3.0f; }
    f1 = arg0->_speed;
    f2 = arg1 * arg0->_acc;
    switch (arg0->_mode) {
    case 2:
    case 4:
        f1 = f1 - f2;
        if (f1 < 0.0f) { arg0->_isRun = 0; f1 = 0.0f; arg0->_speed = 0.0f; }
        break;
    case 3:
    case 5:
        f1 = f1 + f2;
        if (!(f1 <= 0.0f)) { arg0->_isRun = 0; f1 = 0.0f; arg0->_speed = 0.0f; }
        break;
    case 0:
        f0 = arg0->_value;
        f1 = f1 + f2;
        if (!(f1 <= f0)) { f1 = f0; }
        break;
    case 1:
        f1 = f1 - f2;
        f0 = -arg0->_value;
        if (f1 < f0) { f1 = f0; }
        break;
    }
    arg0->_speed = f1;
    return f1 * arg1;
}
