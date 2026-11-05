#include "dw4/reflected.h"
extern "C" {
int FUN_002f8a50(...);
int FUN_002f8a60(...);
int FUN_00304430(...);
int FUN_00304680(...);
extern int DAT_004e0858[4];
extern int DAT_004f95c8[4];
extern int DAT_004fabc0[4];
void FUN_002f9600(igInfo *arg0);
}
class VCc { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void vX(); };
void FUN_002f9600(igInfo *arg0) {
    int *var_a1;
    int n;
    int i;
    int o;
    n = FUN_002f8a50();
    var_a1 = (int *)(arg0->_name);
    var_a1 = var_a1 != 0 ? var_a1 : (int *)&DAT_004e0858[0];
    FUN_00304430(&DAT_004fabc0[0], var_a1);
    FUN_00304680();
    for (i = 0; i < n; i++) {
        if ((o = FUN_002f8a60(arg0, i)) != 0) {
            FUN_00304430(&DAT_004f95c8[0]);
            FUN_00304680();
            ((VCc *)o)->vX();
        }
    }
}
