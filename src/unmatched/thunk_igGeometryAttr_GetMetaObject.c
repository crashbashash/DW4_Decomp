/* 0x00137970 — thunk_igGeometryAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igGeometryAttr_GetMetaObject();

void thunk_igGeometryAttr_GetMetaObject(void) {
    igGeometryAttr_GetMetaObject();
}
