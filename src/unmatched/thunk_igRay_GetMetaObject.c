/* 0x001883c0 — thunk_igRay_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igRay_GetMetaObject();

void thunk_igRay_GetMetaObject(void) {
    igRay_GetMetaObject();
}
