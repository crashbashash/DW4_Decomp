/* 0x00196840 — thunk_igObjectPool_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igObjectPool_GetMetaObject();

void thunk_igObjectPool_GetMetaObject(void) {
    igObjectPool_GetMetaObject();
}
