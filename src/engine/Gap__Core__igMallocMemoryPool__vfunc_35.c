/* 0x003226e0 — Gap::Core::igMallocMemoryPool::vfunc_35: setter for the pool's 64-bit _size
 * (+136 in include/dw4/reflected.h).  It reports through a status word, always the
 * "succeeded" one (docs/engine/array-storage.md: the word at 0x004fb410). */
#include "dw4/reflected.h"
/* Status word reported on success; array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded[4];
void Gap__Core__igMallocMemoryPool__vfunc_35(int *outStatus, igMallocMemoryPool *self, long long size) {
    self->_size = size;
    *outStatus = g_statusSucceeded[0];
}
