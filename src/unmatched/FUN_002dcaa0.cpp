extern "C" {
int igObject_Destroy(...);
int igObject_GetAllocator(...);
}
struct PoolStatus { int a; };
class RefPool { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual PoolStatus open();
    virtual PoolStatus close();
    int references;
};
extern "C" RefPool *FUN_002ba650(...);
struct PoolRef {
    RefPool *p;
    PoolRef(RefPool *pool) : p(pool) {}
    ~PoolRef() {
        RefPool *pool = p;
        if (pool != 0) {
            pool->references = pool->references - 1;
            if ((pool->references & 0x7FFFFF) == 0) {
                igObject_Destroy(pool);
            }
        }
    }
    void retain() const {
        RefPool *pool = p;
        if (pool != 0) {
            pool->references = pool->references + 1;
        }
    }
    RefPool *get() const { return p; }
};
struct PoolOwner { char p[8]; RefPool *pool; };
static inline void setPool(PoolOwner *self, RefPool *pool) {
    RefPool *previous;
    if (pool != 0) {
        pool->references = pool->references + 1;
    }
    previous = self->pool;
    if (previous != 0) {
        previous->references = previous->references - 1;
        if ((previous->references & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->pool = pool;
}
extern "C" void FUN_002dcaa0(PoolOwner *self, int open) {
    if (open != 0) {
        if (self->pool == 0) {
            PoolRef created(FUN_002ba650(igObject_GetAllocator(self)));
            created.get()->open();
            setPool(self, created.get());
        }
    } else {
        if (self->pool != 0) {
            PoolRef kept(self->pool);
            kept.retain();
            setPool(self, 0);
            if (kept.get() != 0) {
                kept.get()->close();
            }
        }
    }
}
