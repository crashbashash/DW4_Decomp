/* 0x002c6220 — thunk_igEnumMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igEnumMetaField_GetMetaObject();

void thunk_igEnumMetaField_GetMetaObject(void) {
    igEnumMetaField_GetMetaObject();
}
