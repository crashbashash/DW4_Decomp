/* 0x002c92d0 — thunk_igPointerList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igPointerList_GetMetaObject();

void thunk_igPointerList_GetMetaObject(void) {
    igPointerList_GetMetaObject();
}
