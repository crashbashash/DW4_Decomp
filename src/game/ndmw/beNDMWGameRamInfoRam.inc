igMetaObject *g_beNDMWGameRamInfoRam_metaObject;

beNDMWGameRamInfoRam *beNDMWGameRamInfoRam_Create(int allocator) {
    beNDMWGameRamInfoRam_EnsureRegistered();
    return (beNDMWGameRamInfoRam *)igMetaObject_CreateInstance(g_beNDMWGameRamInfoRam_metaObject, allocator);
}

igMetaObject *beNDMWGameRamInfoRam_ResolveMetaObject(void) {
    if (g_beNDMWGameRamInfoRam_metaObject == 0 || !isValid(g_beNDMWGameRamInfoRam_metaObject)) beNDMWGameRamInfoRam_EnsureRegistered();
    return g_beNDMWGameRamInfoRam_metaObject;
}

int beNDMWGameRamInfoRam_GetVTable(void) {
    beNDMWGameRamInfoRam obj;
    int vtable;
    int *dataListRef;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beBaseInfoRam_vtable[0];
    dataListRef = &obj._dataList;
    *dataListRef = 0;
    *(int **)&obj._vtable = &g_beNDMWGameRamInfoRam_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beBaseInfoRam_vtable[0];
    if (dataListRef != 0) {
        igRelease((igObject *)*dataListRef);
    }
    return vtable;
}

void beNDMWGameRamInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWGameRamInfoRam_Register);
}

void *beNDMWGameRamInfoRam_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWGameRamInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNDMWGameRamInfoRam_GetMetaObject,
        "beNDMWGameRamInfoRam",
        0x2c, /* instance size */
        beNDMWGameRamInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWGameRamInfoRam_GetMetaObject(void)
{
    beNDMWGameRamInfoRam_ResolveMetaObject();
}

