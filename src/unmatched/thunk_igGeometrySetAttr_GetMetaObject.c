/* 0x00136f20 — thunk_igGeometrySetAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igGeometrySetAttr_GetMetaObject();

void thunk_igGeometrySetAttr_GetMetaObject(void) {
    igGeometrySetAttr_GetMetaObject();
}
