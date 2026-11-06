/* igProgramFile vtable slot 27: status leaf. Ignores the object and writes the engine's current
 * failure-status word (the one an allocation failure publishes) through the output-first argument;
 * the same leaf as igPsx2Window slot 40. */
extern int g_allocatorFailureStatus[4];
void Gap__Core__igProgramFile__vfunc_27(int *status_out) {
    *status_out = g_allocatorFailureStatus[0];
}
