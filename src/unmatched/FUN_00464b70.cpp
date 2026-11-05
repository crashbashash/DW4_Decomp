extern "C" {
#include "dw4/ipa/ipa_FUN_00464af0.h"
}
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(int, int, float, float); };
struct O { char p[8]; V *o; };
extern "C" int FUN_00464b70(O *self, int x, int y, float f0, float f1) {
    float sp1C;
    float sp18;
    sp18 = f0;
    sp1C = f1;
    FUN_00464af0(&sp18, &sp1C, 0.3f);
    self->o->vX(x, y, sp18, sp1C);
    return 1;
}
