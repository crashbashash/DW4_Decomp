/* 0x002d0900
 * Set the pool's alignment (`_alignment`) and report success through the status
 * word. */
#include "dw4/reflected.h"
/* Success status word at 0x004fb410, zero in the pristine ELF (docs/engine/array-storage.md);
 * the array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded[4];
void Gap__Core__igAliasMemoryPool__vfunc_37(int *status, igAliasMemoryPool *self, short alignment) {
    self->_alignment = alignment;
    *status = g_statusSucceeded[0];
}
