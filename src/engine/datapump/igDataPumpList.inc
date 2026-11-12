igMetaObject *FUN_001e53c0(void) {
    if (g_igDataPumpList_metaObject[0] == 0) {
        g_igDataPumpList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igDataPumpList_metaObject[0];
}

igMetaObject *igDataPumpList_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e54a0();
    return g_igDataPumpList_metaObject[0];
}

int igDataPumpList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052ba80[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001e54a0(void)
{
    igMetaObject_RunStaticInit(igDataPumpList_Register);
}

void igDataPumpList_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDataPumpList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igDataPumpList_GetMetaObject,
        igDataPumpList_className,
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

