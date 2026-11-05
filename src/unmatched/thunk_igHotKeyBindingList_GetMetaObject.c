/* 0x0044dc10 — thunk_igHotKeyBindingList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igHotKeyBindingList_GetMetaObject();

void thunk_igHotKeyBindingList_GetMetaObject(void) {
    igHotKeyBindingList_GetMetaObject();
}
