/* 0x0019fa90 — thunk_igGeometryList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igGeometryList_GetMetaObject();

void thunk_igGeometryList_GetMetaObject(void) {
    igGeometryList_GetMetaObject();
}
