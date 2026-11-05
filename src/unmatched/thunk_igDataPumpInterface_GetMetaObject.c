/* 0x001e5640 — thunk_igDataPumpInterface_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igDataPumpInterface_GetMetaObject();

void thunk_igDataPumpInterface_GetMetaObject(void) {
    igDataPumpInterface_GetMetaObject();
}
