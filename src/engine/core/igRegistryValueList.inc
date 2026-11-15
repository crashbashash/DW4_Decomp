igMetaObject *g_igRegistryValueList_metaObject;

igMetaObject *igRegistryValueList_GetOrCreateMetaObject(void) {
    if (g_igRegistryValueList_metaObject == 0) {
        g_igRegistryValueList_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igRegistryValueList_metaObject;
}

igMetaObject *igRegistryValueList_GetMetaObject(void)
{
    igMetaObject *g = g_igRegistryValueList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRegistryValueList_EnsureRegistered();
    return g_igRegistryValueList_metaObject;
}

int igRegistryValueList_GetVTable(void) {
    igRegistryValueList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igRegistryValueList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
}

void igRegistryValueList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igRegistryValueList_Register);
}

static igMetaObjectCallback g_igRegistryValueList_callbackList[] = { igRegistryValue_EnsureRegistered, 0 };

void igRegistryValueList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igRegistryValueList_metaObject,
        (igMetaObjectRegisterFunction)igObjectList_Register,
        (igMetaObjectGetFunction)igObjectList_GetPublishedMetaObject,
        igRegistryValueList_GetMetaObjectFunction,
        "igRegistryValueList",
        0x14,
        igRegistryValueList_GetVTable,
        0,
        0,
        g_igRegistryValueList_callbackList
    );
}

void igRegistryValueList_GetMetaObjectFunction(void) {
    igRegistryValueList_GetMetaObject();
}

