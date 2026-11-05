/* 0x00231780 — thunk_igMessage_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMessage_GetMetaObject();

void thunk_igMessage_GetMetaObject(void) {
    igMessage_GetMetaObject();
}
