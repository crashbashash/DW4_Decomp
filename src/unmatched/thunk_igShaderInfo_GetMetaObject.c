/* 0x00198ec0 — thunk_igShaderInfo_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igShaderInfo_GetMetaObject();

void thunk_igShaderInfo_GetMetaObject(void) {
    igShaderInfo_GetMetaObject();
}
