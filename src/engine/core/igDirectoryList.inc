igMetaObject *g_igDirectoryList_metaObject;

igMetaObject *igDirectoryList_GetOrCreateMetaObject(void) {
    if (g_igDirectoryList_metaObject == 0) {
        g_igDirectoryList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igDirectoryList_metaObject;
}

igMetaObject *igDirectoryList_GetMetaObject(void)
{
    igMetaObject *g = g_igDirectoryList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDirectoryList_EnsureRegistered();
    return g_igDirectoryList_metaObject;
}

int igDirectoryList_GetVTable(void) {
    igDirectoryList list;
    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igDirectoryList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igDirectoryList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDirectoryList_Register);
}

static igMetaObjectCallback g_igDirectoryList_callbackList[] = { igDirectory_EnsureRegistered, 0 };

CallbackArray *igDirectoryList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igDirectoryList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igDirectoryList_GetMetaObjectFunction,
        "igDirectoryList",
        0x14,
        igDirectoryList_GetVTable,
        0,
        0,
        g_igDirectoryList_callbackList
    );
}

void igDirectoryList_GetMetaObjectFunction(void) {
    igDirectoryList_GetMetaObject();
}

