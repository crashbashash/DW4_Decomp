/* 0x002319c0 — thunk_igMessageReceiver_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMessageReceiver_GetMetaObject();

void thunk_igMessageReceiver_GetMetaObject(void) {
    igMessageReceiver_GetMetaObject();
}
