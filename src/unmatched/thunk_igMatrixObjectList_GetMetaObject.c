/* 0x001e4c40 — thunk_igMatrixObjectList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMatrixObjectList_GetMetaObject();

void thunk_igMatrixObjectList_GetMetaObject(void) {
    igMatrixObjectList_GetMetaObject();
}
