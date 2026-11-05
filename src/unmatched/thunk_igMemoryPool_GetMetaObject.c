/* 0x002c05b0 — thunk_igMemoryPool_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMemoryPool_GetMetaObject();

void thunk_igMemoryPool_GetMetaObject(void) {
    igMemoryPool_GetMetaObject();
}
