extern "C" {
struct T { int word0; int references; };
int igObject_Destroy(T *);
void **igObject_GetAllocator(...);
void **Memory_GetAllocatorBySelector(...);
T *FUN_0014db20(...);
T *FUN_0014df70(...);
T *FUN_0014fa50(...);
int memcpy(...);
int FUN_00154c90(...);
int FUN_00157200(...);
int FUN_00159320(...);
int FUN_0015ac10(...);
extern int DAT_005870e8[4];
extern unsigned char GPR_00554c14;
}
class V92a { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(void *, int); };
class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void *vX(int, int); };
struct S { char p0[8]; int f8, f12, f16, f20, f24, f28, f32, f36, f40, f44, f48; int f52; char p56[4]; char f60; char p61[3]; int f64; T *f68; int f72, f76; char p80[4]; int f84; };
static inline void release(T *object) {
    if (object != 0) {
        object->references = object->references - 1;
        if ((object->references & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}
struct TRef {
    T *p;
    TRef(T *object) : p(object) {}
    ~TRef() { release(p); }
};
extern "C" void FUN_001566c0(S *arg0, S *arg1, int arg2, int arg3, int arg4, int arg5) {
    TRef converted(0);
    TRef spare(FUN_0014db20(igObject_GetAllocator(arg0)));
    int spA4;
    int spA0;
    int sp9C;
    S *src;
    char *var_s5;
    int var_s4;
    int var_s3;
    if ((arg1->f84 + (arg1->f64 + (arg1->f72 + (arg1->f40 + (arg1->f36 + (arg1->f28 + arg1->f32)))))) & 7) {
        void **a = igObject_GetAllocator(arg0);
        release(converted.p);
        converted.p = FUN_0014df70(a);
        T *created = converted.p;
        if (!(FUN_00157200(created, FUN_0015ac10(arg1->f44), arg1) & 0xFF)) {
            return;
        }
        ((V92a *)arg0)->vX(converted.p, 0);
    } else {
        ((V92a *)arg0)->vX(arg1, 0);
    }
    {
        T *x = converted.p;
        src = arg1;
        if (x != 0) src = (S *)x;
    }
    arg0->f8 = arg4;
    arg0->f12 = arg5;
    FUN_00159320(arg0, arg0->f44, arg0->f8, arg0->f12, &spA4, &sp9C, &spA0);
    arg0->f48 = spA4;
    arg0->f16 = sp9C;
    arg0->f76 = spA0;
    {
        void **alloc = igObject_GetAllocator(arg0);
        void **v;
        if (GPR_00554c14 != 0) {
            v = alloc;
        } else {
            v = Memory_GetAllocatorBySelector(DAT_005870e8[0]);
        }
        arg0->f52 = (int)((VA *)v)->vX(arg0->f48, 0x80);
    }
    arg0->f60 = 1;
    var_s3 = 0;
    var_s5 = (char *)arg0->f52;
    var_s4 = src->f52 + arg3 * src->f76 + arg2 * ((src->f84 + (src->f64 + (src->f72 + (src->f40 + (src->f36 + (src->f28 + src->f32)))))) >> 3);
    while (var_s3 < arg5) {
        memcpy(var_s5, var_s4, arg0->f76);
        var_s3 += 1;
        var_s4 += src->f76;
        var_s5 += arg0->f76;
    }
    if (arg1->f68 != 0) {
        void **a2 = igObject_GetAllocator(arg0);
        release(arg0->f68);
        arg0->f68 = FUN_0014fa50(a2);
        FUN_00154c90(arg0->f68, arg1->f68, 1);
    }
    if ((arg1->f84 + (arg1->f64 + (arg1->f72 + (arg1->f40 + (arg1->f36 + (arg1->f28 + arg1->f32)))))) & 7) {
        FUN_00157200(arg0, arg1->f44, arg0);
    }
}
