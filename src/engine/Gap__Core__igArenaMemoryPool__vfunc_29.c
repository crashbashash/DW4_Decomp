/* 0x0031cf90
 * igMemoryPool slot 29 (vtable +116): constant 0 for the arena pool.  This is the
 * predicate igAllocator_EncodeIndex (0x002f0670) calls on an allocator: zero selects
 * the primary allocator list (even encoded index), nonzero the secondary list
 * (docs/engine/allocator-registry.md, asm/igAllocator_EncodeIndex.s `lw t9,116(t9)`).
 * igMallocMemoryPool also returns 0; igPageMemoryPool and igStackMemoryPool return 1.
 * The receiver is not read. */
int Gap__Core__igArenaMemoryPool__vfunc_29(void) {
    return 0;
}
