/* 0x00135fc0 — thunk_igLightingStateAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLightingStateAttr_GetMetaObject();

void thunk_igLightingStateAttr_GetMetaObject(void) {
    igLightingStateAttr_GetMetaObject();
}
