#include "dw4/reflected.h"

/* 0x00330da0
 * Slot 35 getter: returns the pool's _resetTime field (the reflected igLongMetaField). */
long long Gap__Core__igPsx2LongTimer__vfunc_35(igPsx2LongTimer *self) {
    return self->_resetTime;
}
