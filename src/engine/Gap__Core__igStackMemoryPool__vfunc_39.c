/* 0x00327740
 * Set the pool's element size (`_elementSize`, +128) and report success through
 * the status word. */
#include "dw4/reflected.h"
/* Success status word at 0x004fb410, zero in the pristine ELF (docs/engine/array-storage.md);
 * the array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded_004fb410[4];
void Gap__Core__igStackMemoryPool__vfunc_39(int *status, igStackMemoryPool *self, int elementSize) {
    self->_elementSize = elementSize;
    *status = g_statusSucceeded_004fb410[0];
}
