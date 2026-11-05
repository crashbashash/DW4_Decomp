#include "dw4/reflected.h"
class E { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual unsigned int vX(); };
extern "C" {
int FUN_00300490(int, int, int);
int igObject_IsKindOf(...);
int FUN_00304430(...);
int FUN_00304680(...);
unsigned int Memory_GetBufferSize(int);
extern int DAT_004faef0[4];
extern int DAT_00585b20[4];
}
extern "C" void igMemoryRefMetaField_Print(igMemoryRefMetaField *arg0, int arg1, int arg2, int arg3) {
    unsigned int n;
    unsigned int sz;
    int base;
    int i;
    base = *(int *)(arg1 + arg0->_offset);
    FUN_00304430(&DAT_004faef0[0], arg3, arg0->_fieldName, base);
    FUN_00304680();
    if (arg2 != 0 && base != 0) {
        sz = ((E *)arg0->_memType)->vX();
        n = Memory_GetBufferSize(base) / sz;
        if (igObject_IsKindOf((E *)arg0->_memType, DAT_00585b20[0]) != 0) {
            for (i = 0; i < (int)n; i++) {
                int e = *(int *)(base + i * 4);
                if (e != 0) {
                    FUN_00300490(e, arg2, arg3);
                }
            }
        }
    }
}
