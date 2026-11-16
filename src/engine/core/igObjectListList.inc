igMetaObject *g_igObjectListList_metaObject;

igMetaObject *igObjectListList_GetOrCreateMetaObject(void) {
    if (g_igObjectListList_metaObject == 0) {
        g_igObjectListList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igObjectListList_metaObject;
}

igMetaObject *igObjectListList_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectListList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igObjectListList_EnsureRegistered();
    return g_igObjectListList_metaObject;
}

int igObjectListList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((igObject *)&tmp[0]);
    tmp[0] = (int)&g_igObjectListList_vtable[0];
    off = g_objectSystem->vtableProbeOffset;
    return *(int *)((char *)tmp + off);
}

void igObjectListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igObjectListList_Register);
}

static igMetaObjectCallback g_igObjectListList_callbackList[] = { igObjectList_EnsureRegistered, 0 };

CallbackArray *igObjectListList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igObjectListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igObjectListList_GetMetaObjectFunction,
        "igObjectListList",
        0x14,
        igObjectListList_GetVTable,
        0,
        0,
        g_igObjectListList_callbackList
    );
}

void igObjectListList_GetMetaObjectFunction(void) {
    igObjectListList_GetMetaObject();
}

