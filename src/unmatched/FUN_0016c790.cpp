class VM { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void* v232(void*,int); };
struct Ent { int *list; };
extern "C" {
VM *Memory_FindBufferOwner(void *);
void *FUN_002ed450(void *, int, int);
void memset(void *, int, int);
int FUN_00165cc0(void *);
void *FUN_002ed240(int, int);
int FUN_002caa70(int);
}
struct Nd { int a; int b; Nd() { a = 0; b = 0; } static void *operator new(unsigned sz, int owner) { return FUN_002ed240(sz, owner); } };
struct T { unsigned short f0; unsigned short f2; unsigned short f4; short pad; int pad8; unsigned short *f12; Ent **f16; };
struct O { int w[240]; T *f960; char pad[4]; char f968; };
extern "C" int FUN_0016c790(O *arg0);
int FUN_0016c790(O *arg0) {
    int s0;
    int a1;
    T *s1 = arg0->f960;
    if (s1->f4 <= 0) {
        s1->f16 = (Ent **)FUN_002ed450(s1->f16, (s1->f0 + 4) * 4, 16);
        memset(s1->f16 + s1->f0, 0, 16);
        if (s1->f2 < 4) {
            VM *o = Memory_FindBufferOwner(s1);
            s1->f12 = (unsigned short *)o->v232(s1->f12, 8);
            s1->f2 = 4;
        }
        a1 = 0;
        do {
            int t = s1->f0; t += a1; s1->f12[a1] = t;
            a1++;
        } while (a1 < 4);
        s1->f4 = 4;
        s1->f0 += 4;
    }
    s0 = s1->f12[s1->f4 - 1];
    s1->f4 = s1->f4 - 1;
    {
        Nd *n = new (FUN_00165cc0(arg0)) Nd;
        int v = FUN_002caa70(FUN_00165cc0(arg0));
        arg0->f960->f16[s0] = (Ent *)n;
        n->a = v;
    }
    arg0->f968 = 0;
    return s0;
}
