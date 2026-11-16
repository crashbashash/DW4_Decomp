igMetaObject *g_beNDMWMdlEnemyInfoWork_metaObject;

beNDMWMdlEnemyInfoWork *beNDMWMdlEnemyInfoWork_Create(int allocator) {
    beNDMWMdlEnemyInfoWork_EnsureRegistered();
    return (beNDMWMdlEnemyInfoWork *)igMetaObject_CreateInstance(g_beNDMWMdlEnemyInfoWork_metaObject, allocator);
}

void *beNDMWMdlEnemyInfoWork_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlEnemyInfoWork_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWMdlEnemyInfoWork_EnsureRegistered();
    }
    return g_beNDMWMdlEnemyInfoWork_metaObject;
}

int beNDMWMdlEnemyInfoWork_GetVTable(void) {
    beNDMWMdlEnemyInfoWork obj;
    int vtable;

    beNDMWMdlPEBaseInfoWork_Construct((beNDMWMdlPEBaseInfoWork *)&obj);
    *(int **)&obj._vtable = &g_beNDMWMdlEnemyInfoWork_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWMdlEnemyInfoWork_vtable[0];
    beNDMWMdlPEBaseInfoWork_Destroy((beNDMWMdlPEBaseInfoWork *)&obj, 0);
    return vtable;
}

void beNDMWMdlEnemyInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlEnemyInfoWork_Register);
}

void *beNDMWMdlEnemyInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlEnemyInfoWork_metaObject,
        beNDMWMdlPEBaseInfoWork_Register,
        beNDMWMdlPEBaseInfoWork_GetPublishedMetaObject,
        beNDMWMdlEnemyInfoWork_GetMetaObject,
        "beNDMWMdlEnemyInfoWork",
        0x114, /* instance size */
        beNDMWMdlEnemyInfoWork_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlEnemyInfoWork_GetMetaObject(void)
{
    beNDMWMdlEnemyInfoWork_GetReadyMetaObject();
}

