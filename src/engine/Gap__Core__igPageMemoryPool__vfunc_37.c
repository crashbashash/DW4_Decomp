/* IgPageMemoryPool vtable slot 37: status leaf. On igMallocMemoryPool this slot sets _alignment;
 * the page pool has no such field. Ignores the pool and writes the engine's failure-status word
 * (the one an allocation failure publishes) through the output-first argument. */
extern int g_allocatorFailureStatus[4];
void Gap__Core__igPageMemoryPool__vfunc_37(int *statusOut) {
    *statusOut = g_allocatorFailureStatus[0];
}
