/* 0x00226000 — thunk_igOptBase_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igOptBase_GetMetaObject();

void thunk_igOptBase_GetMetaObject(void) {
    igOptBase_GetMetaObject();
}
