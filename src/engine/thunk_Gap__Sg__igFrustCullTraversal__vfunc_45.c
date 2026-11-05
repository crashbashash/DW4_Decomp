/* 0x001e0830 — j-thunk for igFrustCullTraversal virtual slot 45 (RTTI vtable name), forwarding to the slot body at 0x001c1c50.
 * Retail bytes are a lone `j 0x001c1c50` (+ delay-slot nop); the callee takes the
 * caller's registers untouched, so the thunk has no arguments of its own. */
int Gap__Sg__igFrustCullTraversal__vfunc_45();

void thunk_Gap__Sg__igFrustCullTraversal__vfunc_45(void) {
    Gap__Sg__igFrustCullTraversal__vfunc_45();
}
