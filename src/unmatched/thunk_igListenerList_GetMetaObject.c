/* 0x00227250 — thunk_igListenerList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igListenerList_GetMetaObject();

void thunk_igListenerList_GetMetaObject(void) {
    igListenerList_GetMetaObject();
}
