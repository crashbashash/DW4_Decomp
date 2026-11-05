/* 0x0019b300 — thunk_igSceneInfo_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igSceneInfo_GetMetaObject();

void thunk_igSceneInfo_GetMetaObject(void) {
    igSceneInfo_GetMetaObject();
}
