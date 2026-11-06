/* 0x002d0930 — igAliasMemoryPool setter for `_elementSize` (+172).
 * Stores the new element size and reports success through the out cell
 * (docs/engine/alias-pool-runtime.md; the cell receives the
 * shared success status word, see g_statusSucceeded). */
#include "dw4/reflected.h"
extern int g_statusSucceeded[4];
void Gap__Core__igAliasMemoryPool__vfunc_39(int *status_out, igAliasMemoryPool *self, int element_size) {
    self->_elementSize = element_size;
    *status_out = g_statusSucceeded[0];
}
