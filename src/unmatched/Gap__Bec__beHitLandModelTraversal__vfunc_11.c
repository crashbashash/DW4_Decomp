#include "dw4/reflected.h"
int FUN_0018f760();
int FUN_001ce970();
int Gap__Core__igObject__vfunc_11();
int igObject_Destroy();
int igObject_GetAllocator();
void Gap__Bec__beHitLandModelTraversal__vfunc_11(beHitLandModelTraversal *arg0) {
    igObject *sp3C;
    igObject *s0;
    igObject *old;

    Gap__Core__igObject__vfunc_11();
    FUN_0018f760(&sp3C, igObject_GetAllocator(arg0));
    s0 = sp3C;
    if (s0 != 0) {
        s0->_refCount = s0->_refCount + 1;
    }
    old = (igObject *)arg0->_volumes;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    arg0->_volumes = (int)s0;
    if (sp3C != 0) {
        sp3C->_refCount = sp3C->_refCount - 1;
        if ((sp3C->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(sp3C);
        }
    }
    FUN_001ce970(arg0);
}
