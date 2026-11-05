/* 0x00131e10 — thunk_igTextureFunctionAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igTextureFunctionAttr_GetMetaObject();

void thunk_igTextureFunctionAttr_GetMetaObject(void) {
    igTextureFunctionAttr_GetMetaObject();
}
