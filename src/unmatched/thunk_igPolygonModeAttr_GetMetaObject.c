/* 0x00134aa0 — thunk_igPolygonModeAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igPolygonModeAttr_GetMetaObject();

void thunk_igPolygonModeAttr_GetMetaObject(void) {
    igPolygonModeAttr_GetMetaObject();
}
