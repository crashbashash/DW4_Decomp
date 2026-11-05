/* 0x0023c820 — thunk_igLuaGlue_GetMetaObject. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igLuaGlue_GetMetaObject();

void thunk_igLuaGlue_GetMetaObject(void) {
    igLuaGlue_GetMetaObject();
}
