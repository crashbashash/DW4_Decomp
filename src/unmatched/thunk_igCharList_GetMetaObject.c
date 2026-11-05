/* 0x002cb000 — thunk_igCharList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCharList_GetMetaObject();

void thunk_igCharList_GetMetaObject(void) {
    igCharList_GetMetaObject();
}
