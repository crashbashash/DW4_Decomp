#include "dw4/reflected.h"
extern "C" {
int FUN_00175ed0(...);
int FUN_00175ef0(...);
int FUN_00175f20(...);
void Gap__Gfx__igPsx2ParticleArray__vfunc_27(igPsx2ParticleArray *arg0, char *arg1);
}
class DW4VC_100_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(char *, int); };
void Gap__Gfx__igPsx2ParticleArray__vfunc_27(igPsx2ParticleArray *arg0, char *arg1) {
    char b[144];
    FUN_00175f20(&b[0], arg1);
    FUN_00175f20(&b[12], arg1 + 12);
    FUN_00175f20(&b[24], arg1 + 24);
    FUN_00175ef0(&b[36], arg1 + 36);
    FUN_00175ef0(&b[52], arg1 + 52);
    FUN_00175ef0(&b[68], arg1 + 68);
    FUN_00175ed0(&b[84], arg1 + 84);
    FUN_00175ed0(&b[92], arg1 + 92);
    FUN_00175ed0(&b[100], arg1 + 100);
    FUN_00175ed0(&b[108], arg1 + 108);
    FUN_00175ed0(&b[116], arg1 + 116);
    FUN_00175f20(&b[124], arg1 + 124);
    FUN_00175ed0(&b[136], arg1 + 136);
    ((DW4VC_100_2 *)(arg0))->vX(&b[0], arg0->_currentEditIndex);
}
