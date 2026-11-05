/* 0x00227b80 — thunk_igIterateDerived_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igIterateDerived_GetMetaObject();

void thunk_igIterateDerived_GetMetaObject(void) {
    igIterateDerived_GetMetaObject();
}
