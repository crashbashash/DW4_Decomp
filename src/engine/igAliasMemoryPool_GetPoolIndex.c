/* 0x002d11f0
 * The pool's index (reflected `_poolIndex`). */
#include "dw4/reflected.h"
int igAliasMemoryPool_GetPoolIndex(igAliasMemoryPool *self) {
    return self->_poolIndex;
}
