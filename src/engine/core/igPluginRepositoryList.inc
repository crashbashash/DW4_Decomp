igMetaObject *igPluginRepositoryList_GetOrCreateMetaObject(void) {
    if (g_igPluginRepositoryList_metaObject[0] == 0) {
        g_igPluginRepositoryList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igPluginRepositoryList_metaObject[0];
}

igMetaObject *igPluginRepositoryList_GetMetaObject(void)
{
    igMetaObject *g = g_igPluginRepositoryList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igPluginRepositoryList_EnsureRegistered();
    return g_igPluginRepositoryList_metaObject[0];
}

int igPluginRepositoryList_GetVTable(void) {
    igPluginRepositoryList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00532e40[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igPluginRepositoryList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPluginRepositoryList_Register);
}

void igPluginRepositoryList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igPluginRepositoryList_metaObject,
        (igMetaObjectRegisterFunction)igObjectList_Register,
        (igMetaObjectGetFunction)igObjectList_GetPublishedMetaObject,
        igPluginRepositoryList_GetMetaObjectFunction,
        igPluginRepositoryList_className,
        0x14,
        igPluginRepositoryList_GetVTable,
        0,
        0,
        (igMetaObjectCallback *)g_igPluginRepositoryList_callbackList
    );
}

void igPluginRepositoryList_GetMetaObjectFunction(void) {
    igPluginRepositoryList_GetMetaObject();
}

