/* 0x002c0680 — thunk_igArenaMemoryPool_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igArenaMemoryPool_GetMetaObject();

void thunk_igArenaMemoryPool_GetMetaObject(void) {
    igArenaMemoryPool_GetMetaObject();
}
