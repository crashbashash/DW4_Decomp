/* IgPageMemoryPool vtable slot 24: status leaf. Same leaf as igMallocMemoryPool slot 24. Ignores
 * the pool and writes the engine's failure-status word (the one an allocation failure publishes)
 * through the output-first argument. */
extern int g_allocatorFailureStatus[4];
void Gap__Core__igPageMemoryPool__vfunc_24(int *statusOut) {
    *statusOut = g_allocatorFailureStatus[0];
}
