/* Exact descriptor factories and post-construction defaults. Virtual classes are ABI slot
 * projections; do not instantiate. Physical factory flag 1 is preserved at constructor calls; no
 * wider constructor ABI is inferred. Recovery notes: docs/engine/field-factories.md. */
extern "C" {
/* Class registration guards: each is igMetaObject_RunStaticInit(<Class>_Register). */
int igStringMetaField_EnsureRegistered(...);
int igObjectRefMetaField_EnsureRegistered(...);
int igIntMetaField_EnsureRegistered(...);
void **igObject_AllocateRawStorage(...);
void **igStringMetaField_Construct(...);
void **igObjectRefMetaField_Construct(...);
void **igIntMetaField_Construct(...);
void **igMetaObject_CreateInstance(...);
void Gap__Core__igObject__vfunc_09(void *);
extern int g_igStringMetaField_metaObject[4];
extern int g_igObjectRefMetaField_metaObject[4];
extern int g_igIntMetaField_metaObject[4];
/* Pointer to the object-system state; its first byte is nonzero once the
 * reflection system is live (docs/engine/field-factories.md, "Factory modes"). */
extern unsigned char * g_objectSystem[4];
void **igStringMetaField_Create(int allocator);
void **igObjectRefMetaField_Create(int allocator);
void **igIntMetaField_Create(int allocator);
void igObjectRefMetaField_InitDefaults(void **self);
void igStringMetaField_InitDefaults(void **self);
}

/* igObject vtable slot projections, named by vfunc index (vtable byte offsets
 * 44, 36 and 140).  vfunc_09 and vfunc_07 are the no-op base hooks 0x2ff140
 * and 0x2ff0e0; vfunc_33 is the default-value setter. */
class igObjectSlot09 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void vfunc_09(); };
class igObjectSlot07 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void vfunc_07(int); };
class igObjectSlot33 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void vfunc_33(int); };

/* 0x002b9750
 * Factory for an igStringMetaField (60-byte instance).  Once the object
 * system is live, ensure the class is registered and let its MetaObject
 * create the instance with the given allocator.  Before that, allocate by
 * hand, construct in place (second argument 1 is the flag retail passes) and
 * run the post-construction hooks, vfunc_09 then vfunc_07(0). */
void **igStringMetaField_Create(int allocator) {
    void **field;

    if (*g_objectSystem[0] != 0) {
        igStringMetaField_EnsureRegistered();
        field = igMetaObject_CreateInstance(g_igStringMetaField_metaObject[0], allocator);
    } else {
        field = igObject_AllocateRawStorage(0x3C, 0, allocator);
        if (field != 0) {
            field = igStringMetaField_Construct(field, 1);
        }
        ((igObjectSlot09 *)field)->vfunc_09();
        ((igObjectSlot07 *)field)->vfunc_07(0);
    }
    return field;
}

/* 0x002bce90
 * Same factory shape for an igObjectRefMetaField (68-byte instance). */
void **igObjectRefMetaField_Create(int allocator) {
    void **field;

    if (*g_objectSystem[0] != 0) {
        igObjectRefMetaField_EnsureRegistered();
        field = igMetaObject_CreateInstance(g_igObjectRefMetaField_metaObject[0], allocator);
    } else {
        field = igObject_AllocateRawStorage(0x44, 0, allocator);
        if (field != 0) {
            field = igObjectRefMetaField_Construct(field, 1);
        }
        ((igObjectSlot09 *)field)->vfunc_09();
        ((igObjectSlot07 *)field)->vfunc_07(0);
    }
    return field;
}

/* 0x002c2cf0
 * Same factory shape for an igIntMetaField (52-byte instance). */
void **igIntMetaField_Create(int allocator) {
    void **field;

    if (*g_objectSystem[0] != 0) {
        igIntMetaField_EnsureRegistered();
        field = igMetaObject_CreateInstance(g_igIntMetaField_metaObject[0], allocator);
    } else {
        field = igObject_AllocateRawStorage(0x34, 0, allocator);
        if (field != 0) {
            field = igIntMetaField_Construct(field, 1);
        }
        ((igObjectSlot09 *)field)->vfunc_09();
        ((igObjectSlot07 *)field)->vfunc_07(0);
    }
    return field;
}

/* 0x00303350
 * Post-construction defaults of an igObjectRefMetaField: run the base hook,
 * then the default setter (vfunc_33) with a null source. */
void igObjectRefMetaField_InitDefaults(void **self) {
    Gap__Core__igObject__vfunc_09(self);
    ((igObjectSlot33 *)self)->vfunc_33(0);
}

/* 0x0030a820
 * Post-construction defaults of an igStringMetaField; same two steps. */
void igStringMetaField_InitDefaults(void **self) {
    Gap__Core__igObject__vfunc_09(self);
    ((igObjectSlot33 *)self)->vfunc_33(0);
}
