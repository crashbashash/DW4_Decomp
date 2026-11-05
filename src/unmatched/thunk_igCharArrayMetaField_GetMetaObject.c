/* 0x002cc4b0 — thunk_igCharArrayMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCharArrayMetaField_GetMetaObject();

void thunk_igCharArrayMetaField_GetMetaObject(void) {
    igCharArrayMetaField_GetMetaObject();
}
