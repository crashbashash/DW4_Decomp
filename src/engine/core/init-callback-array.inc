void igObjectSystem_Startup(ObjectSystemView *self) {
    void *m;
    __internalObjectList *l;
    unsigned int n;
    int b;
    self->started = 1;
    SystemAllocator_EnsureCreated();
    self->vtableProbeOffset = 0;
    if (((MemoryContext * *)g_currentMemoryContext)[0] == 0) {
        m = igMemoryPoolContextInfo_Allocate(0x19F4);
        if (m != 0) m = igMemoryPoolContextInfo_Construct((MemoryContext *)m);
        ((MemoryContext * *)g_currentMemoryContext)[0] = (MemoryContext *)m;
    }
    ((MemoryContext * *)g_currentMemoryContext)[0]->CreateDefaultPools();
    self->metaRegistry = ((__internalObjectList *)InternalObjectList_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap))));
    l = (__internalObjectList *)self->metaRegistry;
    if (l->_data == 0) n = 0; else n = Memory_GetBufferSize((void *)l->_data) >> 2;
    if ((int)n < 0x401) ObjectPointerList_EnsureIndex((__internalNonRefCountedObjectList *)l, 0x400);
    self->metaEnumList = ((__internalObjectList *)InternalObjectList_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap))));
    b = ((int)Memory_AllocateDefaultBuffer((unsigned int)12));
    if (b != 0) b = ((int)igArray_Construct((CallbackArray *)b));
    self->exitCallbacks = (void *)b;
    b = ((int)Memory_AllocateDefaultBuffer((unsigned int)12));
    if (b != 0) b = ((int)igArray_Construct((CallbackArray *)b));
    self->registrationCallbacks = (void *)b;
    igMetaObject_EnsureRegistered();
    self->active = 1;
    self->bootMetaObjectCount = ((__internalObjectList *)self->metaRegistry)->_count;
    self->bootMetaFieldCount = g_metaFieldList[0]->_count;
    igMetaEnum_EnsureRegistered();
    igMallocMemoryPool_EnsureRegistered();
    igArenaMemoryPool_EnsureRegistered();
    igAliasMemoryPool_EnsureRegistered();
    igPageMemoryPool_EnsureRegistered();
    igMemoryDictionary_EnsureRegistered();
    igCharList_EnsureRegistered();
    igCharListNoClean_EnsureRegistered();
    igIntList_EnsureRegistered();
    igIntListNoClean_EnsureRegistered();
    igUnsignedIntList_EnsureRegistered();
    igUnsignedIntListNoClean_EnsureRegistered();
    igStringTable_EnsureRegistered();
    igSymbolTable_EnsureRegistered();
    igCallStackTable_EnsureRegistered();
    igCallStackTracer_EnsureRegistered();
    igPsx2CallStackTracer_EnsureRegistered();
    igLocationTable_EnsureRegistered();
    igEventTracker_EnsureRegistered();
    igFloatMetaField_EnsureRegistered();
    igLongMetaField_EnsureRegistered();
    igUnsignedCharMetaField_EnsureRegistered();
    ((int *)g_igRefMetaField_descriptor)[0] = igRawRefMetaField_GetDefaultDescriptor();
    ((MemoryContext * *)g_currentMemoryContext)[0]->vfunc_43();
}

int igObjectSystem_GetRootPath(int *p)
{
    return (int)((ObjectSystemView *)p)->rootPath.p;
}

int igObjectSystem_GetBasePath(int *p)
{
    return (int)((ObjectSystemView *)p)->basePath.p;
}

void igObjectSystem_InitPaths(ObjectSystemView *self) {
    igStringRef env;
    env = (char *)getenv(IG_ROOT);
    self->rootPath = env;
    self->basePath = (char *)text_dot;
    self->basePath = (char *)text_dot_dot;
}

igMetaObject *igMediaFile_GetPublishedMetaObject(void) {
    return g_igMediaFile_metaObject[0];
}

