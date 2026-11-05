/* 0x00458f50 — thunk_igStatisticsItem_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igStatisticsItem_GetMetaObject();

void thunk_igStatisticsItem_GetMetaObject(void) {
    igStatisticsItem_GetMetaObject();
}
