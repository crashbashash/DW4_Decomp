/* 0x0019c830 — thunk_igOverrideAttrSet_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igOverrideAttrSet_GetMetaObject();

void thunk_igOverrideAttrSet_GetMetaObject(void) {
    igOverrideAttrSet_GetMetaObject();
}
