extern "C" {
void *igIntMetaField_GetDefaultDescriptor(...);
int FUN_002fe600(...);
int FUN_002fe470(...);
int FUN_002ffd40(...);
void *FUN_002fdf00(...);
int FUN_002fc6f0(...);
extern void *DAT_00587198[4];
}
class D { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void v208(int *, int); };
struct Meta { char p[25]; unsigned char persistent; char p26[38]; void *(*getter)(); };
struct FI { char p[37]; unsigned char f37; unsigned char f38; };
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void v56(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual Meta *v88(); };
extern "C" int igObject_WritePersistentFields(O * arg0, int * arg1, int arg2, void * r3, void * r4);
int igObject_WritePersistentFields(O * arg0, int * arg1, int arg2, void * r3, void * r4) {
    int arg3 = (int)r3;
    int arg4 = (int)r4;
    Meta *m;
    int id;
    int i;
    FI *f;

    m = arg0->v88();
    if (m->persistent == 0) {
        return 0;
    }
    arg0->v56();
    id = 0;
    m = (m->getter != 0) ? (Meta *)m->getter() : m;
    if (arg3 != 0) {
        id = FUN_002fe600(arg3, m);
    }
    arg3 = FUN_002fe470(m);
    i = FUN_002fe470(DAT_00587198[0]);
    arg1[0] = id;
    id = i;
    arg1[1] = FUN_002ffd40(arg0);
    if (arg4 != 0) {
        ((D *)igIntMetaField_GetDefaultDescriptor())->v208(arg1, 2);
    }
    arg1 += 2;
    for (; id < arg3; id++) {
        f = (FI *)FUN_002fdf00(m, id);
        if (f->f38 == 1 && f->f37 == 0) {
            arg1 = (int *)((char *)arg1 + FUN_002fc6f0(f, arg0, arg1, arg2, arg4));
        }
    }
    return FUN_002ffd40(arg0);
}
