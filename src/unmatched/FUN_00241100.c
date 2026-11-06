int FUN_00246760();
int *FUN_00246780();
int lua_settop();
int lua_pushvalue();
int lua_type();
int lua_pushstring();
int lua_rawget();
int lua_settable();
int lua_rawset();
void FUN_002410f0(void);
extern int DAT_004ea530[4];
extern unsigned char GPR_00554be0;

int FUN_00241100(int arg0) {
    int sp3C;
    int *temp_s0;

    lua_pushvalue(arg0, 2);
    lua_rawget(arg0, 1);
    if (lua_type(arg0, -1) == 1) {
        lua_settop(arg0, -2);
        lua_pushstring(arg0, &DAT_004ea530[0]);
        lua_rawget(arg0, 1);
        temp_s0 = (int *)(FUN_00246780(&sp3C));
        FUN_00246760(FUN_002410f0, arg0);
        GPR_00554be0 = 0;
        lua_pushvalue(arg0, 2);
        lua_pushvalue(arg0, 3);
        lua_settable(arg0, -3);
        FUN_00246760(temp_s0, sp3C);
        if (GPR_00554be0 == 0) {
            return 0;
        }
        goto block_4;
    }
block_4:
    lua_pushvalue(arg0, 2);
    lua_pushvalue(arg0, 3);
    lua_rawset(arg0, 1);
    return 0;
}
