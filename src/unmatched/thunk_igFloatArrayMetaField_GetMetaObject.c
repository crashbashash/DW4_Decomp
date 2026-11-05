/* 0x002c4a60 — thunk_igFloatArrayMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igFloatArrayMetaField_GetMetaObject();

void thunk_igFloatArrayMetaField_GetMetaObject(void) {
    igFloatArrayMetaField_GetMetaObject();
}
