class EV { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int); };
extern "C" {
unsigned char FUN_0016cb40(int, int);
struct L { char pad[8]; int n; char pad2[4]; EV **d; };
struct T { char pad[16]; int f16; L *f20; int f24; unsigned char f28; };
unsigned char FUN_0013e6e0(T *, int);
void Gap__Attrs__igGeometrySetAttr__vfunc_24(T *arg0, int arg1) {
    int r;
    EV **p;
    EV **e;
    r = 0;
    if (arg0->f24 != 0) {
        if (arg0->f16 == -1) {
            r = FUN_0013e6e0(arg0, arg1);
        }
        if (arg0->f16 >= 0 && arg0->f28 != 0) {
            r = FUN_0016cb40(arg1, arg0->f16);
        }
    }
    if (r == 0 && arg0->f28 != 0) {
        p = arg0->f20->d;
        e = p + arg0->f20->n;
        for (; p < e; p++) {
            (*p)->vX(arg1);
        }
    }
}
}
