#include "dw4/reflected.h"
void FUN_00392d20(beModelCtrlMoveObject *arg0, int arg1, float fparg0, float fparg1, float fparg2) {
    arg0->_mode = arg1;
    arg0->_value = fparg0;
    arg0->_acc = (float) (fparg0 / ((fparg1 * fparg1) / 2.0f));
    arg0->_endTime = fparg2;
    arg0->_isSeqStop = 0;
    switch (arg1) {
    case 4:
        arg0->_speed = fparg0;
        break;
    case 5:
        arg0->_speed = (float) -fparg0;
        break;
    }
    arg0->_isRun = 1;
}
