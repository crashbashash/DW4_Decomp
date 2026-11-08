int dptoli();
int FUN_002467a0();
int lua_type();
long long lua_tonumber();
int *lua_touserdata();
extern int DAT_004ea6b0[4];
extern int DAT_004ea6d0[4];
int FUN_00243ba0(int arg0) {
    int *s0;
    long long *s1;
    int idx;

    s0 = lua_touserdata(arg0, -1);
    if (lua_type(arg0, 2) != 2) {
        FUN_002467a0(&DAT_004ea6b0[0], s0[3]);
        return 0;
    }
    s1 = (long long *)lua_touserdata(arg0, 1);
    idx = dptoli(lua_tonumber(arg0, 2));
    if (lua_type(arg0, 3) != 2) {
        FUN_002467a0(&DAT_004ea6d0[0]);
        return 0;
    }
    s1[idx] = lua_tonumber(arg0, 3);
    return 0;
}
