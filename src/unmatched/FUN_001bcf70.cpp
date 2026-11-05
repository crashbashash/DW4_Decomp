extern "C" {
struct Obj { int w0; unsigned refs; int p8; int f12; int *f16; int f20; unsigned f24; };
Obj *FUN_00139990(...);
int FUN_001b1030(...);
int FUN_001b1100(...);
int FUN_001b9320(...);
int FUN_00300f50(...);
int ObjectList_AppendRetained(...);
int *igObject_AllocateStorage(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
}
struct SL { char p[8]; int count; char p2[4]; int *data; };
struct B { char p[40]; SL *f40; };
struct A { char p[52]; int f52; char q[440]; char f496; char r[7]; int f504; };
extern "C" int FUN_001bcf70(A *arg0, B *arg1);
int FUN_001bcf70(A *arg0, B *arg1) {
    Obj *o;
    int s0;
    s0 = arg0->f52;
    arg0->f496 = 1;
    o = FUN_00139990(igObject_GetAllocator(arg0));
    ObjectList_AppendRetained(arg0->f504, o);
    o->refs = o->refs - 1;
    if ((o->refs & 0x7FFFFF) == 0) igObject_Destroy(o);
    unsigned int n = arg1->f40->count;
    if (o->f24 < n) {
        if (o->f12 != 0) FUN_00300f50(o, o->f12);
        if (o->f16 != 0) FUN_00300f50(o, o->f16);
        o->f16 = igObject_AllocateStorage(o, n * 4);
        o->f24 = n;
    }
    o->f20 = n;
    int i = 0;
    while (i < arg1->f40->count) {
        o->f16[i] = arg1->f40->data[i];
        i++;
    }
    FUN_001b1030(s0, o);
    int r = FUN_001b9320(arg0, arg1);
    FUN_001b1100(s0, o);
    if (r == 2) return 2;
    return 0;
}
