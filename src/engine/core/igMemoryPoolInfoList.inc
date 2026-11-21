igMetaObject *g_igMemoryPoolInfoList_metaObject;

igMetaObject *igMemoryPoolInfoList_GetOrCreateMetaObject(void) {
    if (g_igMemoryPoolInfoList_metaObject == 0) {
        g_igMemoryPoolInfoList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMemoryPoolInfoList_metaObject;
}

igMetaObject *igMemoryPoolInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPoolInfoList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryPoolInfoList_EnsureRegistered();
    return g_igMemoryPoolInfoList_metaObject;
}

int igMemoryPoolInfoList_GetVTable(void) {
    igMemoryPoolInfoList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igMemoryPoolInfoList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igMemoryPoolInfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMemoryPoolInfoList_Register);
}

static igMetaObjectCallback g_igMemoryPoolInfoList_callbackList[] = { igMemoryPoolInfo_EnsureRegistered, 0 };

CallbackArray *igMemoryPoolInfoList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igMemoryPoolInfoList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igMemoryPoolInfoList_GetMetaObjectFunction,
        "igMemoryPoolInfoList",
        0x14,
        igMemoryPoolInfoList_GetVTable,
        0,
        0,
        g_igMemoryPoolInfoList_callbackList
    );
}

void igMemoryPoolInfoList_GetMetaObjectFunction(void) {
    igMemoryPoolInfoList_GetMetaObject();
}

