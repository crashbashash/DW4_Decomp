/* 0x002cd470 — thunk_igAliasMemoryPool_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igAliasMemoryPool_GetMetaObject();

void thunk_igAliasMemoryPool_GetMetaObject(void) {
    igAliasMemoryPool_GetMetaObject();
}
