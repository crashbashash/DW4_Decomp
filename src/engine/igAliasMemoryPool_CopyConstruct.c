/* 0x002d1590 — igAliasMemoryPool_CopyConstruct
 * Copy-construct counterpart of igAliasMemoryPool_Initialize: runs the base-pool
 * copy-construct step (igMemoryPool_CopyConstruct: igObject_CopyConstructHeader, then the 0x0052f620
 * base vtable), publishes the igAliasMemoryPool vtable 0x005313a0 and clears the
 * allocation lock, event tracker and aliased-pool references
 * (docs/engine/allocator-builder.md, alias pool backend trace).  Returns `self`. */
#include "dw4/reflected.h"
int igMemoryPool_CopyConstruct();
/* Vtable image of igAliasMemoryPool; the array form keeps the address load absolute. */
extern int g_igAliasMemoryPool_vtable[4];
void *igAliasMemoryPool_CopyConstruct(igAliasMemoryPool *self) {
    igMemoryPool_CopyConstruct();
    self->_vtable = (int)(&g_igAliasMemoryPool_vtable[0]);
    self->_allocationLock = 0;
    self->_eventTracker = 0;
    self->_aliasedMemoryPool = 0;
    return self;
}
