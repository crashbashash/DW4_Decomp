/* Factory for an igMetaObject (100-byte instance). Once the object system is live, ensure the
 * class is registered (igMetaObject_EnsureRegistered runs
 * igMetaObject_RunStaticInit(igMetaObject_Register)) and let its MetaObject create the instance
 * with the given allocator. Before that, allocate by hand, construct in place (second argument 1
 * is the flag retail passes) and run the post-construction hooks, vfunc_09 then vfunc_07(0). Same
 * factory shape as the other metafield factories in src/engine/field-descriptor-factories.cpp. */
extern "C" {
int igMetaObject_EnsureRegistered(...);
void **igObject_AllocateRawStorage(...);
void **igMetaObject_Construct(...);
void **igMetaObject_CreateInstance(...);
extern int g_igMetaObject_metaObject[4];
/* Pointer to the object-system state; its first byte is nonzero once the
 * reflection system is live (docs/engine/field-factories.md, "Factory modes"). */
extern unsigned char * g_objectSystem[4];
void **igMetaObject_Create(int allocator);
}

/* igObject vtable slot projections (vtable byte offsets 44 and 36), named by
 * vfunc index.  ABI views only: never instantiated. */
class igObjectSlot09 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual int vfunc_09(); };
class igObjectSlot07 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual int vfunc_07(int); };
void **igMetaObject_Create(int allocator) {
    void **metaObject;

    if (*g_objectSystem[0] != 0) {
        igMetaObject_EnsureRegistered();
        metaObject = (void **)(igMetaObject_CreateInstance(g_igMetaObject_metaObject[0], allocator));
    } else {
        metaObject = (void **)(igObject_AllocateRawStorage(0x64, 0, allocator));
        if (metaObject != 0) {
            metaObject = (void **)(igMetaObject_Construct(metaObject, 1));
        }
        ((igObjectSlot09 *)(metaObject))->vfunc_09();
        ((igObjectSlot07 *)(metaObject))->vfunc_07((int)(0));
    }
    return metaObject;
}
