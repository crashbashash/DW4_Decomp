extern "C" {
int FUN_002d7da0(...);
void *Memory_GetAllocatorBySelector(...);
int igObject_Destroy(...);
}
class Alloc { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int v216(int); virtual int v220(int, int); };
class Fld { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int v108(); };
struct Lst { char p[4]; int refs; char p8[8]; int *data; };
struct Lst2 { char p[16]; Fld **data; };
struct Own { char p[188]; Lst2 *f188; char p192[52]; Lst *f244; char p248[36]; Alloc *f284; };
struct Ent { char p[12]; int f12; char p16[12]; int f28; char p32[4]; Fld *f36; int f40; int f44; int f48; };
struct Ref {
    Lst *p;
    Ref(Lst *o) : p(o) { if (p != 0) { p->refs = p->refs + 1; } }
    ~Ref() {
        Lst *object = p;
        if (object) {
            --object->refs;
            if (((unsigned long long)(long long)object->refs & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
extern "C" void Gap__Core__igMemoryDirEntry__vfunc_31(Ent *arg0, Own *arg1);
void Gap__Core__igMemoryDirEntry__vfunc_31(Ent *arg0, Own *arg1) {
    Lst2 *fields = arg1->f188;
    int align = 16;
    Ref sizes(arg1->f244);
    Alloc *a;

    if (0 <= arg0->f44) {
        align = sizes.p->data[arg0->f44];
    } else if (fields != 0) {
        if (0 <= arg0->f40) {
            arg0->f36 = fields->data[arg0->f40];
            align = arg0->f36->v108();
        }
    }
    if ((arg0->f48 == -1) || (arg0->f48 == 1) || (arg0->f48 == 2)) {
        a = arg1->f284;
    } else {
        a = (Alloc *)Memory_GetAllocatorBySelector(arg0->f48);
        if (a == 0) {
            a = arg1->f284;
        }
    }
    if (align < 5) {
        FUN_002d7da0(arg1, arg0->f12, a->v216(arg0->f28));
    } else {
        FUN_002d7da0(arg1, arg0->f12, a->v220(arg0->f28, align & 0xFFFF));
    }
}
