/* 0x002264a0 — thunk_igMessageList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMessageList_GetMetaObject();

void thunk_igMessageList_GetMetaObject(void) {
    igMessageList_GetMetaObject();
}
