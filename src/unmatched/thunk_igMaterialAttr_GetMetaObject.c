/* 0x00135cf0 — thunk_igMaterialAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMaterialAttr_GetMetaObject();

void thunk_igMaterialAttr_GetMetaObject(void) {
    igMaterialAttr_GetMetaObject();
}
