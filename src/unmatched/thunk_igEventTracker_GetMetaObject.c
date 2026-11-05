/* 0x002c5a70 — thunk_igEventTracker_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igEventTracker_GetMetaObject();

void thunk_igEventTracker_GetMetaObject(void) {
    igEventTracker_GetMetaObject();
}
