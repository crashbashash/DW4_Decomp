igMetaObject *g_igThreadList_metaObject;

igMetaObject *igThreadList_GetOrCreateMetaObject(void) {
    if (g_igThreadList_metaObject == 0) {
        g_igThreadList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igThreadList_metaObject;
}

igMetaObject *igThreadList_GetMetaObject(void)
{
    igMetaObject *g = g_igThreadList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igThreadList_EnsureRegistered();
    return g_igThreadList_metaObject;
}

int igThreadList_GetVTable(void) {
    igThreadList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igThreadList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igThreadList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igThreadList_Register);
}

static igMetaObjectCallback g_igThreadList_callbackList[] = { igThread_EnsureRegistered, 0 };

CallbackArray *igThreadList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igThreadList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igThreadList_GetMetaObjectFunction,
        "igThreadList",
        0x14,
        igThreadList_GetVTable,
        0,
        0,
        g_igThreadList_callbackList
    );
}

void igThreadList_GetMetaObjectFunction(void) {
    igThreadList_GetMetaObject();
}

