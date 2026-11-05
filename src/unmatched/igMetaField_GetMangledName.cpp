/* 0x002fd240 - igMetaField_GetMangledName. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
extern "C" {
int FUN_0012a1e8(...);
int strcpy(...);
int strlen(...);
extern int DAT_004c22b8[4];
extern int DAT_004c22c0[4];
int igMetaField_GetMangledName(igMetaField *arg0, void **arg1);
}
class DW4VC_216_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };
int igMetaField_GetMangledName(igMetaField *arg0, void **arg1) {
    int temp_s0;
    int temp_s2;
    int temp_s2_2;
    int temp_s2_3;
    int temp_s3;
    int var_s2;
    int var_v0;

    var_s2 = 0;
    if (arg0 != 0) {
        var_v0 = 0;
        if (arg1 != 0) {
            temp_s0 = arg0->_fieldName;
            temp_s3 = *(int *)((char *)(arg0->_parentMetaObject) + 28);
            temp_s2 = strlen(DAT_004c22b8[0]);
            temp_s2_2 = temp_s2 + strlen(temp_s0);
            temp_s2_3 = strlen(DAT_004c22c0[0]);
            temp_s2_3 = temp_s2_3 + temp_s2_2;
            var_s2 = strlen(temp_s3);
            var_s2 = ((DW4VC_216_1 *)(arg1))->vX((int)(var_s2 + temp_s2_3 + 1));
            strcpy(var_s2, DAT_004c22b8[0]);
            FUN_0012a1e8(var_s2, temp_s3);
            FUN_0012a1e8(var_s2, DAT_004c22c0[0]);
            FUN_0012a1e8(var_s2, temp_s0);
            goto block_3;
        }
    } else {
block_3:
        var_v0 = var_s2;
    }
    return var_v0;
}
