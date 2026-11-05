class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int v108(int, int, int); virtual void e26(); virtual void e27(); virtual int v120(int, int, int); };
struct S { char p0[20]; int f20; int f24; char p1[16]; unsigned char f44; unsigned char f45; char p2[6]; int f52; int f56; int f60; V *f64; };
extern "C" {
int memcpy(int, int, int);
int FUN_002ec570(S *, int);
int Gap__Core__igMediaFile__vfunc_29(S *arg0, int arg1, int arg2, int arg3);
int Gap__Core__igMediaFile__vfunc_29(S *arg0, int arg1, int arg2, int arg3) {
    int s0;
    if (arg0->f45 == 0) {
        return -1;
    }
    if (arg2 == 0) {
        return 0;
    }
    if (arg0->f44 == 1) {
        if (arg0->f20 == 6) {
            arg0->f64->v120(arg0->f24, 0, 2);
        }
        return arg0->f64->v108(arg0->f24, arg1, arg3 * arg2) / arg2;
    }
    s0 = arg2 * arg3;
    if (arg0->f20 == 2) {
        arg0->f56 = arg0->f52;
    }
    FUN_002ec570(arg0, arg0->f56 + s0);
    memcpy(arg0->f60 + arg0->f56, arg1, s0);
    arg0->f56 = arg0->f56 + s0;
    return s0 / arg2;
}
}
