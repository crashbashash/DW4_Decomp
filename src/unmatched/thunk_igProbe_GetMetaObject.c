/* 0x0019e920 — thunk_igProbe_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igProbe_GetMetaObject();

void thunk_igProbe_GetMetaObject(void) {
    igProbe_GetMetaObject();
}
