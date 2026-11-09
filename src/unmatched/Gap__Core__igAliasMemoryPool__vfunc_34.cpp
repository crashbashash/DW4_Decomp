#include "dw4/reflected.h"
extern "C" {
void *FUN_002ba650(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_004fb410[4];
}
struct LockStatus { int v; LockStatus() {} LockStatus(int x) { v = x; } };
class Lock { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual LockStatus open(); virtual LockStatus close(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual LockStatus wait(int); int references; };
struct LockRef {
    Lock *p;
    LockRef(Lock *lock) : p(lock) {}
    ~LockRef() {
        Lock *lock = p;
        if (lock != 0) {
            lock->references = lock->references - 1;
            if ((lock->references & 0x7FFFFF) == 0) {
                igObject_Destroy(lock);
            }
        }
    }
    void retain() const {
        Lock *lock = p;
        if (lock != 0) {
            lock->references = lock->references + 1;
        }
    }
    Lock *get() const { return p; }
};
static inline void setLock(igAliasMemoryPool *pool, Lock *lock) {
    Lock *previous;
    if (lock != 0) {
        lock->references = lock->references + 1;
    }
    previous = (Lock *)pool->_allocationLock;
    if (previous != 0) {
        previous->references = previous->references - 1;
        if ((previous->references & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    pool->_allocationLock = (int)lock;
}
extern "C" LockStatus Gap__Core__igAliasMemoryPool__vfunc_34(igAliasMemoryPool *pool, int enable);
LockStatus Gap__Core__igAliasMemoryPool__vfunc_34(igAliasMemoryPool *pool, int enable) {
    if ((enable & 0xFF) == 0) {
        LockRef kept((Lock *)pool->_allocationLock);
        kept.retain();
        setLock(pool, 0);
        if (kept.get() != 0) {
            kept.get()->wait(1);
            kept.get()->close();
        }
    } else if ((enable & 0xFF) == 1) {
        if (pool->_allocationLock != 0) {
            return DAT_004fb410[0];
        }
        LockRef created((Lock *)FUN_002ba650(igObject_GetAllocator(pool)));
        created.get()->open();
        setLock(pool, created.get());
    }
    return DAT_004fb410[0];
}
