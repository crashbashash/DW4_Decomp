igMetaObject *g_beNDMWDegiDataList_metaObject;

igMetaObject *beNDMWDegiDataList_GetOrCreateMetaObject(void) {
    if (g_beNDMWDegiDataList_metaObject == 0) {
        g_beNDMWDegiDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWDegiDataList_metaObject;
}

void *beNDMWDegiDataList_GetReadyMetaObject(void) {
    bool ok;
    if (g_beNDMWDegiDataList_metaObject == 0) goto make;
    ok = !!(g_beNDMWDegiDataList_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beNDMWDegiDataList_EnsureRegistered();
done:;
    return g_beNDMWDegiDataList_metaObject;
}

int beNDMWDegiDataList_GetVTable(void) {
    beNDMWDegiDataList obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWDegiDataList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beNDMWDegiDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWDegiDataList_Register);
}

static igMetaObjectCallback g_beNDMWDegiDataList_callbackList[] = { beNDMWDegiData_RunStaticInit, 0 };

void *beNDMWDegiDataList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWDegiDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWDegiDataList_GetMetaObject,
        "beNDMWDegiDataList",
        0x14, /* instance size */
        beNDMWDegiDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWDegiDataList_callbackList /* callback list */
    );
}

void beNDMWDegiDataList_GetMetaObject(void)
{
    beNDMWDegiDataList_GetReadyMetaObject();
}

