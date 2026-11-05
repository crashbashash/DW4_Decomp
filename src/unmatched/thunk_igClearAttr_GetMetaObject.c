/* 0x001394c0 — thunk_igClearAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igClearAttr_GetMetaObject();

void thunk_igClearAttr_GetMetaObject(void) {
    igClearAttr_GetMetaObject();
}
