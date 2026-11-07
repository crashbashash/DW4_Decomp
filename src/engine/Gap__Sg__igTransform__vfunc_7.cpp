/* Reset step: runs the shared base step (Gap__Sg__igNode__vfunc_09 receives self and the flag unchanged in
 * a0/a1), then, when `flag` is 0, makes the virtual call at vtable byte offset 112 with (2, 1). */
#include "dw4/reflected.h"
extern "C" {
int Gap__Sg__igNode__vfunc_09(...);
void Gap__Sg__igTransform__vfunc_7(igTransform *self, int flag);
}
class DW4VC_112_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(int, int); };
void Gap__Sg__igTransform__vfunc_7(igTransform *self, int flag) {
    Gap__Sg__igNode__vfunc_09();  /* takes (self, flag) straight from a0/a1 */
    if (flag == 0) {
        ((DW4VC_112_2 *)(self))->vX((int)(2), (int)(1));
    }
}
