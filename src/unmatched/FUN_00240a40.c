void *FUN_0023f830();
int FUN_00241100();
int FUN_00244a50();
int FUN_002467a0();
int lua_settop();
int lua_type();
int lua_tostring();
void *lua_touserdata();
int lua_pushusertag();
extern int DAT_004ea5c0[4];
extern int DAT_004ea5f0[4];
typedef struct X { char pad28[28]; struct Y *f28; } X;
typedef struct Y { char pad32[32]; int (*f32)(int); char pad36[32]; int (*f68)(int); } Y;
typedef struct N { char pad12[12]; int f12; char pad16[4]; struct N *next; char pad24[36]; Y *f60; } N;
int FUN_00240a40(int L) {
    int t;
    N *s;
    X *x;
    int v;
    N *r;
    if (FUN_00244a50(L, 1) != 0) {
        return FUN_00241100(L);
    }
    t = lua_type(L, 2);
    if (t == 3) {
        v = lua_tostring(L, 2);
    } else {
        v = 0;
    }
    s = lua_touserdata(L, -1);
    for (; s != 0; s = s->next) {
        if (v != 0) {
            x = FUN_0023f830(s, v);
            if (x != 0) {
                lua_settop(L, -2);
                lua_pushusertag(L, x, 0);
                return x->f28->f68(L);
            }
        } else if (s->f60 != 0) {
            lua_settop(L, -2);
            lua_pushusertag(L, s->f60, 0);
            return s->f60->f32(L);
        }
    }
    r = lua_touserdata(L, -1);
    if (t == 3) {
        FUN_002467a0(DAT_004ea5c0, v, r->f12);
    } else {
        FUN_002467a0(DAT_004ea5f0, r->f12);
    }
    return 0;
}
