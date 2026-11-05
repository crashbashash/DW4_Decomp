#include "dw4/reflected.h"
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual call (slot 24 = genrand) */
class Rnd { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual unsigned v24(); };
extern "C" void FUN_00448190(beNDMWItemRevisionPocketBase *out, beNDMWStatus *ctx, int x) {
    int v = (((Rnd *)((beSystem *)ctx->_system)->_random)->v24() % 620U) + 1 - ((x / 10 + 10) / 10);
    int r = 1;
    if (v == 1) {
        r = 5;
    } else if (v < 4) {
        r = 4;
    } else if (v < 8) {
        r = 3;
    } else if (v < 16) {
        r = 2;
    } else if (v < 32) {
        r = 1;
    } else {
        r = 0;
    }
    out->_pocket = r;
}
