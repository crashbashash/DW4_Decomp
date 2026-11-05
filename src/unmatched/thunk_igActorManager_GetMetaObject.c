/* 0x0045e530 — thunk_igActorManager_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igActorManager_GetMetaObject();

void thunk_igActorManager_GetMetaObject(void) {
    igActorManager_GetMetaObject();
}
