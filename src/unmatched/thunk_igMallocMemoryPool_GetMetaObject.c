/* 0x002ce440 — thunk_igMallocMemoryPool_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMallocMemoryPool_GetMetaObject();

void thunk_igMallocMemoryPool_GetMetaObject(void) {
    igMallocMemoryPool_GetMetaObject();
}
