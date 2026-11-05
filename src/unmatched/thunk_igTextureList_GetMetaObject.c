/* 0x0013a4c0 — thunk_igTextureList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igTextureList_GetMetaObject();

void thunk_igTextureList_GetMetaObject(void) {
    igTextureList_GetMetaObject();
}
