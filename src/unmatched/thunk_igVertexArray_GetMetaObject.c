/* 0x0014baa0 — thunk_igVertexArray_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igVertexArray_GetMetaObject();

void thunk_igVertexArray_GetMetaObject(void) {
    igVertexArray_GetMetaObject();
}
