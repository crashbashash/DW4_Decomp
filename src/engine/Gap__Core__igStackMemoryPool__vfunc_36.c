#include "dw4/reflected.h"

/* Slot 36 getter: returns the pool's _totalSize field (an int widened to 64 bits). */
long long Gap__Core__igStackMemoryPool__vfunc_36(igStackMemoryPool *self) {
    return self->_totalSize;
}
