typedef struct T { char pad[12]; int f12; } T;
int FUN_00230d80();
int FUN_002467a0();
int lua_type();
int lua_tonumber();
short *lua_touserdata();
extern int DAT_004ea6b0[4];
extern int DAT_004ea6d0[4];
int FUN_00242aa0(int arg0) {
    int temp_s0_2;
    T *temp_s0;
    short *temp_s1;

    temp_s0 = (T *)lua_touserdata(arg0, -1);
    if (lua_type(arg0, 2) != 2) {
        FUN_002467a0(&DAT_004ea6b0[0], temp_s0->f12);
        return 0;
    } else {
        temp_s1 = lua_touserdata(arg0, 1);
        temp_s0_2 = FUN_00230d80(lua_tonumber(arg0, 2));
        if (lua_type(arg0, 3) != 2) {
            FUN_002467a0(&DAT_004ea6d0[0]);
            return 0;
        } else {
            temp_s1[temp_s0_2] = FUN_00230d80(lua_tonumber(arg0, 3));
        }
    }
    return 0;
}
