#include "dw4/igSmartPointer.h"

struct Rc : public igObject { };
class Lock : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int tryLock(int); };
extern "C" {
Rc *FUN_002279d0(int);
int igLockBase_GetMetaObject();
int FUN_0022a8d0(Rc *, int);
Lock *FUN_0022a950(Rc *);
int FUN_0022a9d0(Rc *);
int FUN_002fd610(Lock **, Lock *);
int FUN_002295b0(int, Lock *);
int Gap__igLockInterface__vfunc_27(int self, int mode);
}

struct LockRef {
    Lock *p;
    LockRef() {}
    void attach(Lock *lock) {
        p = lock;
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
    }
    ~LockRef() {
        Lock *lock = get();
        if (lock != 0) {
            lock->_refCount = lock->_refCount - 1;
            if ((lock->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(lock);
            }
        }
    }
    Lock *get() const { return p; }
};
struct Tag { };
static inline Rc *createIterator() {
    Tag tag = Tag();
    return FUN_002279d0(0);
}
int Gap__igLockInterface__vfunc_27(int self, int mode) {
    Lock *found;
    igSmartPointer<Rc> iterator(createIterator());
    FUN_0022a8d0(iterator.p, igLockBase_GetMetaObject());
    for (;;) {
        found = FUN_0022a950(iterator.p);
        if (((found != 0) ^ 1) != 0) {
            break;
        }
        FUN_0022a9d0(iterator.p);
        LockRef lock;
        Lock *created;
        FUN_002fd610(&created, found);
        lock.attach(created);
        if (created != 0) {
            created->_refCount = created->_refCount - 1;
            if ((created->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(created);
            }
        }
        if (lock.get() == 0) {
            continue;
        }
        FUN_002295b0(self, lock.get());
        if (lock.get()->tryLock(mode) != 0) {
            return 1;
        }
    }
    return 0;
}
