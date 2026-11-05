struct Lst { char pad[44]; int cnt; int list; };
class Alloc;
class Obj;
class Alloc { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual char vA();  };
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void v9(int); virtual void d8(); virtual void v11(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual Lst *v22(); union { int w4; struct { unsigned cnt:23; unsigned f:9; } b; struct { unsigned char b0; unsigned char b1; unsigned char lo:7; unsigned char hi:1; unsigned char id; } c; } u; };
extern "C" {
Alloc *Memory_FindOwningAllocator(int);
int ObjectPointerList_Append(int, void *);
int igObject_ConstructFields(void *);
int igObject_GetAllocationBase(void *);
int igObject_ResetUnconstructedFields(void *);
int igObject_ZeroFields(void *);
void igObject_Construct(Obj *arg0, char *arg1);
}
extern int DAT_00586dc8[4];
void igObject_Construct(Obj *arg0, char *arg1) {
    Alloc *a;
    Lst *l;
    *(int *)((char *)arg0 + *(int *)((char *)DAT_00586dc8[0] + 916)) = *(int *)(arg1 + 92);
    arg0->u.w4 = 0;
    arg0->u.b.cnt = 1;
    arg0->u.c.hi = 0;
    a = Memory_FindOwningAllocator(igObject_GetAllocationBase(arg0));
    if (a != 0) {
        arg0->u.c.id = a->vA();
    } else {
        arg0->u.c.id = 0;
    }
    igObject_ZeroFields(arg0);
    igObject_ConstructFields(arg0);
    igObject_ResetUnconstructedFields(arg0);
    arg0->v11();
    arg0->v9(0);
    l = arg0->v22();
    if (l != 0) {
        l->cnt = l->cnt + 1;
        if (l->list != 0) {
            ObjectPointerList_Append(l->list, arg0);
        }
    }
}
