/* 0x001e5520 — thunk_igDataPumpList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igDataPumpList_GetMetaObject();

void thunk_igDataPumpList_GetMetaObject(void) {
    igDataPumpList_GetMetaObject();
}
