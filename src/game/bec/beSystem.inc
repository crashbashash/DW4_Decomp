igMetaObject *g_beSystem_metaObject;
igMetaField *g_beSystem_isShutDownMetaField;
igMetaField *g_beSystem_svWorldTimeLMetaField;
igMetaField *g_beSystem_frameTimeLMetaField;
igMetaField *g_beSystem_frameTimeFMetaField;
igMetaField *g_beSystem_isActiveMetaField;
igMetaField *g_beSystem_isFirstTimeMetaField;
igMetaField *g_beSystem_isFrameSkipMetaField;
igMetaField *g_beSystem_randomMetaField;
igMetaField *g_beSystem_readFileListMetaField;
igMetaField *g_beSystem_stageNameMetaField;
igMetaField *g_beSystem_nextStageMetaField;
igMetaField *g_beSystem_isStageLoopMetaField;
igMetaField *g_beSystem_bootDirectoryMetaField;
igMetaField *g_beSystem_globalStrObjMetaField;
igMetaField *g_beSystem_discErrInfosMetaField;
igMetaField *g_beSystem_viewerSceneMetaField;
igMetaField *g_beSystem_dvdStatMetaField;
igMetaField *g_beSystem_execDvdErrMetaField;
igMetaField *g_beSystem_isDvdErrMetaField;
igMetaField *g_beSystem_isNowFreezeMetaField;
igMetaField *g_beSystem_isNowPadEnableMetaField;
igMetaField *g_beSystem_isResetEnableMetaField;
igMetaField *g_beSystem_isResetNowMetaField;
igMetaField *g_beSystem_isResetLastMetaField;
igMetaField *g_beSystem_isResetReleaseMetaField;
igMetaField *g_beSystem_isSResetEnableMetaField;

