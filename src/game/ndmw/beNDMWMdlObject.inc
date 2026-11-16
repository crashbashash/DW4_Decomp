igMetaObject *g_beNDMWMdlObject_metaObject;

beNDMWMdlObject *beNDMWMdlObject_CreateInstance(int allocator) {
    beNDMWMdlObject_EnsureRegistered();
    return (beNDMWMdlObject *)igMetaObject_CreateInstance(g_beNDMWMdlObject_metaObject, allocator);
}

igMetaObject *beNDMWMdlObject_GetOrCreateMetaObject(void) {
    if (g_beNDMWMdlObject_metaObject == 0) {
        g_beNDMWMdlObject_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMdlObject_metaObject;
}

void *beNDMWMdlObject_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlObject_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWMdlObject_EnsureRegistered();
    }
    return g_beNDMWMdlObject_metaObject;
}

int beNDMWMdlObject_GetVTable(void) {
    beNDMWMdlObject obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    *(int **)&obj._vtable = &g_beNDMWMdlObject_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWMdlObject_vtable[0];
    beModelCtrl_Destroy((beModelCtrl *)&obj, 0);
    return vtable;
}

void beNDMWMdlObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlObject_Register);
}

void *beNDMWMdlObject_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlObject_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlObject_GetMetaObject,
        "beNDMWMdlObject",
        0x2c, /* instance size */
        beNDMWMdlObject_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlObject_GetMetaObject(void)
{
    beNDMWMdlObject_GetReadyMetaObject();
}

