/* 0x00325fa0
 * Set the pool's size limit (`_maxSize`, +120) and report success through the
 * status word. */
#include "dw4/reflected.h"
/* Success status word at 0x004fb410, zero in the pristine ELF; the array form keeps the load
 * absolute (lui/lw). */
extern int g_statusSucceeded[4];
void Gap__Core__igPageMemoryPool__vfunc_41(int *status, igPageMemoryPool *self, long long maxSize) {
    self->_maxSize = maxSize;
    *status = g_statusSucceeded[0];
}
