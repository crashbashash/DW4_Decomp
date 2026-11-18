igMetaObject *g_igInsightPluginList_metaObject;

igMetaObject *igInsightPluginList_GetOrCreateMetaObject(void) {
    if (g_igInsightPluginList_metaObject == 0) {
        g_igInsightPluginList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igInsightPluginList_metaObject;
}

igMetaObject *igInsightPluginList_GetMetaObject(void)
{
    igMetaObject *g = g_igInsightPluginList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igInsightPluginList_EnsureRegistered();
    return g_igInsightPluginList_metaObject;
}

int igInsightPluginList_GetVTable(void) {
    struct Obj_232660 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igInsightPluginList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igInsightPluginList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igInsightPluginList_Register);
}

static igMetaObjectCallback g_igInsightPluginList_callbackList[] = { igInsightPlugin_EnsureRegistered, 0 };

CallbackArray *igInsightPluginList_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igInsightPluginList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igInsightPluginList_GetMetaObjectFunction,
        "igInsightPluginList",
        0x14, /* instance size */
        igInsightPluginList_GetVTable,
        0,
        0, /* extra callback item */
        g_igInsightPluginList_callbackList /* callback list */
    );
}

void igInsightPluginList_GetMetaObjectFunction(void) {
    igInsightPluginList_GetMetaObject();
}

