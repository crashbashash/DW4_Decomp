/* 0x00132d80 — thunk_igTextureAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igTextureAttr_GetMetaObject();

void thunk_igTextureAttr_GetMetaObject(void) {
    igTextureAttr_GetMetaObject();
}
