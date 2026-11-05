/* 0x001e5b40 — thunk_igDataPump_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igDataPump_GetMetaObject();

void thunk_igDataPump_GetMetaObject(void) {
    igDataPump_GetMetaObject();
}