void igObjectSystem_PreExit(ObjectSystemView *self) {
    igEventTrackerView *tracker;

    self->preExitDone = 1;
    tracker = self->globalEventTracker;
    if (tracker != 0) {
        tracker->vfunc_46();
        igEventTracker_SetEventTag((igEventTrackerView *)self->globalEventTracker, (int)&text_exitPre[0]);
    }
}

void igObjectSystem_Exit(ObjectSystemView *self) {
    if (self->globalEventTracker != 0) {
        self->globalEventTracker->vfunc_47();
        igEventTracker_SetEventTag((igEventTrackerView *)self->globalEventTracker, (int)(&text_exitIn[0]));
    }
    if (self->saveEventTrackerOnExit != 0 && ((MemoryContext * *)g_currentMemoryContext)[0] != 0) {
        ((MemoryContext * *)g_currentMemoryContext)[0]->SaveEventTrackers();
    }
}

void igObjectSystem_Shutdown(ObjectSystemView *self) {
    int i;
    int pool;
    igObject *o;
    o = (igObject *)self->metaEnumList;
    o->_refCount = o->_refCount - 1;
    if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
    self->metaEnumList = 0;
    igAdxFile_SetBasePath(0);
    igArray_Destruct((CallbackArray *)self->registrationCallbacks, 1);
    if (g_currentMemoryContext[0] != 0) {
        g_currentMemoryContext[0]->RemoveAllAllocators();
    }
    InternalObjectList_SetCount((__internalObjectList *)g_metaFieldList[0], self->bootMetaFieldCount);
    for (i = self->metaObjectCount - 1; i >= self->bootMetaObjectCount; i--) {
        InternalObjectList_SetAtRetained((__internalObjectList *)self->metaRegistry, i, (igObject *)0);
    }
    self->active = 0;
    o = (igObject *)g_metaFieldList[0];
    o->_refCount = o->_refCount - 1;
    if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
    o = (igObject *)self->metaRegistry;
    o->_refCount = o->_refCount - 1;
    if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
    o = self->retainedObject;
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
    }
    if (g_stringPool[0] == 0) {
        pool = ((int)StringPool_Allocate(16));
        if (pool != 0) pool = ((int)StringPool_Construct((StringPool *)pool));
        g_stringPool[0] = pool;
    }
    StringPool_Destroy((StringPool *)g_stringPool[0], 1);
    self->started = 0;
    if (g_currentMemoryContext[0] != 0) {
        g_currentMemoryContext[0]->Shutdown();
        if (g_currentMemoryContext[0] != 0) {
            g_currentMemoryContext[0]->Destruct(1);
        }
        g_currentMemoryContext[0] = 0;
    }
    SystemAllocator_EnsureDestroyed();
}

/* Register a metaobject in the object system's registry, retaining it. */
void igObjectSystem_AppendMetaObject(void *system,igMetaObject *meta){
    MetaRefList_AppendRetained((__internalObjectList *)((ObjectSystemView *)system)->metaRegistry, (igObject *)meta);
}

int igObjectSystem_FindMetaByName(ObjectSystemView *objectSystem, const char *className) {
    if (objectSystem->active != 0) {
        return (int)ObjectPointerList_FindByStringField((__internalNonRefCountedObjectList *)objectSystem->metaRegistry, g_igMetaObjectNameField[0], className);
    }
    return 0;
}

int igObjectSystem_AppendMetaEnum(int *p, int metaEnum)
{
    return MetaRefList_AppendRetained((__internalObjectList *)((ObjectSystemView *)p)->metaEnumList, (igObject *)metaEnum);
}

int igObjectSystem_AddExitCallback(int *p, int callback)
{
    return igArray_Append((CallbackArray *)((ObjectSystemView *)p)->exitCallbacks, callback);
}

void igObjectSystem_AddRegistrationCallback(ObjectSystemView *self, int (*callback)(int)) {
    int i;

    for (i = 0; i < ((__internalObjectList *)self->metaRegistry)->_count; i++) {
        callback(((int *)((__internalObjectList *)self->metaRegistry)->_data)[i]);
    }
    igArray_Append((CallbackArray *)self->registrationCallbacks, (int)callback);
}

