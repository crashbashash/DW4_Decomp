igMetaObject *g_beNDMWAfsSetupDataList_metaObject;

igMetaObject *FUN_003ca800(void) {
    if (g_beNDMWAfsSetupDataList_metaObject == 0) {
        g_beNDMWAfsSetupDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWAfsSetupDataList_metaObject;
}

void *beNDMWAfsSetupDataList_ResolveMetaObject(void) {
    bool ok;
    if (g_beNDMWAfsSetupDataList_metaObject == 0) goto make;
    ok = !!(g_beNDMWAfsSetupDataList_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_003ca8e0();
done:;
    return g_beNDMWAfsSetupDataList_metaObject;
}

int beNDMWAfsSetupDataList_GetVTable(void) {
    Obj_3ca8a0 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_0053c400[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003ca8e0(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsSetupDataList_Register);
}

static igMetaObjectCallback g_beNDMWAfsSetupDataList_callbackList[] = { FUN_003caa70, 0 };

void *beNDMWAfsSetupDataList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWAfsSetupDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWAfsSetupDataList_GetMetaObject,
        "beNDMWAfsSetupDataList",
        0x14, /* instance size */
        beNDMWAfsSetupDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWAfsSetupDataList_callbackList /* callback list */
    );
}

void beNDMWAfsSetupDataList_GetMetaObject(void)
{
    beNDMWAfsSetupDataList_ResolveMetaObject();
}

