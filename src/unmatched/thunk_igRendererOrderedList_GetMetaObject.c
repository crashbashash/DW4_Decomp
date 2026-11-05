/* 0x0044c700 — thunk_igRendererOrderedList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igRendererOrderedList_GetMetaObject();

void thunk_igRendererOrderedList_GetMetaObject(void) {
    igRendererOrderedList_GetMetaObject();
}
