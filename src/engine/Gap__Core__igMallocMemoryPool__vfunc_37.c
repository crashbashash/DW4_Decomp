/* 0x00322740 — Gap::Core::igMallocMemoryPool::vfunc_37: setter for the pool's _alignment
 * (a 16-bit field at +144 in include/dw4/reflected.h).  Like the other igPsx2/pool
 * setters it reports through a status word, always the "succeeded" one
 * (docs/engine/array-storage.md: the word at 0x004fb410). */
#include "dw4/reflected.h"
/* Status word reported on success; array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded_004fb410[4];
void Gap__Core__igMallocMemoryPool__vfunc_37(int *outStatus, igMallocMemoryPool *self, short alignment) {
    self->_alignment = alignment;
    *outStatus = g_statusSucceeded_004fb410[0];
}
