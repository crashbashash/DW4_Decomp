/* Stub that stores the engine's failure result code through `result`. The global holds 1 (set in
 * the engine init); Gap__Core__igPsx2Thread__vfunc_27 stores it when WakeupThread() fails and the sibling success word
 * (0) on success. */
extern int g_allocatorFailureStatus[4];
void Gap__Core__igPsx2Thread__vfunc_52(int *result) {
    *result = g_allocatorFailureStatus[0];
}
