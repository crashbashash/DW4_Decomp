igMetaObject *g_beNDMWMdlPBullet_metaObject;

beNDMWMdlPBullet *beNDMWMdlPBullet_CreateInstance(int allocator) {
    beNDMWMdlPBullet_EnsureRegistered();
    return (beNDMWMdlPBullet *)igMetaObject_CreateInstance(g_beNDMWMdlPBullet_metaObject, allocator);
}

igMetaObject *beNDMWMdlPBullet_GetOrCreateMetaObject(void) {
    if (g_beNDMWMdlPBullet_metaObject == 0) {
        g_beNDMWMdlPBullet_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMdlPBullet_metaObject;
}

void *beNDMWMdlPBullet_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlPBullet_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWMdlPBullet_EnsureRegistered();
    }
    return g_beNDMWMdlPBullet_metaObject;
}

int beNDMWMdlPBullet_GetVTable(void) {
    beNDMWMdlPBullet obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    *(int **)&obj._vtable = &g_beNDMWMdlPBullet_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWMdlPBullet_vtable[0];
    beModelCtrl_Destroy((beModelCtrl *)&obj, 0);
    return vtable;
}

void beNDMWMdlPBullet_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPBullet_Register);
}

void *beNDMWMdlPBullet_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlPBullet_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlPBullet_GetMetaObject,
        "beNDMWMdlPBullet",
        0x2c, /* instance size */
        beNDMWMdlPBullet_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlPBullet_GetMetaObject(void)
{
    beNDMWMdlPBullet_GetReadyMetaObject();
}

