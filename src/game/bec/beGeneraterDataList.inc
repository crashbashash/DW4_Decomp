igMetaObject *FUN_0035f9d0(void) {
    if (g_beGeneraterDataList_metaObject[0] == 0) {
        g_beGeneraterDataList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beGeneraterDataList_metaObject[0];
}

igMetaObject *FUN_0035fa20(void) {
    if (g_beGeneraterDataList_metaObject[0] == 0 || !isValid(g_beGeneraterDataList_metaObject[0])) FUN_0035fab0();
    return g_beGeneraterDataList_metaObject[0];
}

int beGeneraterDataList_GetVTable(void) {
    struct Obj_35fa70 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00535f10[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0035fab0(void)
{
    igMetaObject_RunStaticInit(beGeneraterDataList_Register);
}

void *beGeneraterDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beGeneraterDataList_GetMetaObject,
        beGeneraterDataList_className,
        0x14, /* instance size */
        beGeneraterDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGeneraterDataList_callbackList /* callback list */
    );
}

void beGeneraterDataList_GetMetaObject(void)
{
    FUN_0035fa20();
}

