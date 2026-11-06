/* C++ unit with typed vtable dummies (slots 100 and 200); fields reloaded for every call; default
 * compiler */
struct Q { virtual void q0(); virtual void q1(); virtual void q2(); virtual void q3(); virtual void q4(); virtual void q5(); virtual void q6(); virtual void q7(); virtual void q8(); virtual void q9(); virtual void q10(); virtual void q11(); virtual void q12(); virtual void q13(); virtual void q14(); virtual void q15(); virtual void q16(); virtual void q17(); virtual void q18(); virtual void q19(); virtual void q20(); virtual void q21(); virtual void q22(); virtual int v23(); };
struct Lst { char p[8]; int cap; };
struct Ev { virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9(); virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15(); virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19(); virtual void e20(); virtual void e21(); virtual void e22(); virtual void e23(); virtual void e24(); virtual void e25(); virtual void e26(); virtual void e27(); virtual void e28(); virtual void e29(); virtual void e30(); virtual void e31(); virtual void e32(); virtual void e33(); virtual void e34(); virtual void e35(); virtual void e36(); virtual void e37(); virtual void e38(); virtual void e39(); virtual void e40(); virtual void e41(); virtual void e42(); virtual void e43(); virtual void e44(); virtual void e45(); virtual void e46(); virtual void e47(); virtual void v48(int);
  char p0[32]; int f36; char p1[12]; int f52; int f56; int f60; int f64; int f68; int f72; int f76; Lst *f80; int f84; int f88; Q *f92; };
extern "C" {
int FUN_002d38d0(int, int);
int FUN_002d38e0(int, int);
int FUN_002d38f0(int);
int FUN_002dca90(void);
int FUN_002dcaa0(Ev *, int);
int FUN_002eb090(int, int);
int FUN_002eb0a0(int, int);
int FUN_002eb0b0(int);
int FUN_0030cf20(int, int);
int FUN_0030cf30(int, int);
int FUN_0030cf40(int);
int List_Reserve(Lst *, int, int);
void Gap__Core__igEventTracker__vfunc_23(Ev *arg0) {
    int n;
    FUN_0030cf20(arg0->f52, 0x100);
    FUN_0030cf30(arg0->f52, 0x20);
    FUN_0030cf40(arg0->f52);
    FUN_0030cf20(arg0->f56, 0x1000);
    FUN_0030cf30(arg0->f56, 0x100);
    FUN_0030cf40(arg0->f56);
    FUN_0030cf20(arg0->f68, 0x200);
    FUN_0030cf30(arg0->f68, 0x20);
    FUN_0030cf40(arg0->f68);
    FUN_0030cf20(arg0->f64, 0x10000);
    FUN_0030cf30(arg0->f64, 0x1000);
    FUN_0030cf40(arg0->f64);
    FUN_0030cf20(arg0->f68, 0x2000);
    FUN_0030cf30(arg0->f68, 0x100);
    FUN_0030cf40(arg0->f68);
    FUN_002d38d0(arg0->f72, 0x10000);
    FUN_002d38e0(arg0->f72, 0x1000);
    FUN_002d38f0(arg0->f72);
    if (arg0->f92->v23() != 0) {
        FUN_002eb090(arg0->f76, 0x4000);
        FUN_002eb0a0(arg0->f76, 0x4000);
        FUN_002eb0b0(arg0->f76);
    }
    n = arg0->f36 * 0x14;
    if (n >= arg0->f80->cap) {
        List_Reserve(arg0->f80, n, 1);
    }
    arg0->v48(arg0->f36 * 2);
    FUN_002dca90();
    arg0->f88 = (int)FUN_002dca90;
    FUN_002dcaa0(arg0, 1);
}
}
