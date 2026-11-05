/* 0x003cb700 — Gap__Bec__beNDMWMcUtilCtrl__vfunc_08. Banked by tools/retype_struct_member.py (shape: base):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
extern "C" {
int FUN_003a9870(...);
int Gap__Core__igObject__vfunc_08__002ff0f0(...);
int igMetaObject_CountInstances(...);
void Gap__Bec__beNDMWMcUtilCtrl__vfunc_08(beNDMWMcUtilCtrl *arg0);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
void Gap__Bec__beNDMWMcUtilCtrl__vfunc_08(beNDMWMcUtilCtrl *arg0) {
    FUN_003a9870(arg0->_svData);
    igMetaObject_CountInstances(((DW4VC_88_0 *)(((char *)(arg0) + 0)))->vX(), 1);
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}
