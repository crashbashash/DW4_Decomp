extern "C" {
extern void * DAT_00587198[4];

void igObject_ConstructFields(void **arg0);
}
class DW4VC_12_1 { public: virtual void d0(); virtual int vX(int); };
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
class DW4VC_124_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int vX(int); };
void igObject_ConstructFields(void **arg0) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    char *meta;
    void **o;
    int n;
    int i;

    meta = (char *)(*(int *)((char *)(((DW4VC_88_0 *)(arg0))->vX()) + 40));
    i = *(int *)((char *)(*(int *)((char *)(DAT_00587198[0]) + 40)) + 12);
    n = *(int *)(meta + 12);
    while (i < n) {
        o = (void **)(*(int *)(*(int *)(meta + 8) + (i * 4)));
        ((DW4VC_124_1 *)(o))->vX((int)(arg0));
        i++;
    }
    ((DW4VC_12_1 *)(arg0))->vX((int)(1));
}
