#include "dw4/reflected.h"

/* 0x003227c0
 * Slot 48 getter: returns the pool's _localNetAllocatedWithOverhead field (bytes currently allocated from this pool, overhead included). */
long long Gap__Core__igMallocMemoryPool__vfunc_48(igMallocMemoryPool *self) {
    return self->_localNetAllocatedWithOverhead;
}
