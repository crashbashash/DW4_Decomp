extern char DAT_004ea530[];
int lua_settop();
int lua_pushvalue();
int lua_type();
int lua_pushstring();
int lua_gettable();
int lua_rawget();
extern int DAT_004ea630[4];
int FUN_00240fd0(int arg0) {
    lua_pushvalue(arg0, 2);
    lua_rawget(arg0, 1);
    if (lua_type(arg0, -1) != 1) {
        return 1;
    }
    lua_settop(arg0, -2);
    lua_pushvalue(arg0, 1);
loop_3:
    lua_pushstring(arg0, &DAT_004ea630[0]);
    lua_rawget(arg0, -2);
    if (lua_type(arg0, -1) == 4) {
        lua_pushvalue(arg0, 2);
        lua_rawget(arg0, -2);
        if (lua_type(arg0, -1) != 1) {
            return 1;
        }
        lua_settop(arg0, -2);
        goto loop_3;
    }
    lua_pushstring(arg0, (int *)DAT_004ea530);
    lua_rawget(arg0, 1);
    lua_pushvalue(arg0, 2);
    lua_gettable(arg0, -2);
    return 1;
}
