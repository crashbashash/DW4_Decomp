/* 0x0014ac00 — thunk_igVertexArray2_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igVertexArray2_GetMetaObject();

void thunk_igVertexArray2_GetMetaObject(void) {
    igVertexArray2_GetMetaObject();
}
