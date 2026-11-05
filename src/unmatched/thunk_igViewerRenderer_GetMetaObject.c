/* 0x0045b160 — thunk_igViewerRenderer_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igViewerRenderer_GetMetaObject();

void thunk_igViewerRenderer_GetMetaObject(void) {
    igViewerRenderer_GetMetaObject();
}
