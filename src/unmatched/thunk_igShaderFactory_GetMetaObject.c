/* 0x00199560 — thunk_igShaderFactory_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igShaderFactory_GetMetaObject();

void thunk_igShaderFactory_GetMetaObject(void) {
    igShaderFactory_GetMetaObject();
}
