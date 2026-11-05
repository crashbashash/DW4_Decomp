extern "C" {
int igMetaField_DeepCopy(...);
int igMetaObject_GetFieldCount(...);
extern int DAT_00587198[4];
void FUN_003006a0(void **arg0, void **arg1);
}
class DW4VC_20_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual int vX(int); };
class DW4VC_72_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual int vX(); };
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
void FUN_003006a0(void **arg0, void **arg1) {
    int var_s0;
    int temp_s1;
    void *temp_s0;
    void *temp_s2;

    temp_s0 = (void *)(((DW4VC_88_0 *)(arg0))->vX());
    ((DW4VC_72_0 *)(arg0))->vX();
    ((DW4VC_72_0 *)(arg1))->vX();
    temp_s2 = (void *)(*(int *)((char *)(temp_s0) + 40));
    temp_s1 = *(int *)((char *)(temp_s2) + 12);
    var_s0 = igMetaObject_GetFieldCount(DAT_00587198[0]);
    for (; var_s0 < temp_s1; var_s0++) {
        igMetaField_DeepCopy(*(int *)(*(int *)((char *)(temp_s2) + 8) + (var_s0 * 4)), arg0, arg1);
    }
    ((DW4VC_20_1 *)(arg0))->vX((int)(arg1));
}
