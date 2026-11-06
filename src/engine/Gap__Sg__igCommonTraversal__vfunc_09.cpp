#include "dw4/reflected.h"
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int); };
extern "C" {
int Gap__Sg__igTraversal__vfunc_09(...);
void igObject_Destroy(igObject *);
extern igObject *DAT_00562640[4];
void Gap__Sg__igCommonTraversal__vfunc_09(igCommonTraversal *arg0, int arg1);
}
void Gap__Sg__igCommonTraversal__vfunc_09(igCommonTraversal *arg0, int arg1) {
    igObject *s0;
    igObject *a0;

    Gap__Sg__igTraversal__vfunc_09(arg0, arg1);
    if (arg1 == 0) {
        s0 = DAT_00562640[0];
        if (s0 != 0) {
            s0->_refCount = s0->_refCount + 1;
        }
        a0 = (igObject *)arg0->_travProcs;
        if (a0 != 0) {
            --a0->_refCount;
            if (((unsigned long long)(long long)a0->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(a0);
            }
        }
        arg0->_travProcs = (int)s0;
        ((C *)arg0->_matrixOptimization)->vX(0);
        *(char *)(arg0->_normalizeNormalsEnable + 12) = 1;
    }
}
