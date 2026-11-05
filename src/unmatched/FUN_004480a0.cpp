#include "dw4/reflected.h"
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual calls */
class Rng { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
 virtual unsigned int draw(); };
extern "C" void FUN_004480a0(beNDMWItemRevisionBase *out, beNDMWStatus *a, unsigned int level) {
    int first = (((Rng *)((beSystem *)a->_system)->_random)->draw() % 6000U) + 1;
    int second = (((Rng *)((beSystem *)a->_system)->_random)->draw() % level) + 1;
    int v;
    if (first == 1) {
        v = level + 1;
    } else if (first < 3001) {
        v = second - first / 10;
    } else {
        v = 0;
    }
    if (v < 0) v = 0;
    out->_revision = v;
}
