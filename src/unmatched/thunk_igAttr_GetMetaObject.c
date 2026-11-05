/* 0x0013b190 — thunk_igAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igAttr_GetMetaObject();

void thunk_igAttr_GetMetaObject(void) {
    igAttr_GetMetaObject();
}
