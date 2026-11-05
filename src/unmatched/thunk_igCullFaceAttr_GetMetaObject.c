/* 0x00138830 — thunk_igCullFaceAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCullFaceAttr_GetMetaObject();

void thunk_igCullFaceAttr_GetMetaObject(void) {
    igCullFaceAttr_GetMetaObject();
}
