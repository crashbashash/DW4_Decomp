/* 0x00139d60 — thunk_igBlendMatricesAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igBlendMatricesAttr_GetMetaObject();

void thunk_igBlendMatricesAttr_GetMetaObject(void) {
    igBlendMatricesAttr_GetMetaObject();
}
