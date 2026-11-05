/* 0x001e5310 — thunk_igDataPumpManager_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igDataPumpManager_GetMetaObject();

void thunk_igDataPumpManager_GetMetaObject(void) {
    igDataPumpManager_GetMetaObject();
}
