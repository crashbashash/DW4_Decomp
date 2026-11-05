/* 0x00450910 — thunk_igFont_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igFont_GetMetaObject();

void thunk_igFont_GetMetaObject(void) {
    igFont_GetMetaObject();
}
