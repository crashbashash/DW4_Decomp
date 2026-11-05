/* 0x00450480 — thunk_igGuiComponent_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igGuiComponent_GetMetaObject();

void thunk_igGuiComponent_GetMetaObject(void) {
    igGuiComponent_GetMetaObject();
}
