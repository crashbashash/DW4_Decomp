int lua_pushusertag();
int lua_settagmethod();
int lua_pushcclosure();

void FUN_00241f70(int arg0, int arg1, int arg2, int arg3, int arg4) {
    lua_pushusertag(arg0, arg1, 0);
    lua_pushcclosure(arg0, arg3, 1);
    lua_settagmethod(arg0, arg2, arg4);
}
