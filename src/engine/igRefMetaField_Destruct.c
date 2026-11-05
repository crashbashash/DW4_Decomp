/* 0x00305cc0 — igRefMetaField adds no teardown of its own: its destructor jumps straight to the igMetaField base destructor.
 * Retail bytes are a lone `j 0x002fc210` (+ delay-slot nop); the callee takes the
 * caller's registers untouched, so the thunk has no arguments of its own. */
int igMetaField_Destruct();

void igRefMetaField_Destruct(void) {
    igMetaField_Destruct();
}
