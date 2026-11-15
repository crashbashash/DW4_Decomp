igMetaObject *g_beModelCtrlAIDataList_metaObject;

igMetaObject *FUN_003546d0(void) {
    if (g_beModelCtrlAIDataList_metaObject == 0) {
        g_beModelCtrlAIDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beModelCtrlAIDataList_metaObject;
}

void *FUN_00354720(void) {
    igMetaObject *g = g_beModelCtrlAIDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003547b0();
    }
    return g_beModelCtrlAIDataList_metaObject;
}

int beModelCtrlAIDataList_GetVTable(void) {
    union U_354770 u;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00537890[0];
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_003547b0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlAIDataList_Register);
}

static igMetaObjectCallback g_beModelCtrlAIDataList_callbackList[] = { FUN_00354940, 0 };

void *beModelCtrlAIDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlAIDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beModelCtrlAIDataList_GetMetaObject,
        "beModelCtrlAIDataList",
        0x14, /* instance size */
        beModelCtrlAIDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beModelCtrlAIDataList_callbackList /* callback list */
    );
}

void beModelCtrlAIDataList_GetMetaObject(void)
{
    FUN_00354720();
}

