/* igPageMemoryPool vtable slot 24: status leaf. Same leaf as igMallocMemoryPool slot 24. Ignores
 * the pool and writes the engine's failure-status word (the word at 0x004fb418, the one an
 * allocation failure publishes) through the output-first argument.md and docs/engine/array-
 * storage.md. */
extern int g_allocatorFailureStatus[4];
void Gap__Core__igPageMemoryPool__vfunc_24(int *statusOut) {
    *statusOut = g_allocatorFailureStatus[0];
}
