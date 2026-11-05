/* 0x0014b010 — thunk_igVertexStream_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igVertexStream_GetMetaObject();

void thunk_igVertexStream_GetMetaObject(void) {
    igVertexStream_GetMetaObject();
}
