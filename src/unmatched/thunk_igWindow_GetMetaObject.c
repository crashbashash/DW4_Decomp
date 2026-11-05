/* 0x00145e60 — thunk_igWindow_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igWindow_GetMetaObject();

void thunk_igWindow_GetMetaObject(void) {
    igWindow_GetMetaObject();
}
