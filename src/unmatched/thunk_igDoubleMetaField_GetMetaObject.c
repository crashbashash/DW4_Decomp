/* 0x002c6d40 — thunk_igDoubleMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igDoubleMetaField_GetMetaObject();

void thunk_igDoubleMetaField_GetMetaObject(void) {
    igDoubleMetaField_GetMetaObject();
}
