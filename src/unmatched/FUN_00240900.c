int FUN_002467a0();
int lua_settop();
int lua_pushusertag();
extern int DAT_004ea5f0[4];
typedef struct E { char pad[32]; int (*fn)(int); } E;
typedef struct P { char pad[12]; int f12; char pad2[4]; struct P *next; char pad3[32]; E *e; } P;
int FUN_00240900(int arg0, P *arg1) {
    P *p;
    for (p = arg1; p != 0; p = p->next) {
        if (p->e != 0) {
            lua_settop(arg0, -2);
            lua_pushusertag(arg0, p->e, 0);
            return p->e->fn(arg0);
        }
    }
    FUN_002467a0(&DAT_004ea5f0[0], arg1->f12);
    return 0;
}
