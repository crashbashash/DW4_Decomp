/* 0x002c23a0 — thunk_igLibraryLoader_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLibraryLoader_GetMetaObject();

void thunk_igLibraryLoader_GetMetaObject(void) {
    igLibraryLoader_GetMetaObject();
}
