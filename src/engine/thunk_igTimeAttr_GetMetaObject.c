/* 0x001310c0 — j-thunk to the igTimeAttr metadata accessor (the class registrar passes this thunk, not the accessor itself, as its metaobject getter).
 * Retail bytes are a lone `j 0x00130fb0` (+ delay-slot nop); the callee takes the
 * caller's registers untouched, so the thunk has no arguments of its own. */
int igTimeAttr_GetMetaObject();

void thunk_igTimeAttr_GetMetaObject(void) {
    igTimeAttr_GetMetaObject();
}
