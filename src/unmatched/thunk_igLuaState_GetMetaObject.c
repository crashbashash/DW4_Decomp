/* 0x0023c620 — thunk_igLuaState_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLuaState_GetMetaObject();

void thunk_igLuaState_GetMetaObject(void) {
    igLuaState_GetMetaObject();
}
