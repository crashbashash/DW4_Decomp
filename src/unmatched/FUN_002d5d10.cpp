extern "C" {
int sscanf(int, void *, int *);
extern int DAT_004f95e8[4];
extern int DAT_004f95f0[4];
int FUN_002d5d10(int *arg0, int arg1, int arg2, int arg3);
}
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int *vX(); };
class B { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void vX(int, int, int); };
struct Q { int p0; int p1; int count; int p3; B **data; };
int FUN_002d5d10(int *arg0, int arg1, int arg2, int arg3) {
    int b;
    int a;
    Q *q;
    int i;

    a = 0;
    sscanf(arg2, &DAT_004f95e8[0], &a);
    q = (Q *)((A *)arg0)->vX()[13];
    for (i = 0; i < q->count; i++) {
        B *o = q->data[i];
        o->vX(arg1 + ((int *)o)[2], arg2 + a, arg3);
    }
    sscanf(arg2, &DAT_004f95f0[0], &b);
    return a + b;
}
