igMetaObject *g_beWaterPlain_metaObject;

beWaterPlain *beWaterPlain_CreateInstance(int allocator) {
    beWaterPlain_EnsureRegistered();
    return (beWaterPlain *)igMetaObject_CreateInstance(g_beWaterPlain_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beWaterPlain_GetOrCreateMetaObject(void) {
    if (g_beWaterPlain_metaObject == 0) {
        g_beWaterPlain_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beWaterPlain_metaObject;
}

void *beWaterPlain_GetMetaObject(void) {
    igMetaObject *g = g_beWaterPlain_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beWaterPlain_EnsureRegistered();
    }
    return g_beWaterPlain_metaObject;
}

int beWaterPlain_GetVTable(void) {
    beWaterPlain obj;
    int vtable;
    igObject **infoListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    infoListSlot = (igObject **)&obj._infoList;
    *infoListSlot = 0;
    obj._vtable = (int)&g_beWaterPlain_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    igObjectRef_Release(infoListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beWaterPlain_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beWaterPlain_Register);
}

CallbackArray *beWaterPlain_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWaterPlain_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beWaterPlain_GetMetaObjectFunction,
        "beWaterPlain",
        0x20, /* instance size */
        beWaterPlain_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beWaterPlain_GetMetaObjectFunction(void)
{
    beWaterPlain_GetMetaObject();
}

