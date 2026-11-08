struct P { int pad[3]; int f12; };
struct P *lua_touserdata(int, int);
int lua_type(int, int);
int FUN_002467a0(void *, int);
int lua_tonumber(int, int);
int dptoli(int);
int litodp(int);
int lua_pushnumber(int, int);
extern char DAT_004ea6b0[];
int FUN_00242590(int arg0) {
    struct P *temp_s0;
    char *temp_s0_2;
    temp_s0 = lua_touserdata(arg0, -1);
    if (lua_type(arg0, 2) != 2) {
        FUN_002467a0(DAT_004ea6b0, temp_s0->f12);
        return 0;
    }
    temp_s0_2 = (char *)lua_touserdata(arg0, 1);
    lua_pushnumber(arg0, litodp(*(temp_s0_2 + dptoli(lua_tonumber(arg0, 2)))));
    return 1;
}
