#include "dw4/reflected.h"
long long Gap__Core__igArenaMemoryPool__vfunc_36(igArenaMemoryPool *arg0) {
    long long temp_v0;

    temp_v0 = arg0->_size;
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return arg0->_systemAllocated;
}
