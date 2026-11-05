extern "C" int igObject_ResetFields(...);
struct S { char pad0[8]; int base; char pad1[56]; int n; };
extern "C" void Gap__Core__igObjectRefArrayMetaField__vfunc_39(S *arg0, int arg1) {
    int i;
    for (i = 0; i < arg0->n; i++) {
        int *p = (int *)(arg1 + arg0->base + (i * 4));
        if (*p != 0) {
            igObject_ResetFields(*p);
        }
    }
}
