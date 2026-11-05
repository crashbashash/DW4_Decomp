/* 0x00459220 — thunk_igViewerAction_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igViewerAction_GetMetaObject();

void thunk_igViewerAction_GetMetaObject(void) {
    igViewerAction_GetMetaObject();
}
