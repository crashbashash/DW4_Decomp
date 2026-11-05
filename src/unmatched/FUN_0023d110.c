typedef struct B {
    signed char type;
    signed char s0:2;
    unsigned char c:1;
    unsigned char u3:2;
    unsigned char d:1;
    unsigned char e:1;
    unsigned char f:1;
    short flags;
} B;
int FUN_0023cd40(B *, int, int, int *);
int FUN_00244a50(int, int);
int lua_settop(int, int);
int lua_type(int, int);
int lua_tag(int, int);
int lua_touserdata(int, int);
int lua_rawgeti(int, int, int);
int lua_getn(int, int);
int FUN_0023d110(B *b, int L, int idx, int *out) {
    int t, t2, y, x, z;
    *out = 0;
    t = lua_type(L, idx);
    if (!(b->flags & (1 << t))) return 0;
    if (t == 4) {
        if (FUN_00244a50(L, idx) != 0) return b->e;
        if (b->d != 0) {
            if (lua_getn(L, idx) == 0) return 1;
            lua_rawgeti(L, idx, 1);
            t2 = lua_type(L, -1);
            if (!(b->flags & (1 << t2))) {
                lua_settop(L, -2);
                return 0;
            }
            if (t2 == 0) {
                x = lua_tag(L, -1);
                y = lua_touserdata(L, -1);
                lua_settop(L, -2);
                return FUN_0023cd40(b, x, y, out);
            }
            if (t2 == 4) {
                z = FUN_00244a50(L, -1);
                lua_settop(L, -2);
                return z != 0;
            }
            lua_settop(L, -2);
            return 1;
        }
        return 0;
    } else if (t == 0) {
        y = lua_touserdata(L, idx);
        return FUN_0023cd40(b, lua_tag(L, idx), y, out);
    } else {
        return 1;
    }
}
