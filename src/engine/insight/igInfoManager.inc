igMetaObject *g_igInfoManager_metaObject;
igMetaField *g_igInfoManager_insightMetaField;

igMetaObject *igInfoManager_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igInfoManager_EnsureRegistered();
    return g_igInfoManager_metaObject;
}

void igInfoManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igInfoManager_Register);
}

static igMetaObjectCallback g_igInfoManager_callbackList[] = { igInsightCore_EnsureRegistered, 0 };

CallbackArray *igInfoManager_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igInfoManager_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        igInfoManager_GetMetaObjectFunction,
        "igInfoManager",
        0x10, /* instance size */
        0,
        &igInfoManager_InitFields,
        0, /* extra callback item */
        g_igInfoManager_callbackList /* callback list */
    );
}

void igInfoManager_GetMetaObjectFunction(void) {
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
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igInfoManager_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igInsightCore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igInfoManager_fieldTable, g_igInfoManager_fieldHandles, g_igInfoManager_fieldOffsets, temp_s2);
}

