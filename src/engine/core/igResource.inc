igMetaObject *g_igResource_metaObject;
igMetaField *g_igResource_imageDirectoryMetaField;
igMetaField *g_igResource_directoryListMetaField;
igMetaField *g_igResource_relativeFilePathMetaField;
igMetaField *g_igResource_absoluteFilePathMetaField;
igMetaField *g_igResource_asyncLoadStateMetaField;
igMetaField *g_igResource_loadQueueMetaField;
igMetaField *g_igResource_loadThreadMetaField;
igMetaField *g_igResource_autoCompatibilityMetaField;
igMetaField *g_igResource_alignmentStringsMetaField;
igMetaField *g_igResource_alignmentValuesMetaField;
igMetaField *g_igResource_postProcessAsyncronousFilesStateMetaField;
igMetaField *g_igResource_temporaryMemoryPoolMetaField;
igMetaField *g_igResource_dataMemoryPoolMetaField;
igMetaField *g_igResource_objectMemoryPoolMetaField;
igMetaField *g_igResource_IGBSharingStateMetaField;
igMetaField *g_igResource_IGBChunkSizeMetaField;
igMetaField *g_igResource_useMemoryPoolAssignmentsStateMetaField;

void *igResource_Create(int pool) {
    igResource_EnsureRegistered();
    return (void *)igMetaObject_CreateInstance(g_igResource_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igResource_GetOrCreateMetaObject(void) {
    if (g_igResource_metaObject == 0) {
        g_igResource_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igResource_metaObject;
}

igMetaObject *igResource_GetMetaObject(void)
{
    igMetaObject *g = g_igResource_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igResource_EnsureRegistered();
    return g_igResource_metaObject;
}

int igResource_GetVTable(void) {
    igResource resource;
    int t;
    igObject_InitHeader((igObject *)&resource);
    resource._vtable = (int)&g_igResource_vtable[0];
    resource._imageDirectory = 0;
    resource._directoryList = 0;
    resource._relativeFilePath = 0;
    resource._absoluteFilePath = 0;
    resource._loadQueue = 0;
    resource._loadThread = 0;
    resource._alignmentStrings = 0;
    resource._alignmentValues = 0;
    resource._temporaryMemoryPool = 0;
    resource._dataMemoryPool = 0;
    resource._objectMemoryPool = 0;
    t = *(int *)((char *)&resource + g_objectSystem->vtableProbeOffset);
    resource._vtable = (int)&g_igResource_vtable[0];
    igSmartPointer_igMemoryPool_Destruct((igSmartPointer<igObject> *)&resource._objectMemoryPool, -1);
    igSmartPointer_igMemoryPool_Destruct((igSmartPointer<igObject> *)&resource._dataMemoryPool, -1);
    igSmartPointer_igMemoryPool_Destruct((igSmartPointer<igObject> *)&resource._temporaryMemoryPool, -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&resource._alignmentValues, -1);
    igSmartPointer_igStringObjList_Destruct((igSmartPointer<igObject> *)&resource._alignmentStrings, -1);
    igSmartPointer_igThread_Destruct((igSmartPointer<igObject> *)&resource._loadThread, -1);
    igSmartPointer_igQueue_Destruct((igQueue **)&resource._loadQueue, -1);
    igStringRef_Destruct((igStringRef *)&resource._absoluteFilePath, -1);
    igStringRef_Destruct((igStringRef *)&resource._relativeFilePath, -1);
    igSmartPointer_igDirectoryList_Destruct((igSmartPointer<igObject> *)&resource._directoryList, -1);
    igSmartPointer_igDirectory_Destruct((igSmartPointer<igObject> *)&resource._imageDirectory, -1);
    return t;
}

igSmartPointer<igObject> *igSmartPointer_igDirectoryList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igQueue **igSmartPointer_igQueue_Destruct(igQueue **self, short deleteFlag) {
    if (self) {
        igQueue *queue = *self;
        if (queue) { queue->_refCount -= 1; if ((queue->_refCount & 0x7fffff) == 0) igObject_Destroy(queue); }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

void igResource_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igResource_Register);
}

static igMetaObjectCallback g_igResource_callbackList[] = { igDirectory_EnsureRegistered, igDirectoryList_EnsureRegistered, igQueue_EnsureRegistered, igThread_EnsureRegistered, igStringObjList_EnsureRegistered, igIntList_EnsureRegistered, igMemoryPool_EnsureRegistered, 0 };

CallbackArray *igResource_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igResource_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igResource_GetMetaObjectFunction,
        "igResource",
        0x4C,
        igResource_GetVTable,
        igResource_InitFields,
        0,
        g_igResource_callbackList
    );
}

void igResource_GetMetaObjectFunction(void) {
    igResource_GetMetaObject();
}

static FieldFactory g_igResource_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igResource_fieldTable[] = {
    "_imageDirectory",
    "_directoryList",
    "_relativeFilePath",
    "_absoluteFilePath",
    "_asyncLoadState",
    "_loadQueue",
    "_loadThread",
    "_autoCompatibility",
    "_alignmentStrings",
    "_alignmentValues",
    "_postProcessAsyncronousFilesState",
    "_temporaryMemoryPool",
    "_dataMemoryPool",
    "_objectMemoryPool",
    "_IGBSharingState",
    "_IGBChunkSize",
    "_useMemoryPoolAssignmentsState",
};
static igMetaField **g_igResource_fieldDescriptors[] = {
    &g_igResource_imageDirectoryMetaField,
    &g_igResource_directoryListMetaField,
    &g_igResource_relativeFilePathMetaField,
    &g_igResource_absoluteFilePathMetaField,
    &g_igResource_asyncLoadStateMetaField,
    &g_igResource_loadQueueMetaField,
    &g_igResource_loadThreadMetaField,
    &g_igResource_autoCompatibilityMetaField,
    &g_igResource_alignmentStringsMetaField,
    &g_igResource_alignmentValuesMetaField,
    &g_igResource_postProcessAsyncronousFilesStateMetaField,
    &g_igResource_temporaryMemoryPoolMetaField,
    &g_igResource_dataMemoryPoolMetaField,
    &g_igResource_objectMemoryPoolMetaField,
    &g_igResource_IGBSharingStateMetaField,
    &g_igResource_IGBChunkSizeMetaField,
    &g_igResource_useMemoryPoolAssignmentsStateMetaField,
};
static int g_igResource_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
    8,
};

