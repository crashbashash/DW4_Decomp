#include "dw4/reflected.h"
extern "C" {
extern int DAT_004fb410[4];
void FUN_002e4240(int *arg0, igIGBFile *arg1);
}
class C156 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int vX(void *); };
void FUN_002e4240(int *arg0, igIGBFile *arg1) {
    int var_s0;
    void *temp_a0;

    arg1->_objectCount = 0;
    arg1->_memoryRefCount = 0;
    arg1->_objectBufferSize = 0;
    arg1->_memoryRefBufferSize = 0;
    for (var_s0 = 0; var_s0 < arg1->_count; var_s0++) {
        temp_a0 = (void *)(*(int *)(arg1->_data + (var_s0 * 4)));
        ((C156 *)temp_a0)->vX(arg1);
    }
    *arg0 = DAT_004fb410[0];
}
