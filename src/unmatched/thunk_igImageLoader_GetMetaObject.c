/* 0x0014db00 — thunk_igImageLoader_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igImageLoader_GetMetaObject();

void thunk_igImageLoader_GetMetaObject(void) {
    igImageLoader_GetMetaObject();
}
