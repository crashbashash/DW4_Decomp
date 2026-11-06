/* src/engine/alias-pool-controls.c — Alias-pool accounting controls and fixed results
 *
 * One translation unit: 7 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
/* Allocator failure-status word at 0x004fb418: the value every allocator status leaf publishes.
 * Paired with the success word at 0x004fb410. */
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

/* 0x002d0620: slot 31, the same counter reset without touching _isActive. */
void Gap__Core__igAliasMemoryPool__vfunc_31(igAliasMemoryPool *self) {
    self->_allocedBytes = 0;
    self->_allocedBytesHigh = 0;
    self->_nAllocs = 0;
    self->_nFrees = 0;
    self->_netAllocsHigh = 0;
}

/* 0x002d0670: slot 33, report whether the pool is active. */
unsigned char Gap__Core__igAliasMemoryPool__vfunc_33(igAliasMemoryPool *self) {
    return self->_isActive;
}

/* 0x002d0680: slot 26, fixed result 0. */
int Gap__Core__igAliasMemoryPool__vfunc_26(void) {
    return 0;
}

/* 0x002d0690: slot 24, output the allocator failure-status word. */
void Gap__Core__igAliasMemoryPool__vfunc_24(int *outStatus) {
    *outStatus = g_allocatorFailureStatus[0];
}

/* 0x002d06a0: slot 25, fixed result 0. */
int Gap__Core__igAliasMemoryPool__vfunc_25(void) {
    return 0;
}

/* 0x002d06b0: slot 29, fixed result 0. */
int Gap__Core__igAliasMemoryPool__vfunc_29(void) {
    return 0;
}
