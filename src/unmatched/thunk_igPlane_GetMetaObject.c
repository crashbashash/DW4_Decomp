/* 0x001885b0 — thunk_igPlane_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igPlane_GetMetaObject();

void thunk_igPlane_GetMetaObject(void) {
    igPlane_GetMetaObject();
}
