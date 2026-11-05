typedef struct T { char pad12[12]; int fc; } T;
int FUN_001005f0();
int *FUN_001006d0();
int sprintf();
int strlen();
int FUN_002467a0();
int lua_settop();
int lua_pushvalue();
int lua_type();
int (*lua_tocfunction(int, int))(int);
T *lua_touserdata();
int lua_pushstring();
int lua_rawget();
int lua_getglobals();
int lua_rawset();
extern int DAT_004ea630[4];
extern int DAT_004ea660[4];
extern int DAT_004ea840[4];
extern int DAT_004ea880[4];
extern int DAT_004ea8e0[4];
int FUN_00244ad0(int arg0) {
    int (*var_s0)(int);
    int *temp_v0_2;
    T *temp_v0;

    if (lua_type(arg0, 1) != 4) {
        FUN_002467a0(&DAT_004ea840[0]);
    }
    do {
        lua_pushstring(arg0, &DAT_004ea630[0]);
        lua_rawget(arg0, -2);
    } while (lua_type(arg0, -1) == 4);
    temp_v0 = lua_touserdata(arg0, -1);
    if (temp_v0 == 0) {
        FUN_002467a0(&DAT_004ea880[0]);
        return 0;
    }
    temp_v0_2 = (int *)(FUN_001006d0(strlen(temp_v0->fc) + 5));
    sprintf(temp_v0_2, &DAT_004ea660[0], temp_v0->fc);
    lua_getglobals(arg0);
    lua_pushstring(arg0, temp_v0_2);
    lua_rawget(arg0, -2);
    var_s0 = (int (*)(int))(lua_tocfunction(arg0, -1));
    FUN_001005f0(temp_v0_2);
    if (var_s0 == 0) {
        lua_settop(arg0, -2);
        lua_pushstring(arg0, temp_v0->fc);
        lua_rawget(arg0, -2);
        var_s0 = (int (*)(int))(lua_tocfunction(arg0, -1));
        if (var_s0 == 0) {
            FUN_002467a0(&DAT_004ea8e0[0], temp_v0->fc);
            return 0;
        }
        goto block_9;
    }
block_9:
    var_s0(arg0);
    lua_pushstring(arg0, &DAT_004ea630[0]);
    lua_pushvalue(arg0, 1);
    lua_rawset(arg0, -3);
    return 1;
}
