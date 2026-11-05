struct X { char pad[4]; int f4; };
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual X *v84(int); };
extern "C" {
int igObject_Destroy(...);
int FUN_00301010(X **arg0, VC *arg1, int arg2);
}
int FUN_00301010(X **arg0, VC *arg1, int arg2) {
    X *volatile sp2C;
    X *t;
    sp2C = arg1->v84(arg2);
    t = sp2C;
    if (t != 0) {
        t->f4 = t->f4 + 1;
    }
    t = sp2C;
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    *arg0 = sp2C;
    t = *arg0;
    if (t != 0) {
        t->f4 = t->f4 + 1;
    }
    t = sp2C;
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    return 0;
}
