class O;
extern "C" int igObject_Destroy(void *);
struct R { int w; };
class Z { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual R v22(O *); };
class Y { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual Z *v21(); };
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int v30(); virtual void e31(); virtual void e32(); virtual void e33(); virtual void e34(); virtual void e35(); virtual void e36(); virtual void e37(); virtual void e38(); virtual void e39(); virtual void e40(); virtual void e41(); virtual R v42(); int rc; };
struct Lst { char p[8]; int n; int pad; O **d; };
struct H { int vt; int f4; Lst *l; };
extern Y *DAT_005871d0[4];
extern "C" void FUN_00305000(H *h) {
    R sp58, sp5C;
    int n;
    O *p;
    int c;
    int k;
    Lst *l;
    int i;
    int m;
    O *o;
    int j;

    n = h->l->n;
    for (i = 0; i < n; i++) {
        o = h->l->d[i];
        if (o->v30()) {
            sp5C = o->v42();
        }
        if (o->v30()) {
            sp58 = DAT_005871d0[0]->v21()->v22(o);
        }
        o->rc = o->rc - 1;
        if (((unsigned long long)((long long)o->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    if (n > 0) {
        l = h->l;
        m = l->n;
        for (j = 0; j < m; j++) {
            p = l->d[j];
            if (p != 0) {
                p->rc = p->rc - 1;
                if (((unsigned long long)((long long)p->rc << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        c = l->n;
        for (k = 0; k < c; k++) {
            l->d[k] = 0;
        }
        l->n = 0;
    }
}
