/* 0x004526b0 — thunk_igBitmapFont_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igBitmapFont_GetMetaObject();

void thunk_igBitmapFont_GetMetaObject(void) {
    igBitmapFont_GetMetaObject();
}
