igMetaObject *g_beWaterMoveDataList_metaObject;

igMetaObject *beWaterMoveDataList_GetOrCreateMetaObject(void) {
    if (g_beWaterMoveDataList_metaObject == 0) {
        g_beWaterMoveDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beWaterMoveDataList_metaObject;
}

void *beWaterMoveDataList_GetMetaObject(void) {
    bool ok;
    if (g_beWaterMoveDataList_metaObject == 0) goto make;
    ok = !!(g_beWaterMoveDataList_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beWaterMoveDataList_EnsureRegistered();
done:;
    return g_beWaterMoveDataList_metaObject;
}

int beWaterMoveDataList_GetVTable(void) {
    struct Obj_3407c0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beWaterMoveDataList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beWaterMoveDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beWaterMoveDataList_Register);
}

static igMetaObjectCallback g_beWaterMoveDataList_callbackList[] = { beWaterMoveData_EnsureRegistered, 0 };

void *beWaterMoveDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWaterMoveDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beWaterMoveDataList_GetMetaObjectFunction,
        "beWaterMoveDataList",
        0x14, /* instance size */
        beWaterMoveDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beWaterMoveDataList_callbackList /* callback list */
    );
}

void beWaterMoveDataList_GetMetaObjectFunction(void)
{
    beWaterMoveDataList_GetMetaObject();
}

