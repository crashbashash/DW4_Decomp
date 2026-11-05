/* 0x002ccff0 — thunk_igBoolArrayMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igBoolArrayMetaField_GetMetaObject();

void thunk_igBoolArrayMetaField_GetMetaObject(void) {
    igBoolArrayMetaField_GetMetaObject();
}
