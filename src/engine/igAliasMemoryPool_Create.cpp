/* 0x002cd170 — igAliasMemoryPool_Create
 * Class factory of igAliasMemoryPool (finding #900, docs/engine/alias-pool-binding.md,
 * "Original factory").  Once the object system is running it registers the class and
 * creates the pool through its metaobject on `allocator`.  During bootstrap, before
 * the object system exists, it allocates the 184-byte pool by hand, constructs it,
 * and then runs virtual slot 44 and slot 36 (with 0) on it.  Retail does not guard
 * those calls against a failed allocation; neither does this.
 * FactoryPoolView is an ABI dispatch view of slots 36 and 44 and must not be
 * instantiated. */
class FactoryPoolView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void Set(int); virtual void d8(); virtual void Init(); };
extern "C" {
/* Object-system pointer; its byte 0 is the "object system active" flag. */
extern unsigned char *g_objectSystem_00586dc8[4];
extern void *g_igAliasMemoryPool_metaObject_005869b0[4];
/* Runs the static initialisation of the igAliasMemoryPool class (igMetaObject_RunStaticInit
 * applied to igAliasMemoryPool_Register). */
void igAliasMemoryPool_EnsureRegistered();
FactoryPoolView *igMetaObject_CreateInstance(void *,void *);
FactoryPoolView *FUN_002f0040(int,int,void *);
FactoryPoolView *igAliasMemoryPool_Construct(FactoryPoolView *,int);
}
extern "C" FactoryPoolView *igAliasMemoryPool_Create(void *allocator) {
    FactoryPoolView *pool;
    if (*g_objectSystem_00586dc8[0]) {
        igAliasMemoryPool_EnsureRegistered();
        pool=igMetaObject_CreateInstance(g_igAliasMemoryPool_metaObject_005869b0[0],allocator);
    } else {
        pool=FUN_002f0040(184,0,allocator);
        if(pool)pool=igAliasMemoryPool_Construct(pool,1);
        pool->Init();
        pool->Set(0);
    }
    return pool;
}
