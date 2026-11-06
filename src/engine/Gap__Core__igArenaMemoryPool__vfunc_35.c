/* igArenaMemoryPool vtable slot 35: status leaf. Ignores the pool and writes the engine's failure-
 * status word (the word at 0x004fb418, set to 1 by the engine init) through the output-first
 * argument; same leaf as FUN_002f0620 and igMallocMemoryPool slot 24. */
extern int g_allocatorFailureStatus[4];
void Gap__Core__igArenaMemoryPool__vfunc_35(int *statusOut) {
    *statusOut = g_allocatorFailureStatus[0];
}
