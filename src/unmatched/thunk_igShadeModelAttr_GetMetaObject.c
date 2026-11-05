/* 0x00133ab0 — thunk_igShadeModelAttr_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igShadeModelAttr_GetMetaObject();

void thunk_igShadeModelAttr_GetMetaObject(void) {
    igShadeModelAttr_GetMetaObject();
}
