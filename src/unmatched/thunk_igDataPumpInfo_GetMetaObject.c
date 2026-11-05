/* 0x001e58a0 — thunk_igDataPumpInfo_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igDataPumpInfo_GetMetaObject();

void thunk_igDataPumpInfo_GetMetaObject(void) {
    igDataPumpInfo_GetMetaObject();
}
