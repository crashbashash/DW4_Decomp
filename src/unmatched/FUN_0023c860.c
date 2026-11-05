/* 0x0023c860 — FUN_0023c860. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int lua_settop(int, int);
int lua_pushstring(int, int);
int lua_pushusertag(int, int, int);
int lua_getglobals();
int lua_rawset(int, int);

void FUN_0023c860(int arg0, int arg1, int arg2, int arg3) {
    lua_getglobals();
    lua_pushstring(arg0, arg1);
    lua_pushusertag(arg0, arg2, arg3);
    lua_rawset(arg0, -3);
    lua_settop(arg0, -2);
}
