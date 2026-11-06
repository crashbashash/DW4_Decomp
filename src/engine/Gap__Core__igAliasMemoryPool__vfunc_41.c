/* Set the pool's size limit (`_maxSize`) and report success through the status word. Sibling
 * setters (vfunc_37 alignment, vfunc_39 element size) share the shape. */
#include "dw4/reflected.h"
/* Success status word, zero in the pristine ELF; the array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded[4];
void Gap__Core__igAliasMemoryPool__vfunc_41(int *status, igAliasMemoryPool *self, long long maxSize) {
    self->_maxSize = maxSize;
    *status = g_statusSucceeded[0];
}
