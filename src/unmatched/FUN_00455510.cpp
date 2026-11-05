extern "C" {
int FUN_001c59e0();
void *igObject_IsKindOf(void *, void *);
extern void *DAT_0058c428[4];
}
struct O {
    char p[32]; int v;
    static O *cast(O *o) {
        if (o != 0 && igObject_IsKindOf(o, DAT_0058c428[0]) != 0) return o;
        return 0;
    }
};
struct B { char p[16]; O **arr; };
struct A { char p[8]; B *b; };
extern "C" int FUN_00455510(A *arg0) {
    int n = FUN_001c59e0();
    int i;
    O *o;
    if (n <= 0) return 0;
    i = n - 1;
    while (i >= 0) {
        o = O::cast(arg0->b->arr[i]);
        if (o != 0) return o->v;
        i--;
    }
    return 0;
}
