/* 0x0045cab0 — thunk_igFlyMode_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igFlyMode_GetMetaObject();

void thunk_igFlyMode_GetMetaObject(void) {
    igFlyMode_GetMetaObject();
}
