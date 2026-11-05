/* 0x002bddb0 — thunk_igNonRefCountedObjectList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igNonRefCountedObjectList_GetMetaObject();

void thunk_igNonRefCountedObjectList_GetMetaObject(void) {
    igNonRefCountedObjectList_GetMetaObject();
}
