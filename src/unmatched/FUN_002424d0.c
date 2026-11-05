/* 0x002424d0 - FUN_002424d0. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
int __floatsidf();
int FUN_002467a0();
void *lua_touserdata();
int lua_pushnumber();
extern int DAT_004ea670[4];
int FUN_002424d0(int arg0) {
    void *temp_v0;
    temp_v0 = (void *)(lua_touserdata(arg0, 1));
    if (temp_v0 == 0) {
        FUN_002467a0(&DAT_004ea670[0]);
        return 0;
    }
    lua_pushnumber(arg0, __floatsidf(*(int *)((char *)(temp_v0) + 48)));
    lua_pushnumber(arg0, __floatsidf(*(int *)((char *)(temp_v0) + 40)));
    lua_pushnumber(arg0, __floatsidf(*(int *)((char *)(temp_v0) + 44)));
    return 3;
}
