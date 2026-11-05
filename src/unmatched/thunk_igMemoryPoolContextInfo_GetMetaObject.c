/* 0x002c03f0 — thunk_igMemoryPoolContextInfo_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMemoryPoolContextInfo_GetMetaObject();

void thunk_igMemoryPoolContextInfo_GetMetaObject(void) {
    igMemoryPoolContextInfo_GetMetaObject();
}
