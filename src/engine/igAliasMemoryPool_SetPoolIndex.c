/* 0x002d1200 — igAliasMemoryPool_SetPoolIndex: setter for the `_poolIndex` field. */
#include "dw4/reflected.h"
void igAliasMemoryPool_SetPoolIndex(igAliasMemoryPool *self, int poolIndex) {
    self->_poolIndex = poolIndex;
}
