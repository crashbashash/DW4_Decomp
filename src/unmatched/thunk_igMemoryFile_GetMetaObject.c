/* 0x002c0920 — thunk_igMemoryFile_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMemoryFile_GetMetaObject();

void thunk_igMemoryFile_GetMetaObject(void) {
    igMemoryFile_GetMetaObject();
}
