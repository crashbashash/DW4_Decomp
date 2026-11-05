/* 0x0019cd40 — thunk_igNodeList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igNodeList_GetMetaObject();

void thunk_igNodeList_GetMetaObject(void) {
    igNodeList_GetMetaObject();
}
