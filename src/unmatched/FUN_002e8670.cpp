extern "C" {
void *FUN_002d7e90(...);
int FUN_002e7030(...);
int igObject_Destroy(...);
int igObject_IsKindOf(...);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern int DAT_00585b70[4];
extern int D_004fb418[4];
}
struct R { int w; R() {} };
struct T { char p0[8]; int count; char p12[4]; void **data; char p20[60]; int f80; int f84; int f88; char p92[8]; int f100; char p104[44]; int f148; char p152[28]; int f180; char p184[68]; int f252; char p256[4]; int f260; };
class E { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v128(T *); virtual void v132(T *); virtual void v136(T *); };
class EE : public E { public: int refs; };
struct Ref {
    EE *p;
    Ref(EE *o) : p(o) { if (p != 0) { p->refs = p->refs + 1; } }
    ~Ref() {
        EE *object = p;
        if (object) {
            --object->refs;
            if (((unsigned long long)(long long)object->refs & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
inline int load(T *t, int *fail) {
    R r;
    int *pp;
    FUN_002e7030(&r, t);
    pp = (int *)((int)&r + 0);
    *fail = D_004fb418[0];
    return *pp;
}
extern "C" void FUN_002e8670(int *arg0, T *arg1);
void FUN_002e8670(int *arg0, T *arg1) {
    int fail;
    int n;
    int i;

    arg1->f252 = arg1->f180;
    arg1->f80 = arg1->f260;
    arg1->f84 = 0;
    arg1->f88 = arg1->f148;
    int got = load(arg1, &fail);
    if (got == DAT_004fb418[0]) {
        *arg0 = fail;
        return;
    }
    n = arg1->count;
    for (i = 0; i < n; i++) {
        if (igObject_IsKindOf(arg1->data[i], DAT_00585b70[0]) != 0) {
            ((EE *)FUN_002d7e90(arg1, i))->v128(arg1);
        }
    }
    if (arg1->f100 < 4) {
        for (i = 0; i < n; i++) {
            if (igObject_IsKindOf(arg1->data[i], DAT_00585b70[0]) != 0) {
                ((EE *)FUN_002d7e90(arg1, i))->v132(arg1);
            }
        }
    } else {
        for (i = 0; i < n; i++) {
            if (igObject_IsKindOf(arg1->data[i], DAT_00585b70[0]) != 0) {
                Ref e((EE *)FUN_002d7e90(arg1, i));
                e.p->v136(arg1);
            }
        }
    }
    *arg0 = DAT_004fb410[0];
}
