/* 0x00225f20 — thunk_igOptConfiguration_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igOptConfiguration_GetMetaObject();

void thunk_igOptConfiguration_GetMetaObject(void) {
    igOptConfiguration_GetMetaObject();
}
