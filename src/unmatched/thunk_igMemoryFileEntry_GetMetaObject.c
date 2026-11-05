/* 0x002c0d00 — thunk_igMemoryFileEntry_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMemoryFileEntry_GetMetaObject();

void thunk_igMemoryFileEntry_GetMetaObject(void) {
    igMemoryFileEntry_GetMetaObject();
}
