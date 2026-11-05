/* 0x00197d50 — thunk_igRenderPackage_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igRenderPackage_GetMetaObject();

void thunk_igRenderPackage_GetMetaObject(void) {
    igRenderPackage_GetMetaObject();
}
