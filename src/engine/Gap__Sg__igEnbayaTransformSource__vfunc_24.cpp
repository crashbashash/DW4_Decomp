extern "C" {
struct EB;
int Gap__Sg__igEnbayaTransformSource__vfunc_24(void *arg0, int a1, int a2, int a3, int a4);
}
class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int, int, int, int, int); };
struct EB { int pad[2]; int f8; VA *obj; };
int Gap__Sg__igEnbayaTransformSource__vfunc_24(void *arg0, int a1, int a2, int a3, int a4) {
    EB *p = (EB *)arg0;
    p->obj->vX(a1, a2, a3, a4, p->f8);
    return 1;
}
