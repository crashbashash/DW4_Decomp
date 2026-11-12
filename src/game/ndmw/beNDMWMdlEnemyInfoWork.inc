void FUN_003c1910(int arg0) {
    FUN_003c1a00();
    igMetaObject_CreateInstance(*(int *)0x58B510, arg0);
}

void *beNDMWMdlEnemyInfoWork_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlEnemyInfoWork_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c1a00();
    }
    return g_beNDMWMdlEnemyInfoWork_metaObject[0];
}

int beNDMWMdlEnemyInfoWork_GetVTable(void) {
    Obj_3c19a0 o;
    int r;

    beNDMWMdlPEBaseInfoWork_Construct(&o);
    o.vt = &DAT_0053d3e0[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_0053d3e0[0];
    FUN_003bfde0((Obj_3bfde0 *)&o, (short)0);
    return r;
}

void FUN_003c1a00(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlEnemyInfoWork_Register);
}

void *beNDMWMdlEnemyInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlEnemyInfoWork_metaObject,
        beNDMWMdlPEBaseInfoWork_Register,
        beNDMWMdlPEBaseInfoWork_GetPublishedMetaObject,
        beNDMWMdlEnemyInfoWork_GetMetaObject,
        beNDMWMdlEnemyInfoWork_className,
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

