/* igMallocMemoryPool vtable slot 24: status leaf. Ignores the pool and writes the engine's
 * failure-status word (the word at 0x004fb418, the one an allocation failure publishes) through
 * the output-first argument; same leaf as FUN_002f0620 and igPsx2Window slot 40. */
extern int g_allocatorFailureStatus[4];
void Gap__Core__igMallocMemoryPool__vfunc_24(int *statusOut) {
    *statusOut = g_allocatorFailureStatus[0];
}
