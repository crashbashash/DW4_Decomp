igMetaObject *g_beBaseInfoManager_metaObject;
igMetaField *g_beBaseInfoManager_systemMetaField;
igMetaField *g_beBaseInfoManager_messengerMetaField;
igMetaField *g_beBaseInfoManager_infoListMetaField;
igMetaField *g_beBaseInfoManager_isUpdateRunMetaField;

igMetaObject *beBaseInfoManager_GetOrCreateMetaObject(void) {
    if (g_beBaseInfoManager_metaObject == 0) {
        g_beBaseInfoManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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

void *beBaseInfoManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beBaseInfoManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
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
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beBaseInfoManager_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beBaseInfoManager_ctorTable, 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beSystem_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)beBaseInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beBaseInfoManager_fieldTable, g_beBaseInfoManager_fieldHandles, g_beBaseInfoManager_fieldOffsets, temp_s2);
}

