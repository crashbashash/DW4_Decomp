extern "C" {
int lua_dobuffer(...);
int luaM_realloc(...);
void *FUN_002c4ca0(...);
int igObject_Destroy(...);
extern int DAT_004eaab0[4];
int FUN_00246b30(int arg0, int arg1);
struct Ref { char pad0[4]; int f4; };
}
class DW4VC_100_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int, int *); };
class DW4VC_104_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
class DW4VC_108_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int); };
class DW4VC_152_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual int vX(int, int); };
class DW4VC_156_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int vX(); };
int FUN_00246b30(int arg0, int arg1) {
    void * volatile sp5C;
    volatile char sp58[4];
    int s0;
    int s1;
    Ref *t;
    int r;

    sp58[0] = 0;
    sp5C = FUN_002c4ca0(0);
    if (((DW4VC_100_2 *)sp5C)->vX(arg1, &DAT_004eaab0[0]) == 0) {
        t = (Ref *)sp5C;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if ((t->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
        return 2;
    }
    ((DW4VC_152_2 *)sp5C)->vX(0, 2);
    s0 = ((DW4VC_156_0 *)sp5C)->vX();
    s1 = luaM_realloc(arg0, 0, s0);
    if (s1 == 0) {
        ((DW4VC_104_0 *)sp5C)->vX();
        t = (Ref *)sp5C;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if ((t->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
        return 4;
    }
    ((DW4VC_152_2 *)sp5C)->vX(0, 0);
    ((DW4VC_108_3 *)sp5C)->vX(s1, s0, 1);
    ((DW4VC_104_0 *)sp5C)->vX();
    s0 = lua_dobuffer(arg0, s1, s0, arg1);
    luaM_realloc(arg0, s1, 0);
    t = (Ref *)sp5C;
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if ((t->f4 & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    return s0;
}
