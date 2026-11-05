/* 0x002cb650 — thunk_igContextExtInfoList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igContextExtInfoList_GetMetaObject();

void thunk_igContextExtInfoList_GetMetaObject(void) {
    igContextExtInfoList_GetMetaObject();
}
