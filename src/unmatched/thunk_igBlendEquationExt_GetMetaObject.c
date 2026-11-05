/* 0x0014ff80 — thunk_igBlendEquationExt_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igBlendEquationExt_GetMetaObject();

void thunk_igBlendEquationExt_GetMetaObject(void) {
    igBlendEquationExt_GetMetaObject();
}
