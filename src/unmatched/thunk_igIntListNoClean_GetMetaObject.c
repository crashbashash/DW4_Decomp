/* 0x002caa50 — thunk_igIntListNoClean_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igIntListNoClean_GetMetaObject();

void thunk_igIntListNoClean_GetMetaObject(void) {
    igIntListNoClean_GetMetaObject();
}
