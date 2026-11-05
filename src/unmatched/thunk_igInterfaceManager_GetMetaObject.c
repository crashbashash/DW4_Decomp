/* 0x00145fe0 — thunk_igInterfaceManager_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igInterfaceManager_GetMetaObject();

void thunk_igInterfaceManager_GetMetaObject(void) {
    igInterfaceManager_GetMetaObject();
}
