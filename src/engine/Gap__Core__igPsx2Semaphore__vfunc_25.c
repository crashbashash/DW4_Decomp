/* IgPsx2Semaphore vtable slot 25, tells whether the semaphore has been created. _semaID (+12)
 * holds the kernel semaphore id; -1 is the "no semaphore yet" value. */
#include "dw4/reflected.h"
int Gap__Core__igPsx2Semaphore__vfunc_25(igPsx2Semaphore *self) {
    return self->_semaID != -1;
}
