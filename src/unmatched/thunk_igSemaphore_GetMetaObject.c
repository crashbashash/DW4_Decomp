/* 0x002ba7b0 — thunk_igSemaphore_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igSemaphore_GetMetaObject();

void thunk_igSemaphore_GetMetaObject(void) {
    igSemaphore_GetMetaObject();
}
