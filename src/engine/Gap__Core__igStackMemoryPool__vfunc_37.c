/* 0x00327710
 * Set the pool's alignment (`_alignment`, +112) and report success through the
 * status word.  vfunc_38 is the matching getter. */
#include "dw4/reflected.h"
/* Success status word at 0x004fb410, zero in the pristine ELF; the array form keeps the load
 * absolute (lui/lw). */
extern int g_statusSucceeded[4];
void Gap__Core__igStackMemoryPool__vfunc_37(int *status, igStackMemoryPool *self, short alignment) {
    self->_alignment = alignment;
    *status = g_statusSucceeded[0];
}
