int FUN_002407c0();
int FUN_00240900();
int FUN_00240fd0();
int FUN_00244a50();
int lua_type();
int lua_tostring();
int lua_touserdata();

void FUN_00240990(int arg0) {
    int temp_s0;

    if (FUN_00244a50(arg0, 1) != 0) {
        FUN_00240fd0(arg0);
        return;
    }
    if (lua_type(arg0, 2) == 3) {
        temp_s0 = lua_touserdata(arg0, -1);
        FUN_002407c0(arg0, temp_s0, lua_tostring(arg0, 2));
        return;
    }
    FUN_00240900(arg0, lua_touserdata(arg0, -1));
}
