igMetaObject *FUN_003416b0(void) {
    if (g_beTimerDataList_metaObject[0] == 0) {
        g_beTimerDataList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beTimerDataList_metaObject[0];
}

void *FUN_00341700(void) {
    igMetaObject *g = g_beTimerDataList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00341790();
    }
    return g_beTimerDataList_metaObject[0];
}

int beTimerDataList_GetVTable(void) {
    struct Obj_341750 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00539760[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00341790(void)
{
    igMetaObject_RunStaticInit(beTimerDataList_Register);
}

void *beTimerDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTimerDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beTimerDataList_GetMetaObject,
        beTimerDataList_className,
        0x14, /* instance size */
        beTimerDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beTimerDataList_callbackList /* callback list */
    );
}

void beTimerDataList_GetMetaObject(void)
{
    FUN_00341700();
}

