int FUN_0023c860();
int FUN_00240990();
int lua_settop();
int lua_insert();
int lua_tostring();
int lua_pushusertag();
int igObjectSystem_FindMetaByNameDefault();
extern int DAT_0056de88[4];
extern int DAT_00498670[4];

int FUN_0023ffd0(int arg0) {
    int temp_s1;
    int temp_v0;

    temp_s1 = lua_tostring(arg0, 1);
    if (DAT_0056de88[0] != 0) {
        lua_insert(arg0, 1);
        lua_pushusertag(arg0, DAT_0056de88[0], 0);
        return FUN_00240990(arg0);
    }
    temp_v0 = igObjectSystem_FindMetaByNameDefault(temp_s1);
    if (temp_v0 != 0) {
        FUN_0023c860(arg0, temp_s1, temp_v0, DAT_00498670[0]);
        lua_settop(arg0, 0);
        lua_pushusertag(arg0, temp_v0, DAT_00498670[0]);
        return 1;
    }
    return 0;
}
