/* 0x00188210 — thunk_igRayList_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igRayList_GetMetaObject();

void thunk_igRayList_GetMetaObject(void) {
    igRayList_GetMetaObject();
}
