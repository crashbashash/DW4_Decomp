/* 0x002b8380 — thunk_igNonRefCountedThreadList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igNonRefCountedThreadList_GetMetaObject();

void thunk_igNonRefCountedThreadList_GetMetaObject(void) {
    igNonRefCountedThreadList_GetMetaObject();
}
