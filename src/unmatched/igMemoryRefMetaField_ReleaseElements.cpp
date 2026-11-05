#include "dw4/reflected.h"
class E { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void vX(); };
extern "C" {
int igObject_IsKindOf(int, int);
unsigned int Memory_GetBufferSize(E **);
int igObject_VisitFields(E *, int, int);
extern int DAT_00585b20[4];
}
extern "C" void igMemoryRefMetaField_ReleaseElements(igMemoryRefMetaField *arg0, int arg1, int arg2, int arg3) {
    E **arr;
    unsigned int n;
    int i;
    E *e;
    if (igObject_IsKindOf(arg0->_memType, DAT_00585b20[0]) != 0) {
        arr = *(E ***)(arg1 + arg0->_offset);
        if (arr != 0) {
            n = Memory_GetBufferSize(arr) >> 2;
            for (i = 0; i < (int)n; i++) {
                e = arr[i];
                if (e != 0) {
                    e->vX();
                    igObject_VisitFields(arr[i], arg2, arg3);
                }
            }
        }
    }
}
