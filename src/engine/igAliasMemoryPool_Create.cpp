/* Class factory of igAliasMemoryPool. Once the object system is running it registers the class and
 * creates the pool through its metaobject on `allocator`. During bootstrap, before the object
 * system exists, it allocates the 184-byte pool by hand, constructs it, and then runs virtual slot
 * 44 and slot 36 (with 0) on it. Those calls are not guarded against a failed allocation.
 * FactoryPoolView is an ABI dispatch view of slots 36 and 44 and must not be instantiated. */
class FactoryPoolView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void Set(int); virtual void d8(); virtual void Init(); };
extern "C" {
/* Object-system pointer; its byte 0 is the "object system active" flag. */
extern unsigned char *g_objectSystem[4];
extern void *g_igAliasMemoryPool_metaObject[4];
void igAliasMemoryPool_EnsureRegistered();
FactoryPoolView *igMetaObject_CreateInstance(void *,void *);
FactoryPoolView *FUN_002f0040(int,int,void *);
FactoryPoolView *igAliasMemoryPool_Construct(FactoryPoolView *,int);
}
extern "C" FactoryPoolView *igAliasMemoryPool_Create(void *allocator) {
    FactoryPoolView *pool;
    if (*g_objectSystem[0]) {
        igAliasMemoryPool_EnsureRegistered();
        pool=igMetaObject_CreateInstance(g_igAliasMemoryPool_metaObject[0],allocator);
    } else {
        pool=FUN_002f0040(184,0,allocator);
        if(pool)pool=igAliasMemoryPool_Construct(pool,1);
        pool->Init();
        pool->Set(0);
    }
    return pool;
}