void igObjectSystem_RunRegistrationCallbacks(int *self, int meta) {
    int n = ((CallbackArray *)self[11])->count;
    int i = 0;
    while (i < n) {
        ((void (*)(int))(*(int **)self[11])[i])(meta);
        i++;
    }
}

void igObjectSystem_SetMemoryEventFormat(ObjectSystemView *objectSystem, char *format) {
    if (format != 0) {
        strncpy(objectSystem->memoryEventFormat, format, 0x7F);
        objectSystem->memoryEventFormat[127] = 0;
    } else {
        objectSystem->memoryEventFormat[0] = 0;
    }
    if ((format != 0) && (*format != 0)) {
        g_memoryEventFormat[0] = objectSystem->memoryEventFormat;
    }
}

void igObjectSystem_SetMarkerEventFormat(ObjectSystemView *objectSystem, char *format) {
    if (format != 0) {
        strncpy(objectSystem->markerEventFormat, format, 0x7F);
        objectSystem->markerEventFormat[127] = 0;
    } else {
        objectSystem->markerEventFormat[0] = 0;
    }
    if ((format != 0) && (*format != 0)) {
        g_markerEventFormat[0] = (void *)objectSystem->markerEventFormat;
    }
}

void igObjectSystem_SetNotificationEventFormat(ObjectSystemView *objectSystem, char *format) {
    if (format != 0) {
        strncpy(objectSystem->notificationEventFormat, format, 0x7F);
        objectSystem->notificationEventFormat[127] = 0;
    } else {
        objectSystem->notificationEventFormat[0] = 0;
    }
    if ((format != 0) && (*format != 0)) {
        g_notificationEventFormat[0] = objectSystem->notificationEventFormat;
    }
}

void igObjectSystem_SetEventTrackerFileName(char *self, char *fileName) {
    if ((fileName != 0) && (*fileName != 0)) {
        strncpy(((ObjectSystemView *)self)->eventTrackerFileName, fileName, 0x7F);
        ((ObjectSystemView *)self)->eventTrackerFileName[127] = 0;
        return;
    }
    ((ObjectSystemView *)self)->eventTrackerFileName[0] = 0;
}

void igObjectSystem_SetSystemPoolEventTrackerFileName(char *a, char *b) {
    if (b != 0 && *b != 0) {
        strncpy(a + 656, b, 127);
        a[783] = 0;
        return;
    }
    a[656] = 0;
}

void igObjectSystem_SetSymbolsFileName(void *self, int fileName) {
    if (fileName != 0) {
        strncpy(((ObjectSystemView *)self)->symbolsFileName, fileName, 0x7F);
        ((ObjectSystemView *)self)->symbolsFileName[127] = 0;
        return;
    }
    ((ObjectSystemView *)self)->symbolsFileName[0] = 0;
}

CallbackArray *igArray_Construct(CallbackArray *array){array->data=0;array->capacity=0;array->count=0;return array;}

/* Free the data buffer, and the array object itself when `deleteFlag` is positive. */
CallbackArray *igArray_Destruct(CallbackArray *array,short deleteFlag){
    if(array){if(array->data)Memory_FreeBuffer(array->data);if(deleteFlag>0)Memory_FreeBufferAliasB(array);}
    return array;
}

/* Grow only when count equals capacity, then store `item` at the end. */
int igArray_Append(CallbackArray *array,int item){
    int capacity=array->capacity;
    if(array->count==capacity){
        if(capacity==0)array->capacity=4;
        else array->capacity*=((capacity*3)/2);
        if(array->data==0)array->data=(int *)(Memory_AllocateBufferDirect((unsigned int)(array->capacity*4), (igMemoryPoolView *)(((ObjectSystemView * *)g_objectSystem)[0]->systemPool)));
        else array->data=(int *)(Memory_ReallocateBuffer(array->data, (unsigned int)(array->capacity*4)));
    }
    array->data[array->count++]=item;
}

int igObjectSystem_OperatorNew(int extra0)
{
    return malloc();
}

int igObjectSystem_OperatorDelete(int extra0)
{
    return free();
}

