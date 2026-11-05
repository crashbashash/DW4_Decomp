/* 0x0014bc30 — thunk_igUserUCodeExt_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igUserUCodeExt_GetMetaObject();

void thunk_igUserUCodeExt_GetMetaObject(void) {
    igUserUCodeExt_GetMetaObject();
}
