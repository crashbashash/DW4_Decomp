#include "dw4/reflected.h"
extern "C" {
int FUN_001b73d0(...);
int FUN_001d9bb0(...);
int Gap__Sg__igTraversal__vfunc_24(...);
void Gap__Sg__igCompileTraversal__vfunc_24(igCompileTraversal *arg0, int arg1);
}
class DW4VC_132_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(); };
void Gap__Sg__igCompileTraversal__vfunc_24(igCompileTraversal *arg0, int arg1) {
    FUN_001b73d0();
    FUN_001d9bb0(arg0->_sorter, arg0->_attrStack);
    if (arg0->_userTimeState != 0) {
        ((DW4VC_132_0 *)(((char *)(arg0) + 0)))->vX();
    }
    Gap__Sg__igTraversal__vfunc_24(arg0, arg1);
}
