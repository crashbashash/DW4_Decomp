/* 0x00327890 — Gap__Core__igStackMemoryPool__vfunc_49. m2c draft with the arithmetic re-typed to 64-bit (retail's
 * `ld`/`dsubu`), verified byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
long long Gap__Core__igStackMemoryPool__vfunc_49(igStackMemoryPool *arg0) {
    long long r = (long long)arg0->_nextInt - (long long)arg0->_stackPtr;
    if (r > 0) return r;
    return 0;
}
