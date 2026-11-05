/* 0x0044d790 — thunk_igModel_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igModel_GetMetaObject();

void thunk_igModel_GetMetaObject(void) {
    igModel_GetMetaObject();
}
