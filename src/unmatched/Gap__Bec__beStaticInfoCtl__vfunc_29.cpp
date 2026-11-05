#include "dw4/reflected.h"
extern "C" {
int ObjectList_AppendRetained(...);
int beMessenger_RegisterReceiver(...);
extern int DAT_004e0858[4];
extern int DAT_0050ff68[4];
struct A;
void Gap__Bec__beStaticInfoCtl__vfunc_29(A *arg0, beBaseInfoRam *arg1);
}
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void v136(); };
/* matching construct: dummy-virtual base so arg0->v136() dispatches through the vtable entry at byte offset 136 */
struct A : VC {};
void Gap__Bec__beStaticInfoCtl__vfunc_29(A *arg0, beBaseInfoRam *arg1) {
    /* matching construct: a typed view of the receiver declared first; casting arg0 at each use makes the compiler hoist the field address into an extra saved register */
    beStaticInfoCtl *self = (beStaticInfoCtl *)arg0; int a0; beBaseInfo *s0; int *a3; int z; int t0;
    a0 = self->_messenger;
    s0 = (beBaseInfo *)arg1->_parentInfo;
    z = ((a0 != 0) ^ 1);
    if (z) { do { arg0->v136(); a0 = self->_messenger; z = ((a0 != 0) ^ 1); } while (z); }
    a3 = (int *)s0->_name;
    t0 = arg1->_ramNo;
    a3 = a3 != 0 ? a3 : &DAT_004e0858[0];
    beMessenger_RegisterReceiver(a0, arg1, &DAT_0050ff68[0], a3, t0);
    ObjectList_AppendRetained(self->_staticInfoList, s0);
}
