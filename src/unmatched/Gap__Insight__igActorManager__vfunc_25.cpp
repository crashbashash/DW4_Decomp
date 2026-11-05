/* 0x00466d00 - Gap__Insight__igActorManager__vfunc_25: retyped on reflected igActorManager. */
#include "dw4/reflected.h"
extern "C" {
class W { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int, int, int, int, float, float); };
struct R { int w0; int rc; };
R *FUN_00236f80(...);
int igObject_Destroy(...);
extern int DAT_0058c790[4];
void Gap__Insight__igActorManager__vfunc_25(igActorManager *arg0);
void Gap__Insight__igActorManager__vfunc_25(igActorManager *arg0) {
    R *temp_v0;
    R *temp_a0;

    temp_v0 = FUN_00236f80(arg0->_insight, DAT_0058c790[0]);
    if (temp_v0 != 0) {
        temp_v0->rc = temp_v0->rc + 1;
    }
    temp_a0 = (R *)arg0->_vsim;
    if (temp_a0 != 0) {
        temp_a0->rc = temp_a0->rc - 1;
        if ((temp_a0->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_vsim = (int)temp_v0;
    ((W *)arg0->_viewport)->vX(0, 0, 0, 0, 0.0f, 1.0f);
    ((W *)arg0->_skelViewport)->vX(0, 0, 0, 0, 0.0f, 0.2f);
}
}
