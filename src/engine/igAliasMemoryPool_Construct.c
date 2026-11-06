/* igAliasMemoryPool constructor. Runs the base-class constructor, publishes the pool's vtable and
 * clears the lock, event-tracker and aliased-pool references (offsets 116, 152, 180), then calls
 * igAliasMemoryPool_Initialize on a non-null receiver and returns it. */
#include "dw4/reflected.h"
int igAliasMemoryPool_Initialize();
int FUN_002effb0();  /* Base-pool constructor: igObject header init, then the base vtable. */
/* Vtable image of igAliasMemoryPool; the array form keeps the address load absolute. */
extern int g_igAliasMemoryPool_vtable[4];
void *igAliasMemoryPool_Construct(igAliasMemoryPool *self) {
    FUN_002effb0();
    self->_vtable = (int)(&g_igAliasMemoryPool_vtable[0]);
    self->_allocationLock = 0;
    self->_eventTracker = 0;
    self->_aliasedMemoryPool = 0;
    if (self != 0) {
        igAliasMemoryPool_Initialize(self);
    }
    return self;
}
