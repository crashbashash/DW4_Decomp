igMetaObject *g_beNDMWMdlMapCursor_metaObject;

void beNDMWMdlMapCursor_CreateInstance(int allocator) {
    beNDMWMdlMapCursor_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWMdlMapCursor_metaObject, allocator);
}

igMetaObject *beNDMWMdlMapCursor_GetOrCreateMetaObject(void) {
    if (g_beNDMWMdlMapCursor_metaObject == 0) {
        g_beNDMWMdlMapCursor_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMdlMapCursor_metaObject;
}

void *beNDMWMdlMapCursor_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlMapCursor_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWMdlMapCursor_EnsureRegistered();
    }
    return g_beNDMWMdlMapCursor_metaObject;
}

int beNDMWMdlMapCursor_GetVTable(void) {
    beNDMWMdlMapCursor obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    *(int **)&obj._vtable = &g_beNDMWMdlMapCursor_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWMdlMapCursor_vtable[0];
    beModelCtrl_Destroy((beModelCtrl *)&obj, 0);
    return vtable;
}

void beNDMWMdlMapCursor_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlMapCursor_Register);
}

void *beNDMWMdlMapCursor_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlMapCursor_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlMapCursor_GetMetaObject,
        "beNDMWMdlMapCursor",
        0x2c, /* instance size */
        beNDMWMdlMapCursor_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlMapCursor_GetMetaObject(void)
{
    beNDMWMdlMapCursor_GetReadyMetaObject();
}

