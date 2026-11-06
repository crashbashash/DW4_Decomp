extern "C" {
int FUN_001c5e20(...);
int igMetaObject_CountInstances(...);
int igObject_Destroy(...);
}
struct Ref { int w0; int rc; };
struct List { int w0; int w4; int count; int cap; Ref **data; };
class T { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();  virtual int vA(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();  virtual void vB();
    char pad[60]; List *f64; List *f68; };
extern "C" void FUN_001c1c60(T *arg0);
void FUN_001c1c60(T *arg0) {
    List *l;
    int n;
    int i;
    Ref *r;
    l = arg0->f64;
    n = l->count;
    for (i = 0; i < n; i++) {
        r = l->data[i];
        if (r != 0) {
            r->rc = r->rc - 1;
            if ((r->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(r);
            }
        }
    }
    n = l->count;
    for (i = 0; i < n; i++) {
        l->data[i] = 0;
    }
    l->count = 0;
    l = arg0->f68;
    n = l->count;
    for (i = 0; i < n; i++) {
        r = l->data[i];
        if (r != 0) {
            r->rc = r->rc - 1;
            if ((r->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(r);
            }
        }
    }
    n = l->count;
    for (i = 0; i < n; i++) {
        l->data[i] = 0;
    }
    l->count = 0;
    if (igMetaObject_CountInstances(arg0->vA(), 1) == 0) {
        arg0->vB();
    }
    FUN_001c5e20(arg0);
}
