int FUN_00340720(void) {
    if (((int *)DAT_00587bb8)[0] == 0) {
        ((int *)DAT_00587bb8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00587bb8)[0];
}

void *FUN_00340770(void) {
    bool ok;
    if (DAT_00587bb8[0] == 0) goto make;
    ok = !!(DAT_00587bb8[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_00340800();
done:;
    return DAT_00587bb8[0];
}

int beWaterMoveDataList_GetVTable(void) {
    struct Obj_3407c0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005399a0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
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

