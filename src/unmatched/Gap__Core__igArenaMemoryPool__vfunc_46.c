/* 0x0031d320 — Gap__Core__igArenaMemoryPool__vfunc_46. m2c draft with the arithmetic re-typed to 64-bit (retail's
 * `ld`/`dsubu`), verified byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
long long Gap__Core__igArenaMemoryPool__vfunc_46(igArenaMemoryPool *arg0) {
    return arg0->_maxSize - arg0->_localNetAllocatedWithOverhead;
}
