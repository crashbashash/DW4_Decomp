int FUN_001006d0();
int FUN_00230d80();
int lua_gettop();
int lua_tonumber();
void *lua_touserdata();
int lua_pushusertag();

int FUN_00243a50(int arg0) {
    int temp_s0;
    int var_v0;

    if (lua_gettop() != 0) {
        var_v0 = FUN_00230d80(lua_tonumber(arg0, -2));
    } else {
        var_v0 = 1;
    }
    temp_s0 = FUN_001006d0(var_v0 * 4);
    lua_pushusertag(arg0, temp_s0, *(int *)((char *)(lua_touserdata(arg0, -1)) + 40));
    return 1;
}
