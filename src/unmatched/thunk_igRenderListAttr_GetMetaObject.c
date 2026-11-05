/* 0x00134010 — thunk_igRenderListAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igRenderListAttr_GetMetaObject();

void thunk_igRenderListAttr_GetMetaObject(void) {
    igRenderListAttr_GetMetaObject();
}
