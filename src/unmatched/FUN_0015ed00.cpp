struct Rc { int w0; int refs; };
extern "C" {
void *FUN_0014b680(...);
int FUN_0015dbc0(...);
int FUN_0015e7b0(...);
int FUN_00164e90(...);
int Memory_FreeBuffer(...);
int igObject_GetAllocator(...);
extern int DAT_0055fa90[4];
}
extern "C" int igObject_Destroy(...);
struct RcRef {
    Rc *p;
    RcRef &operator=(const RcRef &other) {
        Rc *next = other.p;
        Rc *o;
        if (next != 0) next->refs = next->refs + 1;
        if ((o = p) != 0) {
            o->refs = o->refs - 1;
            if ((o->refs & 0x7fffff) == 0) igObject_Destroy(o);
        }
        p = next;
        return *this;
    }
};
class V { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual int v17(int); virtual int v18(int); virtual void d19(); virtual void d20(); virtual void d21(); virtual int v22(int, unsigned int, int, int); virtual int v23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual int v45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual int v59();
 int refs; int f8; unsigned int f12; char p16[8]; RcRef f24; int f28; int f32; int f36; int f40;
};
struct VRef {
    V *p;
    VRef(V *object) : p(object) {}
    ~VRef() {
        V *o;
        if ((o = p) != 0) {
            o->refs = o->refs - 1;
            if ((o->refs & 0x7fffff) == 0) igObject_Destroy(o);
        }
    }
};
extern "C" int FUN_0015ed00(V *arg0, int arg1, unsigned int arg2, int arg3, int arg4) {
    VRef resized((V *)FUN_0014b680(igObject_GetAllocator()));
    unsigned int n;
    int sp88;
    int r;
    unsigned int i;
    resized.p->f24 = arg0->f24;
    r = resized.p->v22(arg1, arg2, arg3, arg4);
    n = arg0->f12;
    n = (n < arg2) ? n : arg2;
    FUN_00164e90(&sp88, arg1, arg0->v23());
    for (i = 0; i < n; i++) {
        FUN_0015dbc0(resized.p, i, arg0, i, &sp88);
    }
    resized.p->v45();
    resized.p->v17(DAT_0055fa90[0]);
    arg0->v17(DAT_0055fa90[0]);
    FUN_0015e7b0(arg0);
    Memory_FreeBuffer(arg0->f8);
    arg0->f12 = arg2;
    arg0->f8 = resized.p->f8;
    arg0->f32 = resized.p->f32;
    arg0->f36 = resized.p->f36;
    arg0->f40 = resized.p->f40;
    arg0->f28 = resized.p->f28;
    arg0->f24 = resized.p->f24;
    resized.p->f12 = 0;
    resized.p->f8 = 0;
    resized.p->f32 = 0;
    resized.p->f36 = 0;
    resized.p->f40 = 0;
    resized.p->f28 = 0;
    arg0->v18(DAT_0055fa90[0]);
    arg0->v59();
    return r;
}
