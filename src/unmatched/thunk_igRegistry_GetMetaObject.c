/* 0x002bb290 — thunk_igRegistry_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igRegistry_GetMetaObject();

void thunk_igRegistry_GetMetaObject(void) {
    igRegistry_GetMetaObject();
}
