/* 0x002c6570 — thunk_igEnumArrayMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igEnumArrayMetaField_GetMetaObject();

void thunk_igEnumArrayMetaField_GetMetaObject(void) {
    igEnumArrayMetaField_GetMetaObject();
}
