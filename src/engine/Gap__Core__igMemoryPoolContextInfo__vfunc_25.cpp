struct R { int f0; int f4; };
struct G { char pad[56]; int f38; };
struct Res {
    int v;
    Res() {}
    Res(const Res &o) { v = o.v; }
    bool operator==(const Res &o) const { return v == o.v; }
};
class Dev {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual Res get(int, int);
};
extern "C" {
extern Res DAT_004fb418[4];
extern Res DAT_004fb410[4];
extern char *DAT_004c2228[4];
extern G *DAT_00586dc8[4];
int FUN_00306360(int, char *, int);
void igObject_Destroy(void *);
}
#define REL2(p) { R *t = p; if (t) { t->f4 = t->f4 - 1; if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) igObject_Destroy(t); } }

extern "C" int Gap__Core__igMemoryPoolContextInfo__vfunc_25(Res *arg0, Dev *arg1, int arg2, char *arg3) {
    R *volatile sp4C;
    int temp_v0;
    char *var_a1;
    sp4C = 0;

    if (arg2 == 0) {
        arg2 = DAT_00586dc8[0]->f38;
    }
    if (arg2 == 0) {
        *arg0 = DAT_004fb418[0];
        REL2(sp4C);
        return 0;
    }
    if ((arg3 == 0) || (var_a1 = arg3, (*arg3 == 0))) {
        arg3 = DAT_004c2228[0];
        var_a1 = arg3;
    }
    temp_v0 = FUN_00306360(arg2, var_a1, 0);
    if (temp_v0 == -1) {
        *arg0 = DAT_004fb418[0];
        REL2(sp4C);
        return 0;
    }
    Res &sp48 = *(Res *)&arg1->get(arg2, temp_v0);
    int ok = DAT_004fb410[0].v;
    if (sp48 == DAT_004fb410[0]) {
        arg0->v = ok;
        REL2(sp4C);
        return 0;
    }
    *arg0 = DAT_004fb418[0];
    REL2(sp4C);
    return 0;
}
