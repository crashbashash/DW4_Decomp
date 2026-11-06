#include "dw4/reflected.h"
long long Gap__Core__igArenaMemoryPool__vfunc_49(igArenaMemoryPool *arg0) {
    return arg0->_maxSize - arg0->_localNetAllocatedWithOverhead;
}
