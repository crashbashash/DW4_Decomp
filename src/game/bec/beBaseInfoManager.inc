igMetaObject *g_beBaseInfoManager_metaObject;
igMetaField *g_beBaseInfoManager_systemMetaField;
igMetaField *g_beBaseInfoManager_messengerMetaField;
igMetaField *g_beBaseInfoManager_infoListMetaField;
igMetaField *g_beBaseInfoManager_isUpdateRunMetaField;

igMetaObject *beBaseInfoManager_GetOrCreateMetaObject(void) {
    if (g_beBaseInfoManager_metaObject == 0) {
        g_beBaseInfoManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beBaseInfoManager_metaObject;
}

igMetaObject *beBaseInfoManager_GetMetaObject(void) {
    igMetaObject *g = g_beBaseInfoManager_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beBaseInfoManager_EnsureRegistered();
    return g_beBaseInfoManager_metaObject;
}

void beBaseInfoManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beBaseInfoManager_Register);
}

static igMetaObjectCallback g_beBaseInfoManager_callbackList[] = { beSystem_EnsureRegistered, beMessenger_EnsureRegistered, beBaseInfoList_EnsureRegistered, 0 };

CallbackArray *beBaseInfoManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beBaseInfoManager_metaObject,
        Gap::Insight::igInfoManager::arkRegisterInternal,
        Gap::Insight::igInfoManager::getClassMeta,
        beBaseInfoManager_GetMetaObjectFunction,
        "beBaseInfoManager",
        0x20, /* instance size */
        0,
        beBaseInfoManager_InitFields,
        0, /* extra callback item */
        g_beBaseInfoManager_callbackList /* callback list */
    );
}

void beBaseInfoManager_GetMetaObjectFunction(void)
{
    beBaseInfoManager_GetMetaObject();
}

static FieldFactory g_beBaseInfoManager_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beBaseInfoManager_fieldTable[] = {
    "_system",
    "_messenger",
    "_infoList",
    "_isUpdateRun",
};
static igMetaField **g_beBaseInfoManager_fieldHandles[] = {
    &g_beBaseInfoManager_systemMetaField,
    &g_beBaseInfoManager_messengerMetaField,
    &g_beBaseInfoManager_infoListMetaField,
    &g_beBaseInfoManager_isUpdateRunMetaField,
};
static int g_beBaseInfoManager_fieldOffsets[] = {
    16,
    20,
    24,
    28,
};

void beBaseInfoManager_InitFields(void) {
    int base;
    void *infoList;
    void *messenger;
    void *system;
    igMetaObject *meta;

    meta = g_beBaseInfoManager_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beBaseInfoManager_ctorTable, 4);
    system = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)system)->_metaObject = (int)beSystem_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)system)->_refCounted = 0;
    messenger = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)messenger)->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    infoList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)infoList)->_metaObject = (int)beBaseInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)infoList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beBaseInfoManager_fieldTable, g_beBaseInfoManager_fieldHandles, g_beBaseInfoManager_fieldOffsets, base);
}

