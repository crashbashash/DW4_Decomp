extern "C" {
int FUN_001b1030(int, void *);
int FUN_001b1100(int, void *);
int FUN_001ce640(int, int);
int FUN_001dca40(void *, void *);
int FUN_001356b0();
}
class V140 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void vX(); };
class V128 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vY(int); };
struct LA { char p0[8]; int count; int p1; int *data; };
struct LB { char p0[8]; int cap; int p1; V128 **data; int count; };
struct G { char p0[8]; int f8; };
struct Src : V140 { char p0[24]; LA *list; };
struct Dst { char p0[52]; int f52; char p1[16]; LB *l72; };
extern "C" G *DAT_00561918[4];
extern "C" int FUN_001b8cf0(Dst *, int);
extern "C" int FUN_001b8de0(Dst *arg0, Src *arg1);
int FUN_001b8de0(Dst *arg0, Src *arg1) {
    int s4, n, i;
    arg1->vX();
    s4 = arg0->f52;
    n = arg1->list->count;
    for (i = 0; i < n; i++) {
        int a = FUN_001ce640(arg1->list->data[i], 0);
        LB *lb = arg0->l72;
        int b = a + DAT_00561918[0]->f8;
        V128 *o;
        if (lb->count >= lb->cap) FUN_001dca40(lb, (void *)&FUN_001356b0);
        o = lb->data[lb->count++];
        o->vY(b);
        FUN_001b1030(s4, o);
        FUN_001b8cf0(arg0, a);
        FUN_001b1100(s4, o);
    }
    return 0;
}
