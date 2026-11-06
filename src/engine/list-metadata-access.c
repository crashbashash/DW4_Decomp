/* Meta-field default descriptors. Each getter returns the class's published descriptor, running
 * the class's registration wrapper first when nothing has been published yet. */
int igUnsignedCharMetaField_EnsureRegistered();
extern int g_igUnsignedCharMetaField_descriptor[4];
int igObjectRefMetaField_EnsureRegistered();
extern int g_igObjectRefMetaField_descriptor[4];
int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int g_igObjectList_metaObject[4];
extern int g_metadataAllocatorKey[4];
int igIntMetaField_EnsureRegistered();
extern int g_igIntMetaField_descriptor[4];
extern int g_igDataList_metaObject[4];
extern int g_igIntList_metaObject[4];

int igUnsignedCharMetaField_GetDefaultDescriptor(void) {
    if (g_igUnsignedCharMetaField_descriptor[0] == 0) {
        igUnsignedCharMetaField_EnsureRegistered();
    }
    return g_igUnsignedCharMetaField_descriptor[0];
}

int igObjectRefMetaField_GetDefaultDescriptor(void) {
    if (g_igObjectRefMetaField_descriptor[0] == 0) {
        igObjectRefMetaField_EnsureRegistered();
    }
    return g_igObjectRefMetaField_descriptor[0];
}

/* Created with allocation only, no field registration, when missing. */
int igObjectList_GetOrCreateMetaObject(void) {
    if (g_igObjectList_metaObject[0] == 0) {
        g_igObjectList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igObjectList_metaObject[0];
}

int igIntMetaField_GetDefaultDescriptor(void) {
    if (g_igIntMetaField_descriptor[0] == 0) {
        igIntMetaField_EnsureRegistered();
    }
    return g_igIntMetaField_descriptor[0];
}

/* Created with allocation only when missing. */
int igDataList_GetOrCreateMetaObject(void) {
    if (g_igDataList_metaObject[0] == 0) {
        g_igDataList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igDataList_metaObject[0];
}

/* Created with allocation only when missing. */
int igIntList_GetOrCreateMetaObject(void) {
    if (g_igIntList_metaObject[0] == 0) {
        g_igIntList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igIntList_metaObject[0];
}
