/* 0x00330e50 -- Gap::Core::igPsx2LongTimer::vfunc_36.
 * Reports whether the timer is stopped: returns _isStopped (+32).  Field name and offset come from the reflected igPsx2LongTimer record
 * (include/dw4/reflected.h). */
#include "dw4/reflected.h"
unsigned char Gap__Core__igPsx2LongTimer__vfunc_36(igPsx2LongTimer *self) {
    return self->_isStopped;
}
