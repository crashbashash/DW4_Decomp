/* 0x001308b0 — thunk_igVertexBlendStateAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igVertexBlendStateAttr_GetMetaObject();

void thunk_igVertexBlendStateAttr_GetMetaObject(void) {
    igVertexBlendStateAttr_GetMetaObject();
}
