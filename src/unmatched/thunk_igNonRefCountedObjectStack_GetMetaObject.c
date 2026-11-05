/* 0x001e44b0 — thunk_igNonRefCountedObjectStack_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igNonRefCountedObjectStack_GetMetaObject();

void thunk_igNonRefCountedObjectStack_GetMetaObject(void) {
    igNonRefCountedObjectStack_GetMetaObject();
}
