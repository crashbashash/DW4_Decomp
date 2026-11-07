class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual int v172(int); };
struct Ent;
struct Lst { int pad0; int pad1; int count; int pad3; Ent **data; };
struct Ctx { char pad[24]; Lst *list; };
extern "C" {
int FUN_002d83b0(Ent *, Ctx *, int);
int FUN_002d8460(Ctx *, int);
int FUN_002d87b0(Ctx *, int, int, int);
int FUN_002d8520(int arg0, VC *arg1, Ctx *arg2);
}
int FUN_002d8520(int arg0, VC *arg1, Ctx *arg2) {
    int i;
    int n;
    if (arg0 == 0) {
        return 1;
    }
    if (arg1 != 0) {
        return arg1->v172(arg0) == -1;
    }
    if ((FUN_002d8460(arg2, arg0) & 0xFF) == 1) {
        return 1;
    }
    n = arg2->list->count;
    for (i = 0; i < n; i++) {
        if ((FUN_002d83b0(arg2->list->data[i], arg2, arg0) & 0xFF) == 1) {
            return 1;
        }
    }
    FUN_002d87b0(arg2, arg0, 0, 0);
    return 0;
}
