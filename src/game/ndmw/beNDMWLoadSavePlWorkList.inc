igMetaObject *g_beNDMWLoadSavePlWorkList_metaObject;

igMetaObject *beNDMWLoadSavePlWorkList_GetOrCreateMetaObject(void) {
    if (g_beNDMWLoadSavePlWorkList_metaObject == 0) {
        g_beNDMWLoadSavePlWorkList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWLoadSavePlWorkList_metaObject;
}

void *beNDMWLoadSavePlWorkList_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadSavePlWorkList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWLoadSavePlWorkList_EnsureRegistered();
    }
    return g_beNDMWLoadSavePlWorkList_metaObject;
}

int beNDMWLoadSavePlWorkList_GetVTable(void) {
    beNDMWLoadSavePlWorkList obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWLoadSavePlWorkList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
}

void beNDMWLoadSavePlWorkList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadSavePlWorkList_Register);
}

static igMetaObjectCallback g_beNDMWLoadSavePlWorkList_callbackList[] = { beNDMWLoadSavePlWork_EnsureRegistered, 0 };

CallbackArray *beNDMWLoadSavePlWorkList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadSavePlWorkList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWLoadSavePlWorkList_GetMetaObject,
        "beNDMWLoadSavePlWorkList",
        0x14, /* instance size */
        beNDMWLoadSavePlWorkList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWLoadSavePlWorkList_callbackList /* callback list */
    );
}

void beNDMWLoadSavePlWorkList_GetMetaObject(void)
{
    beNDMWLoadSavePlWorkList_ResolveMetaObject();
}

