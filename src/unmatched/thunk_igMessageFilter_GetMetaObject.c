/* 0x00231d40 — thunk_igMessageFilter_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMessageFilter_GetMetaObject();

void thunk_igMessageFilter_GetMetaObject(void) {
    igMessageFilter_GetMetaObject();
}
