/* 0x002c1220 — thunk_igMemoryDictionary_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMemoryDictionary_GetMetaObject();

void thunk_igMemoryDictionary_GetMetaObject(void) {
    igMemoryDictionary_GetMetaObject();
}
