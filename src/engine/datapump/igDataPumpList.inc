igMetaObject *g_igDataPumpList_metaObject;

igMetaObject *igDataPumpList_GetOrCreateMetaObject(void) {
    if (g_igDataPumpList_metaObject == 0) {
        g_igDataPumpList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igDataPumpList_metaObject;
}

igMetaObject *igDataPumpList_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDataPumpList_EnsureRegistered();
    return g_igDataPumpList_metaObject;
}

int igDataPumpList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igDataPumpList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igDataPumpList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDataPumpList_Register);
}

static igMetaObjectCallback g_igDataPumpList_callbackList[] = { igDataPump_EnsureRegistered, 0 };

CallbackArray *igDataPumpList_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igDataPumpList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igDataPumpList_GetMetaObjectFunction,
        "igDataPumpList",
        0x14, /* instance size */
        igDataPumpList_GetVTable,
        0,
        0, /* extra callback item */
        g_igDataPumpList_callbackList /* callback list */
    );
}

void igDataPumpList_GetMetaObjectFunction(void) {
    igDataPumpList_GetMetaObject();
}

