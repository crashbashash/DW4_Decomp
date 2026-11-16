igMetaObject *g_beNDMWAfsSetupDataList_metaObject;

igMetaObject *beNDMWAfsSetupDataList_GetOrCreateMetaObject(void) {
    if (g_beNDMWAfsSetupDataList_metaObject == 0) {
        g_beNDMWAfsSetupDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWAfsSetupDataList_metaObject;
}

void *beNDMWAfsSetupDataList_ResolveMetaObject(void) {
    bool ok;
    if (g_beNDMWAfsSetupDataList_metaObject == 0) goto make;
    ok = !!(g_beNDMWAfsSetupDataList_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beNDMWAfsSetupDataList_EnsureRegistered();
done:;
    return g_beNDMWAfsSetupDataList_metaObject;
}

int beNDMWAfsSetupDataList_GetVTable(void) {
    beNDMWAfsSetupDataList obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWAfsSetupDataList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
}

void beNDMWAfsSetupDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsSetupDataList_Register);
}

static igMetaObjectCallback g_beNDMWAfsSetupDataList_callbackList[] = { beNDMWAfsSetupData_EnsureRegistered, 0 };

CallbackArray *beNDMWAfsSetupDataList_Register(void) {
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

