/* 0x002cac10 — thunk_igIntList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igIntList_GetMetaObject();

void thunk_igIntList_GetMetaObject(void) {
    igIntList_GetMetaObject();
}
