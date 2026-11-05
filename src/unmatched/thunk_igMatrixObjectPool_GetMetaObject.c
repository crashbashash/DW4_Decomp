/* 0x00199e30 — thunk_igMatrixObjectPool_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMatrixObjectPool_GetMetaObject();

void thunk_igMatrixObjectPool_GetMetaObject(void) {
    igMatrixObjectPool_GetMetaObject();
}
