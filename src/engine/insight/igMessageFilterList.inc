igMetaObject *g_igMessageFilterList_metaObject;

igMetaObject *FUN_002319d0(void) {
    if (g_igMessageFilterList_metaObject == 0) {
        g_igMessageFilterList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igMessageFilterList_metaObject;
}

igMetaObject *igMessageFilterList_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageFilterList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231ab0();
    return g_igMessageFilterList_metaObject;
}

int igMessageFilterList_GetVTable(void) {
    struct Obj_231a70 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052ce40[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00231ab0(void)
{
    igMetaObject_RunStaticInit(igMessageFilterList_Register);
}

static igMetaObjectCallback g_igMessageFilterList_callbackList[] = { FUN_00231cb0, 0 };

void igMessageFilterList_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMessageFilterList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMessageFilterList_GetMetaObject,
        "igMessageFilterList",
        0x14, /* instance size */
        igMessageFilterList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMessageFilterList_callbackList /* callback list */
    );
}

void thunk_igMessageFilterList_GetMetaObject(void) {
    igMessageFilterList_GetMetaObject();
}

