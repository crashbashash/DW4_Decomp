struct T { char pad[43]; unsigned char b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1; };
int FUN_0023e4c0();
int FUN_0023ec50();
int FUN_002467a0();
int lua_settop();
int *lua_touserdata();
int lua_pushusertag();
extern int DAT_004ea540[4];
int FUN_002406e0(int arg0) {
    int v;
    int *p;
    int s1;
    int *s0;
    p = lua_touserdata(arg0, -1);
    s1 = p[3];
    s0 = (int *)p[7];
    v = FUN_0023e4c0(p, arg0, ((struct T *)p)->b4 ? 2 : 1, -2);
    if (v != 0) {
        if ((int)p != v) {
            lua_settop(arg0, -2);
            lua_pushusertag(arg0, v, 0);
        }
        return FUN_0023ec50(v, arg0);
    }
    FUN_002467a0(&DAT_004ea540[0], s0[3], s1);
    return 0;
}
