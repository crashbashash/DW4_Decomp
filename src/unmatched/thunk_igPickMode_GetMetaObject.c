/* 0x0045c3c0 — thunk_igPickMode_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igPickMode_GetMetaObject();

void thunk_igPickMode_GetMetaObject(void) {
    igPickMode_GetMetaObject();
}
