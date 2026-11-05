/* 0x002bf700 — thunk_igMemoryRefMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMemoryRefMetaField_GetMetaObject();

void thunk_igMemoryRefMetaField_GetMetaObject(void) {
    igMemoryRefMetaField_GetMetaObject();
}
