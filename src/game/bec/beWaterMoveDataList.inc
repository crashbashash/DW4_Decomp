igMetaObject *FUN_00340720(void) {
    if (g_beWaterMoveDataList_metaObject[0] == 0) {
        g_beWaterMoveDataList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beWaterMoveDataList_metaObject[0];
}

void *FUN_00340770(void) {
    bool ok;
    if (g_beWaterMoveDataList_metaObject[0] == 0) goto make;
    ok = !!(g_beWaterMoveDataList_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_00340800();
done:;
    return g_beWaterMoveDataList_metaObject[0];
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

void *beWaterMoveDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWaterMoveDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beWaterMoveDataList_GetMetaObject,
        beWaterMoveDataList_className,
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

