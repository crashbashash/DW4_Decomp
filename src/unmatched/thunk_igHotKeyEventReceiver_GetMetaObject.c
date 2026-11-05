/* 0x0044da00 — thunk_igHotKeyEventReceiver_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igHotKeyEventReceiver_GetMetaObject();

void thunk_igHotKeyEventReceiver_GetMetaObject(void) {
    igHotKeyEventReceiver_GetMetaObject();
}
