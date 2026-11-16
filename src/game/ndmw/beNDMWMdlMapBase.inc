igMetaObject *g_beNDMWMdlMapBase_metaObject;

beNDMWMdlMapBase *beNDMWMdlMapBase_CreateInstance(int allocator) {
    beNDMWMdlMapBase_EnsureRegistered();
    return (beNDMWMdlMapBase *)igMetaObject_CreateInstance(g_beNDMWMdlMapBase_metaObject, allocator);
}

igMetaObject *beNDMWMdlMapBase_GetOrCreateMetaObject(void) {
    if (g_beNDMWMdlMapBase_metaObject == 0) {
        g_beNDMWMdlMapBase_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMdlMapBase_metaObject;
}

igMetaObject *beNDMWMdlMapBase_GetReadyMetaObject(void)
{
    igMetaObject *g = g_beNDMWMdlMapBase_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beNDMWMdlMapBase_EnsureRegistered();
    return g_beNDMWMdlMapBase_metaObject;
}

int beNDMWMdlMapBase_GetVTable(void) {
    beNDMWMdlMapBase obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    *(int **)&obj._vtable = &g_beNDMWMdlMapBase_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWMdlMapBase_vtable[0];
    beModelCtrl_Destroy((beModelCtrl *)&obj, 0);
    return vtable;
}

void beNDMWMdlMapBase_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlMapBase_Register);
}

void *beNDMWMdlMapBase_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlMapBase_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlMapBase_GetMetaObject,
        "beNDMWMdlMapBase",
        0x2c, /* instance size */
        beNDMWMdlMapBase_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlMapBase_GetMetaObject(void)
{
    beNDMWMdlMapBase_GetReadyMetaObject();
}

