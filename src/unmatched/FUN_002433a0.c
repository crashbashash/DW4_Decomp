struct P { int pad[3]; int f12; };
long long __fixdfdi(int);
int dptoli(int);
int FUN_002467a0();
int lua_type(int, int);
int lua_tonumber(int, int);
struct P *lua_touserdata(int, int);
extern char DAT_004ea6b0[];
extern char DAT_004ea6d0[];
int FUN_002433a0(int arg0) {
    struct P *temp_s0;
    char *temp_s1;
    int temp_s0_2;
    temp_s0 = lua_touserdata(arg0, -1);
    if (lua_type(arg0, 2) != 2) {
        FUN_002467a0(DAT_004ea6b0, temp_s0->f12);
        return 0;
    }
    temp_s1 = (char *)lua_touserdata(arg0, 1);
    temp_s0_2 = dptoli(lua_tonumber(arg0, 2));
    if (lua_type(arg0, 3) != 2) {
        FUN_002467a0(DAT_004ea6d0);
        return 0;
    }
    *(long long *)(temp_s1 + (temp_s0_2 * 8)) = __fixdfdi(lua_tonumber(arg0, 3));
    return 0;
}
