/* 0x00325f80 igPageMemoryPool vtable slot 35: status leaf.  On igMallocMemoryPool this slot sets _size; the page pool has no such field.
 * Ignores the pool and writes the engine's failure-status word (the word at 0x004fb418,
 * the one an allocation failure publishes) through the output-first argument; see
 * docs/engine/allocator-registry.md and docs/engine/array-storage.md. */
extern int g_failureStatusWord_004fb418[4];
void Gap__Core__igPageMemoryPool__vfunc_35(int *statusOut) {
    *statusOut = g_failureStatusWord_004fb418[0];
}
