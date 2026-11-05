/* 0x0019cfa0 — thunk_igNode_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igNode_GetMetaObject();

void thunk_igNode_GetMetaObject(void) {
    igNode_GetMetaObject();
}
