/* 0x0013a630 — thunk_igGeometryAttrList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igGeometryAttrList_GetMetaObject();

void thunk_igGeometryAttrList_GetMetaObject(void) {
    igGeometryAttrList_GetMetaObject();
}
