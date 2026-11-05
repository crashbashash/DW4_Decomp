/* 0x002bfec0 — thunk_igMemoryPoolInfoList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMemoryPoolInfoList_GetMetaObject();

void thunk_igMemoryPoolInfoList_GetMetaObject(void) {
    igMemoryPoolInfoList_GetMetaObject();
}
