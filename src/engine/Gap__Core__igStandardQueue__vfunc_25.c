#include "dw4/reflected.h"

/* 0x003286d0
 * Predicate: true once the queue's element storage (`_data`, igMemoryRefMetaField, +36) has been allocated. */
int Gap__Core__igStandardQueue__vfunc_25(igStandardQueue *self) {
    return self->_data != 0;
}
