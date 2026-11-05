/* 0x0014e0e0 — thunk_igImage_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igImage_GetMetaObject();

void thunk_igImage_GetMetaObject(void) {
    igImage_GetMetaObject();
}
