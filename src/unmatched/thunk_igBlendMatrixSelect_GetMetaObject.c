/* 0x001a4ce0 — thunk_igBlendMatrixSelect_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igBlendMatrixSelect_GetMetaObject();

void thunk_igBlendMatrixSelect_GetMetaObject(void) {
    igBlendMatrixSelect_GetMetaObject();
}
