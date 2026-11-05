/* 0x0014bda0 — thunk_igScissorExt_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igScissorExt_GetMetaObject();

void thunk_igScissorExt_GetMetaObject(void) {
    igScissorExt_GetMetaObject();
}
