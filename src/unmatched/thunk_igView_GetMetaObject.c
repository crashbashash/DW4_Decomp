/* 0x0044bc30 — thunk_igView_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igView_GetMetaObject();

void thunk_igView_GetMetaObject(void) {
    igView_GetMetaObject();
}
