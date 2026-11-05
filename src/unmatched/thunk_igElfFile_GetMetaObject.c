/* 0x002cebf0 — thunk_igElfFile_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igElfFile_GetMetaObject();

void thunk_igElfFile_GetMetaObject(void) {
    igElfFile_GetMetaObject();
}
