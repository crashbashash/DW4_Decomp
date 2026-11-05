/* 0x00458c40 — thunk_igStatisticsItemList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igStatisticsItemList_GetMetaObject();

void thunk_igStatisticsItemList_GetMetaObject(void) {
    igStatisticsItemList_GetMetaObject();
}
