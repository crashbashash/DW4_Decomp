/* 0x002ce0e0 — thunk_igStackMemoryPool_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igStackMemoryPool_GetMetaObject();

void thunk_igStackMemoryPool_GetMetaObject(void) {
    igStackMemoryPool_GetMetaObject();
}
