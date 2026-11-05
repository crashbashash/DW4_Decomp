extern "C" {
void *FUN_0018a660(void *);
int FUN_0018ac80(void *, void *);
int FUN_00190060(void *, void *);
int igMatrix44f_SetIdentity(void *);
int igObject_IsKindOf(void *, int);
void *FUN_00301000(void *);
int igObject_Destroy(void *);
extern int DAT_00561230[4];
extern float GPR_0055490c;
extern float GPR_00554910;
}
struct Obj { int vt; int rc; float f8, f12, f16, f20, f24, f28; };
struct Ref {
    Obj *o;
    Ref(Obj *p) : o(p) {}
    ~Ref() {
        Obj *object = o;
        if (object) {
            --object->rc;
            if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
class Dev {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32();
    virtual void get(unsigned, void *);
    virtual void e1(); virtual void e2(); virtual void e3();
    virtual unsigned count();
};

extern "C" int FUN_001b2790(Obj *arg0, Dev *arg1) {
    if (igObject_IsKindOf(arg1, DAT_00561230[0]) != 0) {
        Ref a((Obj *)FUN_0018a660(FUN_00301000(arg0)));
        FUN_00190060(a.o, arg0);
        Ref b((Obj *)FUN_0018a660(FUN_00301000(arg0)));
        Obj *p = b.o;
        p->f8 = p->f12 = p->f16 = GPR_0055490c;
        p->f20 = p->f24 = p->f28 = GPR_00554910;
        unsigned n;
        unsigned i;
        n = arg1->count();
        char sp50[64];
        for (i = 0; i < n; i++) {
            igMatrix44f_SetIdentity(sp50);
            arg1->get(i, sp50);
            FUN_0018ac80(arg0, sp50);
            FUN_00190060(b.o, arg0);
            arg0->f8 = arg0->f12 = arg0->f16 = GPR_0055490c;
            arg0->f20 = arg0->f24 = arg0->f28 = GPR_00554910;
            FUN_00190060(arg0, a.o);
        }
        arg0->f8 = arg0->f12 = arg0->f16 = GPR_0055490c;
        arg0->f20 = arg0->f24 = arg0->f28 = GPR_00554910;
        FUN_00190060(arg0, b.o);
        return 1;
    }
    return 0;
}
