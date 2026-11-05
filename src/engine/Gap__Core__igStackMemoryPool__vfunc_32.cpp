/* 0x003276b0 — Gap__Core__igStackMemoryPool__vfunc_32
 * Disable step of the stack pool: run virtual slot 124 (vfunc_31, 0x00327670, which
 * copies +116 to +132 and recomputes +136 as the 4-byte-aligned end: +132 plus the
 * 64-bit size at +120, less 4), then clear _isActive.  The alias pool has the same
 * pair: its slot 128 calls the receiver's slot 124 and then clears the active byte
 * (docs/engine/alias-pool-binding.md, "Accounting control block"). */
#include "dw4/reflected.h"
extern "C" {

void Gap__Core__igStackMemoryPool__vfunc_32(igStackMemoryPool *self);
}
/* ABI dispatch view of virtual slot 124 (29 leading virtuals); never instantiated. */
class StackPoolSlot124View { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void Reset();
};

void Gap__Core__igStackMemoryPool__vfunc_32(igStackMemoryPool *self) {
    ((StackPoolSlot124View *)self)->Reset();
    self->_isActive = 0;
}
