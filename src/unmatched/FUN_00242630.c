int dptoli();
int FUN_002467a0();
int lua_type();
int lua_tonumber();
void *lua_touserdata();
extern int DAT_004ea6b0[4];
extern int DAT_004ea6d0[4];
int FUN_00242630(int arg0) {
    void *temp_s0;
    void *temp_s1;
    int temp_s0_2;

    temp_s0 = (void *)(lua_touserdata(arg0, -1));
    if (lua_type(arg0, 2) != 2) {
        FUN_002467a0(&DAT_004ea6b0[0], *(int *)((char *)(temp_s0) + 12));
        return 0;
    } else {
        temp_s1 = (void *)(lua_touserdata(arg0, 1));
        temp_s0_2 = dptoli(lua_tonumber(arg0, 2));
        if (lua_type(arg0, 3) != 2) {
            FUN_002467a0(&DAT_004ea6d0[0]);
            return 0;
        } else {
            *(char *)((int)temp_s1 + temp_s0_2) = dptoli(lua_tonumber(arg0, 3));
        }
    }
    return 0;
}
