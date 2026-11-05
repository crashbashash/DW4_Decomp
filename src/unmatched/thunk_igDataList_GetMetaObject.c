/* 0x002c85f0 — thunk_igDataList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igDataList_GetMetaObject();

void thunk_igDataList_GetMetaObject(void) {
    igDataList_GetMetaObject();
}
