void * igDirectory_Create(int allocator) {
    igDirectory_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igDirectory_metaObject, (igMemoryPoolView *)allocator));
}

igMetaObject *igDirectory_GetOrCreateMetaObject(void) {
    if (g_igDirectory_metaObject == 0) {
        g_igDirectory_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igDirectory_metaObject;
}

igMetaObject *igDirectory_GetMetaObject(void)
{
    igMetaObject *g = g_igDirectory_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDirectory_EnsureRegistered();
    return g_igDirectory_metaObject;
}

int igDirectory_GetVTable(void) {
    igDirectory dir;
    int vtable;
    char *p188;
    char *p172;
    char *p168;
    char *p156;
    char *p152;
    char *p148;
    igObject_InitHeader((igObject *)&dir);
    dir._vtable = (int)&g_igDirectory_vtable[0];
    p148 = (char *)&dir._name;
    *(int *)p148 = 0;
    p152 = (char *)&dir._externalDirectoryList;
    *(int *)p152 = 0;
    p156 = (char *)&dir._infoList;
    *(int *)p156 = 0;
    p168 = (char *)&dir._uniqueEntryList;
    *(int *)p168 = 0;
    p172 = (char *)&dir._refList;
    *(int *)p172 = 0;
    p188 = (char *)&dir._metaFieldPerObjectIndices;
    *(int *)p188 = 0;
    dir._loadingSemaphore = 0;
    vtable = *(int *)((char *)&dir + g_objectSystem->vtableProbeOffset);
    dir._vtable = (int)&g_igDirectory_vtable[0];
    igSmartPointer_igSemaphore_Destruct((igObject **)&dir._loadingSemaphore, -1);
    igSmartPointer_igShortListList_Destruct((igSmartPointer<igObject> *)p188, -1);
    igSmartPointer_igPointerList_Destruct((igSmartPointer<igObject> *)p172, -1);
    igSmartPointer_igDirectory_Destruct((igSmartPointer<igObject> *)p168, -1);
    igSmartPointer_igInfoList_Destruct((igSmartPointer<igObject> *)p156, -1);
    igSmartPointer_igDirectoryList_Destruct((igSmartPointer<igObject> *)p152, -1);
    igStringRef_Destruct((igStringRef *)p148, -1);
    return vtable;
}

void igDirectory_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDirectory_Register);
}

static igMetaObjectCallback g_igDirectory_callbackList[] = { igDirEntry_EnsureRegistered, igDirectoryList_EnsureRegistered, igInfoList_EnsureRegistered, igResource_EnsureRegistered, igShortListList_EnsureRegistered, igPointerList_EnsureRegistered, igSemaphore_EnsureRegistered, 0 };

CallbackArray *igDirectory_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igDirectory_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igDirectory_GetMetaObjectFunction,
        "igDirectory",
        0x48,
        igDirectory_GetVTable,
        igDirectory_InitFields,
        igDirectory_StaticInitCallback,
        g_igDirectory_callbackList
    );
}

void igDirectory_GetMetaObjectFunction(void) {
    igDirectory_GetMetaObject();
}

static FieldFactory g_igDirectory_ctorTable[] = {
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igDirectory_fieldTable[] = {
    "_name",
    "_externalDirectoryList",
    "_infoList",
    "_managingResource",
    "_loadPendingState",
    "_validState",
    "_compatibleState",
    "_loadedRefCount",
    "_metaFieldPerObjectIndices",
    "_concreteState",
    "_sharingState",
    "_trackUniqueEntries",
    "_uniqueEntryList",
    "_refList",
    "_autoWriteFilePreProcessState",
    "_useMemoryPoolAssignmentsState",
    "_forceWriteMemoryPoolInfoFromMetaState",
    "_loadingSemaphore",
};
static igMetaField **g_igDirectory_fieldDescriptors[] = {
    &g_igDirectory_nameField,
    &g_igDirectory_externalDirectoryListMetaField,
    &g_igDirectory_infoListMetaField,
    &g_igDirectory_managingResourceMetaField,
    &g_igDirectory_loadPendingStateMetaField,
    &g_igDirectory_validStateMetaField,
    &g_igDirectory_compatibleStateMetaField,
    &g_igDirectory_loadedRefCountMetaField,
    &g_igDirectory_metaFieldPerObjectIndicesMetaField,
    &g_igDirectory_concreteStateMetaField,
    &g_igDirectory_sharingStateMetaField,
    &g_igDirectory_trackUniqueEntriesMetaField,
    &g_igDirectory_uniqueEntryListMetaField,
    &g_igDirectory_refListMetaField,
    &g_igDirectory_autoWriteFilePreProcessStateMetaField,
    &g_igDirectory_useMemoryPoolAssignmentsStateMetaField,
    &g_igDirectory_forceWriteMemoryPoolInfoFromMetaStateMetaField,
    &g_igDirectory_loadingSemaphoreMetaField,
};
static int g_igDirectory_fieldOffsets[] = {
    20,
    24,
    28,
    32,
    48,
    49,
    50,
    52,
    60,
    56,
    36,
    37,
    40,
    44,
    64,
    65,
    66,
    68,
};

void igDirectory_InitFields(void) {
    int base;
    void *externalDirectoryListField;
    void *infoListField;
    void *managingResourceField;
    void *metaFieldPerObjectIndicesField;
    void *uniqueEntryListField;
    void *refListField;
    void *loadingSemaphoreField;
    void *nameField;
    void *meta;

    meta = (void *)g_igDirectory_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igDirectory_ctorTable, 0x12);
    nameField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    igStringMetaField_SetDefaultText((igMetaField *)nameField, 0);
    ((igStringMetaField *)nameField)->_destruct = 1;
    externalDirectoryListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)externalDirectoryListField)->_metaObject = (int)igDirectoryList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)externalDirectoryListField)->_construct = 1;
    infoListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)infoListField)->_metaObject = (int)igInfoList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)infoListField)->_construct = 1;
    managingResourceField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igObjectRefMetaField *)managingResourceField)->_metaObject = (int)igResource_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)managingResourceField)->_refCounted = 0;
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5)))->setDefault(1);
    metaFieldPerObjectIndicesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 8)));
    ((igObjectRefMetaField *)metaFieldPerObjectIndicesField)->_metaObject = (int)igShortListList_GetOrCreateMetaObject();
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xA)))->setDefault(1);
    uniqueEntryListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xC)));
    ((igObjectRefMetaField *)uniqueEntryListField)->_metaObject = (int)igDirectory_GetOrCreateMetaObject();
    refListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xD)));
    ((igObjectRefMetaField *)refListField)->_metaObject = (int)igPointerList_GetOrCreateMetaObject();
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xE)))->setDefault(1);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xF)))->setDefault(1);
    loadingSemaphoreField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x11)));
    ((igObjectRefMetaField *)loadingSemaphoreField)->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)loadingSemaphoreField)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_igDirectory_fieldTable, g_igDirectory_fieldDescriptors, g_igDirectory_fieldOffsets, base);
}

void igDirectory_StaticInitCallback(void) {
    igDirectory_RegisterDependentMetaObjects();
}

