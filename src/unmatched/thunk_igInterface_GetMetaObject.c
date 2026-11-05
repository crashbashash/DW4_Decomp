/* 0x00228ce0 — thunk_igInterface_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igInterface_GetMetaObject();

void thunk_igInterface_GetMetaObject(void) {
    igInterface_GetMetaObject();
}
