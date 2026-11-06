/* Set the pool's size limit (`_maxSize`, +128) and report success through the status word. */
#include "dw4/reflected.h"
/* Success status word, zero in the pristine ELF; the array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded[4];
void Gap__Core__igMallocMemoryPool__vfunc_41(int *status, igMallocMemoryPool *self, long long maxSize) {
    self->_maxSize = maxSize;
    *status = g_statusSucceeded[0];
}
