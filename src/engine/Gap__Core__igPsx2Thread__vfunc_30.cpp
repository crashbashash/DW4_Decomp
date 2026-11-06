struct R { int v; R() {} R(int x) { v = x; } R(const R &o) : v(o.v) {} };
extern "C" {
int CreateThread(...);
int _StartThread(...);
int memset(...);
int FUN_0032f7f0(...);
extern int DAT_004fb418[4];
extern int DAT_004fb410[4];
extern int DAT_0055c870[4];
}
class Sub { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual R v21(); virtual R v22(); virtual int v23(); };
class Obj;
class Mgr { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void v22(Obj *); virtual void v23(Obj *); };
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int v30(); char p4[20]; int w24; char p28[4]; int w32; int w36; int w40; char p44[4]; Sub *sub; char p52[4]; char f56; char f57; char p58[2]; int th; };
extern Mgr *DAT_005871d0[4];
struct TP { int w[12]; };
extern "C" void Gap__Core__igPsx2Thread__vfunc_30(int *out, Obj *o) {
    TP tp;
    R t1, t2, t3;
    if (o->w40 == 0) {
        { *out = DAT_004fb418[0]; return; }
    }
    if (o->v30() != 0) {
        { *out = DAT_004fb418[0]; return; }
    }
    o->f56 = 1;
    o->f57 = 0;
    memset(&tp, 0, 0x30);
    tp.w[1] = (int)&FUN_0032f7f0;
    tp.w[2] = o->w32;
    tp.w[3] = o->w36;
    tp.w[5] = o->w24 / 2;
    tp.w[4] = (int)&DAT_0055c870[0];
    DAT_005871d0[0]->v22(o);
    o->th = CreateThread(&tp);
    if (o->th < 0) {
        o->th = -1;
        { *out = DAT_004fb418[0]; return; }
    }
    if (o->sub->v23() != 0) {
        t1 = o->sub->v22();
    }
    t2 = o->sub->v21();
    o->th = _StartThread(o->th, o);
    if (o->th == -1) {
        DAT_005871d0[0]->v23(o);
        t3 = o->sub->v22();
        { *out = DAT_004fb418[0]; return; }
    }
    { *out = DAT_004fb410[0]; return; }
}
