void igObjectSystem_Startup(ObjectSystemView *self) {
    void *m;
    __internalObjectList *l;
    unsigned int n;
    int b;
    self->started = 1;
    SystemAllocator_EnsureCreated();
    self->vtableProbeOffset = 0;
    if (((MemoryContext * *)DAT_00586fd0)[0] == 0) {
        m = igMemoryPoolContextInfo_Allocate(0x19F4);
        if (m != 0) m = igMemoryPoolContextInfo_Construct((MemoryContext *)m);
        ((MemoryContext * *)DAT_00586fd0)[0] = (MemoryContext *)m;
    }
    ((MemoryContext * *)DAT_00586fd0)[0]->vfunc_42();
    self->metaRegistry = ((__internalObjectList *)InternalObjectList_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap))));
    l = (__internalObjectList *)self->metaRegistry;
    if (l->_data == 0) n = 0; else n = Memory_GetBufferSize((void *)l->_data) >> 2;
    if ((int)n < 0x401) ObjectPointerList_EnsureIndex((__internalNonRefCountedObjectList *)l, 0x400);
    self->auxObjectList = ((__internalObjectList *)InternalObjectList_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap))));
    b = ((int)Memory_AllocateDefaultBuffer((unsigned int)12));
    if (b != 0) b = ((int)igArray_Construct((CallbackArray *)b));
    self->startupCallbacks = (void *)b;
    b = ((int)Memory_AllocateDefaultBuffer((unsigned int)12));
    if (b != 0) b = ((int)igArray_Construct((CallbackArray *)b));
    self->registrationCallbacks = (void *)b;
    igMetaObject_EnsureRegistered();
    self->active = 1;
    self->bootMetaObjectCount = ((__internalObjectList *)self->metaRegistry)->_count;
    self->bootMetaFieldCount = DAT_00587188[0]->_count;
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
    ((MemoryContext * *)DAT_00586fd0)[0]->vfunc_43();
}

int igObjectSystem_GetRootPath(int *p)
{
    return *(int *)((char *)p + 920);
}

int igObjectSystem_GetBasePath(int *p)
{
    return *(int *)((char *)p + 924);
}

void igObjectSystem_InitPaths(ObjectSystemView *arg0) {
    igStringRef env;
    env = (char *)getenv(IG_ROOT);
    arg0->rootPath = env;
    arg0->basePath = (char *)DAT_004f9468;
    arg0->basePath = (char *)DAT_004f9470;
}

igMetaObject *igMediaFile_GetPublishedMetaObject(void) {
    return g_igMediaFile_metaObject[0];
}

void igObjectSystem_PreExit(ObjectSystemView *arg0) {
    igEventTrackerView *temp_a0;

    arg0->preExitDone = 1;
    temp_a0 = arg0->globalEventTracker;
    if (temp_a0 != 0) {
        temp_a0->vfunc_46();
        igEventTracker_SetEventTag((igEventTrackerView *)arg0->globalEventTracker, (int)&text_exitPre[0]);
    }
}

void igObjectSystem_Exit(ObjectSystemView *arg0) {
    if (arg0->globalEventTracker != 0) {
        arg0->globalEventTracker->vfunc_47();
        igEventTracker_SetEventTag((igEventTrackerView *)arg0->globalEventTracker, (int)(&text_exitIn[0]));
    }
    if (arg0->saveEventTrackerOnExit != 0 && ((MemoryContext * *)DAT_00586fd0)[0] != 0) {
        ((MemoryContext * *)DAT_00586fd0)[0]->vfunc_56();
    }
}

