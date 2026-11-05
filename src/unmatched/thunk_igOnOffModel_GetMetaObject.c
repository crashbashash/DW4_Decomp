/* 0x0044d550 — thunk_igOnOffModel_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igOnOffModel_GetMetaObject();

void thunk_igOnOffModel_GetMetaObject(void) {
    igOnOffModel_GetMetaObject();
}
