#include "dw4/reflected.h"

/* 0x0031d330
 * Accessor: the arena's reflected _localNetAllocated statistic (igLongMetaField, +24). */
long long Gap__Core__igArenaMemoryPool__vfunc_47(igArenaMemoryPool *self) {
    return self->_localNetAllocated;
}
