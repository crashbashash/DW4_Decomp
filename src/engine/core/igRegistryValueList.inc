igMetaObject *igRegistryValueList_GetOrCreateMetaObject(void) {
    if (g_igRegistryValueList_metaObject[0] == 0) {
        g_igRegistryValueList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igRegistryValueList_metaObject[0];
}

igMetaObject *igRegistryValueList_GetMetaObject(void)
{
    igMetaObject *g = g_igRegistryValueList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRegistryValueList_EnsureRegistered();
    return g_igRegistryValueList_metaObject[0];
}

int igRegistryValueList_GetVTable(void) {
    igRegistryValueList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00533010[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igRegistryValueList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igRegistryValueList_Register);
}

void igRegistryValueList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igRegistryValueList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igRegistryValueList_GetMetaObjectFunction,
        igRegistryValueList_className,
        0x14, /* instance size */
        igRegistryValueList_GetVTable,
        0,
        0, /* extra callback item */
        g_igRegistryValueList_callbackList /* callback list */
    );
}

void igRegistryValueList_GetMetaObjectFunction(void) {
    igRegistryValueList_GetMetaObject();
}

