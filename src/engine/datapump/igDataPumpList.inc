igMetaObject *g_igDataPumpList_metaObject;

igMetaObject *FUN_001e53c0(void) {
    if (g_igDataPumpList_metaObject == 0) {
        g_igDataPumpList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igDataPumpList_metaObject;
}

igMetaObject *igDataPumpList_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e54a0();
    return g_igDataPumpList_metaObject;
}

int igDataPumpList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igDataPumpList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
}

void FUN_001e54a0(void)
{
    igMetaObject_RunStaticInit(igDataPumpList_Register);
}

static igMetaObjectCallback g_igDataPumpList_callbackList[] = { FUN_001e5ab0, 0 };

CallbackArray *igDataPumpList_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igDataPumpList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igDataPumpList_GetMetaObject,
        "igDataPumpList",
        0x14, /* instance size */
        igDataPumpList_GetVTable,
        0,
        0, /* extra callback item */
        g_igDataPumpList_callbackList /* callback list */
    );
}

void thunk_igDataPumpList_GetMetaObject(void) {
    igDataPumpList_GetMetaObject();
}

