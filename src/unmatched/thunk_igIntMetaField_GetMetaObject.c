/* 0x002c2fb0 — thunk_igIntMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igIntMetaField_GetMetaObject();

void thunk_igIntMetaField_GetMetaObject(void) {
    igIntMetaField_GetMetaObject();
}
