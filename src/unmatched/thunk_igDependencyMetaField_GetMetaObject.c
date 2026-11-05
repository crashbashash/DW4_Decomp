/* 0x002c8110 — thunk_igDependencyMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igDependencyMetaField_GetMetaObject();

void thunk_igDependencyMetaField_GetMetaObject(void) {
    igDependencyMetaField_GetMetaObject();
}
