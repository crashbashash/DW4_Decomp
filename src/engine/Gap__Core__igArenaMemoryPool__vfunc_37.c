/* Setter for the pool's _alignment (a 16-bit field at +172 in include/dw4/reflected.h). It reports
 * through a status word, always the "succeeded" one (docs/engine/array-storage.md: the word at
 * 0x004fb410). */
#include "dw4/reflected.h"
/* Status word reported on success; array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded[4];
void Gap__Core__igArenaMemoryPool__vfunc_37(int *outStatus, igArenaMemoryPool *self, short alignment) {
    self->_alignment = alignment;
    *outStatus = g_statusSucceeded[0];
}
