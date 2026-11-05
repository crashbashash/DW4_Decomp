/* 0x00186ba0 — thunk_igVolume_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igVolume_GetMetaObject();

void thunk_igVolume_GetMetaObject(void) {
    igVolume_GetMetaObject();
}
