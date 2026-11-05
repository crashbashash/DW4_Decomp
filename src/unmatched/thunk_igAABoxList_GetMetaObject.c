/* 0x0018a650 — thunk_igAABoxList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igAABoxList_GetMetaObject();

void thunk_igAABoxList_GetMetaObject(void) {
    igAABoxList_GetMetaObject();
}
