int lua_remove();
void *lua_touserdata();
void FUN_00241390(int arg0) {
    void *temp_s0;
    temp_s0 = (void *)(lua_touserdata(arg0, -1));
    lua_remove(arg0, 2);
    lua_remove(arg0, 2);
    ((int (*)())*(int *)((char *)(temp_s0) + 32))(arg0);
}
