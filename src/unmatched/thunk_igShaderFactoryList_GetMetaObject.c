/* 0x00199100 — thunk_igShaderFactoryList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igShaderFactoryList_GetMetaObject();

void thunk_igShaderFactoryList_GetMetaObject(void) {
    igShaderFactoryList_GetMetaObject();
}
