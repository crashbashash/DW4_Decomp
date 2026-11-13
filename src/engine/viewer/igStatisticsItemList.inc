igMetaObject *FUN_00458ae0(void) {
    if (g_igStatisticsItemList_metaObject[0] == 0) {
        g_igStatisticsItemList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igStatisticsItemList_metaObject[0];
}

void *igStatisticsItemList_GetMetaObject(void) {
    igMetaObject *g = g_igStatisticsItemList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00458bc0();
    }
    return g_igStatisticsItemList_metaObject[0];
}

int igStatisticsItemList_GetVTable(void) {
    struct Obj_458b80 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005421c0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void *)g_objectSystem[0])) + 916));
}

void FUN_00458bc0(void)
{
    igMetaObject_RunStaticInit(igStatisticsItemList_Register);
}

void igStatisticsItemList_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStatisticsItemList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igStatisticsItemList_GetMetaObject,
        igStatisticsItemList_className,
        0x14, /* instance size */
        igStatisticsItemList_GetVTable,
        0,
        0, /* extra callback item */
        g_igStatisticsItemList_callbackList /* callback list */
    );
}

void thunk_igStatisticsItemList_GetMetaObject(void) {
    igStatisticsItemList_GetMetaObject();
}

