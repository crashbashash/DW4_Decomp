/* 0x0014b590 — thunk_igVertexData_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igVertexData_GetMetaObject();

void thunk_igVertexData_GetMetaObject(void) {
    igVertexData_GetMetaObject();
}
