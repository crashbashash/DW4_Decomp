/* 0x0045da80 — thunk_igNormalsRenderer_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igNormalsRenderer_GetMetaObject();

void thunk_igNormalsRenderer_GetMetaObject(void) {
    igNormalsRenderer_GetMetaObject();
}
