#include "dw4/reflected.h"
long long Gap__Core__igStackMemoryPool__vfunc_46(igStackMemoryPool *arg0) {
    long long r = (long long)arg0->_nextInt - (long long)arg0->_stackPtr;
    if (r > 0) return r;
    return 0;
}
