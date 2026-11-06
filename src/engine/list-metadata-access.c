/* src/engine/list-metadata-access.c — list metadata allocation and default scalar descriptor publication accessors
 *
 * One translation unit: 6 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
/* Meta-field default descriptors. Each getter returns the class's published descriptor, running
 * the class's registration wrapper first when nothing has been published yet. The wrapper at
 * 0x002b7500 has the same shape as igIntMetaField_EnsureRegistered: it passes the class's Register
 * routine (0x002b7510, igUnsignedCharMetaField_Register) to igMetaObject_RunStaticInit. */
int igUnsignedCharMetaField_EnsureRegistered();
extern int g_igUnsignedCharMetaField_descriptor[4];
int igObjectRefMetaField_EnsureRegistered();
extern int g_igObjectRefMetaField_descriptor[4];
int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int g_igObjectList_metaObject[4];
/* Allocator key used for every metadata allocation (docs/engine/list-registration.md,
 * "Allocation-only getters": allocator key 587040). */
extern int g_metadataAllocatorKey[4];
int igIntMetaField_EnsureRegistered();
extern int g_igIntMetaField_descriptor[4];
extern int g_igDataList_metaObject[4];
extern int g_igIntList_metaObject[4];

/* 0x002b7660: default descriptor of igUnsignedCharMetaField, registered on first use. */
int igUnsignedCharMetaField_GetDefaultDescriptor(void) {
    if (g_igUnsignedCharMetaField_descriptor[0] == 0) {
        igUnsignedCharMetaField_EnsureRegistered();
    }
    return g_igUnsignedCharMetaField_descriptor[0];
}

/* 0x002bd2e0: default descriptor of igObjectRefMetaField, registered on first use. */
int igObjectRefMetaField_GetDefaultDescriptor(void) {
    if (g_igObjectRefMetaField_descriptor[0] == 0) {
        igObjectRefMetaField_EnsureRegistered();
    }
    return g_igObjectRefMetaField_descriptor[0];
}

/* 0x002bd6c0: igObjectList metaObject, created (allocation only, no field registration) when missing. */
int igObjectList_GetOrCreateMetaObject(void) {
    if (g_igObjectList_metaObject[0] == 0) {
        g_igObjectList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igObjectList_metaObject[0];
}

/* 0x002c3090: default descriptor of igIntMetaField, registered on first use. */
int igIntMetaField_GetDefaultDescriptor(void) {
    if (g_igIntMetaField_descriptor[0] == 0) {
        igIntMetaField_EnsureRegistered();
    }
    return g_igIntMetaField_descriptor[0];
}

/* 0x002c8490: igDataList metaObject, created (allocation only) when missing. */
int igDataList_GetOrCreateMetaObject(void) {
    if (g_igDataList_metaObject[0] == 0) {
        g_igDataList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igDataList_metaObject[0];
}

/* 0x002caab0: igIntList metaObject, created (allocation only) when missing. */
int igIntList_GetOrCreateMetaObject(void) {
    if (g_igIntList_metaObject[0] == 0) {
        g_igIntList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igIntList_metaObject[0];
}
