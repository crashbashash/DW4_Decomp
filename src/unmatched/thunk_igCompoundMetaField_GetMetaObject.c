/* 0x002cbdc0 — thunk_igCompoundMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCompoundMetaField_GetMetaObject();

void thunk_igCompoundMetaField_GetMetaObject(void) {
    igCompoundMetaField_GetMetaObject();
}
