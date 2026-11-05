/* 0x0032af40 — j-thunk for igCallStackTracer virtual slot 25 (RTTI vtable name), forwarding to the slot body at 0x002d4350.
 * Retail bytes are a lone `j 0x002d4350` (+ delay-slot nop); the callee takes the
 * caller's registers untouched, so the thunk has no arguments of its own. */
int Gap__Core__igCallStackTracer__vfunc_25();

void thunk_Gap__Core__igCallStackTracer__vfunc_25(void) {
    Gap__Core__igCallStackTracer__vfunc_25();
}
