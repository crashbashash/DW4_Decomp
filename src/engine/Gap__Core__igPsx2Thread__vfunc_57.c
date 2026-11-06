/* Stop check: when a stop has been requested (`_stopRequested`), call FUN_00330440 with result 0.
 * FUN_00330440 stores its second argument in `_result` (+0x34) and passes the thread to a global
 * object, i.e. it ends the thread with that result. The sibling FUN_003303f0 does the same test
 * and then also sets `_atStoppingPoint`. */
#include "dw4/reflected.h"
int FUN_00330440();

void Gap__Core__igPsx2Thread__vfunc_57(igPsx2Thread *self) {
    if (self->_stopRequested != 0) {
        FUN_00330440(self, 0);
    }
}
