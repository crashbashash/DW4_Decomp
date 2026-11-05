/* 0x002cd840 — thunk_igPageMemoryPool_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igPageMemoryPool_GetMetaObject();

void thunk_igPageMemoryPool_GetMetaObject(void) {
    igPageMemoryPool_GetMetaObject();
}
