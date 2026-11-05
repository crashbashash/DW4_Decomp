extern "C" {
int igMetaField_ConstructCopy(...);
int igMetaObject_GetFieldCount(...);
extern int DAT_00587198[4];
void FUN_00300600(void **arg0, int arg1);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
void FUN_00300600(void **arg0, int arg1) {
    /* matching construct: variant search — decl order [2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    char *meta;
    int n;
    int i;

    meta = (char *)(*(int *)((char *)(((DW4VC_88_0 *)(arg0))->vX()) + 40));
    n = *(int *)(meta + 12);
    i = igMetaObject_GetFieldCount(DAT_00587198[0]);
    while (i < n) {
        igMetaField_ConstructCopy(*(int *)(*(int *)(meta + 8) + (i * 4)), arg0, arg1);
        i++;
    }
}
