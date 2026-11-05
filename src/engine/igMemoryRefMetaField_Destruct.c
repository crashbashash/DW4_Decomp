/* 0x002fba20 — igMemoryRefMetaField adds no teardown of its own: its destructor jumps straight to the igRefMetaField destructor.
 * Retail bytes are a lone `j 0x00305cc0` (+ delay-slot nop); the callee takes the
 * caller's registers untouched, so the thunk has no arguments of its own. */
int igRefMetaField_Destruct();

void igMemoryRefMetaField_Destruct(void) {
    igRefMetaField_Destruct();
}
