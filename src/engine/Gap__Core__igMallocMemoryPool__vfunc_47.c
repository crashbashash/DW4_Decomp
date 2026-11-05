#include "dw4/reflected.h"

/* 0x003227b0
 * Slot 47 getter: returns the pool's _localNetAllocated field (bytes currently allocated from this pool). */
long long Gap__Core__igMallocMemoryPool__vfunc_47(igMallocMemoryPool *self) {
    return self->_localNetAllocated;
}
