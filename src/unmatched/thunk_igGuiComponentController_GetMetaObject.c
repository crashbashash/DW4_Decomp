/* 0x0044fba0 — thunk_igGuiComponentController_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igGuiComponentController_GetMetaObject();

void thunk_igGuiComponentController_GetMetaObject(void) {
    igGuiComponentController_GetMetaObject();
}
