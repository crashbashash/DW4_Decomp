/* 0x002cb9f0 — thunk_igContextExt_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igContextExt_GetMetaObject();

void thunk_igContextExt_GetMetaObject(void) {
    igContextExt_GetMetaObject();
}
