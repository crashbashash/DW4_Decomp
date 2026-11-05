/* 0x002bb8b0 — thunk_igRefMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igRefMetaField_GetMetaObject();

void thunk_igRefMetaField_GetMetaObject(void) {
    igRefMetaField_GetMetaObject();
}
