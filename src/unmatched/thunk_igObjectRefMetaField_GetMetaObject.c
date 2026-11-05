/* 0x002bd140 — thunk_igObjectRefMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igObjectRefMetaField_GetMetaObject();

void thunk_igObjectRefMetaField_GetMetaObject(void) {
    igObjectRefMetaField_GetMetaObject();
}
