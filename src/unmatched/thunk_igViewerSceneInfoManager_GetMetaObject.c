/* 0x00459ed0 — thunk_igViewerSceneInfoManager_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igViewerSceneInfoManager_GetMetaObject();

void thunk_igViewerSceneInfoManager_GetMetaObject(void) {
    igViewerSceneInfoManager_GetMetaObject();
}
