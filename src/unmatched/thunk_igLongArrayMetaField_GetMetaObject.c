/* 0x002c1e20 — thunk_igLongArrayMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLongArrayMetaField_GetMetaObject();

void thunk_igLongArrayMetaField_GetMetaObject(void) {
    igLongArrayMetaField_GetMetaObject();
}
