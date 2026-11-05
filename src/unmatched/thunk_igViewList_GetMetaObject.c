/* 0x0044bb50 — thunk_igViewList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igViewList_GetMetaObject();

void thunk_igViewList_GetMetaObject(void) {
    igViewList_GetMetaObject();
}
