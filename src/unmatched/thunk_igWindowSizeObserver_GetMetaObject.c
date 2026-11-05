/* 0x0044f200 — thunk_igWindowSizeObserver_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igWindowSizeObserver_GetMetaObject();

void thunk_igWindowSizeObserver_GetMetaObject(void) {
    igWindowSizeObserver_GetMetaObject();
}
