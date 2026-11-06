/* igAliasMemoryPool vtable slot 35: status leaf. Ignores the pool and writes the engine's failure-
 * status word (the word at 0x004fb418, set to 1 by the engine init) through the output-first
 * argument; same leaf as the 2d0690 entry of the accounting control block table in
 * docs/engine/alias-pool-binding.md and the concrete alias pool of docs/engine/alias-pool-
 * runtime.md. */
extern int g_allocatorFailureStatus[4];
void Gap__Core__igAliasMemoryPool__vfunc_35(int *statusOut) {
    *statusOut = g_allocatorFailureStatus[0];
}
