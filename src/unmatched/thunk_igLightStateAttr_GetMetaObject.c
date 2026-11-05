/* 0x00136500 — thunk_igLightStateAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLightStateAttr_GetMetaObject();

void thunk_igLightStateAttr_GetMetaObject(void) {
    igLightStateAttr_GetMetaObject();
}
