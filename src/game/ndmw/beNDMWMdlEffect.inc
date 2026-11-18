igMetaObject *g_beNDMWMdlEffect_metaObject;

beNDMWMdlEffect *beNDMWMdlEffect_CreateInstance(int allocator) {
    beNDMWMdlEffect_EnsureRegistered();
    return (beNDMWMdlEffect *)igMetaObject_CreateInstance(g_beNDMWMdlEffect_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWMdlEffect_GetOrCreateMetaObject(void) {
    if (g_beNDMWMdlEffect_metaObject == 0) {
        g_beNDMWMdlEffect_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWMdlEffect_metaObject;
}

void *beNDMWMdlEffect_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlEffect_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWMdlEffect_EnsureRegistered();
    }
    return g_beNDMWMdlEffect_metaObject;
}

int beNDMWMdlEffect_GetVTable(void) {
    beNDMWMdlEffect obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    *(int **)&obj._vtable = &g_beNDMWMdlEffect_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWMdlEffect_vtable[0];
    beModelCtrl_Destroy((beModelCtrl *)&obj, 0);
    return vtable;
}

void beNDMWMdlEffect_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlEffect_Register);
}

CallbackArray *beNDMWMdlEffect_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlEffect_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlEffect_GetMetaObject,
        "beNDMWMdlEffect",
        0x2c, /* instance size */
        beNDMWMdlEffect_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlEffect_GetMetaObject(void)
{
    beNDMWMdlEffect_GetReadyMetaObject();
}

