extern "C" {
int igObject_IsAlikeDeep(...);
int igObject_IsKindOf(...);
int Memory_GetBufferSize(...);
extern int DAT_00585b20[4];
}
struct F { char pad[8]; int f8; char pad2[48]; int f60; };
class DW4VC_188_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual int vX(int, int); char pad[4]; int f8; char pad2[48]; int f60; };
extern "C" int igMemoryRefMetaField_IsAlikeDeep(DW4VC_188_2 *arg0, int arg1, int arg2) {
    int off;
    int n;
    int a;
    int b;
    int i;

    if (igObject_IsKindOf(arg0->f60, DAT_00585b20[0]) == 0) {
        return arg0->vX(arg1, arg2);
    }
    off = arg0->f8;
    a = *(int *)(arg1 + off);
    b = *(int *)(arg2 + off);
    if (a == b) {
        return 1;
    }
    if (a == 0 || b == 0) {
        return 0;
    }
    n = Memory_GetBufferSize(a);
    if (n != Memory_GetBufferSize(b)) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (!(igObject_IsAlikeDeep(*(int *)(a + i * 4), *(int *)(b + i * 4)) & 0xFF)) {
            return 0;
        }
    }
    return 1;
}
