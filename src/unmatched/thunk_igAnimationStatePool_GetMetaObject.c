/* 0x001a6910 — thunk_igAnimationStatePool_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igAnimationStatePool_GetMetaObject();

void thunk_igAnimationStatePool_GetMetaObject(void) {
    igAnimationStatePool_GetMetaObject();
}
