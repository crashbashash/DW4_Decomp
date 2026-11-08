int dptoli();
int FUN_002467a0();
int lua_type();
int lua_tonumber();
void *lua_touserdata();
int lua_pushnumber();
extern int DAT_004ea6b0[4];
int FUN_00243b00(int arg0) {
    void *temp_s0;
    void *temp_s0_2;

    temp_s0 = (void *)(lua_touserdata(arg0, -1));
    if (lua_type(arg0, 2) != 2) {
        FUN_002467a0(&DAT_004ea6b0[0], *(int *)((char *)(temp_s0) + 12));
        return 0;
    }
    temp_s0_2 = (void *)(lua_touserdata(arg0, 1));
    lua_pushnumber(arg0, *(long long *)((char *)temp_s0_2 + (dptoli(lua_tonumber(arg0, 2)) * 8)));
    return 1;
}
