/* 0x00330960: igPsx2Thread vtable slot 38, a plain getter that returns the reflected
 * field _stack (the raw stack pointer, include/dw4/reflected.h igPsx2Thread +32). */
#include "dw4/reflected.h"
int Gap__Core__igPsx2Thread__vfunc_38(igPsx2Thread *self) {
    return self->_stack;
}
