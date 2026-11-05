extern "C" {
struct R { char pad[4]; int f4; char pad2[12]; int f14; char pad3[4]; unsigned char f1c; };
struct Ent { int f0; R *f4; int f8; int fc; int f10; int f14; };
struct Tab { char pad[16]; Ent *f10; };
struct A { char pad[328]; Tab *f148; char pad2[1136]; unsigned char f5bc; };
void **FUN_00165cf0(...);
int FUN_0016aea0(...);
int FUN_001ea420(...);
int FUN_001f05a0(...);
int FUN_0020b270(...);
int igObject_Destroy(...);
void FUN_0016af30(A *arg0, int arg1, R *arg2);
}
class VC_220 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52();  virtual int vX(int, int); };
void FUN_0016af30(A *arg0, int arg1, R *arg2) {
    Ent *e;
    int n;
    R *t;
    void **o;
    e = &arg0->f148->f10[arg1];
    if (arg2 != 0) {
        arg2->f4 = arg2->f4 + 1;
    }
    t = e->f4;
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    e->f4 = arg2;
    e->f14 = 0;
    n = 256;
    if (arg0->f5bc != 0 && e->f0 < 17) {
        e->fc = 0;
        n = 16;
    }
    if (e->f10 != 0 && e->f8 != 0) {
        FUN_001f05a0(2, FUN_0020b270(FUN_001ea420(e->f8)));
    } else if (e->f10 == 0) {
        o = FUN_00165cf0(arg0);
        e->f10 = ((VC_220 *)o)->vX(n * 4, 128);
    }
    if (e->f10 != 0) {
        arg2->f1c = 1;
        FUN_0016aea0(arg0, e->fc, e->f10, arg2->f14);
    }
}
