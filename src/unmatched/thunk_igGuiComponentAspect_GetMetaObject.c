/* 0x0044fcd0 — thunk_igGuiComponentAspect_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igGuiComponentAspect_GetMetaObject();

void thunk_igGuiComponentAspect_GetMetaObject(void) {
    igGuiComponentAspect_GetMetaObject();
}
