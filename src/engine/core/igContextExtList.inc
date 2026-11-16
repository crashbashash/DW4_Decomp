igMetaObject *g_igContextExtList_metaObject;

igMetaObject *igContextExtList_GetOrCreateMetaObject(void) {
    if (g_igContextExtList_metaObject == 0) {
        g_igContextExtList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igContextExtList_metaObject;
}

igMetaObject *igContextExtList_GetMetaObject(void)
{
    igMetaObject *g = g_igContextExtList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igContextExtList_EnsureRegistered();
    return g_igContextExtList_metaObject;
}

int igContextExtList_GetVTable(void) {
    igContextExtList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igContextExtList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igContextExtList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igContextExtList_Register);
}

static igMetaObjectCallback g_igContextExtList_callbackList[] = { igContextExt_EnsureRegistered, 0 };

CallbackArray *igContextExtList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igContextExtList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igContextExtList_GetMetaObjectFunction,
        "igContextExtList",
        0x14,
        igContextExtList_GetVTable,
        0,
        0,
        g_igContextExtList_callbackList
    );
}

void igContextExtList_GetMetaObjectFunction(void) {
    igContextExtList_GetMetaObject();
}

