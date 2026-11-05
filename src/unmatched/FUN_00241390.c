/* 0x00241390 - FUN_00241390. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
int lua_remove();
void *lua_touserdata();
void FUN_00241390(int arg0) {
    void *temp_s0;
    temp_s0 = (void *)(lua_touserdata(arg0, -1));
    lua_remove(arg0, 2);
    lua_remove(arg0, 2);
    ((int (*)())*(int *)((char *)(temp_s0) + 32))(arg0);
}
