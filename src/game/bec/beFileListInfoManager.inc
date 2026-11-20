igMetaObject *g_beFileListInfoManager_metaObject;
igMetaField *g_beFileListInfoManager_systemMetaField;
igMetaField *g_beFileListInfoManager_messengerMetaField;
igMetaField *g_beFileListInfoManager_sceneInfoManagerMetaField;
igMetaField *g_beFileListInfoManager_isReadOnetimeMetaField;
igMetaField *g_beFileListInfoManager_onetimeCountMetaField;
igMetaField *g_beFileListInfoManager_fnamesMetaField;
igMetaField *g_beFileListInfoManager_infoListMetaField;
igMetaField *g_beFileListInfoManager_dirListMetaField;
igMetaField *g_beFileListInfoManager_readInfoListMetaField;
igMetaField *g_beFileListInfoManager_importantInfoListMetaField;
igMetaField *g_beFileListInfoManager_loadedMetaField;
igMetaField *g_beFileListInfoManager_procMetaField;

beFileListInfoManager *beFileListInfoManager_CreateInstance(int allocator) {
    beFileListInfoManager_EnsureRegistered();
    return (beFileListInfoManager *)igMetaObject_CreateInstance(g_beFileListInfoManager_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beFileListInfoManager_GetOrCreateMetaObject(void) {
    if (g_beFileListInfoManager_metaObject == 0) {
        g_beFileListInfoManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beFileListInfoManager_metaObject;
}

void *beFileListInfoManager_GetMetaObject(void) {
    igMetaObject *g = g_beFileListInfoManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beFileListInfoManager_EnsureRegistered();
    }
    return g_beFileListInfoManager_metaObject;
}

int beFileListInfoManager_GetVTable(void) {
    beFileListInfoManager obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&g_beFileListInfoManager_vtable[0];
    obj._fnames = 0;
    obj._infoList = 0;
    obj._dirList = 0;
    obj._readInfoList = 0;
    obj._importantInfoList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beFileListInfoManager_vtable[0];
    igSmartPointer_igInfoList_Destruct((igSmartPointer<igObject> *)&obj._importantInfoList, -1);
    igSmartPointer_igInfoList_Destruct((igSmartPointer<igObject> *)&obj._readInfoList, -1);
    igSmartPointer_igDirectoryList_Destruct((igSmartPointer<igObject> *)&obj._dirList, -1);
    igSmartPointer_igInfoList_Destruct((igSmartPointer<igObject> *)&obj._infoList, -1);
    igSmartPointer_igStringRefList_Destruct((igSmartPointer<igObject> *)&obj._fnames, -1);
    igInfoManager_Destroy((igInfoManager *)&obj, 0);
    return vtable;
}

void beFileListInfoManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beFileListInfoManager_Register);
}

static igMetaObjectCallback g_beFileListInfoManager_callbackList[] = { beSystem_EnsureRegistered, beMessenger_EnsureRegistered, igViewerSceneInfoManager_EnsureRegistered, igStringRefList_EnsureRegistered, igInfoList_EnsureRegistered, igDirectoryList_EnsureRegistered, 0 };

CallbackArray *beFileListInfoManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beFileListInfoManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beFileListInfoManager_GetMetaObjectFunction,
        "beFileListInfoManager",
        0x40, /* instance size */
        beFileListInfoManager_GetVTable,
        beFileListInfoManager_InitFields,
        0, /* extra callback item */
        g_beFileListInfoManager_callbackList /* callback list */
    );
}

void beFileListInfoManager_GetMetaObjectFunction(void)
{
    beFileListInfoManager_GetMetaObject();
}

static FieldFactory g_beFileListInfoManager_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beFileListInfoManager_fieldTable[] = {
    "_system",
    "_messenger",
    "_sceneInfoManager",
    "_isReadOnetime",
    "_onetimeCount",
    "_fnames",
    "_infoList",
    "_dirList",
    "_readInfoList",
    "_importantInfoList",
    "_loaded",
    "_proc",
};
static igMetaField **g_beFileListInfoManager_fieldHandles[] = {
    &g_beFileListInfoManager_systemMetaField,
    &g_beFileListInfoManager_messengerMetaField,
    &g_beFileListInfoManager_sceneInfoManagerMetaField,
    &g_beFileListInfoManager_isReadOnetimeMetaField,
    &g_beFileListInfoManager_onetimeCountMetaField,
    &g_beFileListInfoManager_fnamesMetaField,
    &g_beFileListInfoManager_infoListMetaField,
    &g_beFileListInfoManager_dirListMetaField,
    &g_beFileListInfoManager_readInfoListMetaField,
    &g_beFileListInfoManager_importantInfoListMetaField,
    &g_beFileListInfoManager_loadedMetaField,
    &g_beFileListInfoManager_procMetaField,
};
static int g_beFileListInfoManager_fieldOffsets[] = {
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
};

void beFileListInfoManager_InitFields(void) {
    int base;
    void *system;
    void *messenger;
    void *sceneInfoManager;
    void *fnames;
    void *infoList;
    void *dirList;
    void *readInfoList;
    void *importantInfoList;
    igMetaObject *meta;

    meta = g_beFileListInfoManager_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beFileListInfoManager_ctorTable, 0xC);
    system = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)system)->_metaObject = (int)beSystem_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)system)->_refCounted = 0;
    messenger = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)messenger)->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    sceneInfoManager = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)sceneInfoManager)->_metaObject = (int)igViewerSceneInfoManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)sceneInfoManager)->_refCounted = 0;
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt(meta, base + 4)))->setDefault(-1);
    fnames = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)fnames)->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)fnames)->_construct = 1;
    infoList = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((igObjectRefMetaField *)infoList)->_metaObject = (int)igInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)infoList)->_construct = 1;
    dirList = (void *)(igMetaObject_GetFieldAt(meta, base + 7));
    ((igObjectRefMetaField *)dirList)->_metaObject = (int)igDirectoryList_GetOrCreateMetaObject();
    ((igRefMetaField *)dirList)->_construct = 1;
    readInfoList = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)readInfoList)->_metaObject = (int)igInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)readInfoList)->_construct = 1;
    importantInfoList = (void *)(igMetaObject_GetFieldAt(meta, base + 9));
    ((igObjectRefMetaField *)importantInfoList)->_metaObject = (int)igInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)importantInfoList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beFileListInfoManager_fieldTable, g_beFileListInfoManager_fieldHandles, g_beFileListInfoManager_fieldOffsets, base);
}

