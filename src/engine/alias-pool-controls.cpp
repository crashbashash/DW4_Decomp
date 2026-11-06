/* igAliasMemoryPool binding and disable: the setter that retains the aliased pool and records
 * whether it accepts this pool, and the disable callback. */
#include "dw4/reflected.h"
/* Retail ABI views, not original class definitions. Virtual tables include
 * an eight-byte header; Object projects slot376. Never instantiate these views. */
class Object { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual unsigned char Check(void *); unsigned refs; };
extern "C" void igObject_Destroy(Object *);
extern "C" {

void Gap__Core__igAliasMemoryPool__vfunc_32(igAliasMemoryPool *self);
}
class DW4VC_124_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int vX(); };

/* Bind `alias` as the pool this one forwards to. The new alias is retained before the previous one
 * is released (so assigning the same object is safe); the previous alias is destroyed when its
 * reference count drops to zero. The alias is then asked (virtual slot 376) whether it accepts
 * this pool and the low byte of the answer becomes _isReassignable; a null alias clears it. */
extern "C" void igAliasMemoryPool_AssignAlias(igAliasMemoryPool *self, Object *alias) {
    Object *old;
    if (alias) alias->refs++;
    old = (Object *)self->_aliasedMemoryPool;
    if (old) {
        old->refs--;
        if ((old->refs & 0x7fffff) == 0)
            igObject_Destroy(old);
    }
    self->_aliasedMemoryPool = (int)alias;
    if (alias) self->_isReassignable = alias->Check(self);
    else self->_isReassignable = 0;
}

/* Disable the pool: run the receiver's virtual at vtable offset 124 (the reset callback), then
 * clear _isActive afterwards, even if the callback wrote it. */
void Gap__Core__igAliasMemoryPool__vfunc_32(igAliasMemoryPool *self) {
    ((DW4VC_124_0 *)(((char *)(self) + 0)))->vX();
    self->_isActive = 0;
}
