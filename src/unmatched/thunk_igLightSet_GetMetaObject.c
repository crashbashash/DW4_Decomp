/* 0x0019dd60 — thunk_igLightSet_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLightSet_GetMetaObject();

void thunk_igLightSet_GetMetaObject(void) {
    igLightSet_GetMetaObject();
}
