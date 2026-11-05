int FUN_00100290();
int FUN_00230d80();
int FUN_002467a0();
int lua_type();
int lua_tonumber();
void *lua_touserdata();
int lua_pushnumber();
extern int DAT_004ea6b0[4];
int FUN_00243770(int arg0) {
    void *temp_s0;
    void *temp_s0_2;
    temp_s0 = (void *)(lua_touserdata(arg0, -1));
    if (lua_type(arg0, 2) != 2) {
        FUN_002467a0(&DAT_004ea6b0[0], *(int *)((char *)(temp_s0) + 12));
        return 0;
    }
    temp_s0_2 = (void *)(lua_touserdata(arg0, 1));
    lua_pushnumber(arg0, FUN_00100290(*(unsigned char *)((char *)temp_s0_2 + FUN_00230d80(lua_tonumber(arg0, 2)))));
    return 1;
}
