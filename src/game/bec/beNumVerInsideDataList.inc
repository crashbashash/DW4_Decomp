igMetaObject *FUN_0034dcd0(void) {
    if (g_beNumVerInsideDataList_metaObject[0] == 0) {
        g_beNumVerInsideDataList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNumVerInsideDataList_metaObject[0];
}

void *FUN_0034dd20(void) {
    igMetaObject *g = g_beNumVerInsideDataList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034ddb0();
    }
    return g_beNumVerInsideDataList_metaObject[0];
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

void *beNumVerInsideDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNumVerInsideDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNumVerInsideDataList_GetMetaObject,
        beNumVerInsideDataList_className,
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

