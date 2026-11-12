igMetaObject *FUN_0036bc60(void) {
    if (g_beActionStarterDataList_metaObject[0] == 0) {
        g_beActionStarterDataList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beActionStarterDataList_metaObject[0];
}

void *FUN_0036bcb0(void) {
    igMetaObject *g = g_beActionStarterDataList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0036bd40();
    }
    return g_beActionStarterDataList_metaObject[0];
}

int beActionStarterDataList_GetVTable(void) {
    struct Obj_36bd00 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00534410[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0036bd40(void)
{
    igMetaObject_RunStaticInit(beActionStarterDataList_Register);
}

void *beActionStarterDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beActionStarterDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beActionStarterDataList_GetMetaObject,
        beActionStarterDataList_className,
        0x14, /* instance size */
        beActionStarterDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beActionStarterDataList_callbackList /* callback list */
    );
}

void beActionStarterDataList_GetMetaObject(void)
{
    FUN_0036bcb0();
}

