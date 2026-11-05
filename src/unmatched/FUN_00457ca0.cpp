extern "C" int igObject_Destroy(...);
struct R { int w0; int refs; };
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void v92(); virtual void v96(); int w4; R *r; };
extern "C" void FUN_00457ca0(O *arg0, R *arg1) {
    R *old;
    R *a;

    old = arg0->r;
    if (old != arg1) {
        if (old != 0) {
            arg0->v96();
        }
        if (arg1 != 0) {
            arg1->refs = arg1->refs + 1;
        }
        a = arg0->r;
        if (a != 0) {
            a->refs = a->refs - 1;
            if ((a->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
        arg0->r = arg1;
        if (arg0->r != 0) {
            arg0->v92();
        }
    }
}
