/* 0x0032ed90: igPsx2Semaphore vtable slot 29, a plain getter that returns the reflected
 * field _maxCount (the maximum count the semaphore was created with, include/dw4/reflected.h igPsx2Semaphore +20). */
#include "dw4/reflected.h"
int Gap__Core__igPsx2Semaphore__vfunc_29(igPsx2Semaphore *self) {
    return self->_maxCount;
}
