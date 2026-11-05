/* 0x0019ae90 — thunk_igSegment_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igSegment_GetMetaObject();

void thunk_igSegment_GetMetaObject(void) {
    igSegment_GetMetaObject();
}
