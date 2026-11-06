void *FUN_0023f830();
int lua_pushvalue();
int lua_tostring();
int lua_pushusertag();
int lua_getglobals();
int lua_rawset();
extern int DAT_0056de88[4];
int FUN_002400a0(int arg0) {
    void *temp_v0;

    if (DAT_0056de88[0] != 0) {
        temp_v0 = (void *)(FUN_0023f830(DAT_0056de88[0], lua_tostring(arg0, 1)));
        if (temp_v0 != 0) {
            lua_pushusertag(arg0, temp_v0, 0);
            return ((int (*)())*(int *)((char *)(*(int *)((char *)(temp_v0) + 28)) + 68))(arg0);
        }
        goto block_4;
    }
block_4:
    lua_getglobals(arg0);
    lua_pushvalue(arg0, 1);
    lua_pushvalue(arg0, 3);
    lua_rawset(arg0, -3);
    return 0;
}
