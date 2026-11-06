/* J-thunk to the igTimeAttr metadata accessor (the class registrar passes this thunk, not the
 * accessor itself, as its metaobject getter). The callee takes the caller's registers untouched,
 * so the thunk has no arguments of its own. */
int igTimeAttr_GetMetaObject();

void thunk_igTimeAttr_GetMetaObject(void) {
    igTimeAttr_GetMetaObject();
}
