#include "dw4/reflected.h"
long long Gap__Core__igPageMemoryPool__vfunc_49(igPageMemoryPool *arg0) {
    return arg0->_maxSize - arg0->_localNetAllocatedWithOverhead;
}
