/* 0x0014b320 — thunk_igVertexDataList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igVertexDataList_GetMetaObject();

void thunk_igVertexDataList_GetMetaObject(void) {
    igVertexDataList_GetMetaObject();
}
