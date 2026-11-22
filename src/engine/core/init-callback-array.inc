MemoryContext *g_currentMemoryContext;
Gap::Core::__internalObjectList *g_metaFieldList;

void igObjectSystem_Startup(ObjectSystemView *self) {
    void *m;
    __internalObjectList *l;
    unsigned int n;
    int b;
    self->started = 1;
    SystemAllocator_EnsureCreated();
    self->vtableProbeOffset = 0;
    if (g_currentMemoryContext == 0) {
        m = igMemoryPoolContextInfo_Allocate(0x19F4);
        if (m != 0) m = igMemoryPoolContextInfo_Construct((MemoryContext *)m);
        g_currentMemoryContext = (MemoryContext *)m;
    }
    g_currentMemoryContext->CreateDefaultPools();
    self->metaRegistry = Gap::Core::__internalObjectList::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap));
    l = (__internalObjectList *)self->metaRegistry;
    if (l->_data == 0) n = 0; else n = Memory_GetBufferSize((void *)l->_data) >> 2;
    if ((int)n < 0x401) ((Gap::Core::__internalNonRefCountedObjectList *)l)->setCapacity(0x400);
    self->metaEnumList = Gap::Core::__internalObjectList::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap));
    b = ((int)Memory_AllocateDefaultBuffer((unsigned int)12));
    if (b != 0) b = ((int)igArray_Construct((CallbackArray *)b));
    self->exitCallbacks = (void *)b;
    b = ((int)Memory_AllocateDefaultBuffer((unsigned int)12));
    if (b != 0) b = ((int)igArray_Construct((CallbackArray *)b));
    self->registrationCallbacks = (void *)b;
    igMetaObject_EnsureRegistered();
    self->active = 1;
    self->bootMetaObjectCount = ((__internalObjectList *)self->metaRegistry)->_count;
    self->bootMetaFieldCount = g_metaFieldList->_count;
    Gap::Core::igMetaEnum::arkRegister();
    igMallocMemoryPool_EnsureRegistered();
    igArenaMemoryPool_EnsureRegistered();
    igAliasMemoryPool_EnsureRegistered();
    igPageMemoryPool_EnsureRegistered();
    igMemoryDictionary_EnsureRegistered();
    Gap::Core::igCharList::arkRegister();
    Gap::Core::igCharListNoClean::arkRegister();
    Gap::Core::igIntList::arkRegister();
    Gap::Core::igIntListNoClean::arkRegister();
    Gap::Core::igUnsignedIntList::arkRegister();
    Gap::Core::igUnsignedIntListNoClean::arkRegister();
    igStringTable_EnsureRegistered();
    igSymbolTable_EnsureRegistered();
    igCallStackTable_EnsureRegistered();
    igCallStackTracer_EnsureRegistered();
    igPsx2CallStackTracer_EnsureRegistered();
    igLocationTable_EnsureRegistered();
    igEventTracker_EnsureRegistered();
    Gap::Core::igFloatMetaField::arkRegister();
    Gap::Core::igLongMetaField::arkRegister();
    Gap::Core::igUnsignedCharMetaField::arkRegister();
    Gap::Core::igRefMetaField::setMetaField(Gap::Core::igRawRefMetaField::getMetaField());
    g_currentMemoryContext->OnStartupComplete();
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
    env = (char *)getenv("IG_ROOT");
    self->rootPath = env;
    self->basePath = (char *)".";
    self->basePath = (char *)"..";
}

unsigned char g_useOwnerAllocator;

