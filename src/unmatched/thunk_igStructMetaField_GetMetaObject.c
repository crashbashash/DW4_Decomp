/* 0x002b8b40 — thunk_igStructMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igStructMetaField_GetMetaObject();

void thunk_igStructMetaField_GetMetaObject(void) {
    igStructMetaField_GetMetaObject();
}
