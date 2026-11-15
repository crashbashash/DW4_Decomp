igMetaObject *g_beWaterMoveDataList_metaObject;

igMetaObject *FUN_00340720(void) {
    if (g_beWaterMoveDataList_metaObject == 0) {
        g_beWaterMoveDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beWaterMoveDataList_metaObject;
}

void *FUN_00340770(void) {
    bool ok;
    if (g_beWaterMoveDataList_metaObject == 0) goto make;
    ok = !!(g_beWaterMoveDataList_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_00340800();
done:;
    return g_beWaterMoveDataList_metaObject;
}

int beWaterMoveDataList_GetVTable(void) {
    struct Obj_3407c0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005399a0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00340800(void)
{
    igMetaObject_RunStaticInit(beWaterMoveDataList_Register);
}

static igMetaObjectCallback g_beWaterMoveDataList_callbackList[] = { FUN_00340990, 0 };

void *beWaterMoveDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWaterMoveDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beWaterMoveDataList_GetMetaObject,
        "beWaterMoveDataList",
        0x14, /* instance size */
        beWaterMoveDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beWaterMoveDataList_callbackList /* callback list */
    );
}

void beWaterMoveDataList_GetMetaObject(void)
{
    FUN_00340770();
}

