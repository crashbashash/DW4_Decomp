/* 0x001e4db0 — thunk_igMatrixObject_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMatrixObject_GetMetaObject();

void thunk_igMatrixObject_GetMetaObject(void) {
    igMatrixObject_GetMetaObject();
}
