/* 0x0014dd30 — thunk_igImageUtils_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igImageUtils_GetMetaObject();

void thunk_igImageUtils_GetMetaObject(void) {
    igImageUtils_GetMetaObject();
}
