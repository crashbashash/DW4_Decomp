/* 0x0019f040 — thunk_igIniShaderFactory_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igIniShaderFactory_GetMetaObject();

void thunk_igIniShaderFactory_GetMetaObject(void) {
    igIniShaderFactory_GetMetaObject();
}
