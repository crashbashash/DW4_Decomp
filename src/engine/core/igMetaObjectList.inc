igMetaObject *g_igMetaObjectList_metaObject;

void * igMetaObjectList_Create(int pool) {
    igMetaObjectList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igMetaObjectList_metaObject, (igMemoryPoolView *)pool));
}

igMetaObject *igMetaObjectList_GetOrCreateMetaObject(void) {
    if (g_igMetaObjectList_metaObject == 0) {
        g_igMetaObjectList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMetaObjectList_metaObject;
}

igMetaObject *igMetaObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaObjectList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMetaObjectList_EnsureRegistered();
    return g_igMetaObjectList_metaObject;
}

int igMetaObjectList_GetVTable(void) {
    igMetaObjectList obj;

    igObject_InitHeader((igObject *)&obj);
    obj._vtable = (int)&g_igMetaObjectList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igMetaObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMetaObjectList_Register);
}

static igMetaObjectCallback g_igMetaObjectList_callbackList[] = { igMetaObject_EnsureRegistered, 0 };

CallbackArray *igMetaObjectList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igMetaObjectList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igMetaObjectList_GetMetaObjectFunction,
        "igMetaObjectList",
        0x14,
        igMetaObjectList_GetVTable,
        0,
        0,
        g_igMetaObjectList_callbackList
    );
}

void igMetaObjectList_GetMetaObjectFunction(void) {
    igMetaObjectList_GetMetaObject();
}

