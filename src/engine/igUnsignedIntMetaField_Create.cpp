/* Factory for an igUnsignedIntMetaField (52-byte instance). Once the object system is live, ensure
 * the class is registered and let its MetaObject create the instance with the given allocator.
 * Before that, allocate by hand, construct in place (second argument 1) and run the post-
 * construction hooks, vfunc_09 then vfunc_07(0). */
extern "C" {
int igUnsignedIntMetaField_EnsureRegistered(...);
void **igObject_AllocateRawStorage(...);
void **igUnsignedIntMetaField_Construct(...);
void **igMetaObject_CreateInstance(...);
extern int g_igUnsignedIntMetaField_metaObject[4];
/* Pointer to the object-system state; its first byte is nonzero once the reflection system is
 * live. */
extern unsigned char * g_objectSystem[4];
void **igUnsignedIntMetaField_Create(int allocator);
}

/* igObject vtable slot projections (vtable byte offsets 44 and 36), named by
 * vfunc index.  ABI views only: never instantiated. */
class igObjectSlot09 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual int vfunc_09(); };
class igObjectSlot07 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual int vfunc_07(int); };
void **igUnsignedIntMetaField_Create(int allocator) {
    void **field;

    if (*g_objectSystem[0] != 0) {
        igUnsignedIntMetaField_EnsureRegistered();
        field = (void **)(igMetaObject_CreateInstance(g_igUnsignedIntMetaField_metaObject[0], allocator));
    } else {
        field = (void **)(igObject_AllocateRawStorage(0x34, 0, allocator));
        if (field != 0) {
            field = (void **)(igUnsignedIntMetaField_Construct(field, 1));
        }
        ((igObjectSlot09 *)(field))->vfunc_09();
        ((igObjectSlot07 *)(field))->vfunc_07((int)(0));
    }
    return field;
}
