#include "dw4/igSmartPointer.h"
extern "C" {
int igObject_GetAllocator(...);
}
struct PoolStatus { int a; };
class RefPool : public igVirtualObject { public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual PoolStatus open();
    virtual PoolStatus close();
    
};
extern "C" RefPool *FUN_002ba650(...);

struct PoolOwner { char p[8]; RefPool *pool; };
static inline void setPool(PoolOwner *self, RefPool *pool) {
    RefPool *previous;
    if (pool != 0) {
        pool->_refCount = pool->_refCount + 1;
    }
    previous = self->pool;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->pool = pool;
}
extern "C" void FUN_002dcaa0(PoolOwner *self, int open) {
    if (open != 0) {
        if (self->pool == 0) {
            igSmartPointer<RefPool> created(FUN_002ba650(igObject_GetAllocator(self)));
            created.get()->open();
            setPool(self, created.get());
        }
    } else {
        if (self->pool != 0) {
            igSmartPointer<RefPool> kept(self->pool);
            kept.retain();
            setPool(self, 0);
            if (kept.get() != 0) {
                kept.get()->close();
            }
        }
    }
}
