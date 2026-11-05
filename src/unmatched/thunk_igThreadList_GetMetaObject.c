/* 0x002b84f0 — thunk_igThreadList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igThreadList_GetMetaObject();

void thunk_igThreadList_GetMetaObject(void) {
    igThreadList_GetMetaObject();
}
