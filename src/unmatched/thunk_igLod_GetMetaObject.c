/* 0x0019d7a0 — thunk_igLod_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLod_GetMetaObject();

void thunk_igLod_GetMetaObject(void) {
    igLod_GetMetaObject();
}
