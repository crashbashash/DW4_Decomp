/* 0x002c9500 — thunk_igDoubleList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igDoubleList_GetMetaObject();

void thunk_igDoubleList_GetMetaObject(void) {
    igDoubleList_GetMetaObject();
}
