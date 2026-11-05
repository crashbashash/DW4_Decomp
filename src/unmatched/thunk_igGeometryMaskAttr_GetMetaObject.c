/* 0x001371c0 — thunk_igGeometryMaskAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igGeometryMaskAttr_GetMetaObject();

void thunk_igGeometryMaskAttr_GetMetaObject(void) {
    igGeometryMaskAttr_GetMetaObject();
}
