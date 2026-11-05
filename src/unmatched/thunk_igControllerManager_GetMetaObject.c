/* 0x00146780 — thunk_igControllerManager_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igControllerManager_GetMetaObject();

void thunk_igControllerManager_GetMetaObject(void) {
    igControllerManager_GetMetaObject();
}
