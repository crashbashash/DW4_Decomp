igMetaObject *g_beGeneraterDataList_metaObject;

igMetaObject *beGeneraterDataList_GetOrCreateMetaObject(void) {
    if (g_beGeneraterDataList_metaObject == 0) {
        g_beGeneraterDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beGeneraterDataList_metaObject;
}

igMetaObject *beGeneraterDataList_GetMetaObject(void) {
    if (g_beGeneraterDataList_metaObject == 0 || !isValid(g_beGeneraterDataList_metaObject)) beGeneraterDataList_EnsureRegistered();
    return g_beGeneraterDataList_metaObject;
}

int beGeneraterDataList_GetVTable(void) {
    struct Obj_35fa70 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beGeneraterDataList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beGeneraterDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterDataList_Register);
}

static igMetaObjectCallback g_beGeneraterDataList_callbackList[] = { beGeneraterData_EnsureRegistered, 0 };

void *beGeneraterDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beGeneraterDataList_GetMetaObjectFunction,
        "beGeneraterDataList",
        0x14, /* instance size */
        beGeneraterDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGeneraterDataList_callbackList /* callback list */
    );
}

void beGeneraterDataList_GetMetaObjectFunction(void)
{
    beGeneraterDataList_GetMetaObject();
}

