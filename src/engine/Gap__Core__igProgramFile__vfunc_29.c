/* 0x003275a0 igProgramFile vtable slot 29: status leaf.  Ignores the object and writes the
 * engine's current failure-status word (the word at 0x004fb418, the one an
 * allocation failure publishes) through the output-first argument; the same
 * leaf as igPsx2Window slot 40 (docs/engine/allocator-registry.md,
 * docs/engine/array-storage.md). */
extern int g_failureStatusWord_004fb418[4];
void Gap__Core__igProgramFile__vfunc_29(int *status_out) {
    *status_out = g_failureStatusWord_004fb418[0];
}
