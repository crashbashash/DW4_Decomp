typedef struct N { char pad24[24]; struct N *f18; char pad28[4]; struct N *f20; } N;
int lua_pushvalue();
int lua_pushusertag();
int lua_settagmethod();
int lua_pushcclosure();
extern int DAT_00498680[4];
int FUN_002412a0();

void FUN_0023ee00(int arg0, int *arg1, int arg2, int arg3) {
    int *temp_s1;
    N *var_s1;

    lua_pushusertag(arg0, arg2, 0);
    lua_pushcclosure(arg0, &FUN_002412a0, 1);
    lua_pushvalue(arg0, -1);
    temp_s1 = &DAT_00498680[arg3];
    lua_settagmethod(arg0, arg1[10], *temp_s1);
    lua_settagmethod(arg0, arg1[11], *temp_s1);
    for (var_s1 = ((N *)arg1)->f18; var_s1 != 0; var_s1 = var_s1->f20) {
        FUN_0023ee00(arg0, (int *)var_s1, arg2, arg3);
    }
}
