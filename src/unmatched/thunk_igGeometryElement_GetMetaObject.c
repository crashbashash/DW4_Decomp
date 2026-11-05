/* 0x004506d0 — thunk_igGeometryElement_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igGeometryElement_GetMetaObject();

void thunk_igGeometryElement_GetMetaObject(void) {
    igGeometryElement_GetMetaObject();
}
