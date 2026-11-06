/* Setter for the pool's _alignment (a 16-bit field at +144). Like the other pool setters it
 * reports through a status word, always the "succeeded" one. */
#include "dw4/reflected.h"
/* Status word reported on success; array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded[4];
void Gap__Core__igMallocMemoryPool__vfunc_37(int *outStatus, igMallocMemoryPool *self, short alignment) {
    self->_alignment = alignment;
    *outStatus = g_statusSucceeded[0];
}