beSystem *beSystem_CreateInstance(int allocator) {
    beSystem_EnsureRegistered();
    return (beSystem *)igMetaObject_CreateInstance(g_beSystem_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beSystem_GetOrCreateMetaObject(void) {
    if (g_beSystem_metaObject == 0) {
        g_beSystem_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beSystem_metaObject;
}

void *beSystem_GetMetaObject(void) {
    unsigned char b;
    if (g_beSystem_metaObject != 0) {
        b = (g_beSystem_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beSystem_EnsureRegistered();
done:
    return g_beSystem_metaObject;
}

int beSystem_GetVTable(void) {
    beSystem obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&g_beSystem_vtable[0];
    obj._random = 0;
    obj._readFileList = 0;
    obj._stageName = 0;
    obj._nextStage = 0;
    obj._bootDirectory = 0;
    obj._globalStrObj = 0;
    obj._discErrInfos = 0;
    obj._viewerScene = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beSystem_vtable[0];
    igSmartPointer_igGroup_Destruct((igSmartPointer<igObject> *)&obj._viewerScene, -1);
    igSmartPointer_igInfoList_Destruct((igSmartPointer<igObject> *)&obj._discErrInfos, -1);
    igSmartPointer_igStringObj_Destruct((igSmartPointer<igObject> *)&obj._globalStrObj, -1);
    igSmartPointer_igDirectory_Destruct((igSmartPointer<igObject> *)&obj._bootDirectory, -1);
    igStringRef_Destruct((igStringRef *)&obj._nextStage, -1);
    igStringRef_Destruct((igStringRef *)&obj._stageName, -1);
    igSmartPointer_igStringRefList_Destruct((igSmartPointer<igObject> *)&obj._readFileList, -1);
    igSmartPointer_igRandomNumber_Destruct((igSmartPointer<igObject> *)&obj._random, (short)(-1));
    igInfoManager_Destroy((igInfoManager *)&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_igRandomNumber_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

void beSystem_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSystem_Register);
}

static igMetaObjectCallback g_beSystem_callbackList[] = { igRandomNumber_EnsureRegistered, igStringRefList_EnsureRegistered, Gap::Core::igDirectory::arkRegister, igStringObj_EnsureRegistered, Gap::Core::igInfoList::arkRegister, Gap::Sg::igGroup::arkRegister, 0 };

CallbackArray *beSystem_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSystem_metaObject,
        Gap::Insight::igInfoManager::arkRegisterInternal,
        Gap::Insight::igInfoManager::getClassMeta,
        beSystem_GetMetaObjectFunction,
        "beSystem",
        0x68, /* instance size */
        beSystem_GetVTable,
        beSystem_InitFields,
        0, /* extra callback item */
        g_beSystem_callbackList /* callback list */
    );
}

void beSystem_GetMetaObjectFunction(void)
{
    beSystem_GetMetaObject();
}

static FieldFactory g_beSystem_ctorTable[] = {
    igBoolMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igFloatMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beSystem_fieldTable[] = {
    "_isShutDown",
    "_svWorldTimeL",
    "_frameTimeL",
    "_frameTimeF",
    "_isActive",
    "_isFirstTime",
    "_isFrameSkip",
    "_random",
    "_readFileList",
    "_stageName",
    "_nextStage",
    "_isStageLoop",
    "_bootDirectory",
    "_globalStrObj",
    "_discErrInfos",
    "_viewerScene",
    "_dvdStat",
    "_execDvdErr",
    "_isDvdErr",
    "_isNowFreeze",
    "_isNowPadEnable",
    "_isResetEnable",
    "_isResetNow",
    "_isResetLast",
    "_isResetRelease",
    "_isSResetEnable",
};
static igMetaField **g_beSystem_fieldHandles[] = {
    &g_beSystem_isShutDownMetaField,
    &g_beSystem_svWorldTimeLMetaField,
    &g_beSystem_frameTimeLMetaField,
    &g_beSystem_frameTimeFMetaField,
    &g_beSystem_isActiveMetaField,
    &g_beSystem_isFirstTimeMetaField,
    &g_beSystem_isFrameSkipMetaField,
    &g_beSystem_randomMetaField,
    &g_beSystem_readFileListMetaField,
    &g_beSystem_stageNameMetaField,
    &g_beSystem_nextStageMetaField,
    &g_beSystem_isStageLoopMetaField,
    &g_beSystem_bootDirectoryMetaField,
    &g_beSystem_globalStrObjMetaField,
    &g_beSystem_discErrInfosMetaField,
    &g_beSystem_viewerSceneMetaField,
    &g_beSystem_dvdStatMetaField,
    &g_beSystem_execDvdErrMetaField,
    &g_beSystem_isDvdErrMetaField,
    &g_beSystem_isNowFreezeMetaField,
    &g_beSystem_isNowPadEnableMetaField,
    &g_beSystem_isResetEnableMetaField,
    &g_beSystem_isResetNowMetaField,
    &g_beSystem_isResetLastMetaField,
    &g_beSystem_isResetReleaseMetaField,
    &g_beSystem_isSResetEnableMetaField,
};
static int g_beSystem_fieldOffsets[] = {
    16,
    24,
    32,
    40,
    44,
    45,
    46,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
    76,
    80,
    84,
    88,
    92,
    93,
    94,
    95,
    96,
    97,
    98,
    99,
};

void beSystem_InitFields(void) {
    void *random;
    void *readFileList;
    void *bootDirectory;
    void *globalStrObj;
    void *discErrInfos;
    void *viewerScene;
    int base;
    igMetaObject *meta;

    meta = g_beSystem_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSystem_ctorTable, 0x1A);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt(meta, base + 3)))->setDefault(1.0f);
    random = (void *)(igMetaObject_GetFieldAt(meta, base + 7));
    ((igObjectRefMetaField *)random)->_metaObject = (int)igRandomNumber_GetOrCreateMetaObject();
    ((igRefMetaField *)random)->_construct = 1;
    readFileList = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)readFileList)->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)readFileList)->_construct = 1;
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt(meta, base + 0xA)))->setDefault(0);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt(meta, base + 0xB)))->setDefault(1);
    bootDirectory = (void *)(igMetaObject_GetFieldAt(meta, base + 0xC));
    ((igObjectRefMetaField *)bootDirectory)->_metaObject = (int)Gap::Core::igDirectory::getClassTypeLazy();
    globalStrObj = (void *)(igMetaObject_GetFieldAt(meta, base + 0xD));
    ((igObjectRefMetaField *)globalStrObj)->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
    ((igRefMetaField *)globalStrObj)->_construct = 1;
    discErrInfos = (void *)(igMetaObject_GetFieldAt(meta, base + 0xE));
    ((igObjectRefMetaField *)discErrInfos)->_metaObject = (int)Gap::Core::igInfoList::getClassTypeLazy();
    ((igRefMetaField *)discErrInfos)->_construct = 1;
    viewerScene = (void *)(igMetaObject_GetFieldAt(meta, base + 0xF));
    ((igObjectRefMetaField *)viewerScene)->_metaObject = (int)Gap::Sg::igGroup::getClassTypeLazy();
    ((igRefMetaField *)viewerScene)->_construct = 1;
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt(meta, base + 0x15)))->setDefault(1);
    igMetaObject_NameFields(meta, g_beSystem_fieldTable, g_beSystem_fieldHandles, g_beSystem_fieldOffsets, base);
}