void igResource_InitFields(void) {
    int base;
    void *imageDirectoryField;
    void *directoryListField;
    void *loadQueueField;
    void *loadThreadField;
    void *alignmentStringsField;
    void *alignmentValuesField;
    void *temporaryMemoryPoolField;
    void *dataMemoryPoolField;
    void *objectMemoryPoolField;
    void *meta;

    meta = (void *)g_igResource_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igResource_ctorTable, 0x11);
    imageDirectoryField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)imageDirectoryField)->_metaObject = (int)igDirectory_GetOrCreateMetaObject();
    directoryListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)directoryListField)->_metaObject = (int)igDirectoryList_GetOrCreateMetaObject();
    ((igRefMetaField *)directoryListField)->_construct = 1;
    ((igMetaField *)directoryListField)->_persistent = 0;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3), 0);
    loadQueueField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5)));
    ((igObjectRefMetaField *)loadQueueField)->_metaObject = (int)igQueue_GetOrCreateMetaObject();
    loadThreadField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6)));
    ((igObjectRefMetaField *)loadThreadField)->_metaObject = (int)igThread_GetOrCreateMetaObject();
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7)))->setDefault(1);
    alignmentStringsField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 8)));
    ((igObjectRefMetaField *)alignmentStringsField)->_metaObject = (int)igStringObjList_GetOrCreateMetaObject();
    ((igMetaField *)alignmentStringsField)->_persistent = 0;
    alignmentValuesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 9)));
    ((igObjectRefMetaField *)alignmentValuesField)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igMetaField *)alignmentValuesField)->_persistent = 0;
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xA)))->setDefault(1);
    temporaryMemoryPoolField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xB)));
    ((igObjectRefMetaField *)temporaryMemoryPoolField)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    dataMemoryPoolField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xC)));
    ((igObjectRefMetaField *)dataMemoryPoolField)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    objectMemoryPoolField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xD)));
    ((igObjectRefMetaField *)objectMemoryPoolField)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xE)))->setDefault(1);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xF)))->setDefault(0x20000);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x10)))->setDefault(1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igResource_fieldTable, g_igResource_fieldDescriptors, g_igResource_fieldOffsets, base);
}