/* The current allocator when objects follow their owner's, otherwise the system pool. */
static inline igMemoryPoolView *ownerOrSystemPool() {
    igMemoryPoolView *current = (igMemoryPoolView *)Memory_GetCurrentAllocator();
    return g_useOwnerAllocator != 0 ? current : (igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
}

/* Give the file an empty prefix. */
static inline void clearPrefix(const igSmartPointer<igObject> &holder) {
    char *interned;
    /* matching construct: register-allocator tracer — the file pointer, numbered after the token, takes s1; assigning
     * `_prefix = (const char *)0` computes the member's address into s2 first */
    Gap::Core::igPsx2File *file = (Gap::Core::igPsx2File *)holder.p;
    interned = (char *)StringPool_Intern(InternedStrings::get(), (char *)0);
    releaseString(file->_prefix.p);
    file->_prefix.p = interned;
}

static inline void setName(igDirectory *directory, char *name) {
    char *interned = (char *)StringPool_Intern(InternedStrings::get(), name);
    releaseString((char *)directory->_name);
    directory->_name = (int)interned;
}

static inline void setRegistryFile(igRegistry *registry, const igSmartPointer<igObject> &value) {
    igObject *file = value.p;
    if (file != 0) file->_refCount = file->_refCount + 1;
    igObject::release((igObject *)registry->_registryFile);
    registry->_registryFile = (int)file;
}

static inline void setTemporaryMemoryPool(igResource *resource, igObject *pool) {
    if (pool != 0) pool->_refCount = pool->_refCount + 1;
    igObject::release((igObject *)resource->_temporaryMemoryPool);
    resource->_temporaryMemoryPool = (int)pool;
}

char *g_alchemyVersionString = "Intrinsic Alchemy  v3.2 -0810 (Static/Release) \nBuilt by terada on Tue Aug 10 11:05:06 JST 2004";
unsigned char g_loadAlchemyIni = 1;
igResourceView *g_globalContext;
char *g_alchemyIniText;
igLongTimerView *g_igIGBFile_loadTimer;
char *g_alchemyIniPath;
int g_igPsx2_atfilePrefix;

/* Set the object system up after its classes are registered: read alchemy.ini (from a file, or from the
 * text the game embeds), open the media, create the driver database, the plugin helper and the resource
 * manager with its "system" directory, read the core settings, and cache the vtables the ini lists. */
void igObjectSystem_Initialize(ObjectSystemView *self) {
    igObjectSystem_InitPaths(self);
    self->configRegistry = (igRegistry *)Gap::Core::igRegistry::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap));
    if (g_loadAlchemyIni && igRegistry_IsLoadingEnabled()) {
        if (g_alchemyIniPath != 0) {
            igSmartPointer<igObject> file((igObject *)Gap::Core::igPsx2File::_instantiateFromPool(ownerOrSystemPool()));
            clearPrefix(file);
            setRegistryFile(self->configRegistry, file);
            ((Gap::Core::igRegistry *)self->configRegistry)->load(g_alchemyIniPath, (char *)"");
        } else {
            if (g_alchemyIniText != 0) {
                igSmartPointer<igObject> file((igObject *)Gap::Core::igMemoryFile::_instantiateFromPool(ownerOrSystemPool()));
                Gap::Core::igMemoryFile::setMemoryFile((char const *)("alchemy.ini"), (void const *)g_alchemyIniText, strlen(g_alchemyIniText));
                setRegistryFile(self->configRegistry, file);
            }
            ((Gap::Core::igRegistry *)self->configRegistry)->load((char *)"", (char *)"");
        }
    }
    bool useFileIO = true;
    ((Gap::Core::igRegistry *)self->configRegistry)->getValue(2,"useFileIO", *(unsigned char *)&useFileIO, 1, 0);
    if (useFileIO) {
        igSmartPointer<igObject> media((igObject *)igPsx2Media_Create((int)ownerOrSystemPool()));
        if (((igPsx2Media *)media.p)->_initialized == 1) {
            Gap::Core::igMedia::registerMedia((Gap::Core::igMedia *)media.p);
            Gap::Core::igMedia::setDefaultMedia((Gap::Core::igMedia *)media.p);
            Gap::Core::igMediaFile::arkRegister();
            Gap::Core::igFile::getClassMeta()->_abstractProxy = (int)Gap::Core::igMediaFile::getClassMeta;
        }
    } else {
        igPsx2_LoadIopModule((char *)"libsd.irx", 1, 0, 0);
    }
    if (g_igPsx2_atfilePrefix != 0) {
        igPsx2_SetupOutputFiles();
    }
    self->driverDatabase = (igDriverDatabase *)igDriverDatabase_Create((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap));
    igDriverDatabase_GatherProperties(self->driverDatabase, 0);
    igIGBFile_EnsureRegistered();
    self->pluginHelper = (igPluginHelper *)igPluginHelper_Create((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap));
    igPluginHelper_LoadPluginsFromRegistry(self->pluginHelper);
    igPluginHelper_AddRepository(self->pluginHelper, (int)"Alchemy", (int)"plugins", 1);
    self->metaObjectCount = ((__internalObjectList *)self->metaRegistry)->_count;
    self->metaFieldCount = g_metaFieldList->_count;
    igReport_ReadSettings();
    self->resource = (igResource *)igResource_Create((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap));
    g_globalContext = (igResourceView *)self->resource;
    igSmartPointer<igObject> directory((igObject *)Gap::Core::igDirectory::_instantiateFromPool(ownerOrSystemPool()));
    setName((igDirectory *)directory.p, (char *)"system");
    ((igResourceView *)self->resource)->addDirectory(directory);
    ((Gap::Core::igDirectory *)directory.p)->loadRef();
    igSmartPointer<igObject> metaFieldInfo((igObject *)igMetaFieldInfo_Create((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    ((Gap::Core::igNamedObject *)metaFieldInfo.p)->setName("metafield info");
    ((Gap::Core::igDirectory *)directory.p)->appendInfo((igInfo *)metaFieldInfo.p);
    ((Gap::Core::igRegistry *)self->configRegistry)->getValue(2,"failOnDllVersionMismatch", self->reportHeaderVersionMismatch, 1, 0);
    ((Gap::Core::igRegistry *)self->configRegistry)->getValue(2,"warnOnDllDateMismatch", self->warnOnDllDateMismatch, 1, 0);
    ((Gap::Core::igRegistry *)self->configRegistry)->getValue(2,"resourceTempMemoryPoolSize", *(int *)(&self->resourceTempPoolSize), 0, 0);
    if (g_currentMemoryContext != 0) {
        g_currentMemoryContext->Initialize();
    }
    if (self->resourceTempPoolSize != 0) {
        self->resourceTempPool = (igMemoryPoolView *)igStackMemoryPool_Create(0);
        int memory = (int)Memory_AllocateDefaultBuffer(self->resourceTempPoolSize);
        memset((void *)memory, 0, self->resourceTempPoolSize);
        self->resourceTempPool->SetRawMemory(memory, self->resourceTempPoolSize, 1);
        self->resourceTempPool->SetSize(self->resourceTempPool->GetMaxSize());
        if (self->useGlobalEventTracker && self->saveEventTrackerOnExit) {
            igEventTrackerView *tracker = (igEventTrackerView *)igEventTracker_Create(Memory_GetNonTrackedAllocator());
            igEventTracker_SetCapacity((int)tracker, 0x4000);
            tracker->Initialize();
            self->resourceTempPool->SetEventTracker(tracker);
        }
        self->resourceTempPool->Activate();
        setTemporaryMemoryPool(self->resource, (igObject *)self->resourceTempPool);
    }
    ((Gap::Core::igRegistry *)self->configRegistry)->getValue(2,"stringPoolStatisticsLevel", *(int *)(&self->stringPoolStatisticsLevel), 0, 0);
    Gap::Core::igFile::setSearchPathFromRegistry();
    g_igIGBFile_loadTimer = (igLongTimerView *)Gap::Core::igTimer::_instantiateFromPool((igMemoryPoolView *)self->systemPool);
    g_igIGBFile_loadTimer->Start();
    igReport_Printf("\n%s\n\n", g_alchemyVersionString);
    igReport_Flush();
    if (self->copyVTables != 0) {
        int section = ((Gap::Core::igRegistry *)self->configRegistry)->findSection("CLASSES_TO_VTABLE_CACHE", 1);
        if (section != -1) {
            int count = ((Gap::Core::igRegistry *)self->configRegistry)->getRawValueCount();
            int i;
            self->vtableClassNames = (igStringTableView *)igStringTable_Create((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap));
            igStringTable_SetCapacity((int)self->vtableClassNames, 512);
            igStringTable_SetHashCapacity((int)self->vtableClassNames, 16);
            igStringTable_Reserve(self->vtableClassNames);
            for (i = 0; i < count; i++) {
                igRegistryValue *entry = (igRegistryValue *)((Gap::Core::igRegistry *)self->configRegistry)->getRawValue(i);
                if (entry != 0 && entry->_section == section) {
                    igStringObj *value = (igStringObj *)entry->_value;
                    if (value == 0 || igStringObj_Text(value) == 0 || *igStringObj_Text(value) != '0') {
                        char *className = igStringObj_Text((igStringObj *)entry->_valueName);
                        igStringTable_AppendString(self->vtableClassNames, className);
                        if (self->fastPool != 0) {
                            igMetaObject *meta = (igMetaObject *)igObjectSystem_FindMetaByName(self, className);
                            if (meta != 0) {
                                igMetaObject_CopyVTable(meta, self->fastPool);
                            }
                        }
                    }
                }
            }
        }
    }
    StringTable_SetSynchronization(1);
}

void igObjectSystem_PreExit(ObjectSystemView *self) {
    igEventTrackerView *tracker;

    self->preExitDone = 1;
    tracker = self->globalEventTracker;
    if (tracker != 0) {
        tracker->PreExit();
        igEventTracker_SetEventTag((igEventTrackerView *)self->globalEventTracker, (int)"exitPre");
    }
}

/* Release one reference the object system holds, without testing for none. */
static inline void releaseObject(igObject *object) {
    object->release();
}

AllocatorRegistry *g_primaryAllocatorList;
AllocatorRegistry *g_secondaryAllocatorList;

/* Undo igObjectSystem_Initialize: stop the resource manager, run the exit callbacks, drop the classes
 * registered since the set-up, and release the configuration registry, the resource manager and the
 * other managers the set-up created. */
void igObjectSystem_Finalize(ObjectSystemView *self) {
    igResource *resource;
    igMemoryPoolView *pool;
    igEventTrackerView *tracker;
    int count;
    int i;
    igResource_RemoveIGBFiles(self->resource);
    if (self->resource->_asyncLoadState) {
        igResource_StopAsyncLoading((igResourceView *)self->resource);
    }
    resource = self->resource;
    igObject::release((igObject *)resource->_temporaryMemoryPool);
    resource->_temporaryMemoryPool = 0;
    resource = self->resource;
    igObject::release((igObject *)resource->_objectMemoryPool);
    resource->_objectMemoryPool = 0;
    resource = self->resource;
    igObject::release((igObject *)resource->_dataMemoryPool);
    resource->_dataMemoryPool = 0;
    StringTable_SetSynchronization(0);
    count = g_secondaryAllocatorList->count;
    for (i = 0; i < count; i++) {
        pool = g_secondaryAllocatorList->data[i];
        if (pool != 0) {
            pool->EnableAllocationLock(0);
            tracker = (igEventTrackerView *)pool->GetEventTracker();
            if (tracker != 0) {
                igEventTracker_SetThreadSafe(tracker, 0);
            }
        }
    }
    count = g_primaryAllocatorList->count;
    for (i = 0; i < count; i++) {
        pool = g_primaryAllocatorList->data[i];
        if (pool != 0) {
            pool->EnableAllocationLock(0);
            tracker = (igEventTrackerView *)pool->GetEventTracker();
            if (tracker != 0) {
                igEventTracker_SetThreadSafe(tracker, 0);
            }
        }
    }
    if (g_currentMemoryContext != 0) {
        g_currentMemoryContext->ReleaseContextInfo();
    }
    igObjectSystem_Exit(self);
    self->exitDone = 1;
    for (i = ((CallbackArray *)self->exitCallbacks)->count; --i >= 0;) {
        ((void (*)())((CallbackArray *)self->exitCallbacks)->data[i])();
    }
    igArray_Destruct((CallbackArray *)self->exitCallbacks, 1);
    self->exitCallbacks = 0;
    igResource_ClearDirectories(self->resource);
    releaseObject((igObject *)self->driverDatabase);
    releaseObject((igObject *)g_igIGBFile_loadTimer);
    g_metaFieldList->setCount(self->metaFieldCount);
    for (i = ((__internalObjectList *)self->metaRegistry)->_count - 1; i >= self->metaObjectCount; i--) {
        ((Gap::Core::__internalObjectList *)self->metaRegistry)->set(i, (Gap::Core::igObject *)0);
    }
    releaseObject((igObject *)self->pluginHelper);
    self->pluginHelper = 0;
    if (self->resourceTempPool != 0) {
        self->resourceTempPool->Deactivate();
        int memory = self->resourceTempPool->GetRawMemory();
        if (memory != 0) {
            self->resourceTempPool->SetRawMemory(0, 0, 0);
            Memory_FreeBuffer((void *)memory);
        }
        resource = self->resource;
        igObject::release((igObject *)resource->_temporaryMemoryPool);
        resource->_temporaryMemoryPool = 0;
        releaseObject((igObject *)self->resourceTempPool);
        self->resourceTempPool = 0;
    }
    if (self->vtableClassNames != 0) {
        releaseObject((igObject *)self->vtableClassNames);
        self->vtableClassNames = 0;
    }
    if (self->symbolTable != 0) {
        releaseObject((igObject *)self->symbolTable);
        self->symbolTable = 0;
    }
    releaseObject((igObject *)self->configRegistry);
    releaseObject((igObject *)self->resource);
    igReport_RestoreDefaults();
    igReport_SetOutputFile(0);
    igReport_SetErrorFile(0);
    self->rootPath = (char *)0;
    self->basePath = (char *)0;
}

void igObjectSystem_Exit(ObjectSystemView *self) {
    if (self->globalEventTracker != 0) {
        self->globalEventTracker->Exit();
        igEventTracker_SetEventTag((igEventTrackerView *)self->globalEventTracker, (int)("exitIn"));
    }
    if (self->saveEventTrackerOnExit != 0 && g_currentMemoryContext != 0) {
        g_currentMemoryContext->SaveEventTrackers();
    }
}

void igObjectSystem_Shutdown(ObjectSystemView *self) {
    int i;
    int pool;
    igObject *o;
    o = (igObject *)self->metaEnumList;
    o->release();
    self->metaEnumList = 0;
    Gap::Core::igFile::setSearchPath(0);
    igArray_Destruct((CallbackArray *)self->registrationCallbacks, 1);
    if (g_currentMemoryContext != 0) {
        g_currentMemoryContext->RemoveAllAllocators();
    }
    g_metaFieldList->setCount(self->bootMetaFieldCount);
    for (i = self->metaObjectCount - 1; i >= self->bootMetaObjectCount; i--) {
        ((Gap::Core::__internalObjectList *)self->metaRegistry)->set(i, (Gap::Core::igObject *)0);
    }
    self->active = 0;
    o = (igObject *)g_metaFieldList;
    o->release();
    o = (igObject *)self->metaRegistry;
    o->release();
    o = self->retainedObject;
    igObject::release(o);
    if (g_stringPool == 0) {
        pool = ((int)StringPool_Allocate(16));
        if (pool != 0) pool = ((int)StringPool_Construct((StringPool *)pool));
        g_stringPool = (StringPool *)pool;
    }
    StringPool_Destroy((StringPool *)g_stringPool, 1);
    self->started = 0;
    if (g_currentMemoryContext != 0) {
        g_currentMemoryContext->Shutdown();
        if (g_currentMemoryContext != 0) {
            g_currentMemoryContext->Destruct(1);
        }
        g_currentMemoryContext = 0;
    }
    SystemAllocator_EnsureDestroyed();
}

/* Register a metaobject in the object system's registry, retaining it. */
void igObjectSystem_AppendMetaObject(void *system,igMetaObject *meta){
    ((Gap::Core::__internalObjectList *)(((ObjectSystemView *)system)->metaRegistry))->append((Gap::Core::igObject *)meta);
}

int igObjectSystem_FindMetaByName(ObjectSystemView *objectSystem, const char *className) {
    if (objectSystem->active != 0) {
        return (int)((Gap::Core::__internalNonRefCountedObjectList *)objectSystem->metaRegistry)->search((Gap::Core::igStringMetaField *)g_igMetaObjectNameField, className);
    }
    return 0;
}

int igObjectSystem_AppendMetaEnum(int *p, int metaEnum)
{
    return ((Gap::Core::__internalObjectList *)(((ObjectSystemView *)p)->metaEnumList))->append((Gap::Core::igObject *)metaEnum);
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

char *g_memoryEventFormat = "ka(s)[i]: p(l)r', %s'";

void igObjectSystem_SetMemoryEventFormat(ObjectSystemView *objectSystem, char *format) {
    if (format != 0) {
        strncpy(objectSystem->memoryEventFormat, format, 0x7F);
        objectSystem->memoryEventFormat[127] = 0;
    } else {
        objectSystem->memoryEventFormat[0] = 0;
    }
    if ((format != 0) && (*format != 0)) {
        g_memoryEventFormat = objectSystem->memoryEventFormat;
    }
}

char *g_markerEventFormat = "k[i] u v w j ";

void igObjectSystem_SetMarkerEventFormat(ObjectSystemView *objectSystem, char *format) {
    if (format != 0) {
        strncpy(objectSystem->markerEventFormat, format, 0x7F);
        objectSystem->markerEventFormat[127] = 0;
    } else {
        objectSystem->markerEventFormat[0] = 0;
    }
    if ((format != 0) && (*format != 0)) {
        g_markerEventFormat = (char *)objectSystem->markerEventFormat;
    }
}

char *g_notificationEventFormat = "p(l)[i]: x: y - zc^s+o'0x%x' : f(l)^'\n    %s'";

void igObjectSystem_SetNotificationEventFormat(ObjectSystemView *objectSystem, char *format) {
    if (format != 0) {
        strncpy(objectSystem->notificationEventFormat, format, 0x7F);
        objectSystem->notificationEventFormat[127] = 0;
    } else {
        objectSystem->notificationEventFormat[0] = 0;
    }
    if ((format != 0) && (*format != 0)) {
        g_notificationEventFormat = objectSystem->notificationEventFormat;
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
        strncpy(((ObjectSystemView *)self)->symbolsFileName, (const char *)fileName, 0x7F);
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
        if(array->data==0)array->data=(int *)(Memory_AllocateBufferDirect((unsigned int)(array->capacity*4), (igMemoryPoolView *)(g_objectSystem->systemPool)));
        else array->data=(int *)(Memory_ReallocateBuffer(array->data, (unsigned int)(array->capacity*4)));
    }
    array->data[array->count++]=item;
}

void *igObjectSystem_OperatorNew(unsigned int size)
{
    return malloc(size);
}

void igObjectSystem_OperatorDelete(void *block)
{
    free(block);
}

