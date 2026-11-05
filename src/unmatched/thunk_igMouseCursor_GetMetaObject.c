/* 0x0044e5f0 — thunk_igMouseCursor_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMouseCursor_GetMetaObject();

void thunk_igMouseCursor_GetMetaObject(void) {
    igMouseCursor_GetMetaObject();
}
