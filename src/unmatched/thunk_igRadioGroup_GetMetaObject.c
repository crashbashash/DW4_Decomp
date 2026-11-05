/* 0x0044d050 — thunk_igRadioGroup_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igRadioGroup_GetMetaObject();

void thunk_igRadioGroup_GetMetaObject(void) {
    igRadioGroup_GetMetaObject();
}
