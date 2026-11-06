#include "dw4/reflected.h"

/* Deactivates the pool: clears the reflected _isActive flag (igBoolMetaField, +112). */
void Gap__Core__igMallocMemoryPool__vfunc_32(igMallocMemoryPool *self) {
    self->_isActive = 0;
}
