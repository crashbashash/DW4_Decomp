class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int v88(); };
class A { public: int pad[3]; C *f12; int pad2[2]; int f24; };
extern "C" {
extern int DAT_005610a8[4];
extern int DAT_005610b8[4];
extern int DAT_005610c8[4];
extern int DAT_00586808[4];
extern int DAT_00586818[4];
extern int DAT_00586830[4];
extern int DAT_00586840[4];
extern int DAT_00586898[4];
int FUN_00162b50(A *arg0) {
    if (DAT_00586808[0] == arg0->f12->v88() || DAT_00586898[0] == arg0->f12->v88() || DAT_00586818[0] == arg0->f12->v88() || DAT_00586830[0] == arg0->f12->v88() || DAT_00586840[0] == arg0->f12->v88()) {
        return arg0->f24;
    }
    if (DAT_005610c8[0] == arg0->f12->v88()) {
        return 2;
    }
    if (DAT_005610b8[0] == arg0->f12->v88()) {
        return 3;
    }
    if (DAT_005610a8[0] == arg0->f12->v88()) {
        return 4;
    }
    return 0;
}
}
