/* 0x002bbf50 — thunk_igRawRefArrayMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igRawRefArrayMetaField_GetMetaObject();

void thunk_igRawRefArrayMetaField_GetMetaObject(void) {
    igRawRefArrayMetaField_GetMetaObject();
}
