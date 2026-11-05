/* 0x002cb270 — thunk_igBoolList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igBoolList_GetMetaObject();

void thunk_igBoolList_GetMetaObject(void) {
    igBoolList_GetMetaObject();
}
