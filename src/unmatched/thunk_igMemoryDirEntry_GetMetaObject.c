/* 0x002c0f30 — thunk_igMemoryDirEntry_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMemoryDirEntry_GetMetaObject();

void thunk_igMemoryDirEntry_GetMetaObject(void) {
    igMemoryDirEntry_GetMetaObject();
}
