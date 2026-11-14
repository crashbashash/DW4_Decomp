void * igDirectory_Create(int allocator) {
    igDirectory_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586668), (igMemoryPoolView *)allocator));
}

igMetaObject *igDirectory_GetOrCreateMetaObject(void) {
    if (g_igDirectory_metaObject[0] == 0) {
        g_igDirectory_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igDirectory_metaObject[0];
}

igMetaObject *igDirectory_GetMetaObject(void)
{
    igMetaObject *g = g_igDirectory_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDirectory_EnsureRegistered();
    return g_igDirectory_metaObject[0];
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
    vtable = *(int *)((char *)&dir + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    dir._vtable = (int)&g_igDirectory_vtable[0];
    igSmartPointer_igSemaphore_Destruct((igObject **)&dir._loadingSemaphore, -1);
    igSmartPointer_igShortListList_Destruct((igSmartPointer<igObject> *)p188, -1);
    FUN_00135430(p172, -1);
    FUN_001d36d0(p168, -1);
    FUN_001d35d0(p156, -1);
    igSmartPointer_igDirectoryList_Destruct((void **)p152, -1);
    StringRef_Destruct_00130720(p148, -1);
    return vtable;
}

void igDirectory_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDirectory_Register);
}

void igDirectory_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igDirectory_metaObject,
        (igMetaObjectRegisterFunction)igObjectList_Register,
        (igMetaObjectGetFunction)igObjectList_GetPublishedMetaObject,
        igDirectory_GetMetaObjectFunction,
        igDirectory_className,
        0x48,
        igDirectory_GetVTable,
        igDirectory_InitFields,
        igDirectory_StaticInitCallback,
        (igMetaObjectCallback *)g_igDirectory_callbackList
    );
}

void igDirectory_GetMetaObjectFunction(void) {
    igDirectory_GetMetaObject();
}

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

    meta = (void *)g_igDirectory_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igDirectory_ctorTable[0], 0x12);
    nameField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    igStringMetaField_SetDefaultText((int *)nameField, 0);
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
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5))), 1);
    metaFieldPerObjectIndicesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 8)));
    ((igObjectRefMetaField *)metaFieldPerObjectIndicesField)->_metaObject = (int)igShortListList_GetOrCreateMetaObject();
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xA))), 1);
    uniqueEntryListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xC)));
    ((igObjectRefMetaField *)uniqueEntryListField)->_metaObject = (int)igDirectory_GetOrCreateMetaObject();
    refListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xD)));
    ((igObjectRefMetaField *)refListField)->_metaObject = (int)igPointerList_GetOrCreateMetaObject();
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xE))), 1);
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xF))), 1);
    loadingSemaphoreField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x11)));
    ((igObjectRefMetaField *)loadingSemaphoreField)->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)loadingSemaphoreField)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igDirectory_fieldTable[0], (igMetaField ***)&g_igDirectory_fieldDescriptors[0], &g_igDirectory_fieldOffsets[0], base);
}

void igDirectory_StaticInitCallback(void) {
    igDirectory_RegisterDependentMetaObjects();
}

