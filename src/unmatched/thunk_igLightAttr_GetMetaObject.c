/* 0x00136910 — thunk_igLightAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLightAttr_GetMetaObject();

void thunk_igLightAttr_GetMetaObject(void) {
    igLightAttr_GetMetaObject();
}
