/* 0x002b99c0 — thunk_igStringMetaField_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igStringMetaField_GetMetaObject();

void thunk_igStringMetaField_GetMetaObject(void) {
    igStringMetaField_GetMetaObject();
}
