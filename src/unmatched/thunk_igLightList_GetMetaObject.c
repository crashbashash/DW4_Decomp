/* 0x00136740 — thunk_igLightList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLightList_GetMetaObject();

void thunk_igLightList_GetMetaObject(void) {
    igLightList_GetMetaObject();
}
