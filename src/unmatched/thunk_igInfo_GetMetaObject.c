/* 0x002c3720 — thunk_igInfo_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igInfo_GetMetaObject();

void thunk_igInfo_GetMetaObject(void) {
    igInfo_GetMetaObject();
}
