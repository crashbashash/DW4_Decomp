#include "dw4/reflected.h"

/* 0x00325fc0
 * Slot 42 getter: returns the pool's _maxSize field (same field as slot 36). */
long long Gap__Core__igPageMemoryPool__vfunc_42(igPageMemoryPool *self) {
    return self->_maxSize;
}
