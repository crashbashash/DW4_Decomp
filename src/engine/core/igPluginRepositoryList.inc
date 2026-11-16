igMetaObject *g_igPluginRepositoryList_metaObject;
int g_locationTypeMetaEnum;

igMetaObject *igPluginRepositoryList_GetOrCreateMetaObject(void) {
    if (g_igPluginRepositoryList_metaObject == 0) {
        g_igPluginRepositoryList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igPluginRepositoryList_metaObject;
}

igMetaObject *igPluginRepositoryList_GetMetaObject(void)
{
    igMetaObject *g = g_igPluginRepositoryList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPluginRepositoryList_EnsureRegistered();
    return g_igPluginRepositoryList_metaObject;
}

int igPluginRepositoryList_GetVTable(void) {
    igPluginRepositoryList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igPluginRepositoryList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igPluginRepositoryList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPluginRepositoryList_Register);
}

static igMetaObjectCallback g_igPluginRepositoryList_callbackList[] = { igPluginRepository_EnsureRegistered, 0 };

CallbackArray *igPluginRepositoryList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igPluginRepositoryList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igPluginRepositoryList_GetMetaObjectFunction,
        "igPluginRepositoryList",
        0x14,
        igPluginRepositoryList_GetVTable,
        0,
        0,
        g_igPluginRepositoryList_callbackList
    );
}

void igPluginRepositoryList_GetMetaObjectFunction(void) {
    igPluginRepositoryList_GetMetaObject();
}

