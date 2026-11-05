/* 0x00186da0 — thunk_igVolumeList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igVolumeList_GetMetaObject();

void thunk_igVolumeList_GetMetaObject(void) {
    igVolumeList_GetMetaObject();
}
