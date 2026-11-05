/* 0x00322710
 * Set the pool's size limit (`_maxSize`, +128) and report success through the
 * status word. */
#include "dw4/reflected.h"
/* Success status word at 0x004fb410, zero in the pristine ELF (docs/engine/array-storage.md);
 * the array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded_004fb410[4];
void Gap__Core__igMallocMemoryPool__vfunc_41(int *status, igMallocMemoryPool *self, long long maxSize) {
    self->_maxSize = maxSize;
    *status = g_statusSucceeded_004fb410[0];
}
