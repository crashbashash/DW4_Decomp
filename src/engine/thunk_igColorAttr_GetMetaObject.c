/* J-thunk to the igColorAttr metadata accessor (the class registrar passes this thunk, not the
 * accessor itself, as its metaobject getter). The callee takes the caller's registers untouched,
 * so the thunk has no arguments of its own. */
int igColorAttr_GetMetaObject();

void thunk_igColorAttr_GetMetaObject(void) {
    igColorAttr_GetMetaObject();
}
