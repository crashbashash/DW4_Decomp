igMetaObject *g_beNDMWGameRamInfo_metaObject;

beNDMWGameRamInfo *beNDMWGameRamInfo_Create(int allocator) {
    beNDMWGameRamInfo_EnsureRegistered();
    return (beNDMWGameRamInfo *)igMetaObject_CreateInstance(g_beNDMWGameRamInfo_metaObject, allocator);
}

void *beNDMWGameRamInfo_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWGameRamInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWGameRamInfo_EnsureRegistered();
    }
    return g_beNDMWGameRamInfo_metaObject;
}

int beNDMWGameRamInfo_GetVTable(void) {
    beNDMWGameRamInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    *(int **)&obj._vtable = &g_beNDMWGameRamInfo_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWGameRamInfo_vtable[0];
    beBaseInfo_Destroy(&obj, 0);
    return vtable;
}

void beNDMWGameRamInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWGameRamInfo_Register);
}

void *beNDMWGameRamInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWGameRamInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWGameRamInfo_GetMetaObject,
        "beNDMWGameRamInfo",
        0x1c, /* instance size */
        beNDMWGameRamInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWGameRamInfo_GetMetaObject(void)
{
    beNDMWGameRamInfo_ResolveMetaObject();
}

