/* 0x0019f830 — thunk_igGraphPath_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igGraphPath_GetMetaObject();

void thunk_igGraphPath_GetMetaObject(void) {
    igGraphPath_GetMetaObject();
}
