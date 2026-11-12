igMetaObject *FUN_002319d0(void) {
    if (g_igMessageFilterList_metaObject[0] == 0) {
        g_igMessageFilterList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igMessageFilterList_metaObject[0];
}

igMetaObject *igMessageFilterList_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageFilterList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231ab0();
    return g_igMessageFilterList_metaObject[0];
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

void igMessageFilterList_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageFilterList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMessageFilterList_GetMetaObject,
        igMessageFilterList_className,
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

