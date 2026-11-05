extern "C" {
int FUN_001b1030(...);
int FUN_001dca40(...);
int FUN_001356b0(...);
}
class V128 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int); };
struct List { char p0[8]; int cap; char p1[4]; V128 **items; int count; };
struct O { char p0[52]; int f52; char p1[16]; List *list; };
extern "C" V128 *FUN_001b7330(O *arg0, int arg1);
V128 *FUN_001b7330(O *arg0, int arg1) {
    List *l = arg0->list;
    int idx;
    V128 *e;
    if (l->count >= l->cap) {
        FUN_001dca40(l, &FUN_001356b0);
    }
    idx = l->count;
    l->count = idx + 1;
    e = l->items[idx];
    e->vX(arg1);
    FUN_001b1030(arg0->f52, e);
    return e;
}
