/* 0x00233400 — thunk_igViewportResizedMessage_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igViewportResizedMessage_GetMetaObject();

void thunk_igViewportResizedMessage_GetMetaObject(void) {
    igViewportResizedMessage_GetMetaObject();
}
