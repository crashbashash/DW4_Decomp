/* 0x002d0a80
 * Release the pool's allocation lock, then hand back the value the caller
 * supplied: when a lock object is attached (_allocationLock), call its
 * virtual method at vtable offset 124 (the same unlock call as
 * igAliasMemoryPool_Unlock); the status it returns is discarded.  This lets a
 * caller write `return igAliasMemoryPool_UnlockAndReturn(pool, result)` to
 * leave a locked section while preserving its result
 * (docs/engine/alias-pool-runtime.md). */
#include "dw4/reflected.h"
extern "C" {

int igAliasMemoryPool_UnlockAndReturn(igAliasMemoryPool *self, int result);
}
/* The unlock call returns a 4-byte struct by value; MWCC passes it through a hidden
 * return buffer, which the stack slot below reproduces (docs/engine/m2c-bulk.md). */
struct LockStatus { int word; };
/* The lock object's vtable: 29 unnamed padding slots, then the unlock call (offset 124 with
 * the two-word class header in front of the slots). */
class AllocationLockVtable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual LockStatus unlock(); };
int igAliasMemoryPool_UnlockAndReturn(igAliasMemoryPool *self, int result) {
    LockStatus status;
    void **lockObject;

    lockObject = (void **)(self->_allocationLock);
    if (lockObject != 0) {
        status = ((AllocationLockVtable *)(lockObject))->unlock();
    }
    return result;
}
