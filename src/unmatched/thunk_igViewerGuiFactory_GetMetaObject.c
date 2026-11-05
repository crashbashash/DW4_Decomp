/* 0x0045bca0 — thunk_igViewerGuiFactory_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igViewerGuiFactory_GetMetaObject();

void thunk_igViewerGuiFactory_GetMetaObject(void) {
    igViewerGuiFactory_GetMetaObject();
}
