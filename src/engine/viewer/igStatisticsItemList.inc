int FUN_00458ae0(void) {
    if (DAT_0058c700[0] == 0) {
        DAT_0058c700[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c700[0];
}

void *igStatisticsItemList_GetMetaObject(void) {
    struct G *g = ((G *)DAT_0058c700[0]);
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00458bc0();
    }
    return ((G *)DAT_0058c700[0]);
}

int igStatisticsItemList_GetVTable(void) {
    struct Obj_458b80 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005421c0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void *)DAT_00586dc8[0])) + 916));
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

