struct Rc { int w0; int refs; };
extern "C" {
void *FUN_0014b680(...);
int FUN_0015dbc0(...);
int FUN_0015e7b0(...);
int FUN_00164e90(...);
int Memory_FreeBuffer(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_0055fa90[4];
}
class V { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual int v17(int); virtual int v18(int); virtual void d19(); virtual void d20(); virtual void d21(); virtual int v22(int, unsigned int, int, int); virtual int v23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual int v45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual int v59();
 char p4[4]; int f8; unsigned int f12; char p16[8]; Rc *f24; int f28; int f32; int f36; int f40;
};
extern "C" int FUN_0015ed00(V *arg0, int arg1, unsigned int arg2, int arg3, int arg4);
extern "C" int FUN_0015ed00(V *arg0, int arg1, unsigned int arg2, int arg3, int arg4) {
    V *volatile sp8C;
    unsigned int n;
    int sp88;
    int r;
    unsigned int i;
    Rc *a0;
    Rc **pp;
    Rc *s0;
    sp8C = (V *)FUN_0014b680(igObject_GetAllocator());
    pp = &sp8C->f24;
    s0 = arg0->f24;
    if (s0 != 0) {
        s0->refs = s0->refs + 1;
    }
    a0 = *pp;
    if (a0 != 0) {
        a0->refs = a0->refs - 1;
        if ((a0->refs & 0x7fffff) == 0) {
            igObject_Destroy(a0);
        }
    }
    *pp = s0;
    r = sp8C->v22(arg1, arg2, arg3, arg4);
    n = arg0->f12;
    n = (n < arg2) ? n : arg2;
    FUN_00164e90(&sp88, arg1, arg0->v23());
    for (i = 0; i < n; i++) {
        FUN_0015dbc0(sp8C, i, arg0, i, &sp88);
    }
    sp8C->v45();
    sp8C->v17(DAT_0055fa90[0]);
    arg0->v17(DAT_0055fa90[0]);
    FUN_0015e7b0(arg0);
    Memory_FreeBuffer(arg0->f8);
    arg0->f12 = arg2;
    arg0->f8 = sp8C->f8;
    arg0->f32 = sp8C->f32;
    arg0->f36 = sp8C->f36;
    arg0->f40 = sp8C->f40;
    arg0->f28 = sp8C->f28;
    s0 = sp8C->f24;
    if (s0 != 0) {
        s0->refs = s0->refs + 1;
    }
    a0 = arg0->f24;
    if (a0 != 0) {
        a0->refs = a0->refs - 1;
        if ((a0->refs & 0x7fffff) == 0) {
            igObject_Destroy(a0);
        }
    }
    arg0->f24 = s0;
    sp8C->f12 = 0;
    sp8C->f8 = 0;
    sp8C->f32 = 0;
    sp8C->f36 = 0;
    sp8C->f40 = 0;
    sp8C->f28 = 0;
    arg0->v18(DAT_0055fa90[0]);
    arg0->v59();
    a0 = (Rc *)sp8C;
    if (a0 != 0) {
        Rc *rr = a0;
        rr->refs = rr->refs - 1;
        if ((rr->refs & 0x7fffff) == 0) {
            igObject_Destroy(rr);
        }
    }
    return r;
}
