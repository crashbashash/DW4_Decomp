/* 0x002bd820 — thunk_igObjectList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igObjectList_GetMetaObject();

void thunk_igObjectList_GetMetaObject(void) {
    igObjectList_GetMetaObject();
}
