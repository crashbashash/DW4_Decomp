igMetaObject *g_beNDMWMdlEnemyInfoWork_metaObject;

void beNDMWMdlEnemyInfoWork_Create(int allocator) {
    beNDMWMdlEnemyInfoWork_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWMdlEnemyInfoWork_metaObject, allocator);
}

void *beNDMWMdlEnemyInfoWork_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlEnemyInfoWork_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWMdlEnemyInfoWork_EnsureRegistered();
    }
    return g_beNDMWMdlEnemyInfoWork_metaObject;
}

int beNDMWMdlEnemyInfoWork_GetVTable(void) {
    Obj_3c19a0 o;
    int r;

    beNDMWMdlPEBaseInfoWork_Construct(&o);
    o.vt = &g_beNDMWMdlEnemyInfoWork_vtable[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beNDMWMdlEnemyInfoWork_vtable[0];
    FUN_003bfde0((Obj_3bfde0 *)&o, (short)0);
    return r;
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

