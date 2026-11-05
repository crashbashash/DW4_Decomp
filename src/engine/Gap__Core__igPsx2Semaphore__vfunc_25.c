/* 0x003309c0: igPsx2Semaphore vtable slot 25, tells whether the semaphore has been created.
 * _semaID (include/dw4/reflected.h igPsx2Semaphore +12) holds the kernel semaphore id; -1 is
 * the "no semaphore yet" value (hypothesis: the PS2 kernel's CreateSema failure value). */
#include "dw4/reflected.h"
int Gap__Core__igPsx2Semaphore__vfunc_25(igPsx2Semaphore *self) {
    return self->_semaID != -1;
}
