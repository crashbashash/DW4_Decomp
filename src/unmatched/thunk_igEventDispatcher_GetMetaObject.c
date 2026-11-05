/* 0x00451610 — thunk_igEventDispatcher_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igEventDispatcher_GetMetaObject();

void thunk_igEventDispatcher_GetMetaObject(void) {
    igEventDispatcher_GetMetaObject();
}
