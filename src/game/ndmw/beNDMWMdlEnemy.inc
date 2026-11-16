igMetaObject *g_beNDMWMdlEnemy_metaObject;

beNDMWMdlEnemy *beNDMWMdlEnemy_CreateInstance(int allocator) {
    beNDMWMdlEnemy_EnsureRegistered();
    return (beNDMWMdlEnemy *)igMetaObject_CreateInstance(g_beNDMWMdlEnemy_metaObject, allocator);
}

igMetaObject *beNDMWMdlEnemy_GetOrCreateMetaObject(void) {
    if (g_beNDMWMdlEnemy_metaObject == 0) {
        g_beNDMWMdlEnemy_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMdlEnemy_metaObject;
}

igMetaObject *beNDMWMdlEnemy_GetReadyMetaObject(void) {
    if (g_beNDMWMdlEnemy_metaObject == 0 || !isValid(g_beNDMWMdlEnemy_metaObject)) beNDMWMdlEnemy_EnsureRegistered();
    return g_beNDMWMdlEnemy_metaObject;
}

int beNDMWMdlEnemy_GetVTable(void) {
    beNDMWMdlEnemy obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    *(int **)&obj._vtable = &g_beNDMWMdlEnemy_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWMdlEnemy_vtable[0];
    beNDMWMdlPEBase_Destroy((beNDMWMdlPEBase *)&obj, 0);
    return vtable;
}

void beNDMWMdlEnemy_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlEnemy_Register);
}

void *beNDMWMdlEnemy_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlEnemy_metaObject,
        beNDMWMdlPEBase_Register,
        beNDMWMdlPEBase_GetPublishedMetaObject,
        beNDMWMdlEnemy_GetMetaObject,
        "beNDMWMdlEnemy",
        0x2c, /* instance size */
        beNDMWMdlEnemy_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlEnemy_GetMetaObject(void)
{
    beNDMWMdlEnemy_GetReadyMetaObject();
}

