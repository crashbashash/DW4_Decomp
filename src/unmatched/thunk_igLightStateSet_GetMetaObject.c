/* 0x0019daf0 — thunk_igLightStateSet_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLightStateSet_GetMetaObject();

void thunk_igLightStateSet_GetMetaObject(void) {
    igLightStateSet_GetMetaObject();
}
