#include "dw4/reflected.h"
extern "C" {
int sprintf(...);
int strlen(...);
int FUN_00300f50(...);
int FUN_00304430(...);
int FUN_00304680(...);
int igObject_AllocateStorage(...);
extern int DAT_004faf60[4];
extern int DAT_004faf78[4];
extern int DAT_004faf80[4];
extern int DAT_004faf88[4];
extern igMetaObject * DAT_00587198[4];
void FUN_00300490(void **arg0, int arg1, int arg2);
}
class DW4VC_72_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual int vX(); };
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual igMetaObject * vX(); };
class DW4VC_164_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual int vX(int, int, int); };
void FUN_00300490(void **arg0, int arg1, int arg2) {
    unsigned int var_s0;
    unsigned int temp_s1;
    int temp_v0;
    void **temp_a0;
    void *temp_s3;

    temp_s3 = (void *)(((DW4VC_88_0 *)(arg0))->vX()->_metaFields);
    FUN_00304430(&DAT_004faf60[0], arg2, arg0, ((DW4VC_88_0 *)(arg0))->vX()->_name);
    FUN_00304680();
    if (arg1 != 0) {
        temp_v0 = igObject_AllocateStorage(arg0, (strlen(arg2) + 2) * 4);
        sprintf(temp_v0, &DAT_004faf78[0], arg2);
        ((DW4VC_72_0 *)(arg0))->vX();
        temp_s1 = *(int *)((char *)(temp_s3) + 12);
        var_s0 = *(int *)((char *)(DAT_00587198[0]->_metaFields) + 12);
        FUN_00304430(&DAT_004faf80[0], arg2);
        FUN_00304680();
        for (; var_s0 < temp_s1; var_s0++) {
            int *base = *(int **)((char *)(temp_s3) + 8);
            temp_a0 = (void **)base[var_s0];
            ((DW4VC_164_3 *)(temp_a0))->vX((int)(arg0), (int)(arg1 - 1), (int)(temp_v0));
        }
        FUN_00304430(&DAT_004faf88[0], arg2);
        FUN_00304680();
        FUN_00300f50(arg0, temp_v0);
    }
}
