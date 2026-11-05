/* 0x001e4170 — thunk_igLongStack_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLongStack_GetMetaObject();

void thunk_igLongStack_GetMetaObject(void) {
    igLongStack_GetMetaObject();
}
