class T { public: virtual void d(); int references; };
class R { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void vX(int); };
struct A { char p[12]; T *f12; };
extern "C" {
T *FUN_001341b0(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
void Gap__Core__igSetRenderDestinationAttr__vfunc_26(A *arg0, int arg1);
}
void Gap__Core__igSetRenderDestinationAttr__vfunc_26(A *arg0, int arg1) {
    T * volatile sp4C;
    T *s0;
    T *a0;
    T *x;
    T *y;
    if (arg0->f12 == 0) {
        sp4C = FUN_001341b0(igObject_GetAllocator());
        s0 = sp4C;
        if (s0 != 0) {
            s0->references = s0->references + 1;
        }
        a0 = arg0->f12;
        if (a0 != 0) {
            a0->references = a0->references - 1;
            if (((unsigned long long)((long long)a0->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a0);
            }
        }
        arg0->f12 = s0;
        x = sp4C;
        if (x != 0) {
            x->references = x->references - 1;
            y = sp4C;
            if (((unsigned long long)((long long)y->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(y);
            }
        }
    }
    ((R *)arg0->f12)->vX(arg1);
}
