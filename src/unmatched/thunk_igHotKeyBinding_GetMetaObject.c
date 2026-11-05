/* 0x0044ddd0 — thunk_igHotKeyBinding_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igHotKeyBinding_GetMetaObject();

void thunk_igHotKeyBinding_GetMetaObject(void) {
    igHotKeyBinding_GetMetaObject();
}
