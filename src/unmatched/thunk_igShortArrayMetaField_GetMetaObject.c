/* 0x002ba4d0 — thunk_igShortArrayMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igShortArrayMetaField_GetMetaObject();

void thunk_igShortArrayMetaField_GetMetaObject(void) {
    igShortArrayMetaField_GetMetaObject();
}
