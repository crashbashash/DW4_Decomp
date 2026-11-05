/* 0x002c72b0 — thunk_igDirectoryList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igDirectoryList_GetMetaObject();

void thunk_igDirectoryList_GetMetaObject(void) {
    igDirectoryList_GetMetaObject();
}
