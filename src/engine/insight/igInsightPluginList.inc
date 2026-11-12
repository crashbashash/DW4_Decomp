igMetaObject *FUN_002325c0(void) {
    if (g_igInsightPluginList_metaObject[0] == 0) {
        g_igInsightPluginList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igInsightPluginList_metaObject[0];
}

igMetaObject *igInsightPluginList_GetMetaObject(void)
{
    igMetaObject *g = g_igInsightPluginList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002326a0();
    return g_igInsightPluginList_metaObject[0];
}

int igInsightPluginList_GetVTable(void) {
    struct Obj_232660 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052cd70[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_002326a0(void)
{
    igMetaObject_RunStaticInit(igInsightPluginList_Register);
}

void igInsightPluginList_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igInsightPluginList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igInsightPluginList_GetMetaObject,
        igInsightPluginList_className,
        0x14, /* instance size */
        igInsightPluginList_GetVTable,
        0,
        0, /* extra callback item */
        g_igInsightPluginList_callbackList /* callback list */
    );
}

void thunk_igInsightPluginList_GetMetaObject(void) {
    igInsightPluginList_GetMetaObject();
}

