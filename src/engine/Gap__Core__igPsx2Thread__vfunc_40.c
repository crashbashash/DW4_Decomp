/* 0x00330970: igPsx2Thread vtable slot 40, a plain getter that returns the reflected
 * field _stackSize (the stack size in bytes, include/dw4/reflected.h igPsx2Thread +36). */
#include "dw4/reflected.h"
int Gap__Core__igPsx2Thread__vfunc_40(igPsx2Thread *self) {
    return self->_stackSize;
}
