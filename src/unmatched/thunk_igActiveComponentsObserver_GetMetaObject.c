/* 0x0044ebe0 — thunk_igActiveComponentsObserver_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igActiveComponentsObserver_GetMetaObject();

void thunk_igActiveComponentsObserver_GetMetaObject(void) {
    igActiveComponentsObserver_GetMetaObject();
}
