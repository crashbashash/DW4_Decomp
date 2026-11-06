#include "dw4/reflected.h"
/* Allocator failure-status word: the value every allocator status leaf publishes. Paired with the
 * success word. */
extern int g_allocatorFailureStatus[4];

/* slot 30, reset the allocation counters and mark the pool active. */
void Gap__Core__igAliasMemoryPool__vfunc_30(igAliasMemoryPool *self) {
    self->_allocedBytes = 0;
    self->_allocedBytesHigh = 0;
    self->_nAllocs = 0;
    self->_nFrees = 0;
    self->_netAllocsHigh = 0;
    self->_isActive = 1;
}

/* Slot 31, the same counter reset without touching _isActive. */
void Gap__Core__igAliasMemoryPool__vfunc_31(igAliasMemoryPool *self) {
    self->_allocedBytes = 0;
    self->_allocedBytesHigh = 0;
    self->_nAllocs = 0;
    self->_nFrees = 0;
    self->_netAllocsHigh = 0;
}

/* Slot 33, report whether the pool is active. */
unsigned char Gap__Core__igAliasMemoryPool__vfunc_33(igAliasMemoryPool *self) {
    return self->_isActive;
}

/* Slot 26, fixed result 0. */
int Gap__Core__igAliasMemoryPool__vfunc_26(void) {
    return 0;
}

/* Slot 24, output the allocator failure-status word. */
void Gap__Core__igAliasMemoryPool__vfunc_24(int *outStatus) {
    *outStatus = g_allocatorFailureStatus[0];
}

/* Slot 25, fixed result 0. */
int Gap__Core__igAliasMemoryPool__vfunc_25(void) {
    return 0;
}

/* Slot 29, fixed result 0. */
int Gap__Core__igAliasMemoryPool__vfunc_29(void) {
    return 0;
}
