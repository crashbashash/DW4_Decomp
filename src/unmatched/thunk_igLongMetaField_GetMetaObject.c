/* 0x002c1b90 — thunk_igLongMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLongMetaField_GetMetaObject();

void thunk_igLongMetaField_GetMetaObject(void) {
    igLongMetaField_GetMetaObject();
}
