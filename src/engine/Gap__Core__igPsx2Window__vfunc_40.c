/* 0x00149160 igPsx2Window vtable slot 40: status leaf.  Ignores the object and writes the
 * engine's current failure-status word (the word at 0x004fb418, the one an
 * allocation failure publishes) through the output-first argument; see
 * docs/engine/allocator-registry.md and docs/engine/array-storage.md. */
extern int g_failureStatusWord_004fb418[4];
void Gap__Core__igPsx2Window__vfunc_40(int *status_out) {
    *status_out = g_failureStatusWord_004fb418[0];
}
