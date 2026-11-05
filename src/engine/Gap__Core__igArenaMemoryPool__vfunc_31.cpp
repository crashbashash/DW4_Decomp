/* 0x0031cdf0
 * Pool teardown/reset step.  A pool that has a size (_size at +160) calls the
 * virtual at vtable byte offset 204, clears _systemAllocated and zeroes the
 * 0x814-byte arena state block if one is attached; a pool with no size instead
 * calls the virtual at vtable byte offset 108 with 1.  The two vtable calls
 * are spelled through the dummy classes below (one per distinct vtable offset;
 * dN are placeholder virtuals that only position vX); the callees are not yet
 * identified. */
#include "dw4/reflected.h"
extern "C" {
int memset(...);
void Gap__Core__igArenaMemoryPool__vfunc_31(igArenaMemoryPool *self);
}
class DW4VC_108_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int); };
class DW4VC_204_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual int vX(); };
void Gap__Core__igArenaMemoryPool__vfunc_31(igArenaMemoryPool *self) {
    int arenaState;

    if (self->_size != 0) {
        ((DW4VC_204_0 *)self)->vX();
        self->_systemAllocated = 0;
        arenaState = self->_arenaState;
        if (arenaState != 0) {
            memset(arenaState, 0, 0x814);
        }
    } else {
        ((DW4VC_108_1 *)self)->vX(1);
    }
}
