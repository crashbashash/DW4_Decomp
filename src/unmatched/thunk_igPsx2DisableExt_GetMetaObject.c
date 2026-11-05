/* 0x0014f8c0 — thunk_igPsx2DisableExt_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igPsx2DisableExt_GetMetaObject();

void thunk_igPsx2DisableExt_GetMetaObject(void) {
    igPsx2DisableExt_GetMetaObject();
}
