char FUN_001002d0();
int dptoli();
int FUN_002467a0();
int lua_type();
int lua_tonumber();
void *lua_touserdata();
extern int DAT_004ea980[4];
extern int DAT_004ea9a0[4];
int FUN_002442e0(int arg0) {
    void *temp_s0;
    void *temp_s1;
    int temp_s0_2;

    temp_s0 = (void *)(lua_touserdata(arg0, -1));
    if (lua_type(arg0, 2) != 2) {
        FUN_002467a0(&DAT_004ea9a0[0], *(int *)((char *)(temp_s0) + 12));
        return 0;
    } else {
        temp_s1 = (void *)(lua_touserdata(arg0, 1));
        temp_s0_2 = dptoli(lua_tonumber(arg0, 2));
        if (lua_type(arg0, 3) != 2) {
            FUN_002467a0(&DAT_004ea980[0]);
            return 0;
        } else {
            *(char *)((char *)temp_s1 + temp_s0_2) = FUN_001002d0(0, lua_tonumber(arg0, 3));
        }
    }
    return 0;
}
