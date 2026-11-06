/* IgStackMemoryPool vtable slot 35: status leaf. Ignores the object and writes the engine's
 * current failure-status word (the one an allocation failure publishes) through the output-first
 * argument. */
extern int g_allocatorFailureStatus[4];
void Gap__Core__igStackMemoryPool__vfunc_35(int *status_out) {
    *status_out = g_allocatorFailureStatus[0];
}
