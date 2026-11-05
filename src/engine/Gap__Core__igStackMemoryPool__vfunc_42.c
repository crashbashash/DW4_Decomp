/* 0x003277c0 - igStackMemoryPool vtable slot 42: getter for the reflected
 * _totalSize (+120, igUnsignedLongMetaField).  Returned as a 64-bit value
 * (the load is `ld`), like igArenaMemoryPool slot 42 for its _maxSize. */
#include "dw4/reflected.h"
long long Gap__Core__igStackMemoryPool__vfunc_42(igStackMemoryPool *self) {
    return self->_totalSize;
}
