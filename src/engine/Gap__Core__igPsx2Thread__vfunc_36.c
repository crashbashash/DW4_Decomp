/* 0x00330890: igPsx2Thread vtable slot 36, a plain getter that returns the reflected
 * field _arg (the raw argument handed to the thread function, include/dw4/reflected.h igPsx2Thread +28). */
#include "dw4/reflected.h"
int Gap__Core__igPsx2Thread__vfunc_36(igPsx2Thread *self) {
    return self->_arg;
}
