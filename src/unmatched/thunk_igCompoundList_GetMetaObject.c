/* 0x00225980 — thunk_igCompoundList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCompoundList_GetMetaObject();

void thunk_igCompoundList_GetMetaObject(void) {
    igCompoundList_GetMetaObject();
}
