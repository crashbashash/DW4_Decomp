/* 0x00229340 — thunk_igBase_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igBase_GetMetaObject();

void thunk_igBase_GetMetaObject(void) {
    igBase_GetMetaObject();
}
