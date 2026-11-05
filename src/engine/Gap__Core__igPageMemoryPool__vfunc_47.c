#include "dw4/reflected.h"

/* 0x00326020
 * Slot 47 getter: returns the pool's _localNetAllocated field (bytes currently allocated from this pool). */
long long Gap__Core__igPageMemoryPool__vfunc_47(igPageMemoryPool *self) {
    return self->_localNetAllocated;
}
