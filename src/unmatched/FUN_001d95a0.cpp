class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
struct E { int pad[3]; int f12; };
struct B { int pad[4]; E **arr; };
struct O { int vt; int pad[3]; B *b; };
extern "C" int FUN_001d95a0(O *arg0, int arg1, int *arg2) {
    int i;
    while ((i = *arg2) < ((VC *)arg0)->vX()) {
        E *e = arg0->b->arr[i];
        *arg2 += 1;
        if (e->f12 == arg1) {
            return *arg2 - 1;
        }
    }
    return -1;
}
