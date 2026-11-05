/* 0x001a4a00 — thunk_igBoundingBoxesMaker_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igBoundingBoxesMaker_GetMetaObject();

void thunk_igBoundingBoxesMaker_GetMetaObject(void) {
    igBoundingBoxesMaker_GetMetaObject();
}
