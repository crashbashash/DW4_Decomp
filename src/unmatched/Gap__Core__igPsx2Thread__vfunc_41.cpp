struct R { int v; R(int x) { v = x; } R() {} };
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int v100(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual R v124(); virtual void d30(); virtual R v132(int); };
struct O { char p[48]; C *c; int f52; };
extern "C" {
extern int DAT_004fb418[4];
R Gap__Core__igPsx2Thread__vfunc_41(O *arg1, int arg2, int *arg3);
}
R Gap__Core__igPsx2Thread__vfunc_41(O *arg1, int arg2, int *arg3) {
    if (arg1->c->v100() == 0) {
        return R(DAT_004fb418[0]);
    }
    R t = arg1->c->v132(arg2);
    if (t.v != DAT_004fb418[0]) {
        arg1->c->v124();
        *arg3 = arg1->f52;
    }
    return t;
}
