#include "dw4/reflected.h"
long long Gap__Core__igMallocMemoryPool__vfunc_49(igMallocMemoryPool *arg0) {
    return arg0->_maxSize - arg0->_localNetAllocatedWithOverhead;
}
