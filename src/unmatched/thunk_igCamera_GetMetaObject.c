/* 0x001a46f0 — thunk_igCamera_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igCamera_GetMetaObject();

void thunk_igCamera_GetMetaObject(void) {
    igCamera_GetMetaObject();
}
