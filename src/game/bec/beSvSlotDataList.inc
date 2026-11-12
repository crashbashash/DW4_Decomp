igMetaObject *FUN_0034a4a0(void) {
    if (g_beSvSlotDataList_metaObject[0] == 0) {
        g_beSvSlotDataList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beSvSlotDataList_metaObject[0];
}

void *FUN_0034a4f0(void) {
    igMetaObject *g = g_beSvSlotDataList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034a580();
    }
    return g_beSvSlotDataList_metaObject[0];
}

int beSvSlotDataList_GetVTable(void) {
    struct Obj_34a540 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538a90[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0034a580(void)
{
    igMetaObject_RunStaticInit(beSvSlotDataList_Register);
}

void *beSvSlotDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvSlotDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beSvSlotDataList_GetMetaObject,
        beSvSlotDataList_className,
        0x14, /* instance size */
        beSvSlotDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beSvSlotDataList_callbackList /* callback list */
    );
}

void beSvSlotDataList_GetMetaObject(void)
{
    FUN_0034a4f0();
}

