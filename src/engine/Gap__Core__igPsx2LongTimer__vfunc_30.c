/* Reset the timer. Marks it stopped and loads the accumulated `_additionalTime` from `_resetTime`
 * (vfunc_33 sets `_resetTime`, vfunc_35 reads it back, vfunc_36 reads `_isStopped`). */
#include "dw4/reflected.h"
void Gap__Core__igPsx2LongTimer__vfunc_30(igPsx2LongTimer *self) {
    self->_isStopped = 1;
    self->_additionalTime = (long long) self->_resetTime;
}
