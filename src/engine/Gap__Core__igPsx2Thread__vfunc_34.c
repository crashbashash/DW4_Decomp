/* 0x00330880: igPsx2Thread vtable slot 34, a plain getter that returns the reflected
 * field _function (the raw thread entry-function pointer, include/dw4/reflected.h igPsx2Thread +40). */
#include "dw4/reflected.h"
int Gap__Core__igPsx2Thread__vfunc_34(igPsx2Thread *self) {
    return self->_function;
}
