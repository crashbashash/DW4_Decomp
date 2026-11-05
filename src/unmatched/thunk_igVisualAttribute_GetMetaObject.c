/* 0x00130420 — thunk_igVisualAttribute_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igVisualAttribute_GetMetaObject();

void thunk_igVisualAttribute_GetMetaObject(void) {
    igVisualAttribute_GetMetaObject();
}
