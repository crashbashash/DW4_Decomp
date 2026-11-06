int lua_pushnil();
int lua_pushstring();

void FUN_0023d070(int dummy0, int arg1, int arg2) {
    if (arg2 != 0) {
        lua_pushstring(arg1, arg2);
        return;
    }
    lua_pushnil(arg1);
}
