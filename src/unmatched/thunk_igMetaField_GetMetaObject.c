/* 0x002bedc0 — thunk_igMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaField_GetMetaObject();

void thunk_igMetaField_GetMetaObject(void) {
    igMetaField_GetMetaObject();
}
