/* igStackMemoryPool vtable slot 34: status leaf. Ignores the object and writes the engine's
 * current failure-status word (the word at 0x004fb418, the one an allocation failure publishes)
 * through the output-first argument.md and docs/engine/array-storage.md. */
extern int g_allocatorFailureStatus[4];
void Gap__Core__igStackMemoryPool__vfunc_34(int *status_out) {
    *status_out = g_allocatorFailureStatus[0];
}
