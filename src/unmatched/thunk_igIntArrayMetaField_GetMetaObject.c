/* 0x002c3280 — thunk_igIntArrayMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igIntArrayMetaField_GetMetaObject();

void thunk_igIntArrayMetaField_GetMetaObject(void) {
    igIntArrayMetaField_GetMetaObject();
}
