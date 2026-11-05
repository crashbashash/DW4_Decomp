/* 0x002f00d0 - the default allocator: asks the allocator registry for selector 2
 * through Memory_GetAllocatorBySelector (docs/engine/allocator-registry.md,
 * "Allocation dispatch").  Compiled as a tail call, so the selector load sits in
 * the jump's delay slot. */
int Memory_GetAllocatorBySelector();

void Memory_GetDefaultAllocator(void) {
    Memory_GetAllocatorBySelector(2);
}
