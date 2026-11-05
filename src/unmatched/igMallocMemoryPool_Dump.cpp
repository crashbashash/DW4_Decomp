extern "C" {
int printf(int *);
void *FUN_002c4ca0(void *);
int FUN_00308390(int *, int);
int FUN_00322820(void *);
int FUN_00322860(void *);
int igObject_Destroy(void *);
void *igObject_GetAllocator(void *);
extern int DAT_004f92f0[4];
extern int DAT_004ff1b0[4];
extern int DAT_004ff1f0[4];
void igMallocMemoryPool_Dump(void *self, int a1, int a2, int a3, int t0);
}
struct P { int p0; int rc; };
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int v23(int, int *); virtual void v24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void v29(int *); };
struct M { char p[152]; int f152; };
struct Ref {
    V *p;
    Ref(V *q) { p = q; }
    ~Ref() { P *o; if ((o = (P *)p) != 0) { --o->rc; if ((o->rc & 0x7fffff) == 0) igObject_Destroy(o); } }
};
void igMallocMemoryPool_Dump(void *self, int a1, int a2, int a3, int t0) {
    int *g;
    FUN_00322820(self);
    g = &DAT_004ff1b0[0];
    if (t0 != 0) {
        Ref r((V *)FUN_002c4ca0(igObject_GetAllocator(self)));
        if (r.p->v23(t0, &DAT_004f92f0[0]) == 0) {
            if (((M *)self)->f152 >= 2) {
                FUN_00308390(&DAT_004ff1f0[0], t0);
            }
            FUN_00322860(self);
            return;
        }
        r.p->v29(g);
        r.p->v24();
    } else {
        printf(g);
    }
    FUN_00322860(self);
}
