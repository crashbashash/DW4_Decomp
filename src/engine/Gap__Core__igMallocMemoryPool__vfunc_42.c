#include "dw4/reflected.h"

/* 0x00322730
 * Accessor: the pool's reflected _maxSize field (igUnsignedLongMetaField, +128). */
long long Gap__Core__igMallocMemoryPool__vfunc_42(igMallocMemoryPool *self) {
    return self->_maxSize;
}
