/* 0x001324b0 — thunk_igTextureCubeAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igTextureCubeAttr_GetMetaObject();

void thunk_igTextureCubeAttr_GetMetaObject(void) {
    igTextureCubeAttr_GetMetaObject();
}
