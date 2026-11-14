void *igResource_Create(int pool) {
    igResource_EnsureRegistered();
    return (void *)igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585978), (igMemoryPoolView *)pool);
}

igMetaObject *igResource_GetOrCreateMetaObject(void) {
    if (g_igResource_metaObject[0] == 0) {
        g_igResource_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igResource_metaObject[0];
}

igMetaObject *igResource_GetMetaObject(void)
{
    igMetaObject *g = g_igResource_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igResource_EnsureRegistered();
    return g_igResource_metaObject[0];
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
    t = *(int *)((char *)&resource + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    resource._vtable = (int)&g_igResource_vtable[0];
    igSmartPointer_igMemoryPool_Destruct(&resource._objectMemoryPool, -1);
    igSmartPointer_igMemoryPool_Destruct(&resource._dataMemoryPool, -1);
    igSmartPointer_igMemoryPool_Destruct(&resource._temporaryMemoryPool, -1);
    igSmartPointer_igIntList_Destruct(&resource._alignmentValues, -1);
    igSmartPointer_igStringObjList_Destruct(&resource._alignmentStrings, -1);
    igSmartPointer_igThread_Destruct(&resource._loadThread, -1);
    igSmartPointer_igQueue_Destruct((igQueue **)&resource._loadQueue, -1);
    igStringRef_Destruct(&resource._absoluteFilePath, -1);
    igStringRef_Destruct(&resource._relativeFilePath, -1);
    igSmartPointer_igDirectoryList_Destruct((void **)&resource._directoryList, -1);
    igSmartPointer_igDirectory_Destruct(&resource._imageDirectory, -1);
    return t;
}

void **igSmartPointer_igDirectoryList_Destruct(void **self, long long deleteFlag) {
    igObject *object;

    if (self != 0) {
        object = (igObject *)*self;
        if (object != 0) {
            object->_refCount = object->_refCount - 1;
            if ((object->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
        if ((short)deleteFlag > 0) {
            __dl__FPv(self);
        }
    }
    return self;
}

igQueue **igSmartPointer_igQueue_Destruct(igQueue **self, short deleteFlag) {
    if (self) {
        igQueue *queue = *self;
        if (queue) { queue->_refCount -= 1; if ((queue->_refCount & 0x7fffff) == 0) igObject_Destroy(queue); }
        if (deleteFlag > 0) __dl__FPv(self);
    }
    return self;
}

void igResource_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igResource_Register);
}

void igResource_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igResource_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igResource_GetMetaObjectFunction,
        igResource_className,
        0x4C,
        igResource_GetVTable,
        igResource_InitFields,
        0,
        (igMetaObjectCallback *)g_igResource_callbackList
    );
}

void igResource_GetMetaObjectFunction(void) {
    igResource_GetMetaObject();
}

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

    meta = (void *)g_igResource_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igResource_ctorTable[0], 0x11);
    imageDirectoryField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)imageDirectoryField)->_metaObject = (int)igDirectory_GetOrCreateMetaObject();
    directoryListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)directoryListField)->_metaObject = (int)igDirectoryList_GetOrCreateMetaObject();
    ((igRefMetaField *)directoryListField)->_construct = 1;
    ((igMetaField *)directoryListField)->_persistent = 0;
    igStringMetaField_SetDefaultText((int *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2))), 0);
    igStringMetaField_SetDefaultText((int *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3))), 0);
    loadQueueField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5)));
    ((igObjectRefMetaField *)loadQueueField)->_metaObject = (int)igQueue_GetOrCreateMetaObject();
    loadThreadField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6)));
    ((igObjectRefMetaField *)loadThreadField)->_metaObject = (int)igThread_GetOrCreateMetaObject();
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7))), 1);
    alignmentStringsField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 8)));
    ((igObjectRefMetaField *)alignmentStringsField)->_metaObject = (int)igStringObjList_GetOrCreateMetaObject();
    ((igMetaField *)alignmentStringsField)->_persistent = 0;
    alignmentValuesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 9)));
    ((igObjectRefMetaField *)alignmentValuesField)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igMetaField *)alignmentValuesField)->_persistent = 0;
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xA))), 1);
    temporaryMemoryPoolField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xB)));
    ((igObjectRefMetaField *)temporaryMemoryPoolField)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    dataMemoryPoolField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xC)));
    ((igObjectRefMetaField *)dataMemoryPoolField)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    objectMemoryPoolField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xD)));
    ((igObjectRefMetaField *)objectMemoryPoolField)->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xE))), 1);
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xF))), 0x20000);
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x10))), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igResource_fieldTable[0], (igMetaField ***)&g_igResource_fieldDescriptors[0], &g_igResource_fieldOffsets[0], base);
}

