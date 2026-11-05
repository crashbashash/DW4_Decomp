/* 0x00139080 — j-thunk to the igColorAttr metadata accessor (finding #389: the class registrar passes this thunk, not the accessor itself, as its metaobject getter).
 * Retail bytes are a lone `j 0x00138f70` (+ delay-slot nop); the callee takes the
 * caller's registers untouched, so the thunk has no arguments of its own. */
int igColorAttr_GetMetaObject();

void thunk_igColorAttr_GetMetaObject(void) {
    igColorAttr_GetMetaObject();
}
