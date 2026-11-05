/* 0x0014a160 — thunk_igVisualContext_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igVisualContext_GetMetaObject();

void thunk_igVisualContext_GetMetaObject(void) {
    igVisualContext_GetMetaObject();
}
