/* 0x002d09e0 — Gap__Core__igAliasMemoryPool__vfunc_49. m2c draft with the arithmetic re-typed to 64-bit (retail's
 * `ld`/`dsubu`), verified byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
long long Gap__Core__igAliasMemoryPool__vfunc_49(igAliasMemoryPool *arg0) {
    return arg0->_maxSize - arg0->_allocedBytes;
}
