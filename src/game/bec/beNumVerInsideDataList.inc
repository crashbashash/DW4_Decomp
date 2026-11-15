igMetaObject *g_beNumVerInsideDataList_metaObject;

igMetaObject *FUN_0034dcd0(void) {
    if (g_beNumVerInsideDataList_metaObject == 0) {
        g_beNumVerInsideDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNumVerInsideDataList_metaObject;
}

void *FUN_0034dd20(void) {
    igMetaObject *g = g_beNumVerInsideDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034ddb0();
    }
    return g_beNumVerInsideDataList_metaObject;
}

int beNumVerInsideDataList_GetVTable(void) {
    struct Obj_34dd70 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538390[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0034ddb0(void)
{
    igMetaObject_RunStaticInit(beNumVerInsideDataList_Register);
}

static igMetaObjectCallback g_beNumVerInsideDataList_callbackList[] = { FUN_0034df30, 0 };

void *beNumVerInsideDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNumVerInsideDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNumVerInsideDataList_GetMetaObject,
        "beNumVerInsideDataList",
        0x14, /* instance size */
        beNumVerInsideDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNumVerInsideDataList_callbackList /* callback list */
    );
}

void beNumVerInsideDataList_GetMetaObject(void)
{
    FUN_0034dd20();
}

