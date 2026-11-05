/* 0x00196560 — thunk_igTransform_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igTransform_GetMetaObject();

void thunk_igTransform_GetMetaObject(void) {
    igTransform_GetMetaObject();
}
