/* 0x002407c0 — FUN_002407c0. Hand-retyped from the m2c draft, verified byte-identical to retail by tools/verify.py. */
int __floatsidf();
void *FUN_0023f830();
void *FUN_0023fb30();
int FUN_002467a0();
int lua_settop();
int lua_pushvalue();
int lua_type();
int lua_pushnumber();
int lua_pushusertag();
int lua_rawget();
int lua_getref();
extern int DAT_004ea5c0[4];
struct Vt { char p[72]; int (*f72)(int); };
struct Fn { char p0[28]; struct Vt *vt; };
struct Nd { char p0[20]; struct Nd *next; char p24[28]; int f52; };
int FUN_002407c0(int arg0, struct Nd *arg1, int arg2) {
    struct Nd *var_s1;
    struct Fn *temp_v0;
    char *temp_v0_2;

    for (var_s1 = arg1; var_s1 != 0; var_s1 = var_s1->next) {
        lua_getref(arg0, var_s1->f52);
        lua_pushvalue(arg0, 2);
        lua_rawget(arg0, -2);
        if (lua_type(arg0, -1) != 1) {
            return 1;
        }
        lua_settop(arg0, -3);
        temp_v0 = (struct Fn *)FUN_0023f830(var_s1, arg2);
        if (temp_v0 != 0) {
            lua_settop(arg0, -2);
            lua_pushusertag(arg0, temp_v0, 0);
            return temp_v0->vt->f72(arg0);
        }
    }
    temp_v0_2 = (char *)FUN_0023fb30(arg2, arg1);
    if (temp_v0_2 != 0) {
        lua_pushnumber(arg0, __floatsidf(*(int *)(temp_v0_2 + 20)));
        return 1;
    }
    FUN_002467a0(&DAT_004ea5c0[0], arg2, *(int *)((char *)arg1 + 12));
    return 0;
}
