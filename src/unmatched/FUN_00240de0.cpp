struct Meta { char p[28]; int f28; };
struct Ob { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual Meta *v20(); };
struct It { int b; int c; };
struct En { char p[12]; Meta *f12; int f16; };
extern int DAT_00498668[4];
extern int DAT_004ea5f0[4];
extern "C" {
int FUN_00240360(It *);
int FUN_00240370(It *, int);
int FUN_00240390(It *, int);
int FUN_00240420(int);
En *FUN_00240430(It *);
int FUN_00240440(It *, int);
int FUN_002404b0(Meta *, int);
int FUN_00240a40(int);
int FUN_00241100(int);
int FUN_00241210(int, int, Ob *, int, int);
int FUN_00244a50(int, int);
int FUN_002467a0(int *, int);
int lua_type(int, int);
int lua_tag(int, int);
int lua_tostring(int, int);
Ob *lua_touserdata(int, int);
int igMetaObject_FindFieldByName(Meta *, int);
int strcmp(int, int);
int FUN_00240de0(int arg0) {
    Ob *v0;
    Meta *s1;
    int s0, s4, v02, v04, s1v;
    En *e;
    It sp68;
    if (FUN_00244a50(arg0, 1) != 0) {
        return FUN_00241100(arg0);
    }
    s4 = lua_tag(arg0, 1);
    s0 = lua_type(arg0, 2);
    v0 = lua_touserdata(arg0, 1);
    s1 = v0->v20();
    if (s4 != DAT_00498668[0]) {
        if (s0 == 3) {
            v02 = lua_tostring(arg0, 2);
            FUN_00240440(&sp68, FUN_002404b0(s1, v02));
            while (FUN_00240360(&sp68) != 0) {
                e = FUN_00240430(&sp68);
                if (e->f12 == s1) {
                    if (strcmp(FUN_00240420(e->f16), v02) == 0) {
                        s1v = e->f16;
                        FUN_00240390(&sp68, -1);
                        goto out;
                    }
                }
                FUN_00240370(&sp68, 0);
            }
            FUN_00240390(&sp68, -1);
            s1v = 0;
out:
            FUN_00241210(arg0, s1v, v0, v02, 3);
            return 0;
        }
        return FUN_00240a40(arg0);
    }
    if (s0 == 3) {
        v04 = lua_tostring(arg0, 2);
        FUN_00241210(arg0, igMetaObject_FindFieldByName(s1, v04), v0, v04, 3);
    } else {
        FUN_002467a0(DAT_004ea5f0, s1->f28);
    }
    return 0;
}
}
