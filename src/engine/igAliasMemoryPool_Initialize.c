/* Initialization helper of the alias pool: runs the base-pool initialization
 * (igMemoryPool_Initialize: igObject_InitHeader, then the base vtable), publishes the
 * igAliasMemoryPool vtable and clears the allocation lock, event tracker and aliased-pool
 * references (offsets 116, 152 and 180). Returns `self`. */
#include "dw4/reflected.h"
int igMemoryPool_Initialize();
/* Vtable image of igAliasMemoryPool; the array form keeps the address load absolute. */
extern int g_igAliasMemoryPool_vtable[4];
void *igAliasMemoryPool_Initialize(igAliasMemoryPool *self) {
    igMemoryPool_Initialize();
    self->_vtable = (int)(&g_igAliasMemoryPool_vtable[0]);
    self->_allocationLock = 0;
    self->_eventTracker = 0;
    self->_aliasedMemoryPool = 0;
    return self;
}
