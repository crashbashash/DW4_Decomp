/* 0x00227440 — thunk_igIterator_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igIterator_GetMetaObject();

void thunk_igIterator_GetMetaObject(void) {
    igIterator_GetMetaObject();
}
