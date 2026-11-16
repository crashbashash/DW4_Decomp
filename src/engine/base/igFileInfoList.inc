igMetaObject *g_igFileInfoList_metaObject;

igMetaObject *FUN_00228cf0(void) {
    if (g_igFileInfoList_metaObject == 0) {
        g_igFileInfoList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igFileInfoList_metaObject;
}

igMetaObject *igFileInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igFileInfoList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00228dd0();
    return g_igFileInfoList_metaObject;
}

int igFileInfoList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_igFileInfoList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00228dd0(void)
{
    igMetaObject_RunStaticInit(igFileInfoList_Register);
}

static igMetaObjectCallback g_igFileInfoList_callbackList[] = { FUN_002290c0, 0 };

void igFileInfoList_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFileInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igFileInfoList_GetMetaObject,
        "igFileInfoList",
        0x14, /* instance size */
        igFileInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igFileInfoList_callbackList /* callback list */
    );
}

void thunk_igFileInfoList_GetMetaObject(void) {
    igFileInfoList_GetMetaObject();
}

