/* 0x002b7b30 — thunk_igTimer_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igTimer_GetMetaObject();

void thunk_igTimer_GetMetaObject(void) {
    igTimer_GetMetaObject();
}
