igMetaObject *igDirectoryList_GetOrCreateMetaObject(void) {
    if (g_igDirectoryList_metaObject[0] == 0) {
        g_igDirectoryList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igDirectoryList_metaObject[0];
}

igMetaObject *igDirectoryList_GetMetaObject(void)
{
    igMetaObject *g = g_igDirectoryList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDirectoryList_EnsureRegistered();
    return g_igDirectoryList_metaObject[0];
}

int igDirectoryList_GetVTable(void) {
    igDirectoryList list;
    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_005323c0[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igDirectoryList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDirectoryList_Register);
}

void igDirectoryList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igDirectoryList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igDirectoryList_GetMetaObjectFunction,
        igDirectoryList_className,
        0x14, /* instance size */
        igDirectoryList_GetVTable,
        0,
        0, /* extra callback item */
        g_igDirectoryList_callbackList /* callback list */
    );
}

void igDirectoryList_GetMetaObjectFunction(void) {
    igDirectoryList_GetMetaObject();
}

