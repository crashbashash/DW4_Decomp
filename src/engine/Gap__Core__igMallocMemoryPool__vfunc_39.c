/* Set the pool's element size (`_elementSize`, +124) and report success through the status word. */
#include "dw4/reflected.h"
/* Success status word, zero in the pristine ELF; the array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded[4];
void Gap__Core__igMallocMemoryPool__vfunc_39(int *status, igMallocMemoryPool *self, int elementSize) {
    self->_elementSize = elementSize;
    *status = g_statusSucceeded[0];
}
