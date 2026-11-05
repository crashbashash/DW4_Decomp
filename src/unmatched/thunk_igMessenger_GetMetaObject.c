/* 0x002315c0 — thunk_igMessenger_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMessenger_GetMetaObject();

void thunk_igMessenger_GetMetaObject(void) {
    igMessenger_GetMetaObject();
}
