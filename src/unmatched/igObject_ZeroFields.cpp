#include "dw4/reflected.h"
extern "C" {
extern void * DAT_00586dc8[4];
extern igMetaObject * DAT_00587198[4];
void igObject_ZeroFields(void **arg0);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
class DW4VC_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int); };
void igObject_ZeroFields(void **arg0) {
    int temp_s0;
    int var_s3;
    void **temp_a0;
    void *temp_s1;
    igMetaObject *temp_v0;
    bool t;

    temp_v0 = (igMetaObject *)(((DW4VC_88_0 *)(arg0))->vX());
    if (((temp_v0 != 0) && (t = temp_v0->_validity & 4)) || (*(unsigned char *)((char *)(DAT_00586dc8[0]) + 20) == 0) || (*(unsigned char *)((char *)(DAT_00586dc8[0]) + 0) != 0)) {
        temp_s1 = (void *)(temp_v0->_metaFields);
        var_s3 = *(int *)((char *)(DAT_00587198[0]->_metaFields) + 12);
        temp_s0 = *(int *)((char *)(temp_s1) + 12);
        for (; var_s3 < temp_s0; var_s3++) {
            temp_a0 = (void **)(*(int *)(*(int *)((char *)(temp_s1) + 8) + (var_s3 * 4)));
            ((DW4VC_132_1 *)(temp_a0))->vX((int)(arg0));
        }
    }
}
