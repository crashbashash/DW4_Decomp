igMetaObject *g_igPluginRepositoryList_metaObject;
int g_locationTypeMetaEnum;

igMetaObject *igPluginRepositoryList_GetOrCreateMetaObject(void) {
    if (g_igPluginRepositoryList_metaObject == 0) {
        g_igPluginRepositoryList_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
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
    return *(int *)((char *)&list + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
}

void igPluginRepositoryList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPluginRepositoryList_Register);
}

static igMetaObjectCallback g_igPluginRepositoryList_callbackList[] = { igPluginRepository_EnsureRegistered, 0 };

void igPluginRepositoryList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igPluginRepositoryList_metaObject,
        (igMetaObjectRegisterFunction)igObjectList_Register,
        (igMetaObjectGetFunction)igObjectList_GetPublishedMetaObject,
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

