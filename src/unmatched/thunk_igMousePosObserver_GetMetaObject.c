/* 0x0044ef90 — thunk_igMousePosObserver_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMousePosObserver_GetMetaObject();

void thunk_igMousePosObserver_GetMetaObject(void) {
    igMousePosObserver_GetMetaObject();
}
