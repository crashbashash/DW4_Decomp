/* 0x00149ff0 — thunk_igVisualContextList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igVisualContextList_GetMetaObject();

void thunk_igVisualContextList_GetMetaObject(void) {
    igVisualContextList_GetMetaObject();
}
