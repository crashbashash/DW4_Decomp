#include "dw4/reflected.h"
struct E { unsigned sz : 31; unsigned f : 1; };
long long Gap__Core__igStackMemoryPool__vfunc_47(igStackMemoryPool *arg0) {
    long long total = 0;
    struct E *e;
    int cur;
    if (arg0->_isActive == 0) {
        return 0;
    }
    cur = arg0->_stackPtr;
    e = (struct E *)arg0->_nextInt + 1;
    arg0 = (igStackMemoryPool *)arg0->_rawMemory;
    while (cur != (int)arg0) {
        unsigned long long t = e->sz;
        e++;
        total += t;
        cur -= t;
    }
    return total;
}
