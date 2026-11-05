/* 0x0019cb90 — thunk_igNodeListList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igNodeListList_GetMetaObject();

void thunk_igNodeListList_GetMetaObject(void) {
    igNodeListList_GetMetaObject();
}
