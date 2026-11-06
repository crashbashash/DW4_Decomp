/* Dropped leading parameter: lua_touserdata takes (arg0, n). */
int __floatsidf();
int FUN_00230d80();
int FUN_002467a0();
int lua_type();
int lua_tonumber();
void *lua_touserdata();
int lua_pushnumber();
extern int DAT_004ea6b0[4];
int FUN_00242e70(int arg0) {
    void *temp_s0;
    void *temp_s0_2;

    temp_s0 = (void *)(lua_touserdata(arg0, -1));
    if (lua_type(arg0, 2) != 2) {
        FUN_002467a0(&DAT_004ea6b0[0], *(int *)((char *)(temp_s0) + 12));
        return 0;
    }
    temp_s0_2 = (void *)(lua_touserdata(arg0, 1));
    lua_pushnumber(arg0, __floatsidf(*(int *)((char *)temp_s0_2 + (FUN_00230d80(lua_tonumber(arg0, 2)) * 4))));
    return 1;
}
