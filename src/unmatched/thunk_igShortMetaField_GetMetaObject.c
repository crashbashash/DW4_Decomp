/* 0x002ba200 — thunk_igShortMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igShortMetaField_GetMetaObject();

void thunk_igShortMetaField_GetMetaObject(void) {
    igShortMetaField_GetMetaObject();
}
