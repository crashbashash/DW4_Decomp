/* 0x002c16d0 — thunk_igMediaList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMediaList_GetMetaObject();

void thunk_igMediaList_GetMetaObject(void) {
    igMediaList_GetMetaObject();
}
