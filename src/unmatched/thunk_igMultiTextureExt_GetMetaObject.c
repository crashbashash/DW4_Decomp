/* 0x0014d640 — thunk_igMultiTextureExt_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMultiTextureExt_GetMetaObject();

void thunk_igMultiTextureExt_GetMetaObject(void) {
    igMultiTextureExt_GetMetaObject();
}
