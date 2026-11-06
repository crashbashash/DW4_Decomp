/* 0x00330f90 igStackMemoryPool vtable slot 41: status leaf.  Ignores the object and writes the
 * engine's current failure-status word (the word at 0x004fb418, the one an
 * allocation failure publishes) through the output-first argument; see
 * docs/engine/allocator-registry.md and docs/engine/array-storage.md. */
extern int g_allocatorFailureStatus[4];
void Gap__Core__igStackMemoryPool__vfunc_41(int *status_out) {
    *status_out = g_allocatorFailureStatus[0];
}