void igObjectSystem_Shutdown(ObjectSystemView *arg0) {
    int i;
    int v;
    igObject *o;
    o = (igObject *)arg0->auxObjectList;
    o->_refCount = o->_refCount - 1;
    if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
    arg0->auxObjectList = 0;
    igAdxFile_SetBasePath(0);
    igArray_Destruct((CallbackArray *)arg0->registrationCallbacks, 1);
    if (DAT_00586fd0[0] != 0) {
        DAT_00586fd0[0]->vfunc_47();
    }
    InternalObjectList_SetCount((__internalObjectList *)DAT_00587188[0], arg0->bootMetaFieldCount);
    for (i = arg0->metaObjectCount - 1; i >= arg0->bootMetaObjectCount; i--) {
        InternalObjectList_SetAtRetained((__internalObjectList *)arg0->metaRegistry, i, (igObject *)0);
    }
    arg0->active = 0;
    o = (igObject *)DAT_00587188[0];
    o->_refCount = o->_refCount - 1;
    if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
    o = (igObject *)arg0->metaRegistry;
    o->_refCount = o->_refCount - 1;
    if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
    o = arg0->retainedObject;
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
    }
    if (g_stringPool[0] == 0) {
        v = ((int)StringPool_Allocate(16));
        if (v != 0) v = ((int)StringPool_Construct((StringPool *)v));
        g_stringPool[0] = v;
    }
    StringPool_Destroy((StringPool *)g_stringPool[0], 1);
    arg0->started = 0;
    if (DAT_00586fd0[0] != 0) {
        DAT_00586fd0[0]->vfunc_44();
        if (DAT_00586fd0[0] != 0) {
            DAT_00586fd0[0]->Destruct(1);
        }
        DAT_00586fd0[0] = 0;
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

int igObjectSystem_AppendMetaEnum(int *p, int extra1)
{
    return MetaRefList_AppendRetained((__internalObjectList *)(*(int *)((char *)p + 36)), (igObject *)extra1);
}

int igObjectSystem_AddExitCallback(int *p, int extra1)
{
    return igArray_Append((CallbackArray *)(*(int *)((char *)p + 40)), extra1);
}

void igObjectSystem_AddRegistrationCallback(ObjectSystemView *arg0, int (*arg1)(int)) {
    int i;

    for (i = 0; i < ((__internalObjectList *)arg0->metaRegistry)->_count; i++) {
        arg1(((int *)((__internalObjectList *)arg0->metaRegistry)->_data)[i]);
    }
    igArray_Append((CallbackArray *)arg0->registrationCallbacks, (int)arg1);
}

void igObjectSystem_RunRegistrationCallbacks(int *arg0, int arg1) {
    int n = *(int *)(arg0[11] + 4);
    int i = 0;
    while (i < n) {
        ((void (*)(int))(*(int **)arg0[11])[i])(arg1);
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
        DAT_004c1eb8[0] = objectSystem->memoryEventFormat;
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
        DAT_004c1ec0[0] = (void *)objectSystem->markerEventFormat;
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
        DAT_004c1ec8[0] = objectSystem->notificationEventFormat;
    }
}

void igObjectSystem_SetEventTrackerFileName(char *arg0, char *arg1) {
    if ((arg1 != 0) && (*arg1 != 0)) {
        strncpy(arg0 + 528, arg1, 0x7F);
        arg0[655] = 0;
        return;
    }
    arg0[528] = 0;
}

void igObjectSystem_SetSystemPoolEventTrackerFileName(char *a, char *b) {
    if (b != 0 && *b != 0) {
        strncpy(a + 656, b, 127);
        a[783] = 0;
        return;
    }
    a[656] = 0;
}

void igObjectSystem_SetSymbolsFileName(void *arg0, int arg1) {
    if (arg1 != 0) {
        strncpy((char *)arg0 + 0x310, arg1, 0x7F);
        *((char *)arg0 + 911) = 0;
        return;
    }
    *((char *)arg0 + 784) = 0;
}

CallbackArray *igArray_Construct(CallbackArray *array){array->data=0;array->capacity=0;array->count=0;return array;}

/* Free the data buffer, and the array object itself when `deleteFlag` is positive. */
CallbackArray *igArray_Destruct(CallbackArray *array,short deleteFlag){
    if(array){if(array->data)Memory_FreeBuffer(array->data);if(deleteFlag>0)FUN_002ed5c0(array);}
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

