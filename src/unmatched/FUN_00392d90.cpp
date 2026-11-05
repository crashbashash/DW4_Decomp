#include "dw4/reflected.h"
extern "C" {
void FUN_00392d20(beModelCtrlMoveObject *, int, float, float, float);
void FUN_00392d90(beModelCtrlMoveObject *s);
}
void FUN_00392d90(beModelCtrlMoveObject *s) {
    float z = 0.0f;
    s->_endTime = z;
    if (s->_mode == 0) { FUN_00392d20(s, 2, s->_stopValue, s->_stopFrame, z); } else if (s->_mode == 1) { FUN_00392d20(s, 3, s->_stopValue, s->_stopFrame, z); } else { s->_isRun = 0; s->_speed = z; }
    s->_isSeqStop = 0;
}
