/* 0x002c6fd0 — thunk_igDoubleArrayMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igDoubleArrayMetaField_GetMetaObject();

void thunk_igDoubleArrayMetaField_GetMetaObject(void) {
    igDoubleArrayMetaField_GetMetaObject();
}
