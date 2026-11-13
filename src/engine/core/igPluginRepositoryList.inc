igMetaObject *FUN_002bc760(void) {
    if (g_igPluginRepositoryList_metaObject[0] == 0) {
        g_igPluginRepositoryList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igPluginRepositoryList_metaObject[0];
}

igMetaObject *igPluginRepositoryList_GetMetaObject(void)
{
    igMetaObject *g = g_igPluginRepositoryList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bc840();
    return g_igPluginRepositoryList_metaObject[0];
}

int igPluginRepositoryList_GetVTable(void) {
    struct Obj_2bc800 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00532e40[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002bc840(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPluginRepositoryList_Register);
}

void igPluginRepositoryList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPluginRepositoryList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igPluginRepositoryList_GetMetaObject,
        igPluginRepositoryList_className,
        0x14, /* instance size */
        igPluginRepositoryList_GetVTable,
        0,
        0, /* extra callback item */
        g_igPluginRepositoryList_callbackList /* callback list */
    );
}

void thunk_igPluginRepositoryList_GetMetaObject(void) {
    igPluginRepositoryList_GetMetaObject();
}

