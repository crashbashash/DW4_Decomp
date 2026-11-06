/* IgPsx2Window vtable slot 40: status leaf. Ignores the object and writes the engine's current
 * failure-status word (the one an allocation failure publishes) through the output-first argument. */
extern int g_allocatorFailureStatus[4];
void Gap__igPsx2Window__vfunc_40(int *status_out) {
    *status_out = g_allocatorFailureStatus[0];
}
