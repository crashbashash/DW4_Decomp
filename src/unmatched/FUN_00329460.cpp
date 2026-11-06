struct R { int v; R() {} R(int x) { v = x; } R(const R &o) : v(o.v) {} };
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual int v17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual R v25(int, int, int); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual int v40(int); virtual R v41(int, int); };
extern "C" {
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
R FUN_00329460(C *arg1, int arg2, int arg3) {
    int r17 = arg1->v17();
    if (r17 == arg2 + arg3) {
        int t = arg1->v40(-arg3);
        if (t != -1) {
            arg1->v25(0, t, arg3);
            return R(DAT_004fb410[0]);
        }
    } else {
        return arg1->v41(arg2, arg3);
    }
    return R(DAT_004fb418[0]);
}
}
