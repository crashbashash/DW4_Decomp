igMetaObject *g_igInfoManager_metaObject;
igMetaField *g_igInfoManager_insightMetaField;

igMetaObject *igInfoManager_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00233910();
    return g_igInfoManager_metaObject;
}

void FUN_00233910(void)
{
    igMetaObject_RunStaticInit(igInfoManager_Register);
}

static igMetaObjectCallback g_igInfoManager_callbackList[] = { igInsightCore_EnsureRegistered, 0 };

void igInfoManager_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igInfoManager_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igInfoManager_GetMetaObject,
        "igInfoManager",
        0x10, /* instance size */
        0,
        &igInfoManager_InitFields,
        0, /* extra callback item */
        g_igInfoManager_callbackList /* callback list */
    );
}

void thunk_igInfoManager_GetMetaObject(void) {
    igInfoManager_GetMetaObject();
}

static FieldFactory g_igInfoManager_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igInfoManager_fieldTable[] = {
    "_insight",
};
static igMetaField **g_igInfoManager_fieldHandles[] = {
    &g_igInfoManager_insightMetaField,
};
static int g_igInfoManager_fieldOffsets[] = {
    12,
};

void igInfoManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igInfoManager_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igInfoManager_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igInsightCore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, g_igInfoManager_fieldTable, g_igInfoManager_fieldHandles, g_igInfoManager_fieldOffsets, temp_s2);
}

