#include "dw4/reflected.h"

/* Slot 35 getter: returns the timer's _resetTime field (the reflected igLongMetaField). */
long long Gap__Core__igPsx2LongTimer__vfunc_35(igPsx2LongTimer *self) {
    return self->_resetTime;
}
