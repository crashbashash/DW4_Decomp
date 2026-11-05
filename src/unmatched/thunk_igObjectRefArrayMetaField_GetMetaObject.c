/* 0x002bd500 — thunk_igObjectRefArrayMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igObjectRefArrayMetaField_GetMetaObject();

void thunk_igObjectRefArrayMetaField_GetMetaObject(void) {
    igObjectRefArrayMetaField_GetMetaObject();
}
