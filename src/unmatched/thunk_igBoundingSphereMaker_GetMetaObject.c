/* 0x0023ab80 — thunk_igBoundingSphereMaker_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igBoundingSphereMaker_GetMetaObject();

void thunk_igBoundingSphereMaker_GetMetaObject(void) {
    igBoundingSphereMaker_GetMetaObject();
}
