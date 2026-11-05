/* 0x002c1800 — thunk_igMedia_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMedia_GetMetaObject();

void thunk_igMedia_GetMetaObject(void) {
    igMedia_GetMetaObject();
}
