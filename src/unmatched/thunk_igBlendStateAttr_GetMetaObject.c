/* 0x001397a0 — thunk_igBlendStateAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igBlendStateAttr_GetMetaObject();

void thunk_igBlendStateAttr_GetMetaObject(void) {
    igBlendStateAttr_GetMetaObject();
}
