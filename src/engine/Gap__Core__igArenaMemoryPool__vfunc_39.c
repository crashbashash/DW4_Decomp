/* 0x0031d2f0 — Gap::Core::igArenaMemoryPool::vfunc_39: setter for the pool's _elementSize
 * (+144 in include/dw4/reflected.h).  It reports through a status word, always the
 * "succeeded" one (docs/engine/array-storage.md: the word at 0x004fb410). */
#include "dw4/reflected.h"
/* Status word reported on success; array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded[4];
void Gap__Core__igArenaMemoryPool__vfunc_39(int *outStatus, igArenaMemoryPool *self, int elementSize) {
    self->_elementSize = elementSize;
    *outStatus = g_statusSucceeded[0];
}
